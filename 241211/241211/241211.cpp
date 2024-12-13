#include <iostream>
#include <functional>

class CPlayer           //Class는 사용자 정의 변수타입
{
public:
	CPlayer() : mAttack(30), mDefense(20), mName{} //Initializer 생성자 별로 입력가능, 선언과 동시에 초기화와 동일
	{
		mArray = new int[10];
		std::cout << "생성자 호출" << std::endl;
	}
	CPlayer(int num) : mAttack(num), mDefense(num), mName{} 
	{
		mArray = new int[10];
		std::cout << "생성자 호출" << std::endl;
	}
	CPlayer(const char* Name):mAttack(10), mDefense(10)
	{
		mArray = new int[10];
		strcpy_s(mName, Name);
		std::cout << "const char 생성자 호출" << std::endl;
	}
	CPlayer(const CPlayer& ref)
	{
		*this = ref;
		mArray = new int[10];
		mArray = ref.mArray;
		//memcpy(mArray, ref.mArray, sizeof(int) * 10);
		//얕은복사(Shallow copy):데이터를 있는 그대로 복사
		//데이터 값을 그대로 복사하기에 참조하던 주소까지 복사
		//원본이 delete 될 경우에 이미 해제 된 메모리 값을 그대로 가지고 있음
		
		//깊은복사(Deep copy):데이터를 복사하되 새로운 메모리 공간을 할당하고 복사
		//동적할당 된 데이터가 있을 경우 주로 사용
	}
	//복사생성자: 객체를복사해서 새로운 객체를 만들어 낼 때 사용
	//클래스에 없을 경우 컴파일러가 자동으로 복사생성자 1개 생성
	//pplayer1 객체를 인자로 새 객체(pplayer2)의 데이터를 복제하여 생성 
	~CPlayer()
	{
		delete[] mArray;
		std::cout << "소멸자 호출" << std::endl;
	}
public:                 //다른 키워드를 만나기 전 까지 public으로 적용
	char mName[32];     //멤버변수(m)
	int mAttack = 100;  //선언과 동시에 초기화 지원
	int* mArray = nullptr;
	//static int mHP = 500; //static 사용시 즉시 초기화 불가
	static int mHP;			//static 멤버변수는 클래스 외부에 변수 선언이 있어야 함

private:
	int mDefense;
public:
	void SetDefense(int Def)
	{
		mDefense = Def;
	}
	int GetDefense() const
	{
		return mDefense;
	}
	void Output()
	{
		std::cout << "this: "<< this << std::endl;
		//멤버변수 사용 시 this-> 생략이 된 채로 적용
		//this: 자기 자신의 메모리 주소
		//Object.Method() 호출 시 Object의 메모리 주소가 적용됨
	}
	static void OutputStatic()
	{ 
		std::cout << mHP << std::endl;
	}
	//static 멤버함수의 경우 this 사용불가
	//일반 멤버변수를 서용할 때, 어느객체의 멤버변수인지 구분을 위한 this가 존재(생략)
	//this를 사용할 수 없으므로 일반 멤버변수 사용불가
	//static 멤버변수에만 접근가능
};

int CPlayer::mHP = 500; 
//static 멤버변수는 클래스 외부에 선언
//static 멤버변수는 클래스가 생성하는 메모리 크기에 영향 없음
//모든 객체들이 공유하는 변수


void OutputGlobal()
{
	std::cout << "OutputGlobal" << std::endl;
}

int main()
{
	CPlayer player;
	player.mAttack = 100;
	//player.mDefense = 200;        //pirvate 접근 불가
	player.SetDefense(20);          //public method를 통한 값 변경 

	CPlayer* pplayer = new CPlayer; //class의 동적할당
	CPlayer* pplayer1 = new CPlayer("AAA"); //class 오버로딩
	CPlayer* pplayer2 = new CPlayer(*pplayer1); //class 복사생성자 호출

	delete pplayer;
	pplayer = new CPlayer("홍길동");

	CPlayer* cpplayer = (CPlayer*)malloc(sizeof(CPlayer));
	free(cpplayer);

	std::cout << "Global function addr:"<< OutputGlobal << std::endl;
	//함수명을 호출한다는 것은 함수의 memory address를 반환한다

	pplayer->Output();
	//호출 시 this는 pplayer object의 memory address
	pplayer1->Output();
	//호출 시 this는 pplayer1 object의 memory address

	pplayer->mHP = 1234;
	pplayer1->mHP = 5678;
	CPlayer::mHP = 5000;

	std::cout << pplayer->mHP << std::endl;
	std::cout << pplayer1->mHP << std::endl;

	pplayer->OutputStatic();
	pplayer1->OutputStatic();
	CPlayer::OutputStatic();
	//static 멤버함수 호출
	void(*Func)() = CPlayer::OutputStatic;
	std::cout << CPlayer::OutputStatic << std::endl;
	//static 멤버함수 포인터
	
	std::cout << &CPlayer::Output << std::endl;
	std::cout << &CPlayer::SetDefense << std::endl;
	//바인딩 되지 않은 함수의 주소는 반환 불가
	
	void (CPlayer:: * funcPtr)() = &CPlayer::Output;
	//멤버함수 포인터의 주소를 출력하려면, 이를 객체에 바인딩해야 함 
	//멤버함수 포인터 생성
	(pplayer->*funcPtr)();
	(pplayer2->*funcPtr)();

	//클래스 내 함수(맴버함수)의 주소 반환방식
	//클래스 내 함수는 객체가 생성될 때 계속 생성되는 것이 아님
	//객체가 생성되는 것과는 별개로 메소드는 단 하나로 유지
	//실제 객체는 멤버변수(field)의 메모리만 포함

	const CPlayer playerC;
	//const 객체를 생성할 경우 멤버변수의 값을 변경불가
	//일반 멤버함수를 호출할 수 없음
	//뒤에 const가 붙은 함수만 호출가능
	//예)int funciton() const {}
	//멤버함수 뒤 const가 붙으면 이 함수에서는 class의 멤버변수의 값 변경 불가
	//const 객체가 호출할 수 있는 함수가 됨
	
	//playerC.mAttack = 500;	//변경불가
	//playerC.Output();			//변경불가

	playerC.GetDefense();

	//CPlayer* playerC2 = playerC;
	//const때문에 대입불가
	CPlayer* playerC2 = const_cast<CPlayer*>(&playerC);
	//강제 const해제
	playerC2->mAttack = 500;

	CPlayer::OutputStatic();
	void(*Func)() = CPlayer::OutputStatic;
	//전역함수 포인터에 저장 가능 

	void(CPlayer::*Func1)() = &CPlayer::Output;
	////void(CPlayer::*Func2)() = &CPlayer::SetDefense;
	//멤버함수 포인터

	std::function<void()>	func;
	func = std::bind(&CPlayer::Output, player);

	func();

	func = OutputGlobal;

	func();

	std::function<void(int)>	func1;

	func1 = std::bind(&CPlayer::SetDefense,
		player, std::placeholders::_1);

	func1(10);

	std::function<void(int, int)>	func2;

	//func2 = std::bind(&CPlayer::SetTest,player, std::placeholders::_1, std::placeholders::_2);

	return 0;
}

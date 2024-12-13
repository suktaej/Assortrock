#include<iostream>
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
//클래스를 통해 생성할 수 있는 객체의 개수를 제한하고 싶을 때
//클래스를 통해 생성한 객체를 어디서든 사용할 수 있도록 할 때
//주로 관리자 클래스에서 사용
class CSingleton
{
private:
	CSingleton()
	{
	}
	//생성자와 소멸자가 private일 경우
	//클래스 외부에서 생성불가

	~CSingleton()
	{
	}

	static CSingleton* mInst;
	//static변수(class 외부 선언 필요)
public:
	static CSingleton* GetInst()
	//class내부의 함수이므로 생성 가능
	{
		if (nullptr == mInst)
			mInst = new CSingleton;
		return mInst;
	}
	static void DestoryInst()
	{
		//SAFE_DELETE(mInst);
		if (nullptr != mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};

CSingleton* CSingleton::mInst = nullptr;

int main()
{
	//CSingleton single;
	//생성자 호출 불가(private에 생성자가 선언)
	CSingleton* single;
	//포인터는 객체를 생성하는 것이 아닌 객체의 메모리 주소를 저장하므로 선언 가능
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;

	CSingleton::DestoryInst();

	return 0;
}
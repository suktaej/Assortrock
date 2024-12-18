#include <iostream>

class C1
{
private:
	int num;
public:
	C1() {}
	C1(int num) { this->num = num; }
	C1(const C1& ref) { this->num = ref.num; }
	C1(C1&& ref) 
	{
		std::cout << "이동생성자" << std::endl;
	}
	//이동생성자: 객체가 살아있는 상태에서 사용하지 않는다고 보장할 수 있는 상황일 때 사용

	int& RefFunc(int num) { return num; }
};

int Func1(int num)
{
	std::cout << num << std::endl;
	return num;
}

int Func2(const int& num)	
//임시객체를 생성하지 않음
{
	std::cout << num << std::endl;
	return num;
}

int main(void)
{
	C1 temp;
	//temp = C1(30);
	//1. 임시객체 생성
	//2. 대입
	//3. 대입이 끝나는 시점에 임시객체 제거
	//임시객체가 존재하지 않을 경우, 대입이 불가능(코드적으로)
	C1* ptemp = &C1(40);
	//임시객체의 주소를 반환해 주는 경우, 주소에 L-value값이 없으므로 댕글링 포인터 값이 들어감
	//C1(30) = temp;
	
	return 0;
}
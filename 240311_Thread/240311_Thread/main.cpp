#include<iostream>
#include<Windows.h>

//쓰레드를 사용하기 위한 참조
#include<process.h>
//쓰레드 객체를 사용하기 위한 참조
#include<thread>
//여러 쓰레드에서 자동으로 동기화 처리
#include<atomic>

//쓰레드 스위치 간 오류 확인
int gNum = 100;
std::atomic<int> gNum2(100);

//lock, unlock을 위한 변수
//lock-unlock의 비용은 상당히 큰 편
//사용 위치를 고려할 필요가 있음
CRITICAL_SECTION gCrt;

void ThreadFunc1()
{
	std::cout<<"Func1"<<std::endl; 
	for (int i = 0;i < 100000;i++)
	{
		gNum++;
		gNum2.fetch_add(1);
	}
}

void ThreadFunc2()
{ 
	std::cout<<"Func2"<<std::endl; 
	for (int i = 0;i < 100000;i++)
	{
		gNum--;
		gNum2.fetch_add(-1);
	}
}

void ThreadFuncParam1(int a,int b)
{ std::cout<<"FuncParam1"<<std::endl; }

unsigned int __stdcall OldThreadFunc1(void* Arg)
{
	std::cout<<"Func1"<<std::endl; 
	for (int i = 0;i < 100000;i++)
	{
		//Lock
		EnterCriticalSection(&gCrt);

		gNum++;

		//UnLock
		LeaveCriticalSection(&gCrt);
	}
	return 0;
}

unsigned int __stdcall OldThreadFunc2(void* Arg)
{
	std::cout<<"Func2"<<std::endl; 
	for (int i = 0;i < 100000;i++)
	{
		//Lock
		EnterCriticalSection(&gCrt);

		gNum--;

		//UnLock
		LeaveCriticalSection(&gCrt);
	}
	return 0;
}

int main(void)
{
	//크리티컬 섹션 객체 생성
	InitializeCriticalSection(&gCrt);

	//1.process를 사용해서 사용하는 방식(기존방식)

	//인자1. nullptr
	//인자2. 쓰레드가 동작시켜줄 함수의 스텍 크기
	//0 입력 시 자동으로 크기를 조절
	//인자3. 함수의 주소
	//사용할 함수의 반환 타입은 unsigned int로 고정이며 
	//인자4. nullptr
	//인자5, 인자6. 0
	HANDLE Thread1 = (HANDLE)_beginthreadex(nullptr,0, OldThreadFunc1, nullptr, 0,0);
	HANDLE Thread2 = (HANDLE)_beginthreadex(nullptr,0, OldThreadFunc2, nullptr, 0,0);

	//HANDLE로 생성하였으므로 Singal, NonSignal 상태로 나눌 수 있음
	//쓰레드가 종료되면 해당 쓰레드의 핸들은 Signal상태로 전환
	//WaitForSingleObject 함수는 핸들이 Singal 상태인지를 확인하는 이벤트 동기화 함수
	//두 함수를 함께 적용 시 모두 끝까지 대기
	WaitForSingleObject(Thread1, INFINITE);
	WaitForSingleObject(Thread2, INFINITE);

	//사용 후 쓰레드를 종료
	CloseHandle(Thread1);
	CloseHandle(Thread2);
	//생성한 크리티컬 섹션 제거
	DeleteCriticalSection(&gCrt);

	std::cout << "MainThread_End" << std::endl;
	std::cout << gNum << std::endl;
	//============================================

	/*
	//2.thread 객체를 사용하는 방식(C++11 이상)
	//std::thread();
	
	//인자가 없는 함수일 경우
	std::thread thread1(ThreadFunc1);
	std::thread thread2(ThreadFunc2);
	//인자가 있는 함수일 경우
	std::thread thread3(ThreadFuncParam1,10,100);

	//실행
	//join함수는 메인스레드가 이 스레드가 끝날 때까지 대기

	//joinable 함수는 join이 가능한 상태인지 판단
	if(thread1.joinable())
		thread1.join();

	thread2.join();
	thread3.join();

	//deatch 함수는 메인스레드와 독립적으로 동작
	//백그라운드에서 스레드가 동작
	//메인스레드가 먼저 종료될 수 있으므로 위험이 존재
	//thread1.detach();
	//thread2.detach();
	//thread3.detach();

	//쓰레드를 일정시간 대기하는 함수
	//일반적으로 detach와 함께 사용
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//detach에서 쓰레드가 종료되었는지 체크하는 방식은 별도로 구현
	//또는 C++20 이상에서 지원하는 기능을 사용

	std::cout << "MainThread_End" << std::endl;
	std::cout << gNum << std::endl;
	std::cout << gNum2.load() << std::endl;
	//CPU에서 출력가능한 코어 수를 확인해서 사용하는 경우
	//hardware_concurrency() : 실행이 가능한 코어수를 반환받는 함수
	std::cout << std::thread::hardware_concurrency() << std::endl;
	*/
	return 0;
}
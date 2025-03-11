#include<iostream>
#include<Windows.h>

//�����带 ����ϱ� ���� ����
#include<process.h>
//������ ��ü�� ����ϱ� ���� ����
#include<thread>
//���� �����忡�� �ڵ����� ����ȭ ó��
#include<atomic>

//������ ����ġ �� ���� Ȯ��
int gNum = 100;
std::atomic<int> gNum2(100);

//lock, unlock�� ���� ����
//lock-unlock�� ����� ����� ū ��
//��� ��ġ�� ����� �ʿ䰡 ����
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
	//ũ��Ƽ�� ���� ��ü ����
	InitializeCriticalSection(&gCrt);

	//1.process�� ����ؼ� ����ϴ� ���(�������)

	//����1. nullptr
	//����2. �����尡 ���۽����� �Լ��� ���� ũ��
	//0 �Է� �� �ڵ����� ũ�⸦ ����
	//����3. �Լ��� �ּ�
	//����� �Լ��� ��ȯ Ÿ���� unsigned int�� �����̸� 
	//����4. nullptr
	//����5, ����6. 0
	HANDLE Thread1 = (HANDLE)_beginthreadex(nullptr,0, OldThreadFunc1, nullptr, 0,0);
	HANDLE Thread2 = (HANDLE)_beginthreadex(nullptr,0, OldThreadFunc2, nullptr, 0,0);

	//HANDLE�� �����Ͽ����Ƿ� Singal, NonSignal ���·� ���� �� ����
	//�����尡 ����Ǹ� �ش� �������� �ڵ��� Signal���·� ��ȯ
	//WaitForSingleObject �Լ��� �ڵ��� Singal ���������� Ȯ���ϴ� �̺�Ʈ ����ȭ �Լ�
	//�� �Լ��� �Բ� ���� �� ��� ������ ���
	WaitForSingleObject(Thread1, INFINITE);
	WaitForSingleObject(Thread2, INFINITE);

	//��� �� �����带 ����
	CloseHandle(Thread1);
	CloseHandle(Thread2);
	//������ ũ��Ƽ�� ���� ����
	DeleteCriticalSection(&gCrt);

	std::cout << "MainThread_End" << std::endl;
	std::cout << gNum << std::endl;
	//============================================

	/*
	//2.thread ��ü�� ����ϴ� ���(C++11 �̻�)
	//std::thread();
	
	//���ڰ� ���� �Լ��� ���
	std::thread thread1(ThreadFunc1);
	std::thread thread2(ThreadFunc2);
	//���ڰ� �ִ� �Լ��� ���
	std::thread thread3(ThreadFuncParam1,10,100);

	//����
	//join�Լ��� ���ν����尡 �� �����尡 ���� ������ ���

	//joinable �Լ��� join�� ������ �������� �Ǵ�
	if(thread1.joinable())
		thread1.join();

	thread2.join();
	thread3.join();

	//deatch �Լ��� ���ν������ ���������� ����
	//��׶��忡�� �����尡 ����
	//���ν����尡 ���� ����� �� �����Ƿ� ������ ����
	//thread1.detach();
	//thread2.detach();
	//thread3.detach();

	//�����带 �����ð� ����ϴ� �Լ�
	//�Ϲ������� detach�� �Բ� ���
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//detach���� �����尡 ����Ǿ����� üũ�ϴ� ����� ������ ����
	//�Ǵ� C++20 �̻󿡼� �����ϴ� ����� ���

	std::cout << "MainThread_End" << std::endl;
	std::cout << gNum << std::endl;
	std::cout << gNum2.load() << std::endl;
	//CPU���� ��°����� �ھ� ���� Ȯ���ؼ� ����ϴ� ���
	//hardware_concurrency() : ������ ������ �ھ���� ��ȯ�޴� �Լ�
	std::cout << std::thread::hardware_concurrency() << std::endl;
	*/
	return 0;
}
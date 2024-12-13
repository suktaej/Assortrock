#include<iostream>
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
//Ŭ������ ���� ������ �� �ִ� ��ü�� ������ �����ϰ� ���� ��
//Ŭ������ ���� ������ ��ü�� ��𼭵� ����� �� �ֵ��� �� ��
//�ַ� ������ Ŭ�������� ���
class CSingleton
{
private:
	CSingleton()
	{
	}
	//�����ڿ� �Ҹ��ڰ� private�� ���
	//Ŭ���� �ܺο��� �����Ұ�

	~CSingleton()
	{
	}

	static CSingleton* mInst;
	//static����(class �ܺ� ���� �ʿ�)
public:
	static CSingleton* GetInst()
	//class������ �Լ��̹Ƿ� ���� ����
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
	//������ ȣ�� �Ұ�(private�� �����ڰ� ����)
	CSingleton* single;
	//�����ʹ� ��ü�� �����ϴ� ���� �ƴ� ��ü�� �޸� �ּҸ� �����ϹǷ� ���� ����
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;
	std::cout << CSingleton::GetInst() << std::endl;

	CSingleton::DestoryInst();

	return 0;
}
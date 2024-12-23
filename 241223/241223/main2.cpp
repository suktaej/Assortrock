#include <iostream>
#include <cassert>

//operator: ������ ������
//�⺻ ����� �������Ͽ� �ش� ����ü �Ǵ� Ŭ������ ������ ���� ������� ����

struct FPoint
{
	static FPoint Pool[20];

	int x;
	int y;

	FPoint operator + (const FPoint & pt) const
	{
		FPoint result;
		//�׳� x�� ��� �� +�Լ��� ȣ���� ��ü�� x ����
		result.x = x + pt.x;
		result.y = y + pt.y;
		return result;
	}

	FPoint operator + (int Number) const
	{
		FPoint result;
		result.x = x + Number;
		result.y = y + Number;
		return result;
	}

	int operator * () const { return x; }
	//���ڸ� �־����� ���� ��� ������
	//���ڰ� �� ��� ������

	int& operator [] (int Index)
	{
		if (Index < 0 || Index>1)
			assert(false);

		if (nullptr == 0)
			return x;
			
		return y; 

		//return -1;
	}
		//���� ������
	void* operator new (size_t Size)
	{
		return &Pool[0];
	}

	const FPoint& operator ++ ()
	{
		++x;
		++y;
		return *this;
	}
	//��ġ����

	const FPoint& operator ++ (int)
	{
		++x;
		++y;
		return *this;
	}
	//��ġ����

	void operator +=(const FPoint& pt)
	{
		x += pt.x;
		y += pt.y;
	}
};
//��ȯ�ϴ� ���� �ӽð�ü�̹Ƿ� �������� ��ȯ�� ���� ����
//���۷��� ��ȯ ����

FPoint FPoint::Pool[20];

//���ڿ� ���� ����
struct FString
{
	char* Text = nullptr;
	int Count = 0;

public:
	void operator = (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}
		strcpy_s(Text, Count+1, str.Text);
	}

	void operator = (const char* str)
	{
		if (!Text)
		{
			Count = (int)strlen(str);
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}
		strcpy_s(Text, Count+1, str);
	}

	FString operator + (const FString& str) const
	{
		FString result;
	
		if (!Text)
			result = str;
		else
		{
			result.Count = Count + str.Count + 1;
			result.Text = new char[result.Count + 1];
			memset(result.Text, 0, result.Count + 1);
			strcpy_s(result.Text, Count + 1, Text);
			strcat_s(result.Text,result.Count+1,str.Text);
		}
		return result;
	}
};

int main(void)
{
	FPoint p1, p2, p3;
	p1.x = 10;
	p1.y = 20;
	p2.x = 30;
	p2.y = 40;

	p3 = p1 + p2;
	//�̷��� �ǿ����ڿ� ��ġ�ϴ� "+" �����ڰ� �����ϴ�.
	//p1�� + �Լ� ȣ��

	int Number = 10 + 20;
	//�������� ���ϴ� ���� + ������(�Լ� + ȣ��)
	p3 = p1 + 30;
	std::cout << *p1 << std::endl;

	p1[0] = 100;
	std::cout << p1[0] << std::endl;
	std::cout << p1[1] << std::endl;

	FPoint* pt1 = new FPoint;
	//�޸� Ǯ �������
	//����ü ���ο��� new�� ������ ������
	//�����Ҵ��� �ƴ϶� ���� ������ �迭�� ��ȯ�ϴ� ������� ����

	++p1;
	p1++;

	FString str;
	str = "String";

	FString str1;
	str1 = "Test";
	
	FString strResult;
	strResult = str + str1;
	std::cout << strResult.Text << std::endl;

	return 0;
}
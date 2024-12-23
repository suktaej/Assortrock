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
public:
	FString():Text(nullptr),Count(0) {}
	FString(const char* _Text)
	{
		Count = (int)strlen(_Text);
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);
		strcpy_s(Text, Count + 1, _Text);
	}
	FString(const FString& str)
	{
		Count = str.Count;
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);
		strcpy_s(Text, Count + 1, str.Text);
	}
	FString(FString&& str)
	{
		Count = str.Count;
		Text = str.Text;
		//���� ����(rvalue type�� ���� ������ �ϰ� ����)
		str.Text = nullptr;
		//�޸� �̵�
	}
	//�̵��������� �ʿ伺
	//�ӽð�ü�� �޸� �ּҸ� ���Թ��� ��ü�� �޸𸮷� ����
	//�ӵ����鿡�� ����
	
	~FString() 
	{
		if (nullptr != Text)
			delete[] Text;
	}
private:
	char* Text;
	int Count;

public:
	void operator = (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}
		else
		{
			if (Count < str.Count)
			{
				delete[] Text;
				Count = str.Count;
				Text = new char[Count + 1];
				memset(Text, 0, Count + 1);
			}
		}
		strcpy_s(Text, str.Count+1, str.Text);
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
	//�ڵ� �߰� �ʿ�(str�� ���̰� �� ���)

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
	//std::cout << strResult.Text << std::endl;
	FString str2 = "New String";
	//�����ڷ� �ʱ�ȭ
	FString str3 = str2;
	//��������ڷ� �ʱ�ȭ

	FString("temp obj");
	//�ӽð�ü�� ������ ���ÿ� ����

	//FString str4 = FString("temp obj");
	//�ӽð�ü ����ȭ�� �ڵ��Ҵ�
	//�ӽð�ü�� ���ŵ��� �ʰ� ������ �νĵ�
	//�ӽð�ü�� ����. �̵������� ������� �޸� �̵��� �Ͼ
	//str4�� ���ŵ� ��, �ӽð�ü�� ���ŵ� �Ͱ� ����

	FString str4 = std::move(FString("temp obj"));
	//���� �̵�������
	
	return 0;
}
#include<iostream>

class CString
{
private:
	char* str = nullptr;
	int str_count = 0;
public:
	void operator=(const char* str)
	{
		if (this->str)
		{
			delete[] this->str;
			this->str = nullptr;
		}
		
		str_count = strlen(str);
		this->str = new char[str_count + 1];
		memset(this->str, 0, str_count + 1);
	
		strcpy_s(this->str, str_count + 1, str);
	}

	void operator=(const CString& Cstr)
	{
		if (this->str)
		{
			delete this->str;
			this->str = nullptr;
		}
		
		str_count = Cstr.str_count;
		this->str = new char[str_count + 1];
		memset(this->str, 0, str_count + 1);

		strcpy_s(this->str, Cstr.str_count + 1,Cstr.str);
	}

	CString operator+(const CString& Cstr)
	{
		CString result;
		if (!this->str)
			result = Cstr;
		else
		{
			result.str_count = str_count + Cstr.str_count + 1;
			result.str = new char[result.str_count + 1];
			memset(result.str, 0, result.str_count + 1);
			strcpy_s(result.str, this->str_count + 1, this->str);
			strcat_s(result.str, result.str_count + 1, Cstr.str);
		}
		return result;
	}

	char* operator*() const
	{
		return str;
	}
};

int main(void)
{
	return 0;
}
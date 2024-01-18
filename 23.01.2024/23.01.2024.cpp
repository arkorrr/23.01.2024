#include <iostream>

using namespace std;

class MyString
{
	char* str;
	static int count;
	int field = 80;
public:
	MyString()
	{
		str = new char[field];
		count++;
	}
	MyString(const char* text)
	{
		str = new char[strlen(text) + 1];
		strcpy_s(str, strlen(text) + 1, text);
		count++;
	}
	MyString(const MyString& other)
	{
		str = new char[strlen(other.str) + 1];
		strcpy_s(str, strlen(other.str) + 1, other.str);
		count++;
	}
	~MyString()
	{
		delete[] str;
		count--;
	}

	MyString& operator++()
	{
		int len = strlen(str);
		char* newStr = new char[len + 2];
		strcpy_s(newStr, len + 2, str);
		newStr[len] = 'x';
		newStr[len + 1] = '\0';
		delete[] str;
		str = newStr;
		return *this;
	}

	MyString operator++(int)
	{
		MyString temp = *this;
		++(*this);
		return temp;
	}
	MyString operator+(int n) const
	{
		MyString result(*this);
		int overload = strlen(result.str);
		char* temp = new char[overload + n + 1];
		for (int i = 0; i < n; ++i)
		{
			temp[i] = 'x';
		}
		int j = 0;
		for (int i = n; i < overload + n; i++)
		{
			temp[i] = result.str[j];
			j++;
		}
		temp[overload + n] = '\0';
		delete[] result.str;
		result.str = temp;
		return result;
	}
	friend MyString operator+(int n, const MyString& Str)
	{
		return Str + n;
	}
	MyString& operator--()
	{
		int len = strlen(str);
		if (len > 0)
		{
			char* newStr = new char[len];
			strncpy_s(newStr, len, str, len - 1);
			newStr[len - 1] = '\0';
			delete[] str;
			str = newStr;
		}
		return *this;
	}
	MyString operator--(int)
	{
		MyString temp = *this;
		--(*this);
		return temp;
	}
	MyString operator-(int n) const
	{
		MyString result(*this);
		int overload = strlen(result.str);
		if (n < overload)
		{
			char* temp = new char[overload - n + 1];
			strncpy_s(temp, overload - n + 1, result.str, overload - n);
			temp[overload - n] = '\0';
			delete[] result.str;
			result.str = temp;
		}
		else
		{
			delete[] result.str;
			result.str = new char[1];
			result.str[0] = '\0';
		}
		return result;
	}
	friend MyString operator-(int n, const MyString& Str)
	{
		return Str - n;
	}
	MyString& operator=(const MyString& other)
	{
		if (this != &other)
		{
			delete[] str;
			str = new char[strlen(other.str) + 1];
			strcpy_s(str, strlen(other.str) + 1, other.str);
		}
		return *this;
	}
	void input()
	{
		char buffer[256];
		cin.getline(buffer, 256);
		str = new char[strlen(buffer) + 1];
		strcpy_s(str, strlen(buffer) + 1, buffer);
	}

	void output() const
	{
		cout << "String: " << str << endl;
	}

	static int getCount()
	{
		return count;
	}
	friend istream& operator>>(istream& is, MyString& P);
	friend ostream& operator<<(ostream& os, const MyString& P);
};

int MyString::count = 0;

istream& operator>>(istream& is, MyString& P)
{
	cout << "Enter your string: ";
	is >> P.str;
	return is;
}

ostream& operator<<(ostream& os, const MyString& P)
{
	os << "String: " << P.str << endl;
	return os;
}

int main()
{
	MyString str;
	cin >> str;
	cout << str;
	
}



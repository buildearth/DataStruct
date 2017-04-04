#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

class String
{
public:
	String(const char *str = NULL)
	{
		if (str == NULL)
		{
			_data = new char[1];
			_data = '\0';
			return;
		}

		size_t len = strlen(str) + 1;
		_data = new char[len];
		if (_data == NULL)
		{
			return;
		}
		strcpy(_data, str);
	}
	String(const String &other) //Éî¿½±´
	{
		size_t len = strlen(other._data) + 1;
		_data = new char[len];
		if (_data != NULL)
		{
			strcpy(_data, other._data);
		}

	}
	~String()
	{
		delete []_data;
	}

	String &operator=(const String &other)
	{
		if (this == &other)
		{
			return *this;
		}
		
		size_t len = strlen(other._data) + 1;
		char *tmp = new char[len];
		if (tmp != NULL)
		{
			delete[] _data;
			strcpy(tmp, other._data);
			_data = tmp;
		}

		return *this;
	}

	void Print()
	{
		cout << _data << endl;
	}
protected:
	char *_data;
};

void TestString()
{
	String str("hello");
	str.Print();
	String str1(str);
	str1.Print();
	String src("world");
	src = str = str1;
	src.Print();
}
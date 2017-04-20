#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<map>
using namespace std;
//Ѱ��һ���ַ��е�һ������һ�ε��ַ���

char Find(const char * str)
{
	/*
	��1��map
	ʱ�临�Ӷȣ�O(N*lgN)
	*/
	/*map<char, int> st; 
	for (size_t i = 0; i < strlen(str); ++i)
	{
		st[str[i]]++;
	}
	for (size_t i = 0; i < strlen(str); ++i)
	{
		if (st[str[i]] == 1)
			return str[i];
	}

	return '\0';*/
	/*
	----------------------
	ֱ�Ӷ�ֵ�����ַ���256������һ�����飬ÿ���ַ���Ӧλ�ô�����ִ�����
	*/
	size_t chCount[256] = {0};
	for (int i = 0; i < (strlen(str + 1)); ++i)
	{
		chCount[str[i]]++;
	}

	for (int i = 0; i < (strlen(str + 1)); ++i)
	{
		if (chCount[str[i]] == 1)
		{
			return str[i];
		}
	}

	//����û�г���һ�ε��ַ���
	return '\0';
}

void TestFind()
{
	char *str = "acadadcfbb";
	char ch = Find(str);
	cout << ch << endl;
}
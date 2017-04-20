#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<map>
using namespace std;
//寻找一串字符中第一个出现一次的字符；

char Find(const char * str)
{
	/*
	法1：map
	时间复杂度：O(N*lgN)
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
	直接定值法：字符共256个，建一个数组，每个字符对应位置存其出现次数；
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

	//到这没有出现一次的字符；
	return '\0';
}

void TestFind()
{
	char *str = "acadadcfbb";
	char ch = Find(str);
	cout << ch << endl;
}
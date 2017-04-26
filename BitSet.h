#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
using namespace std;

//λͼ
class BitSet
{
public:
	BitSet(const size_t range)
	{
		_a.resize((range>>5) + 1);
	}

	void Set(size_t num)  //��num��¼;
	{
		size_t index = num >> 5;
		size_t pos = num % 32;

		_a[index] |= (1 << pos);
	}

	void Reset(size_t num)  //ɾ��num��¼
	{
		size_t index = num >> 5;
		size_t pos = num % 32;

		_a[index] &= ~(1 << pos);
	}

	bool Test(size_t num) //�ж�num�Ƿ����;
	{
		size_t index = num >> 5;
		size_t pos = num % 32;

		//�ж������λ��0�����ڣ�1���ڣ�

		return _a[index] & (1 << pos);
	}


protected:
	vector<int> _a;
};

void TestBitSet()
{
	BitSet bs(-1);
	bs.Set(1);
	bs.Set(3);
	bs.Set(4);
	bs.Set(8);
	cout << bs.Test(1) << endl;
	cout << bs.Test(10) << endl;
}
#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

#include "BitSet.h"

//布隆过滤器（位图的变形）;
/*一个值映射多个位，判断存在是不准确的，判断不存在是准确的；
它可以通过一个Hash函数将一个元素映射成一个位阵列（Bit array）中的一个点。
这样一来，我们只要看看这个点是不是1就可以知道集合中有没有它了。这就是布隆过滤器的基本思想。
使用hash函数，不可避免的就是哈希冲突，有可能是多个key值映射在同一个位，这就不好去判断，所以需要一个值映射多个位，来减少布隆的失误率;
*/

size_t BKDRHash(const char *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * 131 + ch;
	}
	return hash;
}

struct __HashFunc1
{
	size_t operator()(const string &s)
	{
		return BKDRHash(s.c_str());
	}
};

size_t SDBMHash(const char *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch;
		//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
	}
	return hash;
}

struct __HashFunc2
{
	size_t operator()(const string &s)
	{
		return SDBMHash(s.c_str());
	}
};

size_t RSHash(const char *str)
{
	register size_t hash = 0;
	size_t magic = 63689;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash;
}

struct __HashFunc3
{
	size_t operator()(const string &s)
	{
		return RSHash(s.c_str());
	}
};

size_t APHash(const char *str)
{
	register size_t hash = 0;
	size_t ch;
	for (long i = 0; ch = (size_t)*str++; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}

struct __HashFunc4
{
	size_t operator()(const string &s)
	{
		return APHash(s.c_str());
	}
};

size_t JSHash(const char *str)
{
	if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
		return 0;
	register size_t hash = 1315423911;
	while (size_t ch = (size_t)*str++)
	{
		hash ^= ((hash << 5) + ch + (hash >> 2));
	}
	return hash;
}

struct __HashFunc5
{
	size_t operator()(const string &s)
	{
		return JSHash(s.c_str());
	}
};

template<class K,class HashFunc1 = __HashFunc1, class HashFunc2 = __HashFunc2,class HashFunc3 = __HashFunc3,
			class HashFunc4 = __HashFunc4, class HashFunc5 = __HashFunc5>
class BloomFilter
{
public:
	BloomFilter(size_t n) //n表示存储n个key(即有n个值存入集合)
		:_bs(n*5*2)     //n*5*2，一个n映射5个位，*2表示保持存值的位占1/2的位；
		, _range(n*5*2)
	{}

	void Set(const K &key)
	{
		//字符串转为整形
		size_t hash1 = HashFunc1()(key);
		size_t hash2 = HashFunc2()(key);
		size_t hash3 = HashFunc3()(key);
		size_t hash4 = HashFunc4()(key);
		size_t hash5 = HashFunc5()(key);

		//放入集合
		_bs.Set(hash1 % _range);
		_bs.Set(hash2 % _range);
		_bs.Set(hash3 % _range);
		_bs.Set(hash4 % _range);
		_bs.Set(hash5 % _range);
	}

	bool Test(const K &key)
	{
		
		size_t hash1 = HashFunc1()(key);
		if (_bs.Test(hash1 % _range) == false)
		{
			return false;
		}
		size_t hash2 = HashFunc2()(key);
		if (_bs.Test(hash2 % _range) == false)
		{
			return false;
		}
		size_t hash3 = HashFunc3()(key);
		if (_bs.Test(hash3 % _range) == false)
		{
			return false;
		}
		size_t hash4 = HashFunc4()(key);
		if (_bs.Test(hash4 % _range) == false)
		{
			return false;
		}
		size_t hash5 = HashFunc5()(key);
		if (_bs.Test(hash5 % _range) == false)
		{
			return false;
		}

		return true;  //可能存在误判;
	}
protected:
	BitSet _bs;
	size_t _range;  //范围
};

void TestBloom()
{
	BloomFilter<string> bf(100);
	bf.Set("string");
	bf.Set("sort");
	bf.Set("范围");

	cout << bf.Test("sring") << endl;
	cout << bf.Test("string") << endl;
}
#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*实现布隆过滤器的删除*/
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

template<class K ,class HashFunc1 = __HashFunc1, class HashFunc2 = __HashFunc2, class HashFunc3 = __HashFunc3,
class HashFunc4 = __HashFunc4, class HashFunc5 = __HashFunc5>
class BloomFilter
{
public:
	BloomFilter(size_t n)
		:_range(n*5*2)
	{
		_bf.resize(n * 10);
	}

	void Set(const K &key)
	{
		size_t hash1 = HashFunc1()(key);
		size_t hash2 = HashFunc2()(key);
		size_t hash3 = HashFunc3()(key);
		size_t hash4 = HashFunc4()(key);
		size_t hash5 = HashFunc5()(key);

		_bf[hash1%_range]++;
		_bf[hash2%_range]++;
		_bf[hash3%_range]++;
		_bf[hash4%_range]++;
		_bf[hash5%_range]++;
	}

	void Reset(const K &key)
	{
		size_t hash1 = HashFunc1()(key);
		size_t hash2 = HashFunc2()(key);
		size_t hash3 = HashFunc3()(key);
		size_t hash4 = HashFunc4()(key);
		size_t hash5 = HashFunc5()(key);

		_bf[hash1%_range]--;
		_bf[hash2%_range]--;
		_bf[hash3%_range]--;
		_bf[hash4%_range]--;
		_bf[hash5%_range]--;
	}

	bool Test(const K &key)
	{
		size_t hash1 = HashFunc1()(key);
		if (_bf[hash1%_range] == 0)
		{
			return false;
		}
		size_t hash2 = HashFunc2()(key);
		if (_bf[hash2%_range] == 0)
		{
			return false;
		}
		size_t hash3 = HashFunc3()(key);
		if (_bf[hash3%_range] == 0)
		{
			return false;
		}
		size_t hash4 = HashFunc4()(key);
		if (_bf[hash4%_range] == 0)
		{
			return false;
		}
		size_t hash5 = HashFunc5()(key);
		if (_bf[hash5%_range] == 0)
		{
			return false;
		}

		return true;
	}
protected:
	vector<size_t> _bf;
	size_t _range;  //范围
};

void TestBFReset() //测试布隆的删除
{
	BloomFilter<string> bf(10);
	bf.Set("123");
	bf.Set("456");
	bf.Set("abc");
	bf.Set("bcd");
	bf.Set("hello");

	cout << bf.Test("123") << endl;
	bf.Reset("123");
	cout << bf.Test("123") << endl;

}
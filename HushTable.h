#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

// 素数表，保证哈希表的容量为素数，以近似二倍的增长,来降低哈希冲突;


size_t GetNextPrime(size_t num)
{
	const int _PrimeSize = 28;
	static const unsigned long _PrimeList[_PrimeSize] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul,
		786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul,
		25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul,
		805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};

	for (size_t i = 0; i < _PrimeSize; i++)
	{
		if (num < _PrimeList[i])
		{
			return _PrimeList[i];
		}
	}

	return _PrimeList[_PrimeSize - 1];
}
enum STATE{
	EMPTY,
	EXIST,
	DELETE
};

template<class K>
struct __HushFuncInt
{
	size_t operator()(const K &key)
	{
		return key;
	}
};
static size_t BKDRHash(const  char *str)
{
	unsigned int seed = 131;// 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash*seed + (*str++);
	}
	return(hash & 0x7FFFFFFF);
}

struct __HushFuncString     //对字符串进行除留余数法获取在表中位置；
 {
	size_t operator()(const string & str)
	{
		return BKDRHash(str.c_str());
	}
};

template<class K, class V>
struct HushNode
{
	pair<K, V> _kv;
	STATE _s;

	HushNode()
		:_s(EMPTY)
	{}
};

template<class K, class V, class HushFunc = __HushFuncInt<int>>
class HushTable
{
	typedef HushNode<K,V> Node;
public:
	HushTable()
		:_size(0)
	{}
	HushTable(const size_t size)
		:_size(0)
	{
		_table.resize(size);
	}

	pair<Node *, bool> Insert(const pair<K,V> kv)
	{
		//检查是否需要扩容；
		_Check();
		size_t index = _HushFunc(kv.first);
		
		//进行探测
		while (_table[index]._s == EXIST)
		{
			if (_table[index]._kv.first == kv.first)
			{
				Node * ret = &_table[index];
				return make_pair(ret, false);
			}

			index++;
			if (index == _table.size())
			{
				index = 0;
			}
		}

		//找到位置，并进行插入
		_table[index]._kv = kv;
		_table[index]._s = EXIST;
		++_size;
		Node * ret = &_table[index];
		return make_pair(ret, true);
	}

	Node* Find(const K &key)
	{
		size_t index = _HushFunc(key);
		while (_table[index]._s != EMPTY)
		{
			if (_table[index]._kv.first == key)
			{
				//此处有两种情况能找到这个key ,一种是存在，一种是已经删除，要加以判断；
				if (_table[index]._s == EXIST)
				{
					return &_table[index];
				}
				else
				{
					return NULL;
				}
			}
			else  //第一个不行，线性探测继续找下一个；
			{
				index += 1;
				if (index == _table.size())  //若是从尾开始找的，调到头部；
				{
					index = 0;
				}
			}
		}
		 
		//在此处遍历完整个哈希表，没找到；
		return NULL;
	}

	V & operator[](const K &key)
	{
		pair<Node *, bool> ret = Insert(make_pair(key, V()));
		return (ret.first)->_kv.second;
	}

	bool Remove(const K &key)
	{
		//先找到，进行伪删，也就是把_s状态置为Delete;
		Node *del = this->Find(key);
		if (del)
		{
			del->_s = DELETE;
			_size--;
			return true;
		}
	}

protected:
	size_t _HushFunc(const K &key) //寻找在表中的位置
	{
		HushFunc ht;
		return ht(key) % _table.size();    //除留余数法
	}

	void Swap(HushTable<K, V, HushFunc> &ht)
	{
		swap(_size, ht._size);
		_table.swap(ht._table);
	}

	void _Check()
	{
		if (_table.size() == 0)
		{
			_table.resize(53);
		}
		else if (_size * 10 / _table.size() == 7)
		{
			size_t newSize = GetNextPrime(_table.size());
			HushTable<K, V,HushFunc> newHT(newSize);

			for (size_t i = 0; i < _table.size(); ++i)
			{
				if (_table[i]._s == EXIST)
				{
					newHT.Insert(_table[i]._kv);
				}
			}

			Swap(newHT);
		}
	}

protected:
	vector<Node> _table;
	size_t _size;    //哈希表实际数据个数；
};

void TestHushTable()
{
	//HushTable<int, int> ht;
	//ht[1] = 1;
	HushTable<string, string, __HushFuncString> ht;
	ht["english"] = "英语";
	ht["picture"] = "照片";
	ht["left"] = "左";
	ht.Remove("left");
	//cout << ht.Find("left")->_kv.first << endl;;
}
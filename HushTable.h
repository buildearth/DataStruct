#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

// ��������֤��ϣ�������Ϊ�������Խ��ƶ���������,�����͹�ϣ��ͻ;


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

struct __HushFuncString     //���ַ������г�����������ȡ�ڱ���λ�ã�
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
		//����Ƿ���Ҫ���ݣ�
		_Check();
		size_t index = _HushFunc(kv.first);
		
		//����̽��
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

		//�ҵ�λ�ã������в���
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
				//�˴�������������ҵ����key ,һ���Ǵ��ڣ�һ�����Ѿ�ɾ����Ҫ�����жϣ�
				if (_table[index]._s == EXIST)
				{
					return &_table[index];
				}
				else
				{
					return NULL;
				}
			}
			else  //��һ�����У�����̽���������һ����
			{
				index += 1;
				if (index == _table.size())  //���Ǵ�β��ʼ�ҵģ�����ͷ����
				{
					index = 0;
				}
			}
		}
		 
		//�ڴ˴�������������ϣ��û�ҵ���
		return NULL;
	}

	V & operator[](const K &key)
	{
		pair<Node *, bool> ret = Insert(make_pair(key, V()));
		return (ret.first)->_kv.second;
	}

	bool Remove(const K &key)
	{
		//���ҵ�������αɾ��Ҳ���ǰ�_s״̬��ΪDelete;
		Node *del = this->Find(key);
		if (del)
		{
			del->_s = DELETE;
			_size--;
			return true;
		}
	}

protected:
	size_t _HushFunc(const K &key) //Ѱ���ڱ��е�λ��
	{
		HushFunc ht;
		return ht(key) % _table.size();    //����������
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
	size_t _size;    //��ϣ��ʵ�����ݸ�����
};

void TestHushTable()
{
	//HushTable<int, int> ht;
	//ht[1] = 1;
	HushTable<string, string, __HushFuncString> ht;
	ht["english"] = "Ӣ��";
	ht["picture"] = "��Ƭ";
	ht["left"] = "��";
	ht.Remove("left");
	//cout << ht.Find("left")->_kv.first << endl;;
}
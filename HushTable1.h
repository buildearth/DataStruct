#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;
//拉链法（哈希桶）处理哈希冲突；
enum State{
	EXIST,
	EMPTY,
	DELETE,
};

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
	State _s;
	HushNode *_next;

	HushNode(const pair<K, V> &kv)
		:_kv(kv)
		, _s(EMPTY)
		, _next(NULL)
	{}
};

template<class K, class V, class HushFunc>
class HushTable;

////迭代器
template<class K, class V, class HushFunc, class ValueTypePtr, class ValueTypeRef>
struct __HushIterator
{
	typedef HushNode<K,V> Node;
	typedef pair<K, V> ValueType;
	typedef __HushIterator<K,V, HushFunc, ValueTypePtr, ValueTypeRef> Self;

	Node *_node;    //指向节点的指针
	HushTable<K, V, HushFunc> *_ht;   //哈希表的地址，用来获得下一个位置；

	__HushIterator(Node *node, HushTable<K, V, HushFunc> *ht)
		:_node(node)
		, _ht(ht)
	{}

	ValueTypeRef operator*()
	{
		return _node->_kv;
	}

	ValueTypePtr operator->()
	{
		return &(operator*());
	}

	bool operator!=(const Self & s) const //加上const，const和非const对象都能调；
	{
		return _node != s._node;
	}

	Self & operator++()
	{
		/*两种情况：
		1.数组下挂的链表没有走到结束,直接走下一个
		2.本位置是走后一个，找到下一个有挂链表的位置；
		*/
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			size_t index = _ht->_HushFunc(_node->_kv.first,_ht->_tables.size()); // ??????????????????
			for (index = index + 1; index < _ht->_tables.size(); ++index)
			{
				//找到一个挂有链表的位置
				if (_ht->_tables[index])
				{
					_node = _ht->_tables[index];   //在这个类中无法直接用_ht访问HushTable中的_tables；需要将此类设置为友元类；
					return *this;
				}
			}

			//走完，没有下一个数据；；
			_node = NULL;
		}

		return *this;
	}

	Self operator++(int) //后置++
	{
		Self tmp(_node,_ht);
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			size_t index = _ht->_HushFunc(_node->_kv.first,_ht->_tables.size());
			for (index = index + 1; index < _ht->_tables.size(); ++index)
			{
				if (_ht->_tables[index])
				{
					_node = _ht->_tables[index];
					return tmp;
				}
			}

			_node = NULL;
		}

		return tmp;
	}

};





template<class K, class V, class HushFunc = __HushFuncInt<K>>
class HushTable
{
	typedef HushNode<K, V> Node;
	friend struct __HushIterator<K, V, HushFunc, pair<K, V>*, pair<K, V>&>;
public:
	typedef __HushIterator<K, V, HushFunc, pair<K, V>*, pair<K, V>&> Iterator;
	typedef __HushIterator<K, V, HushFunc, const pair<K, V>*, const pair<K, V>&> ConstIterator;

	HushTable()
		:_size(0)
	{}
	HushTable(const size_t size)
		:_size(0)
	{
		_tables.resize(size);
	}

	pair<Iterator,bool> Insert(const pair<K, V> &kv)
	{
		//check;
		_Check();  //扩容判断
		size_t index = _HushFunc(kv.first,_tables.size());
		//判断哈希桶中是否已有key
		Node *cur = _tables[index];
		while (cur)
		{
			if (cur->_kv.first == kv.first)
			{
				return make_pair(Iterator(cur,this),false);
			}
			else
			{
				cur = cur->_next;
			}
		}

		//对链表中的顺序无要求，进行头插效率高
		//1.无节点，2.有一个或多个，合为一种情况；
		Node *node = new Node(kv);
		node->_next = _tables[index];
		_tables[index] = node;
		_size++;
		return make_pair(Iterator(node, this), true);
	}
	Node *Find(const K &key)
	{
		size_t index = _HushFunc(key, _tables.size());
		Node *cur = _tables[index];
		while (cur)
		{
			if (cur->_kv.first == key)
			{
				return _tables[index];
			}
			else
			{
				cur = cur->_next;
			}
		}

		return NULL;
	}
	bool Remove(const K &key)
	{
		size_t index = _HushFunc(key,_tables.size());
		Node *cur = _tables[index];
		Node *prev = NULL;
		while (cur)
		{
			if (cur->_kv.first == key)
			{

				if (cur == _tables[index])
				{
					_tables[index] = NULL;
				}
				else
				{
					prev->_next = cur->_next;
				}

				delete cur;
				--_size;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}
	}

	Iterator Begin()
	{
		size_t index = 0;
		for (; index < _tables.size(); index++)
		{
			if (_tables[index])
			{
				return Iterator(_tables[index], this);
			}
		}

		//走完没有找到数据
		return End();
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

protected:
	size_t _HushFunc(const K &key,size_t size)
	{
		HushFunc hf;
		return hf(key) % size;
	}

	void _Check()
	{
		if (_tables.size() == _size)
		{
			size_t newSize = GetNextPrime(7);
			vector<Node*> newTables;
			newTables.resize(newSize);

			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node * cur = _tables[i];
				while (cur)
				{
					Node *next = cur->_next;
					size_t index = _HushFunc(cur->_kv.first,_tables.size());
					cur->_next = newTables[index];
					newTables[index] = cur;

					cur = next;
				}
				_tables[i] = NULL;
			}

			_tables.swap(newTables);
		}
	}

	


protected:
	vector<Node *> _tables;
	size_t _size;
};


//模拟实现库中的UnorderMap;只是一层外壳;
template<class K, class V , class Hush = __HushFuncInt<K> >
class UnorderMap
{
	typedef  HushTable<K, V, Hush> HT;
public:
	typedef typename HT::Iterator Iterator;

	Iterator Begin()
	{
		return _table.Begin();
	}

	Iterator End()
	{
		return _table.End();
	}



	pair<Iterator,bool> Insert(const pair<K,V> &kv)
	{
		return _table.Insert(kv);
	}

	V & operator[](const K &key)
	{
		return (*(Insert(make_pair(key, V())).first)).second;
	}
protected:
	HT _table;
};

void TestHushTable1()
{
	HushTable<int,int> ht;
	ht.Insert(make_pair(1, 1));
	ht.Insert(make_pair(2, 2));
	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(8, 6));
	HushTable<int, int, __HushFuncInt<int>>::Iterator it = ht.Begin();
	//cout << it->first << endl;
	while (it != ht.End())
	{
		cout << (*it).first << " ";
		++it;
	}
	
}

void TestUnorderMap()
{
	UnorderMap<string, string, __HushFuncString> ht;
	ht["hello"] = "你好";
	ht["Bird"] = "鸟";
	ht["Bird"] = "小鸟";
	UnorderMap<string, string, __HushFuncString>::Iterator it = ht.Begin();
	while (it != ht.End())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}
#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class K, class V> //K/V
struct SearchBinaryTreeUseNode
{
	K _key;
	V _value;
	SearchBinaryTreeUseNode<K, V> *_left;
	SearchBinaryTreeUseNode<K, V> *_right;

	SearchBinaryTreeUseNode(const K &key, const V &value = V())
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{

	}

};

template<class K, class V>
class SearchBinaryTreeUse
{
	typedef SearchBinaryTreeUseNode<K, V> Node;
public:
	SearchBinaryTreeUse()
		:_root(NULL)
	{}

	bool Insert(const K &key, const V &value)
	{
		return _Insert(_root,key,value);
	}



	Node * Find(const K &key)
	{
		return _Find(_root, key);
	}

	void InOrderR()
	{
		_InOrderR(_root);
	}

protected:
	bool _Insert(Node *&root, const K &key, const V &value)
	{
		if (root == NULL)  //传引用，root有两个意义；
		{
			root = new Node(key, value);
			return true;
		}

		if (key > root->_key)
		{
			return _Insert(root->_right,key,value);
		}
		else if (key < root->_key)
		{
			return _Insert(root->_left, key, value);
		}
		else
		{
			return false;
		}
	}

	Node *_Find(Node *root, const K &key)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_key < key)
		{
			return _Find(root->_right,key);
		}
		else if (root->_key > key)
		{
			return _Find(root->_left, key);
		}
		else
		{
			return root;
		}
	}

	void _InOrderR(Node *root)
	{
		if (root == NULL)
			return;
		
		_InOrderR(root->_left);
		cout << root->_key << " : " << root->_value << endl;
		_InOrderR(root->_right);
	}

protected:
	Node * _root;
};

void TestBSTreeUse()
{
	/*SearchBinaryTreeUse<string,string> tree;  //字典
	tree.Insert("sorry", "对不起");
	tree.Insert("hello", "你好");
	tree.Insert("string", "字符串");
	tree.Insert("world", "世界");
	cout << tree.Find("hello")->_value << endl;*/

	SearchBinaryTreeUse<string, int> tree;   //字符出现次数统计
	string *s1 = new string [10];
	s1[0] = "sring";
	s1[1] = "sring";
	s1[2] = "hello";
	s1[3] = "sring";
	s1[4] = "hello";
	s1[5] = "sring";
	s1[6] = "sort";
	s1[7] = "sring";
	s1[8] = "include";
	s1[9] = "\0";
	int i = 0;
	while (s1[i] != "\0")
	{
		SearchBinaryTreeUseNode<string, int> * tmp = tree.Find(s1[i]);
		if (tmp == NULL)
		{
			tree.Insert(s1[i], 1);
		}
		else
		{
			tmp->_value++;
		}
		i++;
	}

	tree.InOrderR();



}


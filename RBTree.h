#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<string>
using namespace std;

enum Color{RED,BLACK};


template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	Color _color;

	RBTreeNode<K, V> *_left;
	RBTreeNode<K, V> *_right;
	RBTreeNode<K, V> *_parent;

	RBTreeNode(const K &key, const K &value)
		:_key(key)
		, _value(value)
		, _color(RED)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	~RBTree()
	{
		_Destory(_root);  //后序清理
	}
	pair<Node *, bool> Insert(const K &key, const V &value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return make_pair(_root,true);
		}

		//寻找插入位置
		Node *parent = NULL;
		Node *cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur,false);
			}
		}
		//此时parent为要插入节点的父亲节点；
		cur = new Node(key, value);
		Node* tmp = cur;
		if (key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//分情况进行调整
		while (parent && parent->_color == RED)
		{

			Node *grandFather = parent->_parent;

			if (parent == grandFather->_left)
			{
				Node *uncle = grandFather->_right;
				if (uncle && uncle->_color == RED)
				{
					grandFather->_color = RED;
					uncle->_color = parent->_color = BLACK;


					cur = parent;   //继续向上判断，因为这gF有可能是一颗子树的根；
					parent = cur->_parent;


				}
				else  //uncle->_color 为空或者为存在且为黑；
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						cur = parent;
						parent = cur->_parent;
					}

					RotateR(grandFather);

					grandFather->_color = RED;
					parent->_color = BLACK;
					break;   //此时已调整到c没有连续的红色节点；
				}


			}
			else  //右子树
			{
				Node *uncle = grandFather->_left;
				if (uncle && uncle->_color == RED)
				{
					grandFather->_color = RED;
					parent->_color = uncle->_color = BLACK;

					cur = parent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						cur = parent;
						parent = cur->_parent;
					}

					RotateL(grandFather);
					grandFather->_color = RED;
					parent->_color = BLACK;
					break;
				}

			}
			_root->_color = BLACK;
		}
		_root->_color = BLACK;
		return make_pair(tmp,true);
	}
	/*bool Insert(const K &key, const V &value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			_root->_color = BLACK;
			return true;
		}

		//寻找插入位置
		Node *parent = NULL;
		Node *cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		//此时parent为要插入节点的父亲节点；
		cur = new Node(key,value);
		if (key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//分情况进行调整
		while (parent && parent->_color == RED)
		{
			
			Node *grandFather = parent->_parent;
			
			if (parent == grandFather->_left)
			{
				Node *uncle = grandFather->_right;
				if (uncle && uncle->_color == RED)
				{
					grandFather->_color = RED;
					uncle->_color = parent->_color = BLACK;

				
					cur = parent;   //继续向上判断，因为这gF有可能是一颗子树的根；
					parent = cur->_parent;
					
					
				}
				else  //uncle->_color 为空或者为存在且为黑；
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						cur = parent;
						parent = cur->_parent;
					}

					RotateR(grandFather);

					grandFather->_color = RED;
					parent->_color = BLACK;
					break;   //此时已调整到c没有连续的红色节点；
				}
				
				
			}
			else  //右子树
			{
				Node *uncle = grandFather->_left;
				if (uncle && uncle->_color == RED)
				{
					grandFather->_color = RED;
					parent->_color = uncle->_color = BLACK;

					cur = parent;
					parent = cur->_parent;
				}
				else
				{
					if ( cur == parent->_left)
					{
						RotateR(parent);
						cur = parent;
						parent = cur->_parent;
					}

					RotateL(grandFather);
					grandFather->_color = RED;
					parent->_color = BLACK;
					break;
				}
				
			}
			_root->_color = BLACK;
		}
		_root->_color = BLACK;
		return true;
	}*/


	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		if (_root == NULL)
			return true;
		if (_root->_color == RED)
			return false;
		int num = 0;
		int blackNum = 0;
		Node *cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
			{
				blackNum++;
			}
			cur = cur->_left;
		}
		return _IsBalance(_root,blackNum,num);
	}

	bool Remove(const K &key);
	V & operator[](const K &key)
	{
		pair<Node*, bool> ret = Insert(key, V());
		return (ret.first)->_value;
	}


protected:
	bool _IsBalance(Node *root, const int blackNum, int num)
	{
		if (root == NULL)
		{
			if (blackNum != num)
			{
				cout << "路径上黑节点数目不相等" << endl;
				return false;
			}
			else
			{
				return true;
			}
		}
		
		if (root->_color == RED && root->_parent->_color == RED)
		{
			cout << "连续红节点" << endl;
			return false;
		}
		if (root->_color == BLACK)
		{
			num++;
		}

		return _IsBalance(root->_left, blackNum, num) && _IsBalance(root->_right, blackNum, num);
	}
	void _InOrder(Node *root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key <<"--"<< root->_color << " ";
		_InOrder(root->_right);
	}
	void RotateR(Node *parent)
	{
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;
		Node *grandPa = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (grandPa == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (grandPa->_left == parent)
			{
				grandPa->_left = subL;
				subL->_parent = grandPa;
			}
			else
			{
				grandPa->_right = subL;
				subL->_parent = grandPa;
			}
		}
	}

	void RotateL(Node *parent)
	{
		Node *subR = parent->_right;
		Node*subRL = subR->_left;

		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;

		Node *grandPa = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (grandPa == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (parent == grandPa->_left)
			{
				grandPa->_left = subR;
			}
			else
			{
				grandPa->_right = subR;
			}
			subR->_parent = grandPa;
		}
	}

	void _Destory(Node * root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
protected:
	Node *_root;
};


void TestRBTree()
{
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int,int> tree;
	for (int i = 0; i < 9; i++)
	{
		tree.Insert(a[i], i);
	//	cout << tree.IsBalance() << endl;
	}
	cout << tree.IsBalance() << endl;
	tree.InOrder();

	RBTree<string, string> dict;
	dict["sort"] = "排序";
}
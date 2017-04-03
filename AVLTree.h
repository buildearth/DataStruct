#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;

//平衡搜索树：三叉链实现

template<class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;   //平衡因子

	AVLTreeNode<K, V> *_left;
	AVLTreeNode<K, V> *_right;
	AVLTreeNode<K, V> *_parent;

	AVLTreeNode(const K &key, const V &value)
		:_key(key)
		, _value(value)
		, _bf(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{

	}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{

	}

	bool Insert(const K &key, const V &value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		//构建三叉搜索树
		Node *parent = NULL;
		Node *cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;  //不能有重复
			}
		}

		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
			//return true;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
			//return true;
		}

		// g更新平衡因子
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)  //子树高度没有增加
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)  //子树高度增加,依旧处于平衡
			{
				cur = parent;
				parent = cur->_parent;
			}
			else   //2/-2不平衡状态，进行旋转调节，再次平衡
			{
				
				if (parent->_bf == 2)   //左旋
				{
					Node *subR = parent->_right;
					if (subR->_bf == 1) //左单旋
					{
						RotateL(parent);
					}
					else if(subR->_bf == -1)   //右左双旋
					{
						RotateRL(parent);
					}
					
				}
				else
				{
					Node *subL = parent->_left;
					if (subL->_bf == -1)  //右单
					{
						RotateR(parent);
					}
					else
					{
						/*if (parent->_right != NULL)
							RotateL(parent);
						else*/
						RotateLR(parent);
					}
				}
				
				break;
			}

		}
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	/*bool IsBalance()
	{
		return _IsBalance(_root);
	}*/
	bool IsBalance()
	{
		int height = 0;
		return _IsBalance(_root,height);
	}

protected:
	void RotateR(Node *parent)  //右单旋
	{

		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;

		subL->_right = parent;
		Node *ppNode = parent->_parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			subL->_parent = ppNode;
			if (parent == ppNode->_left)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
		}

		//更新平衡因子
			subL->_bf = parent->_bf = 0;
		
		
	}

	void RotateL(Node *parent)  //左单旋
	{
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		
		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;

		Node *ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (parent == ppNode->_left)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
		
			parent->_bf = subR->_bf = 0;
		
		
		
	}

	void RotateRL(Node *parent)  //右左双旋
	{
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);
		
		if (bf == 0)
		{
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
	}

	void RotateLR(Node *parent) //左右双旋
	{
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);
		
		if (bf == 0)
		{
			parent->_bf = subL->_bf = subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}

	}

	void _InOrder(Node *root)  //中序
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << ":" << root->_value << endl;
		_InOrder(root->_right);
	}
	size_t _height(Node *root)
	{
		if (root == NULL)
			return 0;

		size_t LHeight = _height(root->_left);
		size_t RHeight = _height(root->_right);

		return LHeight < RHeight ? RHeight +1 : LHeight +1;
	}


	/*bool _IsBalance(Node *root)  //O(N*N)前序
	{
		if (root == NULL)
			return true;
		size_t l = _height(root->_left);
		size_t r = _height(root->_right);

		if (root->_bf != (r - l))
		{
			cout << "平衡因子异常" <<root->_key<<":"<<root->_bf<< endl;
			return false;
		}
		
		int sub = (int)(r - l);

		return abs(sub) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}*/

	//后续 O(N)
	bool _IsBalance(Node *root, int &height)
	{
		if (root == NULL)
		{
			height = 1;
			return true;
		}
		int l;
		int r ;

		if (_IsBalance(root->_left, l) && _IsBalance(root->_right, r) && abs(r - l) < 2)
		{
			height = l < r ? r + 1 : l + 1;
			if (root->_bf != r - l)
			{
				cout << "平衡因子异常" << endl;
			}
			return true;
		}
	}

protected:
	Node * _root;
};

void TestAVLTree()
{
	//int a[10] = {4,2,6,1,3,5,15,7,16,14};
	int a[9] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> tree;
	for (int i = 0; i < 9; i++)
	{
		tree.Insert(a[i],i);
	}
	tree.InOrder();
	tree.IsBalance();
}
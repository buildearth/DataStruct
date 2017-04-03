#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;

//ƽ����������������ʵ��

template<class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;   //ƽ������

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

		//��������������
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
				return false;  //�������ظ�
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

		// g����ƽ������
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)  //�����߶�û������
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)  //�����߶�����,���ɴ���ƽ��
			{
				cur = parent;
				parent = cur->_parent;
			}
			else   //2/-2��ƽ��״̬��������ת���ڣ��ٴ�ƽ��
			{
				
				if (parent->_bf == 2)   //����
				{
					Node *subR = parent->_right;
					if (subR->_bf == 1) //����
					{
						RotateL(parent);
					}
					else if(subR->_bf == -1)   //����˫��
					{
						RotateRL(parent);
					}
					
				}
				else
				{
					Node *subL = parent->_left;
					if (subL->_bf == -1)  //�ҵ�
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
	void RotateR(Node *parent)  //�ҵ���
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

		//����ƽ������
			subL->_bf = parent->_bf = 0;
		
		
	}

	void RotateL(Node *parent)  //����
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

	void RotateRL(Node *parent)  //����˫��
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

	void RotateLR(Node *parent) //����˫��
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

	void _InOrder(Node *root)  //����
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


	/*bool _IsBalance(Node *root)  //O(N*N)ǰ��
	{
		if (root == NULL)
			return true;
		size_t l = _height(root->_left);
		size_t r = _height(root->_right);

		if (root->_bf != (r - l))
		{
			cout << "ƽ�������쳣" <<root->_key<<":"<<root->_bf<< endl;
			return false;
		}
		
		int sub = (int)(r - l);

		return abs(sub) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}*/

	//���� O(N)
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
				cout << "ƽ�������쳣" << endl;
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
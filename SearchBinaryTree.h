#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
using namespace std;

template<class K>
struct SearchBinaryTreeNode
{
	K _key;
	SearchBinaryTreeNode *_left;
	SearchBinaryTreeNode *_right;

	SearchBinaryTreeNode(const K & x)
		:_key(x)
		, _left(NULL)
		, _right(NULL)
	{

	}
};


template<class K>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{

	}

	~SearchBinaryTree()   //����ɾ��
	{
		_Destory(_root);
	}

	bool Insert(const K &x)  //����������������ֵ�ظ��Ľڵ㣬����ʱҪʶ��
	{
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		else
		{
			Node *parent = NULL;
			Node *cur = _root;
			while (cur)
			{
				parent = cur;
				if (x > cur->_key) //����
				{
					cur = cur->_right;
				}
				else if (x < cur->_key)
				{
					cur = cur->_left;
				}
				else
				{
					return false;  //�����ظ�ֵ���������룻
				}
			}

			if (parent->_key > x)
			{
				parent->_left = new Node(x);
				return true;
			}
			else
			{
				parent->_right = new Node(x);
				return true;
			}
		}

	}


	void InOrder()  //���������������
	{
		_InOrder(_root);
		cout << endl;
	}

	Node * Find(const K &x)
	{
		Node *cur = _root;

		while (cur)
		{
			if (x > cur->_key)
			{
				cur = cur->_right;
			}
			else if (x < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}

	bool Remove(const  K &x)
	{
		if (_root == NULL)
			return false;
		if (_root->_left == NULL && _root->_right == NULL)
		{
			delete _root;
			_root = NULL;
			return true;
		}
		Node * cur = _root;
		Node *parent = cur;

		while (cur)
		{
			if (x > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (x < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				Node *del = NULL;
				//�ҵ��ڵ㣬��������ķ����жϣ�


				if (cur->_left == NULL)
				{
					del = cur;
					if (cur == _root)
					{
						_root = cur->_right;
					}

					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
					}
					else if (parent->_right == cur)
					{
						parent->_right = cur->_right;
					}
				}
				else if (cur->_right == NULL)
				{
					del = cur;
					if (cur == _root)
					{
						_root = cur->_left;
					}

					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else if (parent->_right == cur)
					{
						parent->_right = cur->_left;
					}
				}
				else   //���Ҿ���Ϊ�գ�
				{
					//��������������ڵ㣬�滻ɾ��
					Node * tmp = cur;
					parent = cur;
					cur = cur->_right;  //�Ƚ���������
					while (cur->_left)
					{
						parent = cur;
						cur = cur->_left;
					}
					swap(tmp->_key, cur->_key); //�滻
					del = cur;

					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
					}
					else if (parent->_right = cur)
					{
						parent->_right = cur->_right;
					}
				}
				delete del;
				return true;
			}

		}
		return false;
	}


	/*�ݹ�ʵ��������������*/
	bool InsertR(const K & key)
	{
		return _InsertR(_root,key);
	}

	void InOrderR()
	{
		_InOrder(_root);
		cout << endl;
	}

	const Node * FindR(const K &key)
	{
		return _FindR(_root, key);
	}

	bool RemoveR(const K &key)
	{
		return _RemoveR(_root, key);
	}

protected:
	bool _InsertR(Node *&root, const K &key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return true;
		}

		if (root->_key < key)
		{
			return _InsertR(root->_right,key);
		}
		else if (root->_key > key)
		{
			return _InsertR(root->_left, key);
		}
		else
		{
			return false;
		}
	}

	void _InOrderR(Node * root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node *_FindR(Node *root,const K &key)
	{
		if (root == NULL)
			return NULL;

		if (root->_key == key)
		{
			return root;
		}
		else if (root->_key < key)
		{
			return _FindR(root->_right,key);
		}
		else
		{
			return _FindR(root->_left, key);
		}
	}

	bool _RemoveR(Node *&root, const K &key)  //�����ã�ָ�����Һ��ӵ�ָ���Ǹ���ָ�����Һ���ָ��ı�����
	{
		if (root == NULL)
			return false;

		if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _RemoveR(root->_left,key);
		}
		else   //�ҵ��ڵ㣻
		{
			Node *del = root;
			//�������
			//1.��Ϊ�գ�
			if (root->_left == NULL)  //root���������壬��һ��ָ����������ڵ㣬�ڶ�����ǰ�ڵ�ġ����׽ڵ�->_left��������
			{
				root = root->_right;
			}
			else if (root->_right == NULL) //2.��Ϊ��
			{
				root = root->_left;
			}
			else  //3.���Һ��Ӿ���Ϊ��
			{
				Node *parent = root;
				Node *SubRight = root->_right; //ȥ������������ڵ㣬�滻ɾ����
				

				while (SubRight->_left)
				{
					parent = SubRight;
					SubRight = SubRight->_left;
				}

				swap(root->_key, SubRight->_key);
				del = SubRight;
				if (SubRight == parent->_left)
				{
					parent->_left = SubRight->_right;
				}
				else if (SubRight == parent->_right)
				{
					parent->_right = SubRight->_right;
				}

			}
			delete del;
			return true;
		}
	}



protected:
	void _InOrder(Node * root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
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
	Node * _root;
};

void TestSBTree() //���Էǵݹ�
{
	int a[10] = {5,3,4,1,7,8,2,6,0,9};
	SearchBinaryTree<int> sbTree;
	for (int i = 0; i < 10; i++)
	{
		sbTree.Insert(a[i]);
	}
	sbTree.InOrder();
	//cout << sbTree.Find(0)->_key << endl;
	//cout << sbTree.Find(55) << endl;
	sbTree.Remove(0);
	sbTree.InOrder();
	sbTree.Remove(1);
	sbTree.InOrder();
	sbTree.Remove(4);
	sbTree.InOrder();
	sbTree.Remove(5);
	sbTree.InOrder();
	sbTree.Remove(6);
	sbTree.InOrder();
	sbTree.Remove(7);
	sbTree.InOrder();
	sbTree.Remove(2);
	sbTree.InOrder();
	sbTree.Remove(3);
	sbTree.InOrder();
	
	sbTree.Remove(8);
	sbTree.InOrder();
	sbTree.Remove(9);

	sbTree.InOrder();
}

void TestSBTreeR()
{
	int a[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	SearchBinaryTree<int> sbTree;
	for (int i = 0; i < 10; i++)
	{
		sbTree.InsertR(a[i]);
	}
	sbTree.InOrderR();
	//cout << sbTree.FindR(0)->_key << endl;
	sbTree.RemoveR(0);
	sbTree.InOrderR();

	sbTree.RemoveR(1);
	sbTree.InOrderR();

	sbTree.RemoveR(4);
	sbTree.InOrderR();

	sbTree.RemoveR(5);
	sbTree.InOrderR();

	sbTree.RemoveR(6);
	sbTree.InOrderR();

	sbTree.RemoveR(7);
	sbTree.InOrderR();

	sbTree.RemoveR(2);
	sbTree.InOrderR();

	sbTree.RemoveR(3);
	sbTree.InOrderR();

	sbTree.RemoveR(8);
	sbTree.InOrderR();

	sbTree.RemoveR(9);
	sbTree.InOrderR();
}
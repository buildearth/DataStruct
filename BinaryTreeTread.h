#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<stack>
using namespace std;




enum PointTag
{
	LINK,   //ָ���������£�δ������
	THREAD,  //ָ��ǰ������־��������֮��
};

template<class T>
struct BinaryTreeThdNode  //�������������Ľڵ�
{
	T _data;
	BinaryTreeThdNode<T> * _left;
	BinaryTreeThdNode<T> * _right;

	PointTag _leftTag;
	PointTag _rightTag;

	BinaryTreeThdNode(const T & x)
		:_data(x)
		,_left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{

	}
};


//���������
template<class T, class Ref, class Ptr>
struct BinaryTreeIterator
{
	typedef BinaryTreeThdNode<T> Node;
	Node * _node;
	typedef  BinaryTreeIterator<T, Ref, Ptr> Self;

	BinaryTreeIterator(Node * node)
		:_node(node)
	{}
	Self operator++() //����ǰ��++
	{
		if (_node->_rightTag == THREAD)
		{
			_node = _node->_right;
		}
		else
		{
			Node * left = _node->_right;
			while (left && left->_leftTag == LINK)
			{
				left = left->_left;
			}
			_node = left;
		}

		return *this;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	bool operator!=(const Self &s) const
	{
		return _node != s._node;
	}
};


template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;

public:

	typedef BinaryTreeIterator<T, T&, T*> Iterator;
	typedef BinaryTreeIterator<T, const T&, T*> ConstIterator;

	Iterator Begin()
	{
		Node * left = _root;

		while (left->_leftTag == LINK)
		{
			left = left->_left;
		}

		return Iterator(left);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

	BinaryTreeThd(int * a, size_t size,const T & invalue = T())
	{
		size_t index = 0;
		_root = _CreateTree(a, size, invalue,index);
	}

	/*~BinaryTreeThd()
	{
		_Destroy(_root);
	}*/
	
	//����������
	void InOrderThreading()
	{
		Node * prev = NULL; //������һ�����ʵĽڵ�
		_InOrderThreading(_root, prev);
	}
	//���������������
	void InOrderThd()
	{
		Node * root = _root;
		if (root == NULL)
			return;
		while (root)
		{
			while (root->_leftTag == LINK)
			{
				root = root->_left;
			}
			//�ҵ�����ڵ㣻
			cout << root->_data << " ";

			while (root->_rightTag == THREAD)
			{
				root = root->_right;
				cout << root->_data << " ";
			}

			root = root->_right;
		}
		cout << endl;
	}
	//ǰ��������
	void PrevOrderThreading()
	{
		Node * prev = NULL;
		_PrevOrderThreading(_root, prev);
	}
	//����ǰ��������������
	void PrevOrderThd()
	{
		Node * cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
		

			cur = cur->_right;
		}
		cout << endl;
	}

	//����������������
	void PostOrderThreading()
	{
		Node * prev = NULL;
		_PostOrderThreading(_root, prev);
	}
	//�����������������������
	void PostOrderPhd()
	{
		Node * cur = _root;
		//Node * prev = NULL:
		Node * next = cur->_right;

		if (cur == NULL)
			return;
		while (cur->_right != _root)
		{
			next = cur->_right;
			while (cur->_leftTag == LINK)
			{

				cur = cur->_left;


			}
			//��ʱ�ҵ�����ڵ㣻
			cout << cur->_data << " ";

			while (cur->_rightTag == THREAD)
			{

				cur = cur->_right;
				cout << cur->_data << " ";
			}

			cur = next;
		}
		cout << endl;
	}
protected:
	void _PrevOrderThreading(Node *cur, Node* & prev)
	{
		if (cur == NULL)
			return;
	
		
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		if (cur->_leftTag == LINK)
		_PrevOrderThreading(cur->_left, prev);
		if (cur->_rightTag == LINK)
		_PrevOrderThreading(cur->_right, prev);
	

	}
	Node * _CreateTree(int * a, size_t size,const T & invalue, size_t & index)
	{
		Node * root = NULL;

		if (index < size && a[index] != invalue)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a,size,invalue,++index);
			root->_right = _CreateTree(a, size, invalue, ++index);
		}

		return root;
	}
	
	void _Destroy(Node * root) //�����ú���������������������
	{
		if (root == NULL)
			return;

		_Destroy(root->_left);
		_Destroy(root->_right);

		if (root->_leftTag == THREAD && root->_rightTag == THREAD)
			delete root;
		
	}
	void _InOrderThreading(Node * cur, Node * &prev)
	{
		if (cur == NULL)
			return;

		_InOrderThreading(cur->_left,prev);

		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;

		_InOrderThreading(cur->_right, prev);
	}

	void _PostOrderThreading(Node * cur, Node * & prev)
	{
		if (cur == NULL)
			return;
		
		_PostOrderThreading(cur->_left, prev);
		_PostOrderThreading(cur->_right,prev);

		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;
	}
	
protected:
	Node * _root;
};

void TestBTT()
{
	//int t[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int t[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	/*BinaryTreeThd<int> tree(t,sizeof(t)/sizeof(t[0]), t[3]);
	tree.InOrderThreading();
	tree.InOrderThd();

	BinaryTreeThd<int> tree1(t, sizeof(t) / sizeof(t[0]), t[3]);
	tree1.PrevOrderThreading();
	tree1.PrevOrderThd();

	BinaryTreeThd<int> tree2(t, sizeof(t) / sizeof(t[0]), t[3]);
	tree2.PostOrderThreading();*/
	BinaryTreeThd<int> tree(t, sizeof(t) / sizeof(t[0]), t[2]);
	tree.InOrderThreading();
	tree.InOrderThd();

	BinaryTreeThd<int> tree1(t, sizeof(t) / sizeof(t[0]), t[2]);
	tree1.PrevOrderThreading();
	tree1.PrevOrderThd();

	BinaryTreeThd<int> tree2(t, sizeof(t) / sizeof(t[0]), t[2]);
	tree2.PostOrderThreading();
//	tree2.PostOrderPhd(); //�����������������������ʧ�ܣ�
}


void PrintTree(BinaryTreeThd<int> & t)
{
	BinaryTreeThd<int>::Iterator it = t.Begin();

	while (it != t.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void TestIterator()
{
	int t[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTreeThd<int> tree(t, sizeof(t) / sizeof(t[0]), t[2]);
	tree.InOrderThreading();
	tree.InOrderThd();

	PrintTree(tree);
}

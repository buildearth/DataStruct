#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<stdio.h>
#include<queue>
#include<stack>
using namespace std;

//����������洢��ʾ��

template<class T>   //�ڵ�
struct BinaryTreeNode
{
	BinaryTreeNode<T> * _left;
	BinaryTreeNode<T> * _right;
	T _data;

	BinaryTreeNode()
		:_left(NULL)
		: _right(NULL)
	{

	}

	BinaryTreeNode(const T &data)
		:_left(NULL)
		, _right(NULL)
		, _data(data)
	{

	}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{

	}

	BinaryTree(T * a, size_t size, const T & invalue)  //����һ��������Ҫ�õݹ飬���캯�������õݹ�ʵ�֣���Ҫ��һ���ڲ�������
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalue,index);
	}

	BinaryTree(const BinaryTree<T> & t) //��������
	{
		//_root = _CPBT(t._root);
		_root = _CpTree(t._root);
		
	}



	void PrevOrder()  //ǰ�����
	{
		_PrevOrder(_root);  //�ȸ���ǰ�������������ǰ�����������
		cout << endl;
	}

	void MidOrder()  //�������
	{
		_MidOrder(_root); //������������� �����ʸ��ڵ㣬���������������
		cout << endl;
	}

	void PostOrder()  //�������������������������������� �����������ʸ��ڵ�
	{
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()  //һ��һ��ı�����ʹ�ö���.ÿһ����һ�������
	{
		queue<Node *> q;
		if (_root == NULL)
			return;

		q.push(_root);
		while (!q.empty())
		{
			Node * root = q.front();
			q.pop();
			cout << root->_data << " ";

			if (root->_left != NULL)
				q.push(root->_left);
			if (root->_right != NULL)
				q.push(root->_right);

		}

		cout << endl;
	}

	BinaryTree<T> & operator=(BinaryTree<T> t)
	{
		swap(_root,t._root);

		return *this;
	}

	size_t Size()  //�ڵ����
	{
		size_t count = 0;
		return _Size(_root,count);
	}

	size_t GetLeafSize()  //Ҷ�ӽڵ����,Ҷ�ڵ㣺û���ӽڵ�Ľڵ㣨��Ϊ0��
	{
		size_t count = 0;
		return _LeafSize(_root, count);
	}

	size_t GetKlevel(size_t k) //��K��ڵ������//��k��ڵ�������ڵ�K-1��ڵ�������������������֮�ͣ�
	{
		return _GetKLevel(_root,k);
	}

	~BinaryTree()
	{
		_Clear(_root);
		//_root = NULL: //? ?������һ��ͳ���
	//	printf("0x%p \n",_root);
	}
	
	Node * Find(const T & x)  //Ѱ�ҽڵ�
	{
		return  _Find(_root,x);
	}
	
	size_t Depth()  //�������,��ΪMax����������ȣ���������ȣ�+1��1Ϊ���ڵ����
	{
		return  _Depth(_root);
	}
	//�ǵݹ�ʵ��ǰ�к���

	void PrevOrderNonR()  //����һֱѹջ��ֱ������ȫѹջ���������������⣬���������ʼ���ڵ�һ���ı�����
	{
		if (_root == NULL)
			return;
		stack<Node *> s;  
		Node * cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				cout << cur->_data << " ";  //������ڵ㣻
				s.push(cur);    //���ڵ�ѹջ�����������Ա���������������� ������������
				cur = cur->_left;  //�������� ֪������ȫ�������ꣻ
			}

			Node * top = s.top();  //�������ĸ����棬ȥ��������
			s.pop();  //pop��������ڵ㣻��Ϊ������ڵ���������������������������������ȡ���丸�׽ڣ������ʸ��׽ڵ����������

			cur = top->_right;  //�����⣻ ���������͵�һ��ԭʼ���ڵ�һ��ȥ���ʣ�

		}

		cout << endl;
	}

	void InOrderNonR()
	{
		if (_root == NULL)
			return;

		stack<Node *> s;
		Node * cur = _root;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			
			Node * top = s.top();
			cout << top->_data << " ";
			s.pop();

			cur = top->_right;
		}

		cout << endl;
	}

	void PostOrderNonR()  //�������⣻
	{
		if (_root == NULL)
			return;
		stack<Node *> s;
		Node * cur = _root;
		Node * prev = NULL;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			//����
			Node * top = s.top();

			if (top->_right == NULL || top->_right == prev)   /*�����Ϊ�ջ���ڵ������������prev��˵���������ѷ��ʹ��������Է���top������������˼�������������*/
			{
				cout << top->_data << " ";
				prev = top;
				s.pop();
			}
			else
				cur = top->_right;
		}
		cout << endl;
	}
protected:
	size_t _Depth(Node * root)
	{
		if (root == NULL)
			return 0;
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);

		return left > right?left + 1 : right + 1;

	}
	//Node * _CPBT(Node * cur)  // �����_CpTree���߼�һ����Ϊʲô�������У�����������������������������
	//{
	//	Node * p = NULL:

	//	if (cur != NULL)
	//	{
	//		p = new Node(cur->_data);
	//		p->_left = _BTree(cur->_left);
	//		p->_right = _BTree(cur->_right);
	//	}

	//	return p;
	//}
	Node * _CpTree(Node * cur)  //����һ����
	{
		Node * root = NULL;

		if (cur != NULL)
		{
			root = new Node(cur->_data);
			root->_left = _CpTree(cur->_left);
			root->_right = _CpTree(cur->_right);
		}

		return root;
	}

	void _Clear(Node * root)  //���������
	{
		Node * de = root;
		if (de != NULL)
		{
			_Clear(de->_left);
			_Clear(de->_right);

			delete root;
			//root = NULL:
		}

		return;
	}

	Node * _Find(Node * root,  const T & x)
	{
		if (root == NULL)
		{
			return NULL;
		}
		

		if (root->_data == x)
		{
			return root;
		}
		
		Node * prev = _Find(root->_left,x);
		if (prev)
		{
			return prev;
		}
	
		return _Find(root->_right,x);
		
	}

	/*size_t _Size(Node * root)  //�ڵ��������
	{
		if (root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}*/
	//size_t _Size(Node * root)  //�����̰߳�ȫ���⣬��һ���򵥵����ӣ���_size�������λ�����ظ���ֵ�������ӦΪ����ջ��ͬ��count���ڶ��ϵģ��ӵ�ʱ����ظ���
	//{
	//	if (root == NULL)
	//		return 0;
	//	static int count = 0;
	//	count++;
	//	_Size(root->_left);
	//	_Size(root->_right);

	//	return count;

	//}
	size_t _Size(Node * root,size_t &count)  //�ڵ��������,��취��count����ջ�У�ÿһ��ջ���Լ�������count��
	{
		if (root == NULL)
			return 0;

		count++;

		_Size(root->_left,count);
		_Size(root->_right,count);

		return count;
	}
	size_t _LeafSize(Node * root, size_t &count) //Ҷ�ӽڵ����
	{
		if (root == NULL)
		{
			
			return 0;
		}
		
		if (root->_left == NULL && root->_right == NULL)
		{
			count++;
		}

		_LeafSize(root->_left, count);
		_LeafSize(root->_right, count);

		return count;
	}

	size_t _GetKLevel(Node * root,size_t k)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (k == 1)
		{

			return 1;
		}
		else
		{
			return _GetKLevel(root->_left, k - 1) + _GetKLevel(root->_right, k-1);
		}
	}


	Node * _CreateTree(T *a, size_t size, const T & invalue, size_t & index)
	{
		Node * root = NULL;

		if (index < size && a[index] != invalue)
		{
			root = new Node(a[index]);  //�Ƚ������ڵ�

			root->_left = _CreateTree(a,size,invalue,++index);  //ǰ����������
			root->_right = _CreateTree(a, size, invalue, ++index);  //ǰ����������
		}

		return root;  //�����������������������ڵ�Ϊ�գ�
	}

	void _PrevOrder(Node * root)
	{

		if (root != NULL)
		{
			cout << root->_data << " ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}

		return;
	}

	

	void _MidOrder(Node * root)
	{
		if (root == NULL)
			return;


		_MidOrder(root->_left);
		cout << root->_data << " ";
		_MidOrder(root->_right);


	}

	void _PostOrder(Node * root)
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}


protected:
	Node * _root;
	
};

void TestBinaryTree()
{
	int a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int b[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int> tree(a, 10, a[3]);
	tree.PrevOrder();
	tree.PrevOrderNonR();
	tree.MidOrder();
	tree.InOrderNonR();
	tree.PostOrder();
	tree.PostOrderNonR();
	tree.LevelOrder();

	BinaryTree<int> tree1(tree);
	tree1.PrevOrder();

	/*BinaryTree<int> tree2(b, 15, b[2]);  //��ֵ��������ز��Բ���
	tree2.PrevOrder();
	tree2 = tree1;
	tree2.PrevOrder();*/

	cout << tree.Size() << endl; //���Խڵ��������
	cout << tree.GetLeafSize() << endl;
	cout << tree.GetKlevel(2) << endl;

	cout << tree.Find(9)<< endl;  //���Բ���;
	cout << tree.Depth() << endl;  //���
}
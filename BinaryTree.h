#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<stdio.h>
#include<queue>
#include<stack>
using namespace std;

//二叉树链表存储表示；

template<class T>   //节点
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

	BinaryTree(T * a, size_t size, const T & invalue)  //构造一个数，需要用递归，构造函数不能用递归实现，需要有一个内部函数；
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalue,index);
	}

	BinaryTree(const BinaryTree<T> & t) //拷贝构造
	{
		//_root = _CPBT(t._root);
		_root = _CpTree(t._root);
		
	}



	void PrevOrder()  //前序遍历
	{
		_PrevOrder(_root);  //先根，前序遍历左子树，前序遍历右子树
		cout << endl;
	}

	void MidOrder()  //中序遍历
	{
		_MidOrder(_root); //中序遍历左子树 ，访问根节点，中序遍历右子树；
		cout << endl;
	}

	void PostOrder()  //后续遍历，后序遍历左子树，后序遍历 右子树，访问根节点
	{
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()  //一层一层的遍历，使用队列.每一个带一层入队列
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

	size_t Size()  //节点个数
	{
		size_t count = 0;
		return _Size(_root,count);
	}

	size_t GetLeafSize()  //叶子节点个数,叶节点：没有子节点的节点（度为0）
	{
		size_t count = 0;
		return _LeafSize(_root, count);
	}

	size_t GetKlevel(size_t k) //第K层节点个数；//第k层节点个数等于第K-1层节点左子树和右子树个数之和；
	{
		return _GetKLevel(_root,k);
	}

	~BinaryTree()
	{
		_Clear(_root);
		//_root = NULL: //? ?加上这一句就出错；
	//	printf("0x%p \n",_root);
	}
	
	Node * Find(const T & x)  //寻找节点
	{
		return  _Find(_root,x);
	}
	
	size_t Depth()  //数的深度,化为Max（左子树深度，右子树深度）+1；1为根节点深度
	{
		return  _Depth(_root);
	}
	//非递归实现前中后序

	void PrevOrderNonR()  //左树一直压栈，直到左树全压栈，右树当作子问题，右树进行最开始根节点一样的遍历；
	{
		if (_root == NULL)
			return;
		stack<Node *> s;  
		Node * cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				cout << cur->_data << " ";  //输出根节点；
				s.push(cur);    //根节点压栈保存起来，以便访问玩其左树，在 访问其右树；
				cur = cur->_left;  //访问左树 知道左树全被访问完；
			}

			Node * top = s.top();  //将左树的根保存，去访问右树
			s.pop();  //pop掉这个根节点；因为这个根节点下面访问其右子树，其右子树访问完后，取出其父亲节，并访问父亲节点的右子树；

			cur = top->_right;  //子问题； 右树看作和第一个原始根节点一样去访问；

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

	void PostOrderNonR()  //在理解理解；
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
			//左完
			Node * top = s.top();

			if (top->_right == NULL || top->_right == prev)   /*如果右为空或根节点的右子树等于prev（说明右子树已访问过），可以访问top，否则子问题思想访问右子树；*/
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
	//Node * _CPBT(Node * cur)  // 这个与_CpTree的逻辑一样，为什么不能运行；？？？？？？？？？？？？？？
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
	Node * _CpTree(Node * cur)  //拷贝一个树
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

	void _Clear(Node * root)  //后序清除，
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

	/*size_t _Size(Node * root)  //节点个数计算
	{
		if (root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}*/
	//size_t _Size(Node * root)  //存在线程安全问题，举一个简单的列子，将_size运行两次会出现重复加值得情况，应为两个栈不同但count是在堆上的，加的时候会重复加
	//{
	//	if (root == NULL)
	//		return 0;
	//	static int count = 0;
	//	count++;
	//	_Size(root->_left);
	//	_Size(root->_right);

	//	return count;

	//}
	size_t _Size(Node * root,size_t &count)  //节点个数计算,想办法将count放在栈中，每一个栈有自己独立的count；
	{
		if (root == NULL)
			return 0;

		count++;

		_Size(root->_left,count);
		_Size(root->_right,count);

		return count;
	}
	size_t _LeafSize(Node * root, size_t &count) //叶子节点个数
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
			root = new Node(a[index]);  //先建立根节点

			root->_left = _CreateTree(a,size,invalue,++index);  //前序建立左子树
			root->_right = _CreateTree(a, size, invalue, ++index);  //前序建立右子树
		}

		return root;  //返回条件，子树的子树根节点为空；
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

	/*BinaryTree<int> tree2(b, 15, b[2]);  //赋值运算符重载测试测试
	tree2.PrevOrder();
	tree2 = tree1;
	tree2.PrevOrder();*/

	cout << tree.Size() << endl; //测试节点个数计算
	cout << tree.GetLeafSize() << endl;
	cout << tree.GetKlevel(2) << endl;

	cout << tree.Find(9)<< endl;  //测试查找;
	cout << tree.Depth() << endl;  //深度
}
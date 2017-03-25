#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//大堆和小堆的建立，只是在向上调整和向下调整时，比较不同，其他代码都一样，用仿函数就可以用一份代码构造出两个堆
//仿函数;使类像函数一样使用，重载（）就可以：

template<class T>
struct Less
{
	bool operator()(const T & l, const T & r) const
	{
		return l < r;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T & l, const T & r) const
	{
		return l > r;
	}
};

template<class T, class Compare>
class Head
{
public:
	Compare comFunc;
	Head()
	{

	}
	Head(T *a,size_t n)
	{
		_a.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_a.push_back(a[i]);
		}

		int root = (_a.size() - 2) >> 1;//每个叶子节点都是一个堆，要为堆，第一个和他的左右子树为堆，必须左右的左右子树为堆，化为子问题，要从从后向前的第一个为叶子节点调整；
		while (root >= 0)
		{
			_AdjustDown(root);
			root--;
		}
	}

	void Push(const T &x)  //在堆中插入一个数，向上调整算法，只与最后一个节点到根节点上路径的节点有关，不影响其他节点；
	{
		_a.push_back(x);
		_AdjustUp(_a.size() - 1);
	}
	void Pop()
	{
		assert(!_a.empty());

		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}
	const T & GetTop() const
	{
		return _a[0];
	}

	size_t Size()
	{
		return _a.size();
	}

	bool Empty()
	{
		return _a.empty();
	}

	bool IsHeap()
	{
		int count = 0;
		int parents = (_a.size() - 2) >> 2;
		int child = parents * 2 - 1;

		while (parents >= 0)
		{
			if (child + 1 < _a.size() && _a[child] > _a[child + 1])
			{
				child++;
			}
			if (comFunc(_a[child], _a[parents]))
			{
				return false;
			}
			parents--;
		}

		return true;
	}

	void PrintHead()
	{
		for (int i = 0; i < _a.size(); ++i)
		{
			cout << _a[i] << endl;
		}
		cout << endl;
	}
	void _AdjustDown(int root)  //前提：左右子树都是大堆；
	{
		int parents = root;
		int child = parents * 2 + 1;

		while (child < _a.size()) //保证child是节点，而不是越界，
		{
			if (child + 1 < _a.size() && _a[child] < _a[child + 1])
				child++;

			if (comFunc(_a[child], _a[parents]))
			{
				swap(_a[child], _a[parents]);
				parents = child;
				child = parents * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
protected:
	

	void _AdjustUp(int child)
	{
		int parents = (child - 1) >> 2;

		while (child > 0)
		{
			if (comFunc(_a[child] , _a[parents]))
			{
				swap(_a[child],_a[parents]);
				child = parents;
				parents = (child - 1) >> 1;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};

//void TestHead()
//{
//	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
//	Head<int> head(a,sizeof(a)/sizeof(a[0]));
//	cout << head.IsHeap() << endl;
//	cout << head.Empty() << endl;
//	cout << head.GetTop() << endl;
//	head.Pop();
//	cout << head.Empty() << endl;
//	cout << head.GetTop() << endl;
//}

void TestHead()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Head<int, Greater<int>> head(a, sizeof(a) / sizeof(a[0]));
	cout << head.GetTop() << endl;

	Head<int, Less<int>> head1(a, sizeof(a) / sizeof(a[0]));
	cout << head1.GetTop() << endl;

}

////优先级队列  容器适配器
//
//template<class T, class Compare = Less<T>>
//class PriorityQueue
//{
//public:
//	void Push(const T & x)
//	{
//		_hp.Push(x);
//	}
//
//	void Pop()
//	{
//		_hp.Pop();
//	}
//	
//	const T & Top()
//	{
//		return _hp.GetTop();
//	}
//
//	size_t Size()
//	{
//		return _hp.Size();
//	}
//protected:
//	Head<T, Compare> _hp;
//};
//
//
////测试优先级队列，用库中的优先级队列测试；
//#include<queue>
//void TestPriorityQueue()
//{
//	int  a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
//	priority_queue<int> pq;
//
//	
//	for (size_t i = 0; i < 10; ++i)
//	{
//		pq.push(a[i]);
//	}
//}

//海量数据处理TopK 

void AdjustDown(int * head,int k,int parents)  ///小堆
{
	int child = parents * 2 + 1;
	

	while (child < k)
	{
		if (child + 1 < k && head[child] > head[child + 1])
		{
			child++;
		}

		if (head[child] < head[parents])
		{
			swap(head[child], head[parents]);
			parents = child;
			child = parents * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void TopK(int *a, int n, int k)
{
	int *head = new int[k];
	for (int i = 0; i < k; i++)
	{
		head[i] = a[i];
	}

	//调整这个堆；
	for (int i = (k - 2)/2; i >= 0;i--)
	{
		AdjustDown(head,k,i);
	}

	for (int i = k; i < n; i++)
	{
		if (a[i] > head[0])
		{
			head[0] = a[i];
			AdjustDown(head,k,0);
		}
	}

	for (int j = 0; j < k; j++)
	{
		cout << head[j] << " ";
	}
	cout << endl;

	delete[] head;
}

//堆排序
void AdjustDownS(int *head,int n, int parents) //小堆
{
	int child = parents * 2 + 1;
	if (child + 1 < n && head[child] < head[child + 1])
	{
		child++;
	}

	while (child < n)
	{
		if (head[child] > head[parents])
		{
			swap(head[child], head[parents]);
			parents = child;
			child = parents * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeadSort(int *head,int n) //降序，建小堆
{
	assert(head);
	int i = (n - 2) / 2; //找到最后一个非叶子节点;
	for (; i >= 0; i--) //调整成小堆
	{
		AdjustDown(head,n,i);
	}

	for (int j = n - 1; j >= 0;j--)  //和最后一个交换，去掉最后一个，再进行堆排序，依次类推；
	{
		swap(head[0],head[j]);
		AdjustDown(head,j,0);
	}
}

void HeadSortOrder(int *head,int n)  //升序，建大堆；
{
	assert(head);
	int i = (n - 2) / 2;
	for (; i >= 0; i--)//调整成大堆
	{
		AdjustDownS(head,n,i);
	}

	for (int j = n - 1 ; j >= 0; j--)
	{
		swap(head[0],head[j]);
		AdjustDownS(head,j,0);
	}
}

void TestHeadSort() //测试堆排序
{
	int a[10] = {1,5,3,2,9,9,6,11,25,30};
	HeadSort(a,10);

	for (int i = 0; i < 10;i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	HeadSortOrder(a, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

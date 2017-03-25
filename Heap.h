#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//��Ѻ�С�ѵĽ�����ֻ�������ϵ��������µ���ʱ���Ƚϲ�ͬ���������붼һ�����÷º����Ϳ�����һ�ݴ��빹���������
//�º���;ʹ������һ��ʹ�ã����أ����Ϳ��ԣ�

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

		int root = (_a.size() - 2) >> 1;//ÿ��Ҷ�ӽڵ㶼��һ���ѣ�ҪΪ�ѣ���һ����������������Ϊ�ѣ��������ҵ���������Ϊ�ѣ���Ϊ�����⣬Ҫ�ӴӺ���ǰ�ĵ�һ��ΪҶ�ӽڵ������
		while (root >= 0)
		{
			_AdjustDown(root);
			root--;
		}
	}

	void Push(const T &x)  //�ڶ��в���һ���������ϵ����㷨��ֻ�����һ���ڵ㵽���ڵ���·���Ľڵ��йأ���Ӱ�������ڵ㣻
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
	void _AdjustDown(int root)  //ǰ�᣺�����������Ǵ�ѣ�
	{
		int parents = root;
		int child = parents * 2 + 1;

		while (child < _a.size()) //��֤child�ǽڵ㣬������Խ�磬
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

////���ȼ�����  ����������
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
////�������ȼ����У��ÿ��е����ȼ����в��ԣ�
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

//�������ݴ���TopK 

void AdjustDown(int * head,int k,int parents)  ///С��
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

	//��������ѣ�
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

//������
void AdjustDownS(int *head,int n, int parents) //С��
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
void HeadSort(int *head,int n) //���򣬽�С��
{
	assert(head);
	int i = (n - 2) / 2; //�ҵ����һ����Ҷ�ӽڵ�;
	for (; i >= 0; i--) //������С��
	{
		AdjustDown(head,n,i);
	}

	for (int j = n - 1; j >= 0;j--)  //�����һ��������ȥ�����һ�����ٽ��ж������������ƣ�
	{
		swap(head[0],head[j]);
		AdjustDown(head,j,0);
	}
}

void HeadSortOrder(int *head,int n)  //���򣬽���ѣ�
{
	assert(head);
	int i = (n - 2) / 2;
	for (; i >= 0; i--)//�����ɴ��
	{
		AdjustDownS(head,n,i);
	}

	for (int j = n - 1 ; j >= 0; j--)
	{
		swap(head[0],head[j]);
		AdjustDownS(head,j,0);
	}
}

void TestHeadSort() //���Զ�����
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

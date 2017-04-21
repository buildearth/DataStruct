#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<stack>
using namespace std;
//两个栈实现队列
template<class T>
class CQueue
{
public:
	

	void AppendTail(const T &node)
	{
		_stackIn.push(node);
	}

	T DeleteHead()
	{
		if (_stackOut.empty())
		{
			if (_stackIn.empty())
			{
				return T();
			}

			while (!(_stackIn.empty()))
			{
				_stackOut.push(_stackIn.top());
				_stackIn.pop();
			}
		}
		
		if (_stackOut.empty())
		{
			return T();
		}

		T tmp = _stackOut.top();
		_stackOut.pop();
		return tmp;

	}

protected:
	stack<T> _stackIn;
	stack<T> _stackOut;
};

void TestCQueue()
{
	CQueue<int> cq;
	cq.AppendTail(1);
	cq.DeleteHead();
	cq.DeleteHead();
	cq.AppendTail(2);
	cq.AppendTail(3);
	cq.DeleteHead();
	cq.AppendTail(4);
	cq.AppendTail(5);
	cq.DeleteHead();

}
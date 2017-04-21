#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<queue>
using namespace std;
//两个队列实现栈

template<class T>
class CStack
{
public:
	void Push(const T &node)
	{
		if (_queue2.empty())
			_queue1.push(node);
		else
			_queue2.push(node);
	}

	void Pop()
	{
		if (_queue1.empty())  //队列1为空，把队列2中数据导入1，并删除最后一个数据；
		{
			while (!(_queue2.empty()))
			{
				if (_queue2.size() == 1)
				{
					_queue2.pop();
					break;
				}

				_queue1.push(_queue2.front());
				_queue2.pop();			
			}
		}
		else if (_queue2.empty())
		{
			while (!(_queue1.empty()))
			{
				if (_queue1.size() == 1)
				{
					_queue1.pop();
					break;
				}

				_queue2.push(_queue1.front());
				_queue1.pop();
			}
		}
		else //两个队列均为空
		{
			return;
		}
	}
protected:
	queue<T> _queue1;
	queue<T> _queue2;
};

void TestCStack()
{
	CStack<int> cs;
	cs.Pop();
	cs.Push(1);
	cs.Push(2);
	cs.Push(3);
	cs.Pop();
	cs.Push(5);
	cs.Push(6);
	cs.Pop();
}
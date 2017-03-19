#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>

#include<assert.h>
#include<stack>
#include<queue>
using namespace std;

//栈的应用，逆波兰表达式（RPN）的求解；

//enum Type   //枚举
//{
//	OP_SYMNOL,   //操作符
//	OP_NUM,      //操作数
//	ADD,		//加
//	SUB,		//减
//	MUL,		//乘
//	DIV,		//除
//};
//
//struct Cell
//{
//	Type _type; //所取数的类型
//	int _value;  //所取值
//};

//int CountRPN(Cell rpn[],size_t n)
//{
//	stack<int> s;   //数的压栈
//
//	for (size_t i = 0; i < n; i++)
//	{
//		if (rpn[i]._type == OP_NUM)  //先判断是否为操作数，是压栈保存；
//		{
//			s.push(rpn[i]._value);
//		}
//		else if (rpn[i]._type == OP_SYMNOL)
//		{
//			int right = s.top();  //注意第一个出来的数是运算符右侧的值；
//			s.pop();
//			int left = s.top();   // 第二个出来的是运算符左侧的运算数；
//			s.pop();
//
//			//求解
//			switch (rpn[i]._value)
//			{
//			case ADD:
//				s.push(left + right);
//				break;
//			case SUB:
//				s.push(left - right);
//				break;
//
//			case MUL:
//				s.push(left * right);
//				break;
//
//			case DIV:
//				s.push(left / right);
//				break;
//
//			default:
//				cout << "无效值" << endl;
//			}
//
//
//		}
//	}
//
//	return s.top();
//}



//中缀 表达式转后缀 表达式
/*
左括号“（”的栈外优先级最高，他一来到立即进栈，，但当他进栈后栈内优先级数变得最低，便于括号内其他操作符进栈，其他操作符进栈后优先级数都升1；这样
可以体现在中缀表达式中相同优先级的操作符自左向右计算的要求；

当前操作符优先级数大于等于栈顶操作符优先级数，刚扫面的进栈

小于的时候，栈顶操作符出栈；一直与栈顶比较，知道遇到大于栈顶的操作符，将当前操作符压栈；
*/
int Isp(char ch) //获取操作符进栈后优先数
{
	switch (ch)
	{
	case '#':
		return 0;
	case '(':
		return 1;

	case '+':
	case '-':
		return 3;

	case '*':
	case '/':
		return 5;

	case ')':
		return 8;
	default:
	{
		cout << "没有找到此操作符" << endl;
		return -1;
	}
	}
}

int Icp(char ch) //获取当前扫描到操作符的优先级数
{
	switch (ch)
	{
	case '#':
		return 0;
	case '(':
		return 8;

	case '+':
	case '-':
		return 2;

	case '*':
	case '/':
		return 4;

	case ')':
		return 1;
	default:
	{
		cout << "没有找到此操作符" << endl;
		return -1;
	}
	}
}


//void TestCountRPN()  //测试CountRPN(Cell rpn[],size_t n)；
//{
//	Cell array[] =
//	{
//		{ OP_NUM, 12 },
//		{ OP_NUM, 3 },
//		{ OP_NUM, 4 },
//		{ OP_SYMNOL, ADD },
//		{ OP_SYMNOL, MUL },
//		{ OP_NUM, 6 },
//		{ OP_SYMNOL, SUB },
//		{ OP_NUM, 8 },
//		{ OP_NUM, 2 },
//		{ OP_SYMNOL, DIV },
//		{ OP_SYMNOL, ADD },
//	};
//	size_t len = sizeof(array) / sizeof(array[0]);
//	cout << CountRPN (array,len)<< endl;

//}

//void postfix()  //中缀 表达式转后缀 输出到标准输出；
//{
//	stack<char> s;
//	char ch, y;
//	s.push('#');
//	cin.get(ch);
//	while (ch != '\n')
//	{
//		if (isdigit(ch))
//			cout << ch;
//		else if (ch == ')')
//		{
//
//			for (y = s.top(); y != '('; y = s.top())
//			{
//				s.pop();
//				cout << y;
//				
//			}
//			s.pop(); //pop出左括号;
//
//			/*for (y = s.top(); Isp(y) > Icp(ch); y = s.top())
//			{
//				s.pop();
//				cout << y;
//			}*/
//
//		}
//		else
//		{
//			y = s.top();
//			if (Isp(y) <= Icp(ch))
//			{
//				s.push(ch);
//			}
//			else
//			{
//				for (; Isp(y) > Icp(ch);y = s.top())
//				{
//					cout << y;
//					s.pop();
//				}
//
//				s.push(ch);
//				
//			}
//		}
//		cin.get(ch);
//	}
//
//	while (!s.empty())
//	{
//		y = s.top();
//		cout << y;
//		s.pop();
//
//	}
//
//	cout << endl;
//}
//
////计算从标准输入获得的后缀表达式；
//void DoOperator(stack<int> s, char ch)
//{
//	int right = s.top();
//	s.pop();
//
//	int left = s.top();
//	s.pop();
//
//	switch (ch)
//	{
//	case '+':
//		s.push(left + right);
//		break;
//	case '-':
//		s.push(left - right);
//		break;
//	case '*':
//		s.push(left * right);
//		break;
//	case '/':
//		s.push(left / right);
//		break;
//	default:
//		break;
//
//	}
//
//}
//
//int CountRPN()
//{
//	char ch;
//	int num;
//	stack<int> s;
//
//	for (cin.get(ch); ch != '#'&& ch != '\n'; cin.get(ch))
//	{
//		switch (ch)
//		{
//		case '+':
//		case '-':
//		case '*':
//		case '/':
//			DoOperator(s,ch);
//			break;
//
//		default:  //操作数
//			cin.putback(ch);
//			cin >> num;
//			s.push(num);
//
//		}
//	}
//
//	return s.top();
//}
//
//void TestCountRPN()  //测试：计算从标准输入获得的后缀表达式；
//{
//	postfix();
//	//cout << "表达式值为：" << CountRPN() << endl;
//}

//从标准输入得到表达式，转后缀并存入 队列

//void Testq(queue<int> &q)  //测试队列中的值是否是真确的后缀表达式（打印队列）
//{
//	while (!q.empty())
//	{
//		int  ch = q.front();
//		switch (ch)
//		{
//		case '+':
//			cout << '+';
//			q.pop();
//			break;
//		case '-':
//			cout << '-';
//			q.pop();
//			break;
//		case '*':
//			cout << '*';
//			q.pop();
//			break;
//		case '/':
//			cout << '/';
//			q.pop();
//			break;
//		case '#':
//			cout << '#';
//			q.pop();
//			break;
//		default:
//			cout << q.front() << " ";
//			q.pop();
//			break;
//
//		}
//	}
//}
//计算队列中的后缀表达式；
void PostFix(queue<int> &q)  //中缀 表达式转后缀 输出到队列；
{
	stack<char> s;
	char ch, y;
	int num;
	s.push('#');
	cin.get(ch);
	while (ch != '\n')
	{
		if (isdigit(ch))
		{
			
			cin.putback(ch);  //还给标准输入
			cin >> num;  //取出数字
			q.push(num);
		}
		else if (ch == ')')
		{

			for (y = s.top(); y != '('; y = s.top())  //若为右括号直接将栈中内容弹出知道遇到左括号为止；
			{
				s.pop();
				
				q.push(y);
				
			}
			s.pop(); //pop出左括号;

			

		}
		else
		{
			y = s.top();
			if (Isp(y) <= Icp(ch))  //栈内优先级小于当前优先级，入栈
			{
				s.push(ch);
			}
			else
			{
				for (; Isp(y) > Icp(ch);y = s.top())   //栈内大于当前出栈，近队列
				{
					
					q.push(y);
					s.pop();
				}

				s.push(ch);  //遇到栈内优先级小于当前ch优先级，将ch入栈；
				
			}
		}
		cin.get(ch);
	}

	while (!s.empty()) //将栈中内容出栈依次放到队列；
	{
		y = s.top();
		
		q.push(y);
		s.pop();

	}

	
}


void DoOperator(stack<int> &s, char ch)  //
{
		int right = s.top();
		s.pop();
	
		int left = s.top();
		s.pop();
	
		switch (ch)
		{
		case '+':
			s.push(left + right);
			break;
		case '-':
			s.push(left - right);
			break;
		case '*':
			s.push(left * right);
			break;
		case '/':
			s.push(left / right);
			break;
		default:
			break;
	
		}
}
int CountRPN(queue<int> &q)  //计算队列中存储的后缀表达式
{
	stack<int> s; //保存操作数，计算结果；
	int ch = q.front();

	while (!q.empty() && ch != '#')
	{
		switch (ch)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			DoOperator(s, ch);  //做运算
			break;
		default:
			s.push(ch);
			break;
		}

		q.pop();
		ch = q.front();
	}

	return s.top();
}
void TestCountRPN()
{
	queue<int> q;
	PostFix(q);
	cout << CountRPN(q) << endl;
}
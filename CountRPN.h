#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>

#include<assert.h>
#include<stack>
#include<queue>
using namespace std;

//ջ��Ӧ�ã��沨�����ʽ��RPN������⣻

//enum Type   //ö��
//{
//	OP_SYMNOL,   //������
//	OP_NUM,      //������
//	ADD,		//��
//	SUB,		//��
//	MUL,		//��
//	DIV,		//��
//};
//
//struct Cell
//{
//	Type _type; //��ȡ��������
//	int _value;  //��ȡֵ
//};

//int CountRPN(Cell rpn[],size_t n)
//{
//	stack<int> s;   //����ѹջ
//
//	for (size_t i = 0; i < n; i++)
//	{
//		if (rpn[i]._type == OP_NUM)  //���ж��Ƿ�Ϊ����������ѹջ���棻
//		{
//			s.push(rpn[i]._value);
//		}
//		else if (rpn[i]._type == OP_SYMNOL)
//		{
//			int right = s.top();  //ע���һ������������������Ҳ��ֵ��
//			s.pop();
//			int left = s.top();   // �ڶ����������������������������
//			s.pop();
//
//			//���
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
//				cout << "��Чֵ" << endl;
//			}
//
//
//		}
//	}
//
//	return s.top();
//}



//��׺ ���ʽת��׺ ���ʽ
/*
�����š�������ջ�����ȼ���ߣ���һ����������ջ������������ջ��ջ�����ȼ��������ͣ�����������������������ջ��������������ջ�����ȼ�������1������
������������׺���ʽ����ͬ���ȼ��Ĳ������������Ҽ����Ҫ��

��ǰ���������ȼ������ڵ���ջ�����������ȼ�������ɨ��Ľ�ջ

С�ڵ�ʱ��ջ����������ջ��һֱ��ջ���Ƚϣ�֪����������ջ���Ĳ�����������ǰ������ѹջ��
*/
int Isp(char ch) //��ȡ��������ջ��������
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
		cout << "û���ҵ��˲�����" << endl;
		return -1;
	}
	}
}

int Icp(char ch) //��ȡ��ǰɨ�赽�����������ȼ���
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
		cout << "û���ҵ��˲�����" << endl;
		return -1;
	}
	}
}


//void TestCountRPN()  //����CountRPN(Cell rpn[],size_t n)��
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

//void postfix()  //��׺ ���ʽת��׺ �������׼�����
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
//			s.pop(); //pop��������;
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
////����ӱ�׼�����õĺ�׺���ʽ��
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
//		default:  //������
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
//void TestCountRPN()  //���ԣ�����ӱ�׼�����õĺ�׺���ʽ��
//{
//	postfix();
//	//cout << "���ʽֵΪ��" << CountRPN() << endl;
//}

//�ӱ�׼����õ����ʽ��ת��׺������ ����

//void Testq(queue<int> &q)  //���Զ����е�ֵ�Ƿ�����ȷ�ĺ�׺���ʽ����ӡ���У�
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
//��������еĺ�׺���ʽ��
void PostFix(queue<int> &q)  //��׺ ���ʽת��׺ ��������У�
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
			
			cin.putback(ch);  //������׼����
			cin >> num;  //ȡ������
			q.push(num);
		}
		else if (ch == ')')
		{

			for (y = s.top(); y != '('; y = s.top())  //��Ϊ������ֱ�ӽ�ջ�����ݵ���֪������������Ϊֹ��
			{
				s.pop();
				
				q.push(y);
				
			}
			s.pop(); //pop��������;

			

		}
		else
		{
			y = s.top();
			if (Isp(y) <= Icp(ch))  //ջ�����ȼ�С�ڵ�ǰ���ȼ�����ջ
			{
				s.push(ch);
			}
			else
			{
				for (; Isp(y) > Icp(ch);y = s.top())   //ջ�ڴ��ڵ�ǰ��ջ��������
				{
					
					q.push(y);
					s.pop();
				}

				s.push(ch);  //����ջ�����ȼ�С�ڵ�ǰch���ȼ�����ch��ջ��
				
			}
		}
		cin.get(ch);
	}

	while (!s.empty()) //��ջ�����ݳ�ջ���ηŵ����У�
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
int CountRPN(queue<int> &q)  //��������д洢�ĺ�׺���ʽ
{
	stack<int> s; //�������������������
	int ch = q.front();

	while (!q.empty() && ch != '#')
	{
		switch (ch)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			DoOperator(s, ch);  //������
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
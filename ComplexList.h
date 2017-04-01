#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
/*¸´ÔÓÁ´±íµÄ¸´ÖÆ*/

struct Node
{
	int _x;
	Node * _next;
	Node * _random;

	Node(int x)
		:_x(x)
		, _next(NULL)
		, _random(NULL)
	{}
};

Node * ComplexList()
{
	Node *node1 = new Node(1);
	Node *node2 = new Node(2);
	Node *node3 = new Node(3);
	Node *node4 = new Node(4);
	Node *node5 = new Node(5);

	node1->_next = node2;
	node2->_next = node3;
	node3->_next = node4;
	node4->_next = node5;

	node1->_random = node4;
	node4->_random = node5;
	node3->_random = node2;
	return node1;
}

void CopyNode(Node *&head)
{
	Node *cur = head;
	Node *tmp = NULL;

	while (cur)
	{
		tmp = new Node(cur->_x);
		tmp->_next = cur->_next;
		tmp->_random = cur->_random;
		cur->_next = tmp;

		cur = tmp->_next;
	}
}

Node * ObtainNode(Node *&head)
{
	Node * Nhead = NULL;
	Node *NNode = NULL;
	Node *cur = head;
	Node *prev = NULL;
	
	if (head != NULL)
	{
		Nhead = head->_next;
		head->_next = Nhead->_next;
		cur = head->_next;
		NNode = Nhead;
	}

	while (cur)
	{
		NNode->_next = cur->_next;
		cur = NNode->_next;
		NNode = NNode->_next;
	}

	return Nhead;
}

void Destroy()
{

}

void TestCp()
{
	Node * head1 = ComplexList();
	CopyNode(head1);
	Node *head2 = ObtainNode(head1);
}
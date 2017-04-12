#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
using namespace std;

struct BinaryTreeNode
{
	int _value;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;

	BinaryTreeNode(const int value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
	{

	}
};

typedef BinaryTreeNode Node;


BinaryTreeNode * ConstructCore(int *startPrevOrder, int *endPrevOrder,
	int *startInOrder, int *endInOrder)
{
	int value = startPrevOrder[0];
	Node *root = new Node(value);


	if (startPrevOrder == endPrevOrder)
	{
		if (startInOrder == endInOrder && *startPrevOrder == *startInOrder)
		{
			return root;
		}
		else
		{
			cout << "遍历有错" << endl;
			return NULL;
		}
	}

	//在中序中找根节点
	int *rootInOder = startInOrder;
	while (rootInOder <= endInOrder)
	{
		if (*rootInOder == value)
		{
			break;
		}
		++rootInOder;
	}

	if (rootInOder == endInOrder && *rootInOder != value)
	{
		cout << "序列出错" << endl;
		return NULL;
	}
	int leftLength = rootInOder - startInOrder;
	if (leftLength > 0)
	{
		root->_left = ConstructCore(startPrevOrder + 1, startPrevOrder + leftLength, startInOrder, rootInOder - 1);
	}
	if (leftLength < (endPrevOrder - startPrevOrder))
	{
		root->_right = ConstructCore(startPrevOrder + leftLength + 1, endPrevOrder, rootInOder + 1, endInOrder);
	}

	return root;

}

Node *Construct(int *prevOrder, int *InOrder, int len)
{
	if (prevOrder == NULL || InOrder == NULL || len < 0)
		return NULL;

	return ConstructCore(prevOrder, prevOrder + len -1, InOrder, InOrder + len -1);
}

void InOrder(Node *root)
{
	if (root == NULL)
	{
		return;
	}

	InOrder(root->_left);
	cout << root->_value << " ";
	InOrder(root->_right);
}



void TestReBuild()
{

	int prev[] = {1,2,4,7,3,5,6,8};
	int In[] = {4,7,2,1,5,3,8,6};
	Node *root = Construct(prev, In, 8);
	InOrder(root);
}
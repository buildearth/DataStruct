#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>

#include<assert.h>
#include<stack>
using namespace std;


/* //�� �ļ��еĸ�ʽ
8 9
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
0 0 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1 1
1 1 0 1 0 0 0 0 1
1 1 0 1 0 1 1 0 1
1 1 0 0 0 0 0 0 1
1 1 0 1 1 0 1 0 1

*/
void InitMaze(int ** maze, FILE * fp, int row, int col)  //��ʼ���Թ�
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col;)
		{
			char ch = fgetc(fp);
			if (ch == '1' || ch == '0')
			{
				maze[i][j] = ch - '0';
				j++;
			}
		}
	}
}

bool CheckAccess(int **maze, int row, int col, Pos cur, Pos next)  //���next���λ���Ƿ��ͨ
{
	if (next._row >= 0 && next._row < row
		&& next._col >= 0 && next._col < col)  //�ж��Ƿ����Թ����귶Χ�ڣ��Է�Խ��
	{
		if (maze[cur._row][cur._col] < maze[next._row][next._col] || maze[next._row][next._col] == 0)  
		{
			return true;
		}
	}

	return false;
} 

bool GetMazePath(int **maze,int row,int col, stack<Pos>& path,stack<Pos> & shortPath,Pos cur)
{
	path.push(cur);

	if (cur._row == row - 1)
	{
		if (shortPath.empty() || shortPath.size() > path.size())   //��ȡ���·��
		{
			shortPath = path;
		}
	}

	Pos next = cur;

	//��
	next._row--;
	if (CheckAccess(maze,row,col,cur,next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;   //���߹���·���б�ǣ���Ƿ���Ϊ�߹���·���ε�����
		if (GetMazePath(maze,row,col,path,shortPath,next))
		{
			return true;
		}
	}

	//��
	next = cur;
	next._col++;
	if (CheckAccess(maze, row, col, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		if (GetMazePath(maze, row, col, path, shortPath, next))
		{
			return true;
		}
	}

	//��
	next = cur;
	next._row++;
	if (CheckAccess(maze, row, col, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		if (GetMazePath(maze, row, col, path, shortPath, next))
		{
			return true;
		}
	}

	//��
	next = cur;
	next._col--;
	if (CheckAccess(maze, row, col, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		if (GetMazePath(maze, row, col, path, shortPath, next))
		{
			return true;
		}
	}

	path.pop();

	return false;
}

void ReleaseMaze(int **maze,int row)  //�ͷſռ�
{
	for (int i = 0; i < row; i++)
	{
		delete[] maze[i];
		maze[i] = NULL;
	}

	delete [] maze;
	maze = NULL;
}

void DisPlay(int **maze, int row, int col)   //��ӡ�Թ�
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col;j++)
		{
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

void PrintShortPath(stack<Pos> & cur, int row)  //��ӡ���·��
{
	if (cur.empty())
	{
		return;
	}
	Pos tmp(cur.top());
	cur.pop();
	PrintShortPath(cur,row);

	if (tmp._row == row - 1) //��ӡ·��
	{
		cout << "(" << tmp._row << "," << tmp._col << ")" << endl;;
	}
	else
	{
		cout << "(" << tmp._row << "," << tmp._col << ")" << "-->";
	}

}

void TestMazePath()
{
	int **maze = NULL;   //c++����̬���ٶ�ά����
	FILE * file = fopen("MazeMap.txt", "r");
	assert(file);
	
	int a[2]; //a[0]�У�a[1] �У�
	for (int i = 0; i < 2; i++)
	{
		fscanf(file,"%d",&a[i]); //��ȡ����ֵ��
	}
	
	cout << a[0] << " " << a[1] << endl;
	char ch = fgetc(file);

	while (ch != '\n') //�����һ��ʣ���ַ���
		;


	//��̬���ٶ�ά���飻
	maze = new int *[a[0]];    

	for (int i = 0; i < a[0]; i++)
	{
		maze[i] = new int[a[1]];
	}

	InitMaze(maze,file,a[0],a[1]); //��ʼ����ά���飻
	DisPlay(maze,a[0],a[1]);

	//ȡ��ʼλ��
	Pos entry;
	entry._row = 2;
	entry._col = 0;

	stack<Pos> path;  //����·��
	stack<Pos> shortPath;  //���·��

	GetMazePath(maze,a[0], a[1], path, shortPath, entry); //������·��
	DisPlay(maze, a[0],a[1]);

	cout << "���·��:" << endl;
	PrintShortPath(shortPath, a[0]);
	
	ReleaseMaze(maze, a[0]);  //new�ڶ��Ͽ��ٿռ䣬����delete�ͷţ���Ȼ�����ڴ�й©��
}
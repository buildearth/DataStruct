#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>

#include<assert.h>
#include<stack>
using namespace std;


/* //在 文件中的格式
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
void InitMaze(int ** maze, FILE * fp, int row, int col)  //初始化迷宫
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

bool CheckAccess(int **maze, int row, int col, Pos cur, Pos next)  //检查next这个位置是否可通
{
	if (next._row >= 0 && next._row < row
		&& next._col >= 0 && next._col < col)  //判断是否在迷宫坐标范围内，以防越界
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
		if (shortPath.empty() || shortPath.size() > path.size())   //获取最短路径
		{
			shortPath = path;
		}
	}

	Pos next = cur;

	//上
	next._row--;
	if (CheckAccess(maze,row,col,cur,next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;   //将走过的路进行标记，标记方法为走过的路依次递增；
		if (GetMazePath(maze,row,col,path,shortPath,next))
		{
			return true;
		}
	}

	//右
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

	//下
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

	//左
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

void ReleaseMaze(int **maze,int row)  //释放空间
{
	for (int i = 0; i < row; i++)
	{
		delete[] maze[i];
		maze[i] = NULL;
	}

	delete [] maze;
	maze = NULL;
}

void DisPlay(int **maze, int row, int col)   //打印迷宫
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

void PrintShortPath(stack<Pos> & cur, int row)  //打印最短路径
{
	if (cur.empty())
	{
		return;
	}
	Pos tmp(cur.top());
	cur.pop();
	PrintShortPath(cur,row);

	if (tmp._row == row - 1) //打印路径
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
	int **maze = NULL;   //c++法动态开辟二维数组
	FILE * file = fopen("MazeMap.txt", "r");
	assert(file);
	
	int a[2]; //a[0]行；a[1] 列；
	for (int i = 0; i < 2; i++)
	{
		fscanf(file,"%d",&a[i]); //获取行列值；
	}
	
	cout << a[0] << " " << a[1] << endl;
	char ch = fgetc(file);

	while (ch != '\n') //清除第一行剩余字符；
		;


	//动态开辟二维数组；
	maze = new int *[a[0]];    

	for (int i = 0; i < a[0]; i++)
	{
		maze[i] = new int[a[1]];
	}

	InitMaze(maze,file,a[0],a[1]); //初始化二维数组；
	DisPlay(maze,a[0],a[1]);

	//取起始位置
	Pos entry;
	entry._row = 2;
	entry._col = 0;

	stack<Pos> path;  //所有路径
	stack<Pos> shortPath;  //最短路径

	GetMazePath(maze,a[0], a[1], path, shortPath, entry); //获得最短路径
	DisPlay(maze, a[0],a[1]);

	cout << "最短路径:" << endl;
	PrintShortPath(shortPath, a[0]);
	
	ReleaseMaze(maze, a[0]);  //new在堆上开辟空间，必须delete释放，不然出现内存泄漏；
}
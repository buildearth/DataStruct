#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
using namespace std;

//对称矩阵的压缩存储，只存储上三角或者下三角的数据，最多存储n*(n+)/2个数据；
//template<class T>
//class SymmetricMatrix
//{
//public:
//	SymmetricMatrix(T * a, size_t N)  //也可以使用非类型的类模板参数：template<class T,size_t N>  例子：SymmetricMatrix<int,20> sm;
//		:_N(N)
//	{
//		_matrix = new T[N*(N+1)/2];
//		size_t index = 0;
//
//		for (size_t i = 0; i < N; ++i)
//		{
//			for (size_t j = 0; j < N; ++j)
//			{
//				if (i >= j)
//				{
//					_matrix[index] = a[i*N + j]; //将二维数组转成只存储下三角的一维数组；
//					++index;
//				}
//			}
//		}
//	}
//
//	~SymmetricMatrix()
//	{
//		delete[]_matrix;
//		_N = 0;
//	}
//	const T& Access(size_t i, size_t j) const  //获取(i,j)位置的值
//	{
//		if (i < j)
//			swap(i, j);                      //若找上三角的数据，转到下三角去找；
//
//		return _matrix[i*(i + 1) / 2 + j];
//	}
//	void Display()
//	{
//		for (size_t i = 0; i < _N; ++i)
//		{
//			for (size_t j = 0; j < _N; ++j)
//			{
//				cout << Access(i, j) << " ";
//			}
//			cout << endl;
//		}
//	}
//
//protected:
//	T * _matrix; //压缩存储的一维数组
//	size_t _N;   //N*N矩阵
//};


template<class T,size_t N>  //使用非类型的类模板参数
class SymmetricMatrix
{
public:
	SymmetricMatrix(int a[][N])
	{
		_matrix = new T[N*(N+1)/2];
		size_t index = 0;

		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				if (i >= j) // 下三角压缩存储
				{
					_matrix[index] = a[i][j];
					index++;
				}
			}
		}
	}

	~SymmetricMatrix()
	{
		delete[] _matrix;
	
	}
	
	T& Access(size_t i, size_t j)
	{
		if (i < j)
		{
			swap(i,j);
		}

		return _matrix[i*(i+1)/2 + j];
	}

	void DisPlay()
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				cout << Access(i, j) << " ";
			}

			cout << endl;
		}
	}

protected:
	T * _matrix; //存储压缩之后的对称矩阵


};

void SMTest()  //测试压缩对称矩阵
{
	int a[5][5] = {
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 },
	};
	/*SymmetricMatrix<int> sm((int*)a, 5);
	sm.Display();*/
	SymmetricMatrix<int, 5> sm(a);
	sm.DisPlay();
}


#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<vector>
using namespace std;

//�Գƾ����ѹ���洢��ֻ�洢�����ǻ��������ǵ����ݣ����洢n*(n+)/2�����ݣ�
//template<class T>
//class SymmetricMatrix
//{
//public:
//	SymmetricMatrix(T * a, size_t N)  //Ҳ����ʹ�÷����͵���ģ�������template<class T,size_t N>  ���ӣ�SymmetricMatrix<int,20> sm;
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
//					_matrix[index] = a[i*N + j]; //����ά����ת��ֻ�洢�����ǵ�һά���飻
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
//	const T& Access(size_t i, size_t j) const  //��ȡ(i,j)λ�õ�ֵ
//	{
//		if (i < j)
//			swap(i, j);                      //���������ǵ����ݣ�ת��������ȥ�ң�
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
//	T * _matrix; //ѹ���洢��һά����
//	size_t _N;   //N*N����
//};


template<class T,size_t N>  //ʹ�÷����͵���ģ�����
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
				if (i >= j) // ������ѹ���洢
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
	T * _matrix; //�洢ѹ��֮��ĶԳƾ���


};

void SMTest()  //����ѹ���Գƾ���
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


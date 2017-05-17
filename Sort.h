#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<assert.h>
#include<time.h>
using namespace std;
/*ֱ�Ӳ�������*/
void SortInsert(int *arr, int length)
{
	assert(arr);
	if (length <= 1)   //����ֻ��һ��Ԫ�ز���Ҫ����
	{
		return;
	}
	int index = 0;
	while (index < length - 1)
	{
		int end = index;
		int x = arr[end + 1];
		for (int i = end; end >= 0;)
		{
			if (arr[end] > x)
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
			{
				break;
			}
		}

		//break,���� x������end����һ��λ��
		//forѭ���������,��ʱend = -1��x������0���λ�ã�Ҳ����end+1���λ�ã�
		arr[end + 1] = x;
		index++;
	}
}

void PrintArray(int arr[], int length)
{
	assert(arr);
	for (int i = 0; i < length; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
/*ϣ������*/
void SortShell(int arr[], int length)
{
	assert(arr);
	int gap = length;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < length - gap; i++)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end] > tmp)
				{  
					arr[end + gap] = arr[end];
					end = end - gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = tmp;
		}
	}

}
/*ѡ������:һ��ѡ��������С����ֵ�������ʺϵ�λ��*/
void SelectSort(int *a, int n)
{
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		int minIndex = left;
		int maxIndex = right;
		for (int i = left; i <= right; i++)
		{
			if (a[i] < a[minIndex])
			{
				minIndex = i;
			}
			if (a[i] > a[maxIndex])
			{
				maxIndex = i;
			}
		}
		//�ҵ�left--right�������������Сֵ��
		swap(a[left], a[minIndex]);
		//�����λ���������е���Сֵ����Сλ���������е����ֵ������Ľ������������ֵλ�õ�ֵ��ʹ���ֵ��������minIndex��λ�ã�
		if (maxIndex == left)
		{
			maxIndex = minIndex;
		}
		swap(a[right], a[maxIndex]);
		++left;
		--right;
	}
}
/*���������򣬽���ѣ����ڵ��������
����֮�����ݲ���һ��������ģ����ڵ�ֵ��������һ��Ԫ�ؽ������൱������Ԫ���Ѿ������ʺϵ�λ�á������ݸ�����1�������µ�����һ����
���ظ��������赽ֻ��һ��Ԫ��ʱ�������*/
void AdjustDown(int *a, int n, int root)
{
	assert(a);
	int child = root * 2 + 1;
	while (child < n)
	{
		//�����Һ�����ѡ����ĺ���
		if (child + 1 < n && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[root] < a[child])
		{
			swap(a[root], a[child]);
		}
		else
		{
			break;
		}
		root = child;
		child = root * 2 + 1;
	}
}
void HeapSort(int *a, int n)
{
	//����
	//�����һ����Ҷ�ӽڵ㿪ʼ���ڣ�ֱ�����ڵ�
	for (int i = (n - 2) >> 1; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	for (int end = n - 1; end > 0;)
	{
		swap(a[0], a[end]);
		AdjustDown(a, end--, 0);
	}
}
/*ð���������������Ƚϣ�������ð��ֱ��ð�����һ�����ڶ�ʣ�µ�Ԫ��ð�ݣ�ѭ������*/
void BubbleSort(int *a, int n)
{
	assert(a);

	int end = n - 1;
	while (end > 0)
	{
		int first = 0;
		int second = 1;
		while (second <= end)
		{
			if (a[first] > a[second])
			{
				swap(a[first], a[second]);
			}
			first++;
			second++;
		}
		end--;
	}
}
/*��������
һ������ѡһ��keyȥ��ȷ��λ�ã�key����߶�С��key���ұ߶�����key
*/
int GetMidIndex(int *a, int left, int right) //��Ԫ�ط������key���±꣬ȥ��������
{
	int mid = left + (right - left) / 2;
	//�ҳ�������λ���У���Сλ���м���±겢���ء�
	if (a[left] > a[mid])
	{
		if (a[mid] > a[right])  //l>m>r
		{
			return mid;
		}
		else if (a[right] > a[left]) // r > l > m; 
		{
			return left;
		}
		else  //l > r >m
		{
			return right;
		}
	}
	else  //left <= mid
	{
		if (a[right] < a[left]) //r < l <m
		{
			return left;
		}
		else if (a[right] > a[mid])  //r > m >l
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
}
int  PartSort(int *a, int left, int right)  //����ָ�뷨
{
	int begin = left;
	int end = right;
	int div = GetMidIndex(a, left, right);

	swap(a[div], a[right]);
	int key = a[right];
	while (begin < end)
	{
		//bigin�ұ�key���
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		//end�ұ�keyС��
		while (begin < end && a[end] >= key)
		{
			end--;
		}
		//�ҵ�����,
		swap(a[begin], a[end]);
	}
	swap(a[begin], a[right]);
	return begin;
}

int PartSort1(int *a, int left, int right) //�ڿӷ�,��һ��key = a[end]��Ϊ�ӣ�left�ҵ�һ������key�ģ���key�Ŀӣ�right�ҵ�һ��С��key�ģ���left�Ŀӣ�left�ٴ��ұ�key��Ľ�right�Ŀ�ѭ����leftright��������
{
	int div = GetMidIndex(a, left, right);  //��Ԫ�ط�
	swap(a[div], a[right]);
	int key = a[right];
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			left++;
		}
		a[right] = a[left]; //����
		while (left < right && a[right] >= key)
		{
			right--;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

int PartSort2(int *a, int left, int right) //ǰ��ָ�뷨
{
	int prev = left - 1;
	int index = left;
	while (index < right)
	{
		if (a[index] < a[right])
		{
			prev++;
			if (prev != index)
			{
				swap(a[prev], a[index]);
			}
		}
		index++;
	}
	swap(a[++prev], a[right]);
	return prev;
}

void QuckSort(int *a, int left,int right)
{
	if (left >= right)
	{
		return;
	}
	
	
	int div = PartSort1(a, left, right);

	QuckSort(a, left, div - 1);
	QuckSort(a, div + 1, right);
}
void QuckSortOp(int *a, int left, int right)   //��С�����Ż�
{
	if (left >= right)
	{
		return;
	}
	if (right - left < 100)
	{
		SortInsert(a, right - left + 1);
	}
	else
	{
		int div = PartSort1(a, left, right);

		QuckSort(a, left, div - 1);
		QuckSort(a, div + 1, right);
	}
	
}

/*�ǵݹ�ʵ�ֿ��ţ���Ҫ��תΪ�洢С��������⣬��ջʵ��*/
#include<stack>
void QuckSortNonR(int *a, int left, int right)
{
	stack<int> sk;
	sk.push(right);
	sk.push(left);
	
	while (!sk.empty())
	{
		int begin = sk.top();
		sk.pop();
		int end = sk.top();
		sk.pop();

		int div = PartSort2(a,begin,end);

		//�洢������ջ�У��������
		if (div - 1 > begin)
		{
			sk.push(div - 1);
			sk.push(begin);
		}
		if (end > div + 1)
		{
			sk.push(end);
			sk.push(div + 1);
		}

	}
}

/*�鲢����
�����������飬�ϳ�һ�������Ա������򣻰�һ�����鿴�������������飬�ϲ��������⣺����������û���򣬹鲢ʹ�����򣻻�����һ��Ԫ�أ����Ϲ鲢��
*/


void _MergeSort(int *src, int *dst, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;

	//����������������---��תΪ����������
	_MergeSort(src, dst, left, mid);
	_MergeSort(src, dst, mid + 1, right);

	//�ϲ����������������䣻
	int start1 = left;
	int start2 = mid + 1;
	int index = 0;
	while (start1 <= mid && start2 <= right)
	{
		if (src[start1] < src[start2])
		{
			dst[index++] = src[start1];
			++start1;
		}
		else
		{
			dst[index++] = src[start2];
			++start2;
		}
	}

	while (start1 <= mid)
	{
		dst[index++] = src[start1++];
	}
	while (start2 <= right)
	{
		dst[index++] = src[start2++];
	}

	//������ý�src ---???????
	int i = 0;
	int j = left;
	while (i < index)
	{
		src[j++] = dst[i++];
	}
}

void MergeSort(int *a, int n)
{
	assert(a);
	int *tmp = new int[n];
	_MergeSort(a, tmp, 0, n - 1);    //-???????????Ϊʲôʹ�ø����ռ�tmp;
	delete[] tmp;
}


void TestBubbleSort()
{
	int a[] = { 9,5,4,0,3,6,8,7,1,2 };
	//SortInsert(a,sizeof(a)/sizeof(a[0]));
	//BubbleSort(a,sizeof(a)/sizeof(a[0]));
	//QuckSort(a, 0, 9);
	//QuckSortNonR(a, 0, 9);
	MergeSort(a, 10);
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

//void TestQuckSort()
//{
//	int n = 100000;
//	int *a1 = new int[n];
//	int *a2 = new int[n];
//	srand(time(0));
//	for (int i = 0; i < n; i++)
//	{
//		a1[i] = rand() % 10000000;
//		a2[i] = rand() % 10000000;
//	}
//	time_t start1;
//	time_t start2;
//	time_t end1;
//	time_t end2;
//	time(&start1);
//	QuckSort(a1, 0, n - 1);
//	time(&end1);
//
//	time(&start2);
//	QuckSortOp(a2,0,n-1);
//	time(&end2);
//
//	cout << "sort:" << end1 - start1 << endl;
//	cout << "sortOp:" << end2 - start2 << endl;
//
//}


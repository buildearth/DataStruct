#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<assert.h>
#include<time.h>
using namespace std;
/*直接插入排序*/
void SortInsert(int *arr, int length)
{
	assert(arr);
	if (length <= 1)   //数组只有一个元素不需要排序
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

		//break,出来 x插入在end的下一个位置
		//for循环走完出来,此时end = -1；x插入在0这个位置，也就是end+1这个位置；
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
/*希尔排序*/
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
/*选择排序:一次选出最大和最小两个值，放在适合的位置*/
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
		//找到left--right区间内最大与最小值；
		swap(a[left], a[minIndex]);
		//若最大位置是区间中的最小值，最小位置是区间中的最大值；上面的交换覆盖了最大值位置的值，使最大值交换到了minIndex的位置；
		if (maxIndex == left)
		{
			maxIndex = minIndex;
		}
		swap(a[right], a[maxIndex]);
		++left;
		--right;
	}
}
/*堆排序，升序，建大堆，根节点数据最大；
建堆之后数据并不一定是有序的，根节点值最大，与最后一个元素交换，相当于最大的元素已经到该适合的位置。将数据个数减1，在向下调整成一个堆
，重复上述步骤到只有一个元素时完成排序；*/
void AdjustDown(int *a, int n, int root)
{
	assert(a);
	int child = root * 2 + 1;
	while (child < n)
	{
		//在左右孩子中选出大的孩子
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
	//建堆
	//从最后一个非叶子节点开始调节，直至根节点
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
/*冒泡排序，升序，两两比较，大的向后冒，直到冒到最后一个；在对剩下的元素冒泡，循环步骤*/
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
/*快速排序
一趟排序：选一个key去正确的位置；key的左边都小于key，右边都大于key
*/
int GetMidIndex(int *a, int left, int right) //三元素法，获得key的下标，去避免最坏情况
{
	int mid = left + (right - left) / 2;
	//找出这三个位置中，大小位于中间的下标并返回。
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
int  PartSort(int *a, int left, int right)  //左右指针法
{
	int begin = left;
	int end = right;
	int div = GetMidIndex(a, left, right);

	swap(a[div], a[right]);
	int key = a[right];
	while (begin < end)
	{
		//bigin找比key大的
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		//end找比key小的
		while (begin < end && a[end] >= key)
		{
			end--;
		}
		//找到交换,
		swap(a[begin], a[end]);
	}
	swap(a[begin], a[right]);
	return begin;
}

int PartSort1(int *a, int left, int right) //挖坑法,找一个key = a[end]作为坑，left找到一个大于key的，进key的坑；right找到一个小于key的；进left的坑；left再次找比key大的进right的坑循环至leftright相遇结束
{
	int div = GetMidIndex(a, left, right);  //三元素法
	swap(a[div], a[right]);
	int key = a[right];
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			left++;
		}
		a[right] = a[left]; //进坑
		while (left < right && a[right] >= key)
		{
			right--;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

int PartSort2(int *a, int left, int right) //前后指针法
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
void QuckSortOp(int *a, int left, int right)   //加小区间优化
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

/*非递归实现快排，主要是转为存储小区间的问题，用栈实现*/
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

		//存储区间在栈中，先左后右
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

/*归并排序
两个有序数组，合成一个数组仍保持有序；把一个数组看成两个有序数组，合并；子问题：两个子数组没有序，归并使其有序；划分至一个元素，向上归并；
*/


void _MergeSort(int *src, int *dst, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;

	//左右区间有序问题---》转为子问题解决；
	_MergeSort(src, dst, left, mid);
	_MergeSort(src, dst, mid + 1, right);

	//合并两个有序左右区间；
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

	//有序的拿进src ---???????
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
	_MergeSort(a, tmp, 0, n - 1);    //-???????????为什么使用辅助空间tmp;
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


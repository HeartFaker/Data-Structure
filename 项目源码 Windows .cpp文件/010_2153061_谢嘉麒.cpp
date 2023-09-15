#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<time.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class mysort
{
public:
	void setArray();

	//冒泡排序
	void bubbleSort();

	//选择排序
	void selectSort();

	//直接插入排序
	void straightInsertSort();

	//希尔排序
	void shellSort();

	//快速排序
	void quickSort();

	//堆排序
	void heapSort();

	//归并排序
	void mergeSort();

	//基数排序
	void radixSort();

private:
	int* array = nullptr;
	int count = 0;

	void swap(int t1, int t2);
	void random(int* arrays, int number);
	void fixHeap(int* heap, int end, int i, long long& move);
	int maxbit(int data[], int n);
	void _qsort(int src[], int begin, int end, long long& move);
};

/***************************************************************************
  函数名称：swap(int t1,int t2)
  功    能：交换两数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::swap(int t1, int t2)
{
	int tmp = t1;
	t1 = t2;
	t2 = tmp;
}

int mysort::maxbit(int data[], int n) //基数排序辅助函数，求数据的最大位数
{
	int maxData = data[0];              ///< 最大数
	/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < n; ++i)
	{
		if (maxData < data[i])
			maxData = data[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		//p *= 10; // Maybe overflow
		maxData /= 10;
		++d;
	}
	return d;
	/*    int d = 1; //保存最大的位数
		int p = 10;
		for(int i = 0; i < n; ++i)
		{
			while(data[i] >= p)
			{
				p *= 10;
				++d;
			}
		}
		return d;*/
}

/***************************************************************************
  函数名称：radixSort()
  功    能：基数排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::radixSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	int d = maxbit(copy, count);
	int* tmp = new int[count];
	int* c = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			c[j] = 0; //每次分配前清空计数器
		for (j = 0; j < count; j++)
		{
			k = (copy[j] / radix) % 10; //统计每个桶中的记录数
			c[k]++;
		}
		for (j = 1; j < 10; j++)
			c[j] = c[j - 1] + c[j]; //将tmp中的位置依次分配给每个桶
		for (j = count - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (copy[j] / radix) % 10;
			tmp[c[k] - 1] = copy[j];
			c[k]--;
		}
		for (j = 0; j < count; j++) //将临时数组的内容复制到data中
			copy[j] = tmp[j];
		move += 2 * j;
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]c;

	printf("%s所用时间:    %gms\n", "基数排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "基数排序", move);
	delete[] copy;
}

/***************************************************************************
  函数名称：mergeSort()
  功    能：归并排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::mergeSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;


	clock_t start = clock();

	int* a = copy;
	int* b = new int[count];
	for (int seg = 1; seg < count; seg += seg) {
		for (int start = 0; start < count; start += seg + seg) {
			int low = start, mid = min(start + seg, count), high = min(start + seg + seg, count);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2) {
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
				move++;
			}
			while (start1 < end1) {
				b[k++] = a[start1++];
				move++;
			}
			while (start2 < end2) {
				b[k++] = a[start2++];
				move++;
			}
		}
		int* temp = a;
		a = b;
		b = temp;
	}
	if (a != copy) {
		for (int i = 0; i < count; i++)
			b[i] = a[i];
		b = a;
	}
	delete[] b;

	printf("%s所用时间:    %gms\n", "归并排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s比较次数:    %lld\n", "归并排序", move);
	delete[] copy;
}

void mysort::fixHeap(int* heap, int end, int i, long long& move)
{  //堆调整(最大堆)
	int child = 2 * i + 1;
	while (child < end)
	{
		if (child + 1 < end)
		{
			if (heap[child] < heap[child + 1]) child++;  // 找较大的子节点
		}
		if (heap[i] > heap[child])
			break;
		swap(heap[i], heap[child]);
		move += 3;
		i = child;
		child = 2 * i + 1;
	}
}

/***************************************************************************
  函数名称：heapSort()
  功    能：堆排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::heapSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;


	clock_t start = clock();

	for (int i = (count - 2) / 2; i >= 0; i--)  //堆化,从倒数第二层(向上)开始修复
		fixHeap(copy, count, i, move);

	for (int i = count - 1; i >= 1; i--)
	{
		swap(copy[i], copy[0]);        //将最大的元素放在最后
		move += 3;
		fixHeap(copy, i, 0, move);  //调整剩下的堆
	}

	printf("%s所用时间:    %gms\n", "堆排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "堆排序", move);
	delete[] copy;
}

void mysort::_qsort(int src[], int begin, int end, long long& move) {
	if (begin < end) {
		int key = src[begin];
		int i = begin;
		int j = end;
		while (i < j) {
			while (i < j && src[j] > key) {
				j--;
			}
			if (i < j) {
				src[i] = src[j];
				move++;
				i++;
			}
			while (i < j && src[i] < key) {
				i++;
			}
			if (i < j) {
				src[j] = src[i];
				move++;
				j--;
			}
		}
		src[i] = key;
		move++;
		_qsort(src, begin, i - 1, move);
		_qsort(src, i + 1, end, move);
	}
}

/***************************************************************************
  函数名称：quickSort()
  功    能：快速排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::quickSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	_qsort(copy, 0, count - 1, move);

	printf("%s所用时间:    %gms\n", "快速排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "快速排序", move);
	delete[] copy;
}

/***************************************************************************
  函数名称：shellSort()
  功    能：希尔排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::shellSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;


	clock_t start = clock();

	int gap = 1;
	while (gap < count / 3)
		gap = 3 * gap + 1;  // h依次取1,4,13,40,121
	while (gap)
	{
		for (int i = gap; i < count; i++)
		{
			int temp = copy[i];
			++move;
			int j = i;
			while (j >= gap && temp < copy[j - gap])
			{
				copy[j] = copy[j - gap];
				++move;
				j -= gap;
			}
			copy[j] = temp;
			++move;
		}
		gap /= 3;
	}


	printf("%s所用时间:    %gms\n", "希尔排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "希尔排序", move);
	delete[] copy;
}

/***************************************************************************
  函数名称：straightInsertSort()
  功    能：直接插入排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::straightInsertSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	for (int i = 1; i < count; i++)
	{
		int temp = copy[i];
		++move;
		int j = i;
		while (j > 0 && temp < copy[j - 1]) {  //
			copy[j] = copy[j - 1];
			++move;
			j--;
		}
		copy[j] = temp;
		++move;
	}

	printf("%s所用时间:    %gms\n", "直接插入排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "直接插入排序", move);
	delete[] copy;
}

/***************************************************************************
  函数名称：selectSort()
  功    能：选择排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::selectSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	for (int i = 0; i < count; ++i)
	{
		int min = i;
		for (int j = i + 1; j < count; ++j)
		{
			if (copy[j] < copy[min])
				min = j;
		}
		if (min != i)
		{
			swap(copy[i], copy[min]);
			move += 3;
		}
	}

	printf("%s所用时间:    %gms\n", "选择排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "选择排序", move);
	delete[] copy;
}

/***************************************************************************
  函数名称：bubbleSort()
  功    能：冒泡排序
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::bubbleSort()
{
	//为了不改变已生成数组故将其拷贝数组进行排序
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	bool disordered = true;
	for (int i = count - 1; i >= 0 && disordered; --i)
	{
		disordered = false;
		for (int j = 0; j < i; ++j)
		{
			if (copy[j] > copy[j + 1])
			{
				swap(copy[j], copy[j + 1]);
				move += 3;
				disordered = true;
			}
		}
	}

	printf("%s所用时间:    %gms\n", "冒泡排序", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s交换次数:    %lld\n", "冒泡排序", move);
	delete[] copy;
}

/***************************************************************************
  函数名称：setArray()
  功    能：建立排序数组
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mysort::setArray()
{
	printf("\n请输入要产生的随机数个数：");

	srand((unsigned int)time(NULL));
	scanf("%d", &count);
	//防止数字过大导致程序崩溃
	if (count <= 0 || count > 1e8)
		exit(0);
	array = new int[count];
	random(array, count);
}

//在数组arrays中内产生number个[min,max]区间内的随机数
void mysort::random(int* arrays, int number)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < number; ++i)
		arrays[i] = rand() % number;
}


int main()
{
	printf("**                  排序算法比较                  **\n");
	printf("====================================================\n");
	printf("**                  1.冒泡排序                    **\n");
	printf("**                  2.选择排序                    **\n");
	printf("**                  3.直接插入排序                **\n");
	printf("**                  4.希尔排序                    **\n");
	printf("**                  5.快速排序                    **\n");
	printf("**                  6.堆排序                      **\n");
	printf("**                  7.归并排序                    **\n");
	printf("**                  8.基数排序                    **\n");
	printf("**                  9.退出程序                    **\n");
	printf("====================================================\n");

	mysort s;
	int ch;
	s.setArray();

	while (true)
	{
		printf("\n请选择排序算法：     ");
		scanf("%d", &ch);
		switch (ch)
		{
			case 1:
				s.bubbleSort();
				break;
			case 2:
				s.selectSort();
				break;
			case 3:
				s.straightInsertSort();
				break;
			case 4:
				s.shellSort();
				break;
			case 5:
				s.quickSort();
				break;
			case 6:
				s.heapSort();
				break;
			case 7:
				s.mergeSort();
				break;
			case 8:
				s.radixSort();
				break;
			case 9:
				return 0;
			default:
				printf("输入错误，请重新输入！");
				break;
		}
	}

	return 0;
}
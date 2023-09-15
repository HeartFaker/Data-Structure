#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//最小堆类自此开始
#define DefaultSize 10;

template<class Type>
class minHeap {
private:

	//存放堆中元素的数组
	Type* heap;

	//最小堆中当前元素个数
	int currentSize;

	//最小堆最多允许元素个数
	int maxHeapSize;

	//从start到m下滑调整成为最小堆
	void siftDown(int start, int m);

	//从start到0上滑调整成为最小堆
	void siftUp(int start);

public:

	//空堆构造函数
	minHeap(int sz);

	//利用数组建立堆
	minHeap(Type arr[], int n);

	//析构函数
	~minHeap()
	{
		//delete[] heap;
	}

	//将元素x插入最小堆中
	bool insert(const Type& x);

	//删除堆顶上的最小元素并返回其值
	Type delMin();

	//判断堆是否空
	bool isEmpty()const
	{
		return (currentSize == 0) ? 1 : 0;
	}

	//判断堆是否满
	bool isFull()const
	{
		return (currentSize == maxHeapSize) ? 1 : 0;
	}

	//置空堆
	void makeEmpty()
	{
		currentSize = 0;
	}

	int getCurrentSize()
	{
		return currentSize;
	}

};

/***************************************************************************
  函数名称：minHeap(int sz)
  功    能：最小堆析构函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class Type>
minHeap<Type>::minHeap(int sz)
{
	maxHeapSize = sz;
	heap = new Type[maxHeapSize];
	if (heap == NULL) {
		cerr << "堆存储分配失败" << endl;
		exit(1);
	}
	currentSize = 0;
}

/***************************************************************************
  函数名称：minHeap(Type arr[], int n)
  功    能：基于数组的最小堆析构函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class Type>
minHeap<Type>::minHeap(Type arr[], int n)
{
	maxHeapSize = n;
	heap = new Type[maxHeapSize];
	if (heap == NULL) {
		cerr << "堆存储分配失败" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++)
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0) {
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

/***************************************************************************
  函数名称：siftDown(int start, int m)
  功    能：向下排序实现最小堆
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class Type>
void minHeap<Type>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	Type temp = heap[i];
	while (j <= m) {
		if (j < m && heap[j] > heap[j + 1]) {
			j++;
		}
		if (temp <= heap[j]) {
			break;
		}
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

/***************************************************************************
  函数名称：siftUp(int start)
  功    能：向上浮动实现最小堆
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class Type>
void minHeap<Type>::siftUp(int start)
{
	int j = start;
	int i = (j - 1) / 2;
	Type temp = heap[j];
	while (j > 0) {
		if (heap[i] <= temp) {
			break;
		}
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

/***************************************************************************
  函数名称：insert(const Type& x)
  功    能：插入新元素
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class Type>
bool minHeap<Type>::insert(const Type& x)
{
	if (currentSize == maxHeapSize) {
		cerr << "Heap Full" << endl;
		exit(1);
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

/***************************************************************************
  函数名称：delMin()
  功    能：删除堆元素
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class Type>
Type minHeap<Type>::delMin()
{
	if (!currentSize) {
		cout << "Heap EMpty" << endl;
		exit(1);
	}
	Type temp = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return temp;
}

/*
template<class Type>
Type minHeap<Type>::delMin()
{
	if (!currentSize) {
		cout << "Heap EMpty" << endl;
		exit(1);
	}
	Type temp = heap[1];
	Type temp2 = heap[currentSize--];
	int child, par;
	for (par = 1; par << 1 <= currentSize; par = child)
	{
		child = par << 1;
		if (child<currentSize && heap[child]>heap[child + 1])
			child++;
		if (heap[child] < temp2)
			heap[par] = heap[child];
		else
			break;
	}
	heap[par] = temp2;
	return temp;
}*/

const int Num = 10010;

/***************************************************************************
  函数名称：main()
  功    能：程序主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    int* arr = new int[Num];
    int N = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    minHeap<int> farm(arr, N);
    delete[]arr;
    
    int sum = 0;
    while (farm.getCurrentSize() > 1)
    {
		//取出最小堆顶部的两个元素
        int temp1 = farm.delMin();
        int temp2 = farm.delMin();
		//将其相加后重新放入最小堆，同时和加至总成本
        sum += temp1 + temp2;
        farm.insert(temp1 + temp2);
    }
    printf("%d\n", sum);
    return 0;
}
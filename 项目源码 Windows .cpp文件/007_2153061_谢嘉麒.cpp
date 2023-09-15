#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//��С�����Դ˿�ʼ
#define DefaultSize 10;

template<class Type>
class minHeap {
private:

	//��Ŷ���Ԫ�ص�����
	Type* heap;

	//��С���е�ǰԪ�ظ���
	int currentSize;

	//��С���������Ԫ�ظ���
	int maxHeapSize;

	//��start��m�»�������Ϊ��С��
	void siftDown(int start, int m);

	//��start��0�ϻ�������Ϊ��С��
	void siftUp(int start);

public:

	//�նѹ��캯��
	minHeap(int sz);

	//�������齨����
	minHeap(Type arr[], int n);

	//��������
	~minHeap()
	{
		//delete[] heap;
	}

	//��Ԫ��x������С����
	bool insert(const Type& x);

	//ɾ���Ѷ��ϵ���СԪ�ز�������ֵ
	Type delMin();

	//�ж϶��Ƿ��
	bool isEmpty()const
	{
		return (currentSize == 0) ? 1 : 0;
	}

	//�ж϶��Ƿ���
	bool isFull()const
	{
		return (currentSize == maxHeapSize) ? 1 : 0;
	}

	//�ÿն�
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
  �������ƣ�minHeap(int sz)
  ��    �ܣ���С����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class Type>
minHeap<Type>::minHeap(int sz)
{
	maxHeapSize = sz;
	heap = new Type[maxHeapSize];
	if (heap == NULL) {
		cerr << "�Ѵ洢����ʧ��" << endl;
		exit(1);
	}
	currentSize = 0;
}

/***************************************************************************
  �������ƣ�minHeap(Type arr[], int n)
  ��    �ܣ������������С����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class Type>
minHeap<Type>::minHeap(Type arr[], int n)
{
	maxHeapSize = n;
	heap = new Type[maxHeapSize];
	if (heap == NULL) {
		cerr << "�Ѵ洢����ʧ��" << endl;
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
  �������ƣ�siftDown(int start, int m)
  ��    �ܣ���������ʵ����С��
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�siftUp(int start)
  ��    �ܣ����ϸ���ʵ����С��
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�insert(const Type& x)
  ��    �ܣ�������Ԫ��
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�delMin()
  ��    �ܣ�ɾ����Ԫ��
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�main()
  ��    �ܣ�����������
  ���������
  �� �� ֵ��
  ˵    ����
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
		//ȡ����С�Ѷ���������Ԫ��
        int temp1 = farm.delMin();
        int temp2 = farm.delMin();
		//������Ӻ����·�����С�ѣ�ͬʱ�ͼ����ܳɱ�
        sum += temp1 + temp2;
        farm.insert(temp1 + temp2);
    }
    printf("%d\n", sum);
    return 0;
}
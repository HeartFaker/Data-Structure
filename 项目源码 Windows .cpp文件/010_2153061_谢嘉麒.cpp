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

	//ð������
	void bubbleSort();

	//ѡ������
	void selectSort();

	//ֱ�Ӳ�������
	void straightInsertSort();

	//ϣ������
	void shellSort();

	//��������
	void quickSort();

	//������
	void heapSort();

	//�鲢����
	void mergeSort();

	//��������
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
  �������ƣ�swap(int t1,int t2)
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::swap(int t1, int t2)
{
	int tmp = t1;
	t1 = t2;
	t2 = tmp;
}

int mysort::maxbit(int data[], int n) //���������������������ݵ����λ��
{
	int maxData = data[0];              ///< �����
	/// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
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
	/*    int d = 1; //��������λ��
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
  �������ƣ�radixSort()
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::radixSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	int d = maxbit(copy, count);
	int* tmp = new int[count];
	int* c = new int[10]; //������
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			c[j] = 0; //ÿ�η���ǰ��ռ�����
		for (j = 0; j < count; j++)
		{
			k = (copy[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			c[k]++;
		}
		for (j = 1; j < 10; j++)
			c[j] = c[j - 1] + c[j]; //��tmp�е�λ�����η����ÿ��Ͱ
		for (j = count - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (copy[j] / radix) % 10;
			tmp[c[k] - 1] = copy[j];
			c[k]--;
		}
		for (j = 0; j < count; j++) //����ʱ��������ݸ��Ƶ�data��
			copy[j] = tmp[j];
		move += 2 * j;
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]c;

	printf("%s����ʱ��:    %gms\n", "��������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "��������", move);
	delete[] copy;
}

/***************************************************************************
  �������ƣ�mergeSort()
  ��    �ܣ��鲢����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::mergeSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
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

	printf("%s����ʱ��:    %gms\n", "�鲢����", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s�Ƚϴ���:    %lld\n", "�鲢����", move);
	delete[] copy;
}

void mysort::fixHeap(int* heap, int end, int i, long long& move)
{  //�ѵ���(����)
	int child = 2 * i + 1;
	while (child < end)
	{
		if (child + 1 < end)
		{
			if (heap[child] < heap[child + 1]) child++;  // �ҽϴ���ӽڵ�
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
  �������ƣ�heapSort()
  ��    �ܣ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::heapSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;


	clock_t start = clock();

	for (int i = (count - 2) / 2; i >= 0; i--)  //�ѻ�,�ӵ����ڶ���(����)��ʼ�޸�
		fixHeap(copy, count, i, move);

	for (int i = count - 1; i >= 1; i--)
	{
		swap(copy[i], copy[0]);        //������Ԫ�ط������
		move += 3;
		fixHeap(copy, i, 0, move);  //����ʣ�µĶ�
	}

	printf("%s����ʱ��:    %gms\n", "������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "������", move);
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
  �������ƣ�quickSort()
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::quickSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;

	clock_t start = clock();

	_qsort(copy, 0, count - 1, move);

	printf("%s����ʱ��:    %gms\n", "��������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "��������", move);
	delete[] copy;
}

/***************************************************************************
  �������ƣ�shellSort()
  ��    �ܣ�ϣ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::shellSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
	int* copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	long long move = 0;


	clock_t start = clock();

	int gap = 1;
	while (gap < count / 3)
		gap = 3 * gap + 1;  // h����ȡ1,4,13,40,121
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


	printf("%s����ʱ��:    %gms\n", "ϣ������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "ϣ������", move);
	delete[] copy;
}

/***************************************************************************
  �������ƣ�straightInsertSort()
  ��    �ܣ�ֱ�Ӳ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::straightInsertSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
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

	printf("%s����ʱ��:    %gms\n", "ֱ�Ӳ�������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "ֱ�Ӳ�������", move);
	delete[] copy;
}

/***************************************************************************
  �������ƣ�selectSort()
  ��    �ܣ�ѡ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::selectSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
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

	printf("%s����ʱ��:    %gms\n", "ѡ������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "ѡ������", move);
	delete[] copy;
}

/***************************************************************************
  �������ƣ�bubbleSort()
  ��    �ܣ�ð������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::bubbleSort()
{
	//Ϊ�˲��ı�����������ʽ��俽�������������
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

	printf("%s����ʱ��:    %gms\n", "ð������", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("%s��������:    %lld\n", "ð������", move);
	delete[] copy;
}

/***************************************************************************
  �������ƣ�setArray()
  ��    �ܣ�������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mysort::setArray()
{
	printf("\n������Ҫ�����������������");

	srand((unsigned int)time(NULL));
	scanf("%d", &count);
	//��ֹ���ֹ����³������
	if (count <= 0 || count > 1e8)
		exit(0);
	array = new int[count];
	random(array, count);
}

//������arrays���ڲ���number��[min,max]�����ڵ������
void mysort::random(int* arrays, int number)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < number; ++i)
		arrays[i] = rand() % number;
}


int main()
{
	printf("**                  �����㷨�Ƚ�                  **\n");
	printf("====================================================\n");
	printf("**                  1.ð������                    **\n");
	printf("**                  2.ѡ������                    **\n");
	printf("**                  3.ֱ�Ӳ�������                **\n");
	printf("**                  4.ϣ������                    **\n");
	printf("**                  5.��������                    **\n");
	printf("**                  6.������                      **\n");
	printf("**                  7.�鲢����                    **\n");
	printf("**                  8.��������                    **\n");
	printf("**                  9.�˳�����                    **\n");
	printf("====================================================\n");

	mysort s;
	int ch;
	s.setArray();

	while (true)
	{
		printf("\n��ѡ�������㷨��     ");
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
				printf("����������������룡");
				break;
		}
	}

	return 0;
}
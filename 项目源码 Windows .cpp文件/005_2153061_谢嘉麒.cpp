#include<assert.h>
#include<iostream>
using namespace std;
template<class Type>
class Queue;

//����������ͷ���ĵ���������
template<class T>
struct LinkNode {

	//����ʼ��ָ���Ա�Ľ���๹�캯��
	LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }

	//��ʼ��������ָ���Ա�Ĺ��캯��
	LinkNode(const T& item, LinkNode<T>* ptr = NULL) { data = item; link = ptr; }

	T data;  //��������
	LinkNode<T>* link;  //���ָ��
};

//����������
template<class T>
class List {
public:

	template<class Type>
	friend class Queue;

	//�����๹�캯��
	List() { first = new LinkNode<T>; }
	List(const T& x) { first = new LinkNode<T>(x); }

	//���ƹ��캯��
	List(List<T>& L);

	//�ÿ�����
	void makeEmpty();

	//��������������
	~List();

	//��������ĳ���
	int Length()const;

	//���ظ���ͷ�ڵ�ĵ�ַ
	LinkNode<T>* getHead()const { return first; }

	//�������в��Һ�������x�Ľ��
	LinkNode<T>* Search(T x);

	//������i��Ԫ�صĵ�ַ
	LinkNode<T>* locate(int i);

	//ȡ����i��Ԫ�ص�ֵ
	bool getData(int i, T& x)const;

	//��x�޸ĵ�i��Ԫ�ص�ֵ
	void setData(int i, T& x);

	//�ڵ�i��Ԫ�غ����x
	bool Insert(int i, T& x);

	//ɾȥ��i��Ԫ�أ�x���ظ�Ԫ�ص�ֵ
	bool Remove(int i, T& x);

	//�жϱ��Ƿ�գ����򷵻�true
	bool Isempty()const
	{
		return first->link == NULL ? true : false;
	}

	//������������н��
	void outputAll();

	//���غ�������ֵ
	List<T>& operator = (List<T>& L);

	//��巨����������
	void inputRear(T endTag);
	//ǰ�巨����������
	void inputFront(T endTag);

	//��β������������
	void insert_rear(const T x);

	//ɾ����һ�����ݽ��
	void delete_first();

private:
	LinkNode<T>* first;  //������ı�ͷָ��
	LinkNode<T>* tail;   //������ı�βָ��
};

/***************************************************************************
  �������ƣ�List<T>::List(List<T>& L)
  ��    �ܣ����ƹ��캯��
  ���������List<T>& L
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
List<T>::List(List<T>& L)
{
	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;
		desptr->link = new LinkNode<T>(value);
		desptr = desptr->link;
		srcptr = srcptr->link;
	}
	desptr->link = NULL;
	tail = first;
}

/***************************************************************************
  �������ƣ�void List<T>::makeEmpty()
  ��    �ܣ��ÿ������ͷ��ڴ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
void List<T>::makeEmpty()
{
	LinkNode<T>* q;
	while (first->link != NULL) {
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

/***************************************************************************
  �������ƣ�List<T>::~List()
  ��    �ܣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
List<T>::~List()
{
	makeEmpty();
}

/***************************************************************************
  �������ƣ�List<T>::Length()const
  ��    �ܣ����������ͷ���ĵ�������
  ���������
  �� �� ֵ��return count;
  ˵    ����
***************************************************************************/
template<class T>
int List<T>::Length()const
{
	LinkNode<T>* p = first->link;
	int count = 0;
	while (p != NULL) {
		p = p->link;
		count++;
	}
	return count;
}

/***************************************************************************
  �������ƣ�LinkNode<T>* List<T>::Search(T x)
  ��    �ܣ���������������������x�Ľ��
  ���������T x
  �� �� ֵ�����ҳɹ�ʱ���������ַ�����򷵻�NULL
  ˵    ����
***************************************************************************/
template<class T>
LinkNode<T>* List<T>::Search(T x)
{
	LinkNode<T>* current = first->link;
	while (current != NULL) {
		if (current->data == x) {
			break;
		}
		else {
			current = current->link;
		}
	}
	return current;
}

/***************************************************************************
  �������ƣ�LinkNode<T>* List<T>::locate(int i)
  ��    �ܣ�������i�����ĵ�ַ
  ���������int i
  �� �� ֵ��return current;
  ˵    ����
***************************************************************************/
template<class T>
LinkNode<T>* List<T>::locate(int i)
{
	if (i < 0) {
		return NULL;
	}
	LinkNode<T>* current = first;
	int k = 0;
	while (current != NULL && k < i) {
		current = current->link;
		k++;
	}
	return current;
}

/***************************************************************************
  �������ƣ�bool List<T>::getData(int i, T& x)const
  ��    �ܣ�ȡ����i������ֵ
  ���������int i��T& x
  �� �� ֵ��0/1
  ˵    ����
***************************************************************************/
template<class T>
bool List<T>::getData(int i, T& x)const
{
	if (i <= 0) {
		return NULL;
	}
	LinkNode<T>* current = locate(i);
	if (current == NULL) {
		return false;
	}
	else {
		x = current->data;
		return true;
	}
}

/***************************************************************************
  �������ƣ�List<T>::setData(int i, T& x)
  ��    �ܣ���x�޸ĵ�i������ֵ
  ���������int i��T& x
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
void List<T>::setData(int i, T& x)
{
	if (i <= 0) {
		return;
	}
	LinkNode<T>* current = locate(i);
	if (current == NULL) {
		return;
	}
	else {
		current->data = x;
	}
	return;
}

/***************************************************************************
  �������ƣ�List<T>::Insert(int i, T& x)
  ��    �ܣ��ڵ�i��Ԫ�غ����x
  ���������int i, T& x
  �� �� ֵ��return true OR false
  ˵    ����
***************************************************************************/
template<class T>
bool List<T>::Insert(int i, T& x)
{
	LinkNode<T>* current = locate(i);
	if (current == NULL) {
		return false;
	}
	LinkNode<T>* newNode = new LinkNode<T>(x);
	if (newNode == NULL) {
		cerr << "�洢������󣡣�" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

/***************************************************************************
  �������ƣ�List<T>::Remove(int i,T& x)
  ��    �ܣ��������i��λ�õĽ��ɾ��,ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ
  ���������int i, T& x
  �� �� ֵ��return true OR false
  ˵    ����
***************************************************************************/
template<class T>
bool List<T>::Remove(int i, T& x)
{
	LinkNode<T>* current = locate(i - 1);
	if (current == NULL || current->link == NULL) {
		cerr << "ɾ�����ɹ�" << endl;
		return false;
	}
	LinkNode<T>* del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

/***************************************************************************
  �������ƣ�List::outputAll()
  ��    �ܣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
void List<T>::outputAll()
{
	LinkNode<T>* current = first->link;
	if (current == NULL) {
		cout << "NULL" << endl;
	}
	while (current != NULL) {
		cout << current->data << endl;
		current = current->link;
	}
	return;
}

/***************************************************************************
�������ƣ�List<T>::operator=(List<T>& L)
��    �ܣ����ظ�ֵ�����
���������
�� �� ֵ��
˵    ����
***************************************************************************/
template<class T>
List<T>& List<T>::operator=(List<T>& L)
{
	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;
		desptr->link = new LinkNode<T>(value);
		desptr = desptr->link;
		srcptr = srcptr->link;
	}
	desptr->link = NULL;
	return *this;
}

/***************************************************************************
  �������ƣ�List<T>::inputRear(T endTag)
  ��    �ܣ���巨����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
void List<T>::inputRear(T endTag)
{
	LinkNode<T>* newNode, * last;
	T val;
	makeEmpty();
	cin >> val;
	last = first;
	while (val != endTag) {
		newNode = new LinkNode<T>(val);
		if (newNode == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		cin >> val;
	}
	last->link = NULL;
	tail = last;
	return;
}

/***************************************************************************
  �������ƣ�List<T>::inputFront(T endTag)
  ��    �ܣ�ǰ�巨����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
void List<T>::inputFront(T endTag)
{
	LinkNode<T>* newNode, * last;
	T val;
	makeEmpty();
	cin >> val;
	while (val != endTag) {
		newNode = new LinkNode<T>(val);
		if (newNode == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		cin >> val;
	}
	return;
}

//��β������������
template<class Type>
void List<Type>::insert_rear(const Type data)
{
	//�ж������Ƿ�Ϊ��
	if (Isempty())
	{
		//�����½��
		LinkNode<Type>* newNode = new LinkNode<Type>(data, first);

		//�ı�ͷָ���βָ��
		first->link = newNode;
		tail = newNode;
	}
	else
	{
		//�����½��
		LinkNode<Type>* newNode = new LinkNode<Type>(data, tail);

		//�ı�βָ��
		tail->link = newNode;
		tail = newNode;
	}
}

// ɾ��ͷ���
template<class Type>
void List<Type>::delete_first()
{
	if (!Isempty())
	{
		//ɾ��tail�ĺ�̽��
		LinkNode<Type>* delData = first->link;
		//�ж�β���
		if (delData == tail)
		{
			tail = first;
			first->link = nullptr;
			delete delData;
		}
		else
		{
			first->link = delData->link;
			delete delData;
		}

	}
}

//���������
template<class Type>
class Queue
{
private:
	//�ڲ�����һ������
	List<Type> data;

public:
	//���캯��
	//Ĭ�Ϲ��캯��
	Queue();

	//�ж϶����Ƿ�Ϊ��
	inline bool empty()const;
	//���ض��д�С
	inline int size()const;

	//���
	void push(const Type& i);
	//����
	void pop();

	//��ȡ����Ԫ��
	const Type& front()const;
	Type& front();
};

//Ĭ�Ϲ��캯��
template<class Type>
Queue<Type>::Queue()
{

}

//�ж϶����Ƿ�Ϊ��
template<class Type>
inline bool Queue<Type>::empty()const
{
	return this->data.Isempty();
}

//���ض��д�С
template<class Type>
inline int Queue<Type>::size()const
{
	return this->data.Length();
}

//���
template<class Type>
void Queue<Type>::push(const Type& i)
{
	this->data.insert_rear(i);
}

//����
template<class Type>
void Queue<Type>::pop()
{
	this->data.delete_first();
}

//��ȡ����Ԫ��
template<class Type>
const Type& Queue<Type>::front()const
{
	return this->data.first->link->data;
}

template<class Type>
Type& Queue<Type>::front()
{
	return this->data.first->link->data;
}

/***************************************************************************
  �������ƣ�main()
  ��    �ܣ�����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	int N;//�˿�����
	//ֱ��������ȷ
	while (1) {
		while (1)
		{
			cout << "������ͻ������͸�λ�ͻ��ı�ţ�";
			cin >> N;
			if (N <= 0)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "����������������롣" << endl;
			}
			else
				break;
		}
		Queue<int> queueA, queueB;
		//�˿����
		for (int i = 1; i <= N; ++i)
		{
			int temp;
			cin >> temp;
			//ż����B�ӣ�������A��
			if (temp % 2 == 0)
				queueB.push(temp);
			else
				queueA.push(temp);
		}
		cout << "Output:";
		//����
		while (!queueA.empty() || !queueB.empty())
		{
			//Aҵ�������
			for (int i = 0; i < 2; ++i)
				if (!queueA.empty())
				{
					cout << queueA.front() << " ";
					queueA.pop();
				}
			//Bҵ�������
			if (!queueB.empty())
			{
				cout << queueB.front() << " ";
				queueB.pop();
			}
		}
		char s = '0';
		while (1) {
			cout << endl << "�Ƿ����?��y/n��";
			cin >> s;
			if (!cin.good() || (s != 'y' && s != 'n')) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "�������,����������!" << endl;
				continue;
			}
			else {
				cin.clear();
				cin.ignore(1024, '\n');
				break;
			}
		}
		if (s == 'y') {
			cout << endl;
			continue;
		}
		else if (s == 'n') {
			cout << "��ӭ�´��ٴ�ʹ��!" << endl;
			exit(0);
		}
	}
	return 0;
}
#include<iostream>
using namespace std;

template<class T>
class List;

//����������ͷ���ĵ���������
template<class T>
struct LinkNode {

	//������������������������Ϊ��������Ԫ����
	friend std::istream& operator>>(std::istream& istr, LinkNode<T>& x);
	friend std::ostream& operator<<(std::ostream& ostr, const LinkNode<T>& x);

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
	bool IsEmpty()const
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

	//����������Ľ���
	void intersection(List<T>& L);

private:
	LinkNode<T>* first;  //������ı�ͷָ��
};

/***************************************************************************
  �������ƣ�istream& operator>>(istream& istr, LinkNode<T>& x)
  ��    �ܣ����������������������������
  ���������istream& istr, LinkNode& x
  �� �� ֵ��return istr;
  ˵    ����
***************************************************************************/
template<class T>
istream& operator>>(istream& istr, LinkNode<T>& x)
{
	istr >> x.data;
	return istr;
}

/***************************************************************************
  �������ƣ�ostream& operator<<(ostream& ostr, const LinkNode<T>& x)
  ��    �ܣ���������������������������
  ���������ostream& ostr, const LinkNode& x
  �� �� ֵ��return ostr;
  ˵    ����
***************************************************************************/
template<class T>
ostream& operator<<(ostream& ostr, const LinkNode<T>& x)
{
	ostr << x.data << endl;
	return ostr;
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

/***************************************************************************
  �������ƣ�List<T>::intersection(List<T>& L)
  ��    �ܣ���������������Ľ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<class T>
void List<T>::intersection(List<T>& L)
{
	int count = 0;
	LinkNode<T>* p1, * p2;
	p1 = first->link;
	p2 = L.first->link;
	if (first->link == NULL || L.first->link == NULL) {
		cout << "NULL" << endl;
		return;
	}
	while (p1 && p2) {
		if (p1->data == p2->data)
		{
			cout << p1->data << " ";
			count++;
			p1 = p1->link;
			p2 = p2->link;
		}
		else if (p1->data < p2->data)
		{
			p1 = p1->link;
		}
		else
		{

			p2 = p2->link;
		}
	}
	if (count == 0) {
		cout << "NULL" << endl;
	}
	return;
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
	while (1) {
		List<int> list1, list2;
		cout << "������ǽ�������1��";
		list1.inputRear(-1);
		cout << endl << "������ǽ�������2��";
		list2.inputRear(-1);
		cout << endl;
		cout << "��������������Ľ���Ϊ��";
		list1.intersection(list2);
		char s;
		while (1) {
			cout << endl << "�Ƿ��������?��y/n��";
			cin >> s;
			if (!cin.good() || (s != 'y' && s != 'n')) {
				cin.clear();
				cin.ignore(2147483648, '\n');
				cout << "�������,����������!" << endl;
				continue;
			}
			else {
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
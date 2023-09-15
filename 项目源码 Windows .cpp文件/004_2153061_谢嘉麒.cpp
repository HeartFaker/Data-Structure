#include<iostream>
#include<cstring>
using namespace std;

//������Ӵ˿�ʼ
template<class Type>
struct linkNode
{
	//��������������
	Type data;
	linkNode<Type>* next, * prev;

	//Ĭ�Ϲ��캯��
	linkNode() :next(nullptr), prev(nullptr) {};
	//���캯��
	linkNode(Type datas, linkNode<Type>* nexts = nullptr, linkNode<Type>* prevs = nullptr) :data(datas), next(nexts), prev(prevs) {};

};

template<class Type>
class linkList
{
	typedef linkNode<Type>* _iterator;


private:
	//ͷָ��
	linkNode<Type>* head;
	//βָ��
	linkNode<Type>* rear;
	//������
	int _size;

public:
	//Ĭ�Ϲ��캯��
	linkList();
	//���ƹ��캯��
	linkList(const linkList<Type>& x);

	//��������
	~linkList();

	//��������
	class iterator
	{
	private:
		_iterator data;
	public:

		//Ĭ�Ϲ��캯��
		iterator() :data(nullptr) {};
		//���캯��
		iterator(_iterator datas) :data(datas) {};
		iterator(Type d)
		{
			data = new linkNode<Type>;
			data->data = d;
		}

		//���������
		//�����ݲ���
		Type operator*()
		{
			return data->data;
		}
		//�Ƚ������
		inline bool operator==(const iterator& v)const
		{
			return this->data == v.data;
		}
		inline bool operator<(const iterator& v)const
		{
			return this->data < v.data;
		}
		inline bool operator>(const iterator& v)const
		{
			return this->data > v.data;
		}
		inline bool operator<=(const iterator& v)const
		{
			return this->data <= v.data;
		}
		inline bool operator>=(const iterator& v)const
		{
			return this->data >= v.data;
		}
		inline bool operator!=(const iterator& v)const
		{
			return this->data != v.data;
		}

		//���������
		//ǰ������
		inline linkList<Type>::iterator& operator++()
		{
			if (this->data != nullptr) {
				this->data = this->data->next;
			}
			return (*this);
		}
		//��������
		linkList<Type>::iterator operator++(int)
		{
			linkList<Type>::iterator old = (*this);
			++(*this);
			return old;
		}
		//�Լ������
		//ǰ���Լ�
		inline linkList<Type>::iterator& operator--()
		{
			if (this->data != nullptr) {
				this->data = this->data->prev;
			}
			return (*this);
		}
		//�����Լ�
		linkList<Type>::iterator operator--(int)
		{
			linkList<Type>::iterator old = (*this);
			--(*this);
			return old;
		}
		//�������һ����
		linkList<Type>::iterator operator+(int index)
		{
			linkList<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i) {
				++old;
			}
			return old;
		}
		//ǰ�����һ����
		friend typename linkList<Type>::iterator operator+(int index, typename linkList<Type>::iterator data)
		{
			linkList<Type>::iterator old = data;
			for (int i = 0; i < index; ++i)
			{
				++old;
			}
			return old;
		}
		//�����ȥһ����
		linkList<Type>::iterator operator-(int index)
		{
			linkList<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i) {
				--old;
			}
			return old;
		}
		//�Լ�
		linkList<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i) {
				++(*this);
			}
			return (*this);
		}
		//�Լ�
		linkList<Type>::iterator& operator-=(int index)
		{
			for (int i = 0; i < index; i++) {
				--(*this);
			}
			return (*this);
		}
		//��������������֮��ľ���
		int operator-(linkList<Type>::iterator i)
		{
			//����i->dataͨ������ȡnext�����ܹ�����this->data
			int index = 0;
			while (i->data != this->data)
			{
				i++;
				index++;
			}
			return index;
		}

		//��Ԫ��
		friend class linkList<Type>;

	};

	//������
	inline int size()const;

	//�ж������Ƿ�Ϊ��
	inline bool Isempty()const;

	//��β������������
	void push_rear(Type data);

	//��ͷ������������
	void push_front(Type data);

	//����ָ�����ݣ����ص�����
	linkList<Type>::iterator find(const Type& data)const;

	//ɾ��ָ����������Ӧ�Ľ��
	Type remove(linkList<Type>::iterator index);

	//ɾ��β���
	void erase_rear();

	//ɾ����һ�����
	void erase_front();

	//�������
	void clear();

	//������
	bool insert(linkList<Type>::iterator index, Type i);

	//����ָ��λ�õ�һϵ�к���
	//��ʼλ�õ�����
	inline linkList<Type>::iterator begin();
	inline const linkList<Type>::iterator begin()const;

	//���λ�õ�����
	inline linkList<Type>::iterator end();
	inline const linkList<Type>::iterator end()const;

	//���صȺ������
	linkList<Type>& operator=(const linkList<Type>& i);

	//��Ԫ��
	template<class T>
	friend class Stack;
	template<class T>
	friend class Queue;
};

//Ĭ�Ϲ��캯��
template<class Type>
linkList<Type>::linkList()
{
	head = new linkNode<Type>();
	rear = head;
	_size = 0;
}

//���ƹ��캯��
template<class Type>
linkList<Type>::linkList(const linkList& li)
{
	head = new linkNode<Type>();
	rear = head;
	_size = 0;
	//��������и���
	for (auto i = li.begin(); i != li.end(); ++i) {
		this->push_rear(*i);
	}
}

//�ж������Ƿ�Ϊ��
template<class Type>
inline bool linkList<Type>::Isempty()const
{
	return rear == head;
}

//��β������������
template<class Type>
void linkList<Type>::push_rear(Type data)
{
	//�ж������Ƿ�Ϊ��
	if (Isempty()) {
		//�����½��
		linkNode<Type>* newNode = new linkNode<Type>(data, nullptr, head);

		//�ı�ͷβָ��
		head->next = newNode;
		rear = newNode;
	}
	else {
		//�����½��
		linkNode<Type>* newNode = new linkNode<Type>(data, nullptr, rear);

		//�ı�βָ��
		rear->next = newNode;
		rear = newNode;
	}
	++_size;
}

//��ͷ������������
template<class Type>
void linkList<Type>::push_front(Type data)
{
	//�ж������Ƿ�Ϊ��
	if (Isempty())
	{
		//�����½��
		linkNode<Type>* newNode = new linkNode<Type>(data, nullptr, head);

		//�ı�ͷβָ��
		head->next = newNode;
		rear = newNode;
	}
	else {
		//�����½��
		linkNode<Type>* newNode = new linkNode<Type>(data, head->next, head);

		//�ı�ͷ���֮��Ľ��ָ��
		head->next->prev = newNode;

		//�ı�ͷ���ָ��
		head->next = newNode;
	}

	++_size;
}

//��������
template<class Type>
inline int linkList<Type>::size()const
{
	return _size;
}

//�����������ʼλ��
template<class Type>
inline typename linkList<Type>::iterator linkList<Type>::begin()
{
	return linkList<Type>::iterator(this->head->next);
}

template<class Type>
inline const typename linkList<Type>::iterator linkList<Type>::begin()const
{
	return linkList<Type>::iterator(this->head->next);
}

//������������λ��
template<class Type>
inline typename linkList<Type>::iterator linkList<Type>::end()
{
	return linkList<Type>::iterator(this->rear->next);
}

template<class Type>
inline const typename linkList<Type>::iterator linkList<Type>::end()const
{
	return linkList<Type>::iterator(this->rear->next);
}

//ɾ��ָ����������Ӧ�Ľ��
template<class Type>
Type linkList<Type>::remove(typename linkList<Type>::iterator i)
{
	linkNode<Type>* node = i.data;
	Type value = node->data;

	//��node���Ĵ���
	if (node == rear) {
		//���nodeΪβ���
		rear = node->prev;
		rear->next = nullptr;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	delete node;
	return value;
}

//����ĳ�����
template<class Type>
bool linkList<Type>::insert(linkList<Type>::iterator index, Type i)
{
	linkNode<Type>* node = index.data;
	node->prev->next = new linkNode<Type>(i, node, node->prev);
	node->prev = node->prev->next;
	return true;
}

//ɾ��β���
template<class Type>
void linkList<Type>::erase_rear()
{
	if (!Isempty()) {
		//ɾ��rear��Ӧ�Ľ��
		linkNode<Type>* delData = rear;
		rear = rear->prev;
		rear->next = nullptr;
		delete delData;

		_size--;
	}
}

//ɾ��ͷ���
template<class Type>
void linkList<Type>::erase_front()
{
	if (!Isempty()) {
		linkNode<Type>* delData = head->next;
		//�ж�β���
		if (delData == rear) {
			rear = head;
			head->next = nullptr;
			delete delData;
		}
		else {
			head->next = delData->next;
			delData->next->prev = head;
			delete delData;
		}
	}
}

//�������
template<class Type>
void linkList<Type>::clear()
{
	this->_size = 0;
	linkList<Type>::iterator cur = this->begin();
	while (cur.data != nullptr) {
		linkNode<Type>* delData = cur.data;
		cur++;
		delete delData;
	}
	this->rear = this->head;
	this->head->next = nullptr;
}

//��������
template<class Type>
linkList<Type>::~linkList()
{
	this->clear();
	delete this->head;
}

//���صȺ������
template<class Type>
linkList<Type>& linkList<Type>::operator=(const linkList<Type>& li)
{
	//���ԭ���Ľ��
	this->clear();
	//�����㸴��
	for (auto i = li.begin(); i != li.end(); ++i) {
		this->push_rear(*i);
	}
	return *this;
}

//����ָ�����ݣ����ص�����
template<class Type>
typename linkList<Type>::iterator linkList<Type>::find(const Type& data)const
{
	for (auto i = begin(); i != end(); ++i) {
		if (*i == data) {
			return i;
		}
	}
	return linkList<Type>::iterator(nullptr);
}

//�������Դ˽���

//ջ���ɴ˿�ʼ

template<class Type>
class Stack
{
private:
	//������ʽջ
	linkList<Type> data;
public:
	//Ĭ�Ϲ��캯��
	Stack();

	//�ж��Ƿ�ջ��
	inline bool Isempty()const;

	//����ջ�Ĵ�С
	inline int size()const;

	//��ջ
	void push(const Type& i);
	//��ջ
	void pop();

	//��ȡջ��Ԫ��
	const Type& top()const;
};

//Ĭ�Ϲ��캯��
template<class Type>
Stack<Type>::Stack()
{
	//���蹹�����
}

//�ж�ջ�Ƿ�Ϊ��
template<class Type>
inline bool Stack<Type>::Isempty()const
{
	return this->data.Isempty();
}

//��ջ
template<class Type>
void Stack<Type>::push(const Type& i)
{
	this->data.push_rear(i);
}

//��ջ
template<class Type>
void Stack<Type>::pop()
{
	this->data.erase_rear();
}

//��ȡջ��Ԫ��
template<class Type>
const Type& Stack<Type>::top()const
{
	return this->data.rear->data;
}

//����ջ��С
template<class Type>
inline int Stack<Type>::size()const
{
	return this->data._size;
}

//ջ���ɴ˽���

/***************************************************************************
  �������ƣ�translation(const char* s)
  ��    �ܣ����ʽת������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void translation(const char* s)
{
	//����ջ�洢���ʽ�����
	Stack<char> ope;
	//ѹ����ֹ�ַ�
	ope.push('0');
	int isFirst = 0;
	for (int i = 0; s[i] != '\0'; ) {
		int j = 0;
		//�����ո�
		for (; s[i + j] != ' '&& s[i + j] != '\0'; j++)
			;
		//��ȡ���ʽ������
		if ((j == 1)&&(s[i]<'0'||s[i]>'9')) {
			if (s[i] == '+' || s[i] == '-')
			{
				while (ope.top() != '(' && ope.top() != '0') {
					if (ope.top() != '(') {
						printf(" %c", ope.top());
					}
					ope.pop();
				}
				ope.push(s[i]);
			}
			else if (s[i] == ')')
			{

				while (ope.top() != '(' ) {
					if (ope.top() != '(') {
						printf(" %c", ope.top());
					}
					ope.pop();
				}
				ope.pop();
			}
			else if (s[i] == '*' || s[i] == '/' || s[i] == '(')
			{
				ope.push(s[i]);
			}
		}
		else if(j==0) {
			j = 1;
		}
		else {
			char* num = new char[j + 1];
			for (int k = 0; k < j; k++) {
				num[k] = s[i + k];
			}
			if (isFirst == 0)
				cout << atof(num);
			else
				cout << " " << atof(num);
			delete[] num;
		}
		if (isFirst == 0) {
			isFirst = 1;
		}
		i += j;
	}
	//��ջ��ʣ���������
	while (ope.size()!=1)
	{
		if (ope.top() != '(') {
			printf(" %c", ope.top());
		}
		ope.pop();
	}
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
	cout << "��ӭʹ�ñ��ʽת������" << endl;
	while (1) {
		char expression[110];
		char s;
		cout << "�������׺���ʽ��" << endl;
		cin.getline(expression, 1024);
		translation(expression);
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
                cin.clear();
                cin.ignore(2147483648, '\n');
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
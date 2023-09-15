#define _CRT_SECURE_NO_WARNINGS_
#include <iostream>
#include<string>
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

//�������Դ˿�ʼ

#define VECTOR_DEFAULT_SIZE 5 //������С

template<class Type>
class Vector
{
	typedef Type* Pointer;
	typedef Pointer _iterator;

private:

	//���ݴ�С
	int _size;

	//��ǰ����
	int _capacity;

	//����
	Type* _elements;

	//��dataָ���и��ƴ�[low,high)������
	Type* copyFrom(Type* data, int low, int high, int size = 0);

	//����Ԫ������
	void expand();

public:

	//���캯��

	//Ĭ�Ϲ��캯��
	Vector();

	//��ʼ��С���캯��
	Vector(int size);

	//���ƹ��캯��
	Vector(const Vector& v);

	Vector(int sz, Type data)
	{
		this->_size = sz;
		this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

		this->_elements = new Type[_capacity];
		if (_elements == nullptr)
			;
		for (int i = 0; i < sz; i++)
			this->_elements[i] = data;
	}

	//��������
	~Vector();

	//��������
	class iterator
	{
	private:
		_iterator data;
	public:
		typedef Type value_type;

		//Ĭ�Ϲ��캯��
		iterator() :data(nullptr) {};

		//���캯��
		iterator(_iterator datas) :data(datas) {};

		//���������

		//������
		Type& operator*()
		{
			return *data;
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
		inline bool operator>=(const iterator& v)const
		{
			return this->data >= v.data;
		}
		inline bool operator<=(const iterator& v)const
		{
			return this->data <= v.data;
		}
		inline bool operator!=(const iterator& v)const
		{
			return this->data != v.data;
		}

		//���������

		//ǰ������
		inline Vector<Type>::iterator& operator++()
		{
			this->data++;
			return (*this);
		}

		//��������
		Vector<Type>::iterator operator++(int)
		{
			Vector<Type>::iterator old = (*this);
			++(*this);
			return old;
		}

		//�Լ������

		//ǰ���Լ�
		inline Vector<Type>::iterator& operator--()
		{
			this->data--;
			return (*this);
		}

		//�����Լ�
		Vector<Type>::iterator operator--(int)
		{
			Vector<Type>::iterator old = (*this);
			--(*this);
			return old;
		}

		//�����һ����
		Vector<Type>::iterator operator+(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; i++)
				++old;
			return old;
		}

		//ǰ����һ����
		friend typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data) {
			typename Vector<Type>::iterator old = data;
			for (int i = 0; i < index; i++)
				++old;
			return old;
		}

		//���ȥһ����
		Vector<Type>::iterator operator-(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; i++)
				--old;
			return old;
		}

		//�Լ�
		Vector<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; i++)
				++(*this);
			return (*this);
		}

		//�Լ�
		Vector<Type>::iterator& operator-=(int index)
		{
			for (int i = 0; i < index; i++)
				--(*this);
			return (*this);
		}

		friend int operator-(const Vector<Type>::iterator& i, const Vector<Type>::iterator& j)
		{
			return i.data - j.data;
		}
	};

	//������С
	inline int size()const;

	//�ж������Ƿ�Ϊ��
	inline bool Isempty()const;

	//β����������
	void push_back(const Type data);

	//ɾ������
	Type pop_back();

	//��ָ��������ǰ��������
	bool insert(const Vector<Type>::iterator place, Type item);

	//ɾ��ָ��������������
	bool erase(const Vector<Type>::iterator place);

	//�������
	void clear();

	//ͳһ��ֵ
	void fillData(const Type data);

	//������ʼλ�õ�����
	inline Vector<Type>::iterator begin();
	inline const Vector<Type>::iterator begin()const;

	//�������λ�õ�����
	inline Vector<Type>::iterator end();
	inline const Vector<Type>::iterator end()const;

	//��ȡ���һ��Ԫ��
	inline Vector<Type>::iterator last();
	inline const Vector<Type>::iterator last()const;

	//��ȡ��һ������
	Type& front()const
	{
		return this->_elements[0];
	}

	//���������

	//ȡ�±������������
	inline Type& operator[](int i);

	//�Ⱥ������
	Vector<Type>& operator=(const Vector<Type>& v);

	void resize(int sz)
	{
		while (this->_size < sz)
		{
			if (this->_size == this->_capacity) {
				this->expand();
			}
			_size++;
		}
		while (this->_size > sz)
		{
			_size--;
		}
	}

};

//Ĭ�Ϲ��캯��
template<class Type>
Vector<Type>::Vector()
{
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;

	//����Ĭ��������С����ռ�
	this->_elements = new Type[_capacity];
}

//������ʼ��С�Ĺ��캯��
template<class Type>
Vector<Type>::Vector(int size)
{
	this->_size = size;
	this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

	//����ռ�
	this->_elements = new Type[_capacity];
}

//���ƹ��캯��
template<class Type>
Vector<Type>::Vector(const Vector& v)
{
	this->_size = v._size;
	this->_capacity = v._capacity;

	//Ԫ��һһ����
	this->_elements = copyFrom(v._elements, 0, _size, _capacity);
}

//��dataָ���и���[low,high)������
template<class Type>
Type* Vector<Type>::copyFrom(Type* data, int low, int high, int size)
{
	if (size == 0) {
		size = high - low;
	}
	//����ռ�
	Type* newData = new Type[size];

	//һһ����
	for (int i = low; i < high; i++) {
		newData[i] = data[low + i];
	}

	return newData;
}

//��ȡ����Ԫ�ظ���
template<class Type>
inline int Vector<Type>::size()const
{
	return this->_size;
}

//����Ԫ������
template<class Type>
void Vector<Type>::expand()
{

	this->_capacity += VECTOR_DEFAULT_SIZE;

	Type* oldElements = this->_elements;

	//����
	this->_elements = copyFrom(this->_elements, 0, _size, _capacity);

	delete[] oldElements;

}

//��������
template<class Type>
void Vector<Type>::push_back(const Type data)
{
	//�ж�����
	if (this->_size == this->_capacity) {
		this->expand();
	}
	this->_elements[_size++] = data;
}

//ȡ�±������������[]
template<class Type>
inline Type& Vector<Type>::operator[](int i)
{
	if (i < 0 || i >= _size)
		;

	return _elements[i];
}

//ɾ������
template<class Type>
Type Vector<Type>::pop_back()
{
	if (_size == 0)
		;

	//�������һ������
	return _elements[--_size];
}

//������������ʼλ��
template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::begin()
{
	return _size > 0 ? typename Vector<Type>::iterator(&_elements[0]) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::begin()const
{
	return _size > 0 ? typename Vector<Type>::iterator(&_elements[0]) :
		typename Vector<Type>::iterator();
}

//�������������λ��
template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::end()
{
	return _size > 0 ? ++(typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::end()const
{
	return _size > 0 ? ++(typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::last()
{
	return _size > 0 ? (typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::last()const
{
	return _size > 0 ? (typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

//ǰ�ü�һ����
template<class Type>
typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data)
{
	typename Vector<Type>::iterator old = data;
	for (int i = 0; i < index; ++i)
		++old;
	return old;
}

//�ж������Ƿ�Ϊ��
template<class Type>
inline bool Vector<Type>::Isempty()const
{
	return this->_size == 0;
}

//��ָ��������ǰ��������
template<class Type>
bool Vector<Type>::insert(const typename Vector<Type>::iterator place, Type item)
{
	//��ǰ��¼λ��(expand��λ�÷����仯)
	auto places = place;
	int j = places - this->begin();

	//�ж��Ƿ���Ҫ����
	if (this->_size == this->_capacity)
		this->expand();

	//��place�����������Ԫ�����κ���һλ
	int i;

	for (i = _size - 1; i >= j; --i)
		this->_elements[i + 1] = this->_elements[i];

	//��������Ԫ��
	this->_elements[i + 1] = item;
	this->_size++;

	return true;
}

//ɾ��ָ��������������
template<class Type>
bool Vector<Type>::erase(const typename Vector<Type>::iterator place)
{
	//��ȡplace���±�λ��
	int index = place - this->begin();

	if (index < 0 || index >= this->_size)
		return false;

	while (index < this->_size - 1)
	{
		this->_elements[index] = this->_elements[index + 1];
		++index;
	}

	this->_size--;

	return true;
}

//�������
template<class Type>
void Vector<Type>::clear()
{
	//�������Ԫ��
	delete[] _elements;

	//����Ĭ�Ϲ��캯��
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;
	//����Ĭ��������С����ռ�
	this->_elements = new Type[_capacity];
}

//��������
template<class Type>
Vector<Type>::~Vector()
{
	//�������Ԫ��
	delete[] _elements;
}

//���صȺ������
template<class Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& v)
{
	//��ֹ���ҵ���
	if (v._elements == this->_elements)
		return *this;
	this->clear();
	//һ��һ�����ĸ��ƹ�ȥ
	for (auto i = v.begin(); i != v.end(); ++i)
		this->push_back(*i);

	return *this;
}

//ͳһ��ֵ
template<class Type>
void Vector<Type>::fillData(const Type data)
{
	for (auto i = begin(); i != end(); ++i)
		*i = data;
}

//�������Դ˽���

//�ɶ���
template<class T1, class T2>
struct Pair
{
	T1 first;
	T2 second;
	//���캯��
	Pair() {};
	Pair(const T1&, const T2&);
	Pair(const Pair&);
	template<class T3, class T4>
	Pair(const T3& first, const T4& second) :first(first), second(second) {};

	//���������
	Pair& operator=(const Pair& rhs)
	{
		this->first = rhs.first;
		this->second = rhs.second;
		return *this;
	}
	inline bool operator==(const Pair<T1, T2>& rhs)
	{
		return first == rhs.first && second == rhs.second;
	}
	inline bool operator!=(const Pair<T1, T2>& rhs)
	{
		return first != rhs.first || second != rhs.second;
	}

};

template<class T1, class T2>
Pair<T1, T2>::Pair(const T1& first, const T2& second)
{
	this->first = first;
	this->second = second;
}

template<class T1, class T2>
Pair<T1, T2>::Pair(const Pair<T1, T2>& rhs)
{
	this->first = rhs.first;
	this->second = rhs.second;
}

template<class T1, class T2>
bool operator<(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first < rhs2.first || (rhs1.first == rhs2.first && rhs1.second < rhs2.second);
}

template<class T1, class T2>
bool operator>(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first > rhs2.first || (rhs1.first == rhs2.first && rhs1.second > rhs2.second);
}

template<class T1, class T2>
bool operator<=(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first <= rhs2.first || (rhs1.first == rhs2.first && rhs1.second <= rhs2.second);
}

template<class T1, class T2>
bool operator>=(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first >= rhs2.first || (rhs1.first == rhs2.first && rhs1.second >= rhs2.second);
}

template<class T1, class T2>
Pair<T1, T2> operator+(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return Pair<T1, T2>(rhs1.first + rhs2.first, rhs1.second + rhs2.second);
}

template<class T1, class T2>
Pair<T1, T2> operator-(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return Pair<T1, T2>(rhs1.first - rhs2.first, rhs1.second - rhs2.second);
}
//�ɶ����Դ˽���

//ͼ���Դ˿�ʼ

#define MAX_LENGTH 1000000

class graph
{
private:
	//����
	Vector<string> vertex;

	//�ڽӱ�
	Vector<linkList<Pair<int, int>>> adList;

	//prim�㷨���ɵ���С������
	Vector<Pair<int, int>> mstTree;

	//���ͼ
	void clear();

	//Prim�㷨������С������
	void prim(int pos);

	//�ж϶����Ƿ��Ѿ���ͼ��
	int IsVertex(const string& vertex);

	//�Ƚ������ַ����ĸ�������
	bool strcmp(const string& str1, const string& str2);
public:
	//��������
	void setVertex();

	//������
	void setEdge();

	//������С������
	void buildMST();

	//��ӡ��С������
	void printMST();
};

/***************************************************************************
  �������ƣ�setVertex()
  ��    �ܣ����붥�㼰����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::setVertex()
{
	clear();

	int sumVertex = 0;
	printf("�����붥��ĸ�����");
	cin >> sumVertex;
	printf("�������������������ƣ�\n");
	for (int i = 0; i < sumVertex; i++) {
		string vertexName;
		cin >> vertexName;
		if (IsVertex(vertexName) != -1) {
			cout << "����" << vertexName << "�Ѵ��ڣ����������룡\n";
			continue;
		}
		else {
			vertex.push_back(vertexName);
		}
	}
	for (int i = 0; i < vertex.size(); i++) {
		adList.push_back(linkList<Pair<int, int>>());
	}
}

/***************************************************************************
  �������ƣ�clear()
  ��    �ܣ��������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::clear()
{
	vertex.clear();
	adList.clear();
	mstTree.clear();
}

/***************************************************************************
  �������ƣ�IsVertex(const string& v)
  ��    �ܣ��ж϶����Ƿ���ڣ������򷵻���λ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int graph::IsVertex(const string& v)
{
	for (int i = 0; i < vertex.size(); i++) {
		if (vertex[i] == v) {
			return i;
		}
	}
	return -1;
}

/***************************************************************************
  �������ƣ�strcmp(const string& str1, const string& str2)
  ��    �ܣ��Ƚ����ַ����Ƿ���ͬ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool graph::strcmp(const string& str1, const string& str2)
{
	return str1 == str2 ? true : false;
}

/***************************************************************************
  �������ƣ�setEdge()
  ��    �ܣ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::setEdge()
{
	string ver1, ver2;
	int edLength;
	while (true)
	{
		cout << "�������������㼰�ߣ�";
		cin >> ver1 >> ver2 >> edLength;
		int pos1 = IsVertex(ver1);
		int pos2 = IsVertex(ver2);
		if (edLength <= 0) {
			break;
		}
		else if (pos1 == -1) {
			cout << "����" << ver1 << "�����ڣ�����������" << endl;
			continue;
		}
		else if (pos2 == -1) {
			cout << "����" << ver2 << "�����ڣ�����������" << endl;
			continue;
		}
		adList[pos1].push_rear(Pair<int, int>(pos2, edLength));
		adList[pos2].push_rear(Pair<int, int>(pos1, edLength));
	}
}

/***************************************************************************
  �������ƣ�buildMST()
  ��    �ܣ�������С������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::buildMST()
{
	if (vertex.size() == 1) {
		cout << "ֻ��һ�����㣬����������С��" << endl;
		return;
	}
	string ver;
	cout << "��������ʼ���㣺";
	cin >> ver;
	int pos = IsVertex(ver);
	if (pos == -1) {
		cout << "����" << ver << "������" << endl;
		return;
	}
	cout << "����Prim��С��������" << endl;
	prim(pos);
}

/***************************************************************************
  �������ƣ�prim(int pos)
  ��    �ܣ�prim�㷨ʵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::prim(int pos)
{
	mstTree.clear();

	Vector<bool> visited(vertex.size());
	visited.fillData(false);
	visited[pos] = true;

	Vector<int> visitedPrim;
	visitedPrim.push_back(pos);

	while (visitedPrim.size() < vertex.size())
	{
		int start = -1, end = -1, min = MAX_LENGTH;
		for (auto i = visitedPrim.begin(); i != visitedPrim.end(); ++i) {
			for (auto j = adList[(*i)].begin(); j != adList[(*i)].end(); ++j) {
				if (!visited[(*j).first] && (*j).second < min) {
					start = *i;
					end = (*j).first;
					min = (*j).second;
				}
			}
		}
		visited[end] = true;
		visitedPrim.push_back(end);
		mstTree.push_back(Pair<int, int>(start, end));
	}
}

/***************************************************************************
  �������ƣ�printMST()
  ��    �ܣ���ӡ��С������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::printMST()
{
	if (!mstTree.size()) {
		cout << "��С��������δ����" << endl;
		return;
	}
	cout << "��С�������Ķ��㼰��Ϊ��\n\n";
	for (int i = 0; i < mstTree.size(); i++) {
		cout << vertex[mstTree[i].first] << "-<";
		for (auto j = adList[mstTree[i].first].begin(); j != adList[mstTree[i].first].end(); ++j)
		{
			if ((*j).first == mstTree[i].second)
			{
				cout << (*j).second << ">->";
				break;
			}
		}

		cout << vertex[mstTree[i].second] << "\t";
	}
	cout << endl;
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
	cout << "**\t\t�������ģ��ϵͳ\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\tA --- ������������\t\t**" << endl;
	cout << "**\t\tB --- ��ӵ����ı�\t\t**" << endl;
	cout << "**\t\tC --- ������С������\t\t**" << endl;
	cout << "**\t\tD --- ��ʾ��С������\t\t**" << endl;
	cout << "**\t\tE --- �˳�   ����\t\t**" << endl;
	cout << "==================================================" << endl;

	bool loop = true;
	char ch = '0';
	graph Grid;
	while (loop) {
		cout << "\n��ѡ�������";
		cin >> ch;
		if (cin.fail()) {
			cout << "������������������A-E�������ִ�Сд��" << endl;
			cin.clear();
			cin.ignore(1024,'\n');
			continue;
		}
		else {
			switch (ch) {

				case 'a':
				case 'A':
					Grid.setVertex();
					break;

				case 'b':
				case 'B':
					Grid.setEdge();
					break;

				case 'c':
				case 'C':
					Grid.buildMST();
					break;

				case 'd':
				case 'D':
					Grid.printMST();
					break;

				case 'e':
				case 'E':
					exit(0);
					break;

				default:
					cout << "������������������A-E�������ִ�Сд��" << endl;
					cin.clear();
					cin.ignore(1024,'\n');
					break;
			}
		}
	}
	return 0;
}
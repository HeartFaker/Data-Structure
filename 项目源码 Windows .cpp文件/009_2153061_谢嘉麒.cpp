#include<iostream>
using namespace std;

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

#define VECTOR_DEFAULT_SIZE 100 //������С

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


const int DefaultVertices = 1000;

struct edge
{
	//����һ����λ��
	int dest;

	//��Ȩֵ
	int cost;

	//��һ������ָ��
	edge* link;

	//���캯��
	edge() {}
	edge(int num, int weight) :dest(num), cost(weight), link(nullptr) {}

	//�жϲ���
	bool operator!=(edge& R)const {
		return (dest != R.dest) ? true : false;
	}
};

struct vertex
{
	int data;
	edge* adj;
};

class graph
{
public:
	//���캯��
	graph(int sz = DefaultVertices);
	~graph();

	//����λ��ȡ���еĶ�����
	int getValue(int i)
	{
		return(i >= 0 && i < numVertices) ? nodeTable[i].data : 0;
	}

	//���㶥��vertex��ͼ�е�λ��
	int getVertexPos(const int vertex) {
		for (int i = 0; i < numVertices; i++)
			if (nodeTable[i].data == vertex)
				return i;
		return -1;
	}

	//ȡ��<v1,v2>Ȩֵ
	int getWeight(int v1, int v2);

	//���붥��vertex
	bool insertVertex(const int& vertex);

	//�����<v1,v2,weight>
	bool insertEdge(int v1, int v2, int weight);

	//ȡ����λ��Ϊv�ĵ�һ���ڽӶ���λ��
	int getFirstNeighbor(int v);

	//ȡ����v���ڽӶ���w����һ���ڽӶ���λ��
	int getNextNeighbor(int v, int w);

	//����ؼ�·������ӡ�ؼ��
	void criticalPath();

	//��������
	void topologicalSort();

	//void print();
	//void topsort();

private:
	//��������������ͷ��㣩
	vertex* nodeTable;

	//��������
	int numVertices;

	//������
	int numEdges;

	//�������Ϊ
	int maxVertices;

	//��ȱ�
	Vector<int> inDegree;

	//��ؼ�·��
	int sumCost;

	//������������
	int* count;
};

/*
void graph::print()
{
	while (!inDegree.Isempty()) {
		cout << inDegree.pop_back() << " ";
	}
	cout << endl;

	for (int i = 0; i < numVertices; i++) {
		edge* p = nodeTable[i].adj;
		while (p != NULL) {
			cout << p->cost << " ";
			p = p->link;
		}
		cout << endl;
	}
}*/

/***************************************************************************
  �������ƣ�graph(int sz)
  ��    �ܣ�ͼ�๹�캯��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
graph::graph(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	nodeTable = new vertex[sz + 1];
	count = new int[sz];
	for (int i = 0; i < sz; i++) {
		count[i] = 0;
	}
	inDegree.resize(sz);
	if (nodeTable == NULL) {
		cerr << "�ڴ�����ʧ��" << endl;
		exit(1);
	}
	for (int i = 0; i < sz; i++) {
		nodeTable[i].adj = NULL;
	}
}

/***************************************************************************
  �������ƣ�~graph()
  ��    �ܣ�ͼ����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
graph::~graph()
{
	for (int i = 0; i < numVertices; i++) {
		edge* p = nodeTable[i].adj;
		while (p != NULL) {
			nodeTable[i].adj = p->link;
			delete p;
			p = nodeTable[i].adj;
		}
	}
	delete[]nodeTable;
}

/***************************************************************************
  �������ƣ�getFirstNeighbor(int v)
  ��    �ܣ�ȡ�ڽӱ�ĳһλ�õĵ�һ���ڽӽڵ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int graph::getFirstNeighbor(int v)
{
	if (v != -1) {
		edge* p = nodeTable[v].adj;
		if (p != NULL) {
			return p->dest;
		}
	}
	return -1;
}

/***************************************************************************
  �������ƣ�getNextNeighbor(int v, int w)
  ��    �ܣ�ȡ�ڽӱ�ĳһλ��v���ڽӽڵ�w�ĵ�һ���ڽӽڵ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int graph::getNextNeighbor(int v, int w)
{
	if (v != -1) {
		edge* p = nodeTable[v].adj;
		while (p != NULL && p->dest != w) {
			p = p->link;
		}
		if (p != NULL && p->link != NULL) {
			return p->link->dest;
		}
	}
	return -1;
}

/***************************************************************************
  �������ƣ�getWeight(int v1, int v2)
  ��    �ܣ�ȡ�ߵ�Ȩ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int graph::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1) {
		edge* p = nodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL) {
			return p->cost;
		}
	}
	return 0;
}

/***************************************************************************
  �������ƣ�insertVertex(const int& vertex)
  ��    �ܣ����붥��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool graph::insertVertex(const int& vertex)
{
	if (numVertices == maxVertices) {
		return false;
	}
	nodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

/***************************************************************************
  �������ƣ�insertEdge(int v1, int v2, int weight)
  ��    �ܣ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool graph::insertEdge(int v1, int v2, int weight)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		edge* p = nodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
			p = p->link;
		if (p != NULL)
			return false;
		p = new edge;
		p->dest = v2;
		p->cost = weight;
		p->link = nodeTable[v1].adj;
		nodeTable[v1].adj = p;
		numEdges++;
		count[v2]++;
		return true;
	}
	return false;
}

/*
void graph::topsort()
{
	for (int i = 1; i < numVertices; i++) {
		for (int j = numVertices - 1; j >= i; j--) {
			if (inDegree[j - 1] > inDegree[j])
			{
				edge* temp = nodeTable[j - 1].adj;
				nodeTable[j - 1].adj = nodeTable[j].adj;
				nodeTable[j].adj = temp;
			}
		}
	}
}*/

/***************************************************************************
  �������ƣ�topologicalSort()
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::topologicalSort()
{

	inDegree.clear();
	int i, w, v;
	int top = -1;
	for (i = 0; i < numVertices; i++) {
		if (count[i] == 0) {
			count[i] = top;
			top = i;
		}
	}
	for (i = 0; i < numVertices; i++) {
		if (top == -1) {
			cout << "0" << endl;
			exit(0);
		}
		else {
			v = top;
			top = count[top];
			inDegree.push_back(v);
			w = getFirstNeighbor(v);
			while (w != -1) {
				if (--count[w] == 0) {
					count[w] = top;
					top = w;
				}
				w = getNextNeighbor(v, w);
			}
		}
	}
}

/***************************************************************************
  �������ƣ�criticalPath()
  ��    �ܣ���ؼ�·���㷨
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void graph::criticalPath()
{

	topologicalSort();

	int i, j, k;
	i = j = k = 0;
	int Ae, Al, w;

	//	Vector<Pair<int, int>> crEvent(numVertices);

	int* Ve = new int[numVertices];
	int* Vl = new int[numVertices];

	for (i = 0; i < numVertices; i++) {
		Ve[i] = 0;
	}
	for (i = 0; i < numVertices; i++) {
		j = getFirstNeighbor(i);
		while (j != -1) {
			w = getWeight(i, j);
			if (Ve[i] + w > Ve[j]) {
				Ve[j] = Ve[i] + w;
			}
			j = getNextNeighbor(i, j);
		}
	}
	for (i = 0; i < numVertices; i++)
		Vl[i] = Ve[numVertices - 1];

	for (i = 0; i < numVertices; i++) {
		if (Ve[i] > sumCost) {
			sumCost = Ve[i];
		}
	}
	cout << sumCost << endl;

	/*
	for (int h = 0; h < numVertices; h++) {
		cout << Ve[h] << " ";
	}*/

	while (!inDegree.Isempty()) {
		j = inDegree.pop_back();
		k = getFirstNeighbor(j);
		while (k != -1) {
			w = getWeight(j, k);
			if (Vl[k] - w < Vl[j]) {
				Vl[j] = Vl[k] - w;
			}
			k = getNextNeighbor(j, k);
		}
	}

	/*
	for (j = numVertices - 2; j > 0; j--) {
		k = getFirstNeighbor(j);
		while (k != -1) {
			w = getWeight(j, k);
			if (Vl[k] - w < Vl[j]) {
				Vl[j] = Vl[k] - w;
			}
			k = getNextNeighbor(j, k);
		}
	}
	*/
	/*
	cout << endl;
	for (int h = 0; h < numVertices; h++) {
		cout << Vl[h] << " ";
	}
	cout << endl;
	*/

	for (i = 0; i < numVertices; i++) {
		j = getFirstNeighbor(i);
		while (j != -1) {
			Ae = Ve[i];
			Al = Vl[j] - getWeight(i, j);
			if (Al == Ae) {
				//crEvent.push_back(Pair<int, int>(i, j));
				//sumCost += getWeight(i, j);
				cout << getValue(i) << "->" << getValue(j) << endl;
			}
			j = getNextNeighbor(i, j);
		}
	}

	/*
	cout << sumCost << endl;
	for (int i = 0; i < crEvent.size(); i++) {
		cout << getValue(crEvent[i].first) << "->" << getValue(crEvent[i].second) << endl;
	}
	*/

	delete[]Ve;
	delete[]Vl;
}

int main()
{
	int N, M;
	N = M = 0;
	cin >> N >> M;
	graph criticalActivities(N);
	int ver1, ver2, weight;
	for (int i = 0; i < N; i++) {
		criticalActivities.insertVertex(i + 1);
	}
	int i = 0;
	while(i<M){
		cin >> ver1 >> ver2 >> weight;
		int j = criticalActivities.getVertexPos(ver1);
		int k = criticalActivities.getVertexPos(ver2);
		if (j == -1 || k == -1)
			cout << "�˵���������������" << endl;
		else {
			criticalActivities.insertEdge(j, k, weight);
			i++;
		}
	}

	criticalActivities.criticalPath();
	//criticalActivities.topologicalSort();
	//criticalActivities.print();
	return 0;
}
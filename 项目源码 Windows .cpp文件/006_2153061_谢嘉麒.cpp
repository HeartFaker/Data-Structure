#include<iostream>
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
	if (_elements == nullptr)
		;
}

//������ʼ��С�Ĺ��캯��
template<class Type>
Vector<Type>::Vector(int size)
{
	this->_size = size;
	this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

	//����ռ�
	this->_elements = new Type[_capacity];
	if (_elements == nullptr)
		;
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

	if (newData == nullptr)
		;

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
	if (_elements == nullptr)
		;
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

//�����Դ˿�ʼ

struct treeNode
{
	string name;
	Vector<treeNode*> children;

	//���캯��
	treeNode(const string& name) :name(name) {};

private:

	friend class tree;
};

class tree
{
private:
	treeNode* root = nullptr;

public:

	//Ĭ�Ϲ��캯��
	tree() {};

	//������
	void buildTree();

	//������ͥ
	void buildFamily();

	//�����ͥ��Ա
	void addFamilyMem();

	//��ɢ�ֲ���ͥ��ͥ
	void delFamily();

	//���ļ�ͥ��Ա����
	void renameFamilyMem();

	//�����ӡ����
	void showFamily(treeNode* ptr, Vector<Pair<int, bool>>& memberPlace, bool lastMember)const;

	//�û�ѡ���ӡ����
	void showTree();

	//Ѱ�Ҽ����г�Ա�����򷵻ؽ��
	treeNode* search(const string& name)const;

	inline int count(const string& name)const;

	treeNode* searchAt(treeNode* root, const string& name)const;
};

/***************************************************************************
  �������ƣ�showTree()
  ��    �ܣ��û�ѡ���Ƿ��ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::showTree()
{
	char h;
	cout << "�Ƿ��ӡ������(y/n)" << endl;
	cin >> h;
	if (h == 'y') {
		cout << endl << "��ǰ������Ϊ��" << endl;
		Vector<Pair<int, bool>> memberPlace;
		showFamily(root, memberPlace, false);
	}
}

/***************************************************************************
  �������ƣ�showFamily(treeNode* ptr, Vector<Pair<int, bool>>& memberPlace,bool lastMember)const
  ��    �ܣ���ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::showFamily(treeNode* ptr, Vector<Pair<int, bool>>& memberPlace,bool lastMember)const
{
	if (memberPlace.Isempty())
	{
		cout << ptr->name << endl;
		memberPlace.push_back(Pair<int, bool>(ptr->name.length(), true));
	}
	else
	{
		//��memberPlace�����һ�����Ԫ��ȫ����|��ʽ���(����Ϊ�ո�)
		//���һ������Ƿ�ΪlastMemberȷ��
		int blankNumber = 0;
		//����ǰ��n-2��Ԫ��
		for (int i = 0; i < memberPlace.size() - 1; ++i)
		{
			while (memberPlace[i].first > blankNumber++)
			{
				cout << " ";
			}

			if (memberPlace[i].second)
				cout << "��";
			else
				cout << "   ";
		}

		while (memberPlace[memberPlace.size() - 1].first > blankNumber++)
		{
			cout << " ";
		}
		if (lastMember)
			cout << "��  ";
		else
			cout << "��  ";
		cout << ptr->name << endl;
		memberPlace.push_back(Pair<int, bool>(ptr->name.length() + (*memberPlace.last()).first, true));
	}

	if (!ptr->children.Isempty())
	{
		for (auto i = ptr->children.begin(); i != ptr->children.last(); ++i)
		{
			showFamily(*i, memberPlace, false);
		}
		//�����һ���ˣ���ʱӦ�ð���һ���second����Ϊfalse
		if (!memberPlace.Isempty())
			memberPlace[memberPlace.size() - 1].second = false;
		showFamily(*ptr->children.last(), memberPlace, true);
	}
	memberPlace.pop_back();
}

/***************************************************************************
  �������ƣ�buildTree()
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::buildTree()
{
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	string name;
	cin >> name;
	root = new treeNode(name);
	cout << "�˼��׵������ǣ�" << root->name << endl;
}

/***************************************************************************
  �������ƣ�buildFamily()
  ��    �ܣ�������ͥ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::buildFamily()
{
	cout << "������Ҫ������ͥ���˵�������";
	string name;
	cin >> name;
	//�ڼ����в�ѯ�˳�Աλ��
	treeNode* familyMem = search(name);
	if (familyMem == nullptr)
	{
		cout << "���������޸ó�Ա��" << endl;
		return;
	}
	if (!familyMem->children.Isempty())
	{
		cout << "�ó�Ա���м�ͥ��" << endl;
		return;
	}
	int childrenNum;

	cout << "������" << name << "����Ů������";
	cin >> childrenNum;
	if (cin.fail() || childrenNum < 0) {
		cout << "������һ����������" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		return;
	}

	cout << "����������" << name << "�Ķ�Ů��������";
	for (int i = 0; i < childrenNum; i++) {
		cin >> name;
		if (!count(name)) {
			familyMem->children.push_back(new treeNode(name));
		}
		else {
			cout << "����Ϊ" << name << "�ĳ�Ա�Ѵ��ڣ�" << endl;
		}
	}

	//��ӡ�³�Ա��һ������
	cout << name << "�ĵ�һ�������ǣ�";

	int j = 0;
	for (auto i = familyMem->children.begin(); i != familyMem->children.end(); ++i, j++)
	{
		cout << " " << ((familyMem->children)[j])->name;
	}
	cout << endl;

}

/***************************************************************************
  �������ƣ�addFamilyMem()
  ��    �ܣ�Ϊĳ�������Ů
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::addFamilyMem()
{
	cout << "������Ҫ��ӵĶ��ӣ���Ů�������˵�������";
	string name;
	cin >> name;
	treeNode* familyMem = search(name);
	if (familyMem == nullptr) {
		cout << "�������ڲ����ڸó�Ա��" << endl;
		return;
	}
	cout << "������" << name << "����Ӷ��ӣ���Ů������������";
	cin >> name;
	if (!count(name)) {
		familyMem->children.push_back(new treeNode(name));

	}
	else {
		cout << "����Ϊ" << name << "�ĳ�Ա�Ѵ���" << endl;
	}

	cout << name << "�ĵ�һ�������ǣ�";

	int j = 0;
	for (auto i = familyMem->children.begin(); i != familyMem->children.end(); ++i, j++)
	{
		cout << " " << ((familyMem->children)[j])->name;
	}
	cout << endl;
}

/***************************************************************************
  �������ƣ�delFamily()
  ��    �ܣ���ɢ��ͥ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::delFamily()
{
	cout << "������Ҫ��ɢ�ļ�ͥ���˵�������";
	string name;
	cin >> name;
	treeNode* familyMem = search(name);
	if (familyMem == nullptr) {
		cout << "�������ڲ����ڸó�Ա��" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;

	cout << name << "�ĵ�һ�������ǣ�";

	int j = 0;
	for (auto i = familyMem->children.begin(); i != familyMem->children.end(); ++i, j++)
	{
		cout << " " << ((familyMem->children)[j])->name;
	}
	cout << endl;

	familyMem->children.clear();

}

/***************************************************************************
  �������ƣ�renameFamilyMem()
  ��    �ܣ���������ͥ��Ա
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tree::renameFamilyMem()
{
	cout << "������Ҫ�����������˵�Ŀǰ������";
	string name;
	cin >> name;
	treeNode* familyMem = search(name);
	if (familyMem == nullptr) {
		cout << "�������ڲ����ڸó�Ա" << endl;
		return;
	}
	cout << "��������ĺ��������";
	cin >> name;
	if (!count(name)) {
		cout << familyMem->name << "�Ѹ���Ϊ" << name << endl;
		familyMem->name = name;
	}
	else {
		cout << "����Ϊ" << name << "�ĳ�Ա�Ѵ��ڣ�" << endl;
	}
}

/***************************************************************************
  �������ƣ�searchAt(treeNode* root, const string& name)const
  ��    �ܣ��鿴��ǰ����Ƿ�Ϊ����Ҫ���ҵļ����Ա
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
treeNode* tree::searchAt(treeNode* root, const string& name)const
{
	//�鿴��ǰ����Ƿ�Ϊ����Ҫ���ҵļ����Ա
	if (root->name == name)
		return root;
	treeNode* findResult = nullptr;
	for (auto i = root->children.begin(); i != root->children.end(); ++i)
	{
		findResult = searchAt(*i, name);
		if (findResult != nullptr)
			return findResult;
	}
	return nullptr;
}

/***************************************************************************
  �������ƣ�search(const string& name)const
  ��    �ܣ��鿴ĳ��ͥ��Ա��λ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
treeNode* tree::search(const string& name)const
{
	if (root == nullptr) {
		return nullptr;
	}
	else {
		return searchAt(root, name);
	}
}

inline int tree::count(const string& name)const
{
	return search(name) != nullptr ? 1 : 0;
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
	cout << endl << "**                 ���׹���ϵͳ                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
	cout << "**\t\tA --- ����    ��ͥ\t\t**" << endl;
	cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t\t**" << endl;
	cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t\t**" << endl;
	cout << "**\t\tD --- ���ļ�ͥ��Ա����\t\t**" << endl;
	cout << "**\t\tE --- �˳�    ����\t\t**" << endl;
	cout << "**\t\tF --- ��ӡ����\t\t**" << endl;
	cout << "==================================================" << endl;
	
	char ch = '0';
	tree familyTree;

	familyTree.buildTree();

	while (1) {

		cout << endl << "��ѡ��Ҫִ�еĲ�����";
		cin >> ch;
		if (cin.fail() || (ch < 'A' || ch > 'F')) {
			cout << "�����������������!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}

		switch (ch)
		{
			case 'A':
				familyTree.buildFamily();
				break;
			case 'B':
				familyTree.addFamilyMem();

				break;
			case 'C':
				familyTree.delFamily();

				break;
			case 'D':
				familyTree.renameFamilyMem();

				break;
			case 'E':
				exit(0);
				break;
			case 'F':
				familyTree.showTree();
				break;
			default:
				break;
		}
	}
	return 0;
}
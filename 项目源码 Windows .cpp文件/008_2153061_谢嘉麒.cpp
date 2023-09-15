#define _CRT_SECURE_NO_WARNINGS_
#include <iostream>
#include<string>
using namespace std;

//链表类从此开始
template<class Type>
struct linkNode
{
	//链表结点内数据项
	Type data;
	linkNode<Type>* next, * prev;

	//默认构造函数
	linkNode() :next(nullptr), prev(nullptr) {};
	//构造函数
	linkNode(Type datas, linkNode<Type>* nexts = nullptr, linkNode<Type>* prevs = nullptr) :data(datas), next(nexts), prev(prevs) {};

};

template<class Type>
class linkList
{
	typedef linkNode<Type>* _iterator;


private:
	//头指针
	linkNode<Type>* head;
	//尾指针
	linkNode<Type>* rear;
	//链表长度
	int _size;

public:
	//默认构造函数
	linkList();
	//复制构造函数
	linkList(const linkList<Type>& x);

	//析构函数
	~linkList();

	//迭代器类
	class iterator
	{
	private:
		_iterator data;
	public:

		//默认构造函数
		iterator() :data(nullptr) {};
		//构造函数
		iterator(_iterator datas) :data(datas) {};
		iterator(Type d)
		{
			data = new linkNode<Type>;
			data->data = d;
		}

		//运算符重载
		//读数据操作
		Type operator*()
		{
			return data->data;
		}
		//比较运算符
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

		//自增运算符
		//前置自增
		inline linkList<Type>::iterator& operator++()
		{
			if (this->data != nullptr) {
				this->data = this->data->next;
			}
			return (*this);
		}
		//后置自增
		linkList<Type>::iterator operator++(int)
		{
			linkList<Type>::iterator old = (*this);
			++(*this);
			return old;
		}
		//自减运算符
		//前置自减
		inline linkList<Type>::iterator& operator--()
		{
			if (this->data != nullptr) {
				this->data = this->data->prev;
			}
			return (*this);
		}
		//后置自减
		linkList<Type>::iterator operator--(int)
		{
			linkList<Type>::iterator old = (*this);
			--(*this);
			return old;
		}
		//后面加上一个数
		linkList<Type>::iterator operator+(int index)
		{
			linkList<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i) {
				++old;
			}
			return old;
		}
		//前面加上一个数
		friend typename linkList<Type>::iterator operator+(int index, typename linkList<Type>::iterator data)
		{
			linkList<Type>::iterator old = data;
			for (int i = 0; i < index; ++i)
			{
				++old;
			}
			return old;
		}
		//后面减去一个数
		linkList<Type>::iterator operator-(int index)
		{
			linkList<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i) {
				--old;
			}
			return old;
		}
		//自加
		linkList<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i) {
				++(*this);
			}
			return (*this);
		}
		//自减
		linkList<Type>::iterator& operator-=(int index)
		{
			for (int i = 0; i < index; i++) {
				--(*this);
			}
			return (*this);
		}
		//计算两个迭代器之间的距离
		int operator-(linkList<Type>::iterator i)
		{
			//计算i->data通过几次取next运算能够到达this->data
			int index = 0;
			while (i->data != this->data)
			{
				i++;
				index++;
			}
			return index;
		}

		//友元类
		friend class linkList<Type>;

	};

	//链表长度
	inline int size()const;

	//判断链表是否为空
	inline bool Isempty()const;

	//在尾部插入新数据
	void push_rear(Type data);

	//在头部插入新数据
	void push_front(Type data);

	//查找指定数据，返回迭代器
	linkList<Type>::iterator find(const Type& data)const;

	//删除指定迭代器对应的结点
	Type remove(linkList<Type>::iterator index);

	//删除尾结点
	void erase_rear();

	//删除第一个结点
	void erase_front();

	//清空链表
	void clear();

	//插入结点
	bool insert(linkList<Type>::iterator index, Type i);

	//返回指定位置的一系列函数
	//起始位置迭代器
	inline linkList<Type>::iterator begin();
	inline const linkList<Type>::iterator begin()const;

	//最后位置迭代器
	inline linkList<Type>::iterator end();
	inline const linkList<Type>::iterator end()const;

	//重载等号运算符
	linkList<Type>& operator=(const linkList<Type>& i);

	//友元类
	template<class T>
	friend class Stack;
	template<class T>
	friend class Queue;
};

//默认构造函数
template<class Type>
linkList<Type>::linkList()
{
	head = new linkNode<Type>();
	rear = head;
	_size = 0;
}

//复制构造函数
template<class Type>
linkList<Type>::linkList(const linkList& li)
{
	head = new linkNode<Type>();
	rear = head;
	_size = 0;
	//逐个结点进行复制
	for (auto i = li.begin(); i != li.end(); ++i) {
		this->push_rear(*i);
	}
}

//判断链表是否为空
template<class Type>
inline bool linkList<Type>::Isempty()const
{
	return rear == head;
}

//在尾部插入新数据
template<class Type>
void linkList<Type>::push_rear(Type data)
{
	//判断链表是否为空
	if (Isempty()) {
		//建立新结点
		linkNode<Type>* newNode = new linkNode<Type>(data, nullptr, head);

		//改变头尾指针
		head->next = newNode;
		rear = newNode;
	}
	else {
		//建立新结点
		linkNode<Type>* newNode = new linkNode<Type>(data, nullptr, rear);

		//改变尾指针
		rear->next = newNode;
		rear = newNode;
	}
	++_size;
}

//在头部插入新数据
template<class Type>
void linkList<Type>::push_front(Type data)
{
	//判断链表是否为空
	if (Isempty())
	{
		//建立新结点
		linkNode<Type>* newNode = new linkNode<Type>(data, nullptr, head);

		//改变头尾指针
		head->next = newNode;
		rear = newNode;
	}
	else {
		//建立新结点
		linkNode<Type>* newNode = new linkNode<Type>(data, head->next, head);

		//改变头结点之后的结点指针
		head->next->prev = newNode;

		//改变头结点指针
		head->next = newNode;
	}

	++_size;
}

//求链表长度
template<class Type>
inline int linkList<Type>::size()const
{
	return _size;
}

//返回链表的起始位置
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

//返回链表的最后位置
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

//删除指定迭代器对应的结点
template<class Type>
Type linkList<Type>::remove(typename linkList<Type>::iterator i)
{
	linkNode<Type>* node = i.data;
	Type value = node->data;

	//对node结点的处理
	if (node == rear) {
		//如果node为尾结点
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

//插入某个结点
template<class Type>
bool linkList<Type>::insert(linkList<Type>::iterator index, Type i)
{
	linkNode<Type>* node = index.data;
	node->prev->next = new linkNode<Type>(i, node, node->prev);
	node->prev = node->prev->next;
	return true;
}

//删除尾结点
template<class Type>
void linkList<Type>::erase_rear()
{
	if (!Isempty()) {
		//删除rear对应的结点
		linkNode<Type>* delData = rear;
		rear = rear->prev;
		rear->next = nullptr;
		delete delData;

		_size--;
	}
}

//删除头结点
template<class Type>
void linkList<Type>::erase_front()
{
	if (!Isempty()) {
		linkNode<Type>* delData = head->next;
		//判断尾结点
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

//清空链表
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

//析构函数
template<class Type>
linkList<Type>::~linkList()
{
	this->clear();
	delete this->head;
}

//重载等号运算符
template<class Type>
linkList<Type>& linkList<Type>::operator=(const linkList<Type>& li)
{
	//清空原来的结点
	this->clear();
	//逐个结点复制
	for (auto i = li.begin(); i != li.end(); ++i) {
		this->push_rear(*i);
	}
	return *this;
}

//查找指定数据，返回迭代器
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

//链表类自此结束

//向量类自此开始

#define VECTOR_DEFAULT_SIZE 5 //容量大小

template<class Type>
class Vector
{
	typedef Type* Pointer;
	typedef Pointer _iterator;

private:

	//数据大小
	int _size;

	//当前容量
	int _capacity;

	//数据
	Type* _elements;

	//从data指针中复制从[low,high)的数据
	Type* copyFrom(Type* data, int low, int high, int size = 0);

	//扩大元素容量
	void expand();

public:

	//构造函数

	//默认构造函数
	Vector();

	//初始大小构造函数
	Vector(int size);

	//复制构造函数
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

	//析构函数
	~Vector();

	//迭代器类
	class iterator
	{
	private:
		_iterator data;
	public:
		typedef Type value_type;

		//默认构造函数
		iterator() :data(nullptr) {};

		//构造函数
		iterator(_iterator datas) :data(datas) {};

		//运算符重载

		//读数据
		Type& operator*()
		{
			return *data;
		}

		//比较运算符
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

		//自增运算符

		//前置自增
		inline Vector<Type>::iterator& operator++()
		{
			this->data++;
			return (*this);
		}

		//后置自增
		Vector<Type>::iterator operator++(int)
		{
			Vector<Type>::iterator old = (*this);
			++(*this);
			return old;
		}

		//自减运算符

		//前置自减
		inline Vector<Type>::iterator& operator--()
		{
			this->data--;
			return (*this);
		}

		//后置自减
		Vector<Type>::iterator operator--(int)
		{
			Vector<Type>::iterator old = (*this);
			--(*this);
			return old;
		}

		//后加上一个数
		Vector<Type>::iterator operator+(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; i++)
				++old;
			return old;
		}

		//前加上一个数
		friend typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data) {
			typename Vector<Type>::iterator old = data;
			for (int i = 0; i < index; i++)
				++old;
			return old;
		}

		//后减去一个数
		Vector<Type>::iterator operator-(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; i++)
				--old;
			return old;
		}

		//自加
		Vector<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; i++)
				++(*this);
			return (*this);
		}

		//自减
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

	//向量大小
	inline int size()const;

	//判断向量是否为空
	inline bool Isempty()const;

	//尾部插入数据
	void push_back(const Type data);

	//删除数据
	Type pop_back();

	//在指定迭代器前插入数据
	bool insert(const Vector<Type>::iterator place, Type item);

	//删除指定迭代器的数据
	bool erase(const Vector<Type>::iterator place);

	//清空数据
	void clear();

	//统一赋值
	void fillData(const Type data);

	//返回起始位置迭代器
	inline Vector<Type>::iterator begin();
	inline const Vector<Type>::iterator begin()const;

	//返回最后位置迭代器
	inline Vector<Type>::iterator end();
	inline const Vector<Type>::iterator end()const;

	//获取最后一个元素
	inline Vector<Type>::iterator last();
	inline const Vector<Type>::iterator last()const;

	//获取第一个数据
	Type& front()const
	{
		return this->_elements[0];
	}

	//运算符重载

	//取下标运算符的重载
	inline Type& operator[](int i);

	//等号运算符
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

//默认构造函数
template<class Type>
Vector<Type>::Vector()
{
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;

	//根据默认容量大小分配空间
	this->_elements = new Type[_capacity];
}

//给定初始大小的构造函数
template<class Type>
Vector<Type>::Vector(int size)
{
	this->_size = size;
	this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

	//分配空间
	this->_elements = new Type[_capacity];
}

//复制构造函数
template<class Type>
Vector<Type>::Vector(const Vector& v)
{
	this->_size = v._size;
	this->_capacity = v._capacity;

	//元素一一复制
	this->_elements = copyFrom(v._elements, 0, _size, _capacity);
}

//从data指针中复制[low,high)的数据
template<class Type>
Type* Vector<Type>::copyFrom(Type* data, int low, int high, int size)
{
	if (size == 0) {
		size = high - low;
	}
	//申请空间
	Type* newData = new Type[size];

	//一一复制
	for (int i = low; i < high; i++) {
		newData[i] = data[low + i];
	}

	return newData;
}

//获取向量元素个数
template<class Type>
inline int Vector<Type>::size()const
{
	return this->_size;
}

//扩大元素容量
template<class Type>
void Vector<Type>::expand()
{

	this->_capacity += VECTOR_DEFAULT_SIZE;

	Type* oldElements = this->_elements;

	//复制
	this->_elements = copyFrom(this->_elements, 0, _size, _capacity);

	delete[] oldElements;

}

//插入数据
template<class Type>
void Vector<Type>::push_back(const Type data)
{
	//判断容量
	if (this->_size == this->_capacity) {
		this->expand();
	}
	this->_elements[_size++] = data;
}

//取下标运算符的重载[]
template<class Type>
inline Type& Vector<Type>::operator[](int i)
{
	if (i < 0 || i >= _size)
		;

	return _elements[i];
}

//删除数据
template<class Type>
Type Vector<Type>::pop_back()
{
	if (_size == 0)
		;

	//返回最后一个数据
	return _elements[--_size];
}

//返回向量的起始位置
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

//返回向量的最后位置
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

//前置加一个数
template<class Type>
typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data)
{
	typename Vector<Type>::iterator old = data;
	for (int i = 0; i < index; ++i)
		++old;
	return old;
}

//判断向量是否为空
template<class Type>
inline bool Vector<Type>::Isempty()const
{
	return this->_size == 0;
}

//在指定迭代器前插入数据
template<class Type>
bool Vector<Type>::insert(const typename Vector<Type>::iterator place, Type item)
{
	//提前记录位置(expand后位置发生变化)
	auto places = place;
	int j = places - this->begin();

	//判断是否需要扩容
	if (this->_size == this->_capacity)
		this->expand();

	//把place迭代器后面的元素依次后移一位
	int i;

	for (i = _size - 1; i >= j; --i)
		this->_elements[i + 1] = this->_elements[i];

	//最后插入新元素
	this->_elements[i + 1] = item;
	this->_size++;

	return true;
}

//删除指定迭代器的数据
template<class Type>
bool Vector<Type>::erase(const typename Vector<Type>::iterator place)
{
	//获取place的下标位置
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

//清空数据
template<class Type>
void Vector<Type>::clear()
{
	//清空所有元素
	delete[] _elements;

	//调用默认构造函数
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;
	//根据默认容量大小分配空间
	this->_elements = new Type[_capacity];
}

//析构函数
template<class Type>
Vector<Type>::~Vector()
{
	//清空所有元素
	delete[] _elements;
}

//重载等号运算符
template<class Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& v)
{
	//防止自我等于
	if (v._elements == this->_elements)
		return *this;
	this->clear();
	//一个一个结点的复制过去
	for (auto i = v.begin(); i != v.end(); ++i)
		this->push_back(*i);

	return *this;
}

//统一赋值
template<class Type>
void Vector<Type>::fillData(const Type data)
{
	for (auto i = begin(); i != end(); ++i)
		*i = data;
}

//向量类自此结束

//成对类
template<class T1, class T2>
struct Pair
{
	T1 first;
	T2 second;
	//构造函数
	Pair() {};
	Pair(const T1&, const T2&);
	Pair(const Pair&);
	template<class T3, class T4>
	Pair(const T3& first, const T4& second) :first(first), second(second) {};

	//运算符重载
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
//成对类自此结束

//图类自此开始

#define MAX_LENGTH 1000000

class graph
{
private:
	//顶点
	Vector<string> vertex;

	//邻接表
	Vector<linkList<Pair<int, int>>> adList;

	//prim算法生成的最小生成数
	Vector<Pair<int, int>> mstTree;

	//清空图
	void clear();

	//Prim算法构造最小生成树
	void prim(int pos);

	//判断顶点是否已经在图中
	int IsVertex(const string& vertex);

	//比较两个字符串的辅助函数
	bool strcmp(const string& str1, const string& str2);
public:
	//创建顶点
	void setVertex();

	//创建边
	void setEdge();

	//构造最小生成数
	void buildMST();

	//打印最小生成树
	void printMST();
};

/***************************************************************************
  函数名称：setVertex()
  功    能：输入顶点及名称
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void graph::setVertex()
{
	clear();

	int sumVertex = 0;
	printf("请输入顶点的个数：");
	cin >> sumVertex;
	printf("请依次输入各顶点的名称：\n");
	for (int i = 0; i < sumVertex; i++) {
		string vertexName;
		cin >> vertexName;
		if (IsVertex(vertexName) != -1) {
			cout << "顶点" << vertexName << "已存在，请重新输入！\n";
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
  函数名称：clear()
  功    能：清空内容
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void graph::clear()
{
	vertex.clear();
	adList.clear();
	mstTree.clear();
}

/***************************************************************************
  函数名称：IsVertex(const string& v)
  功    能：判断顶点是否存在，存在则返回其位置
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：strcmp(const string& str1, const string& str2)
  功    能：比较两字符串是否相同
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
bool graph::strcmp(const string& str1, const string& str2)
{
	return str1 == str2 ? true : false;
}

/***************************************************************************
  函数名称：setEdge()
  功    能：创建边
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void graph::setEdge()
{
	string ver1, ver2;
	int edLength;
	while (true)
	{
		cout << "请输入两个顶点及边：";
		cin >> ver1 >> ver2 >> edLength;
		int pos1 = IsVertex(ver1);
		int pos2 = IsVertex(ver2);
		if (edLength <= 0) {
			break;
		}
		else if (pos1 == -1) {
			cout << "顶点" << ver1 << "不存在，请重新输入" << endl;
			continue;
		}
		else if (pos2 == -1) {
			cout << "顶点" << ver2 << "不存在，请重新输入" << endl;
			continue;
		}
		adList[pos1].push_rear(Pair<int, int>(pos2, edLength));
		adList[pos2].push_rear(Pair<int, int>(pos1, edLength));
	}
}

/***************************************************************************
  函数名称：buildMST()
  功    能：生成最小生成树
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void graph::buildMST()
{
	if (vertex.size() == 1) {
		cout << "只有一个顶点，无需生成最小树" << endl;
		return;
	}
	string ver;
	cout << "请输入起始顶点：";
	cin >> ver;
	int pos = IsVertex(ver);
	if (pos == -1) {
		cout << "顶点" << ver << "不存在" << endl;
		return;
	}
	cout << "生成Prim最小生成树！" << endl;
	prim(pos);
}

/***************************************************************************
  函数名称：prim(int pos)
  功    能：prim算法实现
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：printMST()
  功    能：打印最小生成树
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void graph::printMST()
{
	if (!mstTree.size()) {
		cout << "最小生成树尚未生成" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为：\n\n";
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
  函数名称：main()
  功    能：程序主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
	cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
	cout << "**\t\tC --- 构建最小生成树\t\t**" << endl;
	cout << "**\t\tD --- 显示最小生成树\t\t**" << endl;
	cout << "**\t\tE --- 退出   程序\t\t**" << endl;
	cout << "==================================================" << endl;

	bool loop = true;
	char ch = '0';
	graph Grid;
	while (loop) {
		cout << "\n请选择操作：";
		cin >> ch;
		if (cin.fail()) {
			cout << "输入有误，请重新输入A-E（不区分大小写）" << endl;
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
					cout << "输入有误，请重新输入A-E（不区分大小写）" << endl;
					cin.clear();
					cin.ignore(1024,'\n');
					break;
			}
		}
	}
	return 0;
}
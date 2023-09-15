#include<iostream>
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
	if (_elements == nullptr)
		;
}

//给定初始大小的构造函数
template<class Type>
Vector<Type>::Vector(int size)
{
	this->_size = size;
	this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

	//分配空间
	this->_elements = new Type[_capacity];
	if (_elements == nullptr)
		;
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

	if (newData == nullptr)
		;

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
	if (_elements == nullptr)
		;
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

//树类自此开始

struct treeNode
{
	string name;
	Vector<treeNode*> children;

	//构造函数
	treeNode(const string& name) :name(name) {};

private:

	friend class tree;
};

class tree
{
private:
	treeNode* root = nullptr;

public:

	//默认构造函数
	tree() {};

	//建立树
	void buildTree();

	//建立家庭
	void buildFamily();

	//加入家庭成员
	void addFamilyMem();

	//解散局部家庭家庭
	void delFamily();

	//更改家庭成员姓名
	void renameFamilyMem();

	//竖向打印家谱
	void showFamily(treeNode* ptr, Vector<Pair<int, bool>>& memberPlace, bool lastMember)const;

	//用户选择打印家谱
	void showTree();

	//寻找家谱中成员，有则返回结点
	treeNode* search(const string& name)const;

	inline int count(const string& name)const;

	treeNode* searchAt(treeNode* root, const string& name)const;
};

/***************************************************************************
  函数名称：showTree()
  功    能：用户选择是否打印家谱
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tree::showTree()
{
	char h;
	cout << "是否打印家谱树(y/n)" << endl;
	cin >> h;
	if (h == 'y') {
		cout << endl << "当前家谱树为：" << endl;
		Vector<Pair<int, bool>> memberPlace;
		showFamily(root, memberPlace, false);
	}
}

/***************************************************************************
  函数名称：showFamily(treeNode* ptr, Vector<Pair<int, bool>>& memberPlace,bool lastMember)const
  功    能：打印家谱
  输入参数：
  返 回 值：
  说    明：
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
		//将memberPlace除最后一项外的元素全部以|形式输出(或者为空格)
		//最后一项根据是否为lastMember确定
		int blankNumber = 0;
		//对于前面n-2个元素
		for (int i = 0; i < memberPlace.size() - 1; ++i)
		{
			while (memberPlace[i].first > blankNumber++)
			{
				cout << " ";
			}

			if (memberPlace[i].second)
				cout << "│";
			else
				cout << "   ";
		}

		while (memberPlace[memberPlace.size() - 1].first > blankNumber++)
		{
			cout << " ";
		}
		if (lastMember)
			cout << "└  ";
		else
			cout << "├  ";
		cout << ptr->name << endl;
		memberPlace.push_back(Pair<int, bool>(ptr->name.length() + (*memberPlace.last()).first, true));
	}

	if (!ptr->children.Isempty())
	{
		for (auto i = ptr->children.begin(); i != ptr->children.last(); ++i)
		{
			showFamily(*i, memberPlace, false);
		}
		//到最后一个了，此时应该把上一层的second更改为false
		if (!memberPlace.Isempty())
			memberPlace[memberPlace.size() - 1].second = false;
		showFamily(*ptr->children.last(), memberPlace, true);
	}
	memberPlace.pop_back();
}

/***************************************************************************
  函数名称：buildTree()
  功    能：创建家谱
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tree::buildTree()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string name;
	cin >> name;
	root = new treeNode(name);
	cout << "此家谱的祖先是：" << root->name << endl;
}

/***************************************************************************
  函数名称：buildFamily()
  功    能：创建家庭
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tree::buildFamily()
{
	cout << "请输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	//在家谱中查询此成员位置
	treeNode* familyMem = search(name);
	if (familyMem == nullptr)
	{
		cout << "本家谱内无该成员！" << endl;
		return;
	}
	if (!familyMem->children.Isempty())
	{
		cout << "该成员已有家庭！" << endl;
		return;
	}
	int childrenNum;

	cout << "请输入" << name << "的子女个数：";
	cin >> childrenNum;
	if (cin.fail() || childrenNum < 0) {
		cout << "请输入一个正整数！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		return;
	}

	cout << "请依次输入" << name << "的儿女的姓名：";
	for (int i = 0; i < childrenNum; i++) {
		cin >> name;
		if (!count(name)) {
			familyMem->children.push_back(new treeNode(name));
		}
		else {
			cout << "姓名为" << name << "的成员已存在！" << endl;
		}
	}

	//打印新成员第一代子孙
	cout << name << "的第一代子孙是：";

	int j = 0;
	for (auto i = familyMem->children.begin(); i != familyMem->children.end(); ++i, j++)
	{
		cout << " " << ((familyMem->children)[j])->name;
	}
	cout << endl;

}

/***************************************************************************
  函数名称：addFamilyMem()
  功    能：为某人添加子女
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tree::addFamilyMem()
{
	cout << "请输入要添加的儿子（或女儿）的人的姓名：";
	string name;
	cin >> name;
	treeNode* familyMem = search(name);
	if (familyMem == nullptr) {
		cout << "本家谱内不存在该成员！" << endl;
		return;
	}
	cout << "请输入" << name << "新添加儿子（或女儿）的姓名：";
	cin >> name;
	if (!count(name)) {
		familyMem->children.push_back(new treeNode(name));

	}
	else {
		cout << "姓名为" << name << "的成员已存在" << endl;
	}

	cout << name << "的第一代子孙是：";

	int j = 0;
	for (auto i = familyMem->children.begin(); i != familyMem->children.end(); ++i, j++)
	{
		cout << " " << ((familyMem->children)[j])->name;
	}
	cout << endl;
}

/***************************************************************************
  函数名称：delFamily()
  功    能：解散家庭
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tree::delFamily()
{
	cout << "请输入要解散的家庭的人的姓名：";
	string name;
	cin >> name;
	treeNode* familyMem = search(name);
	if (familyMem == nullptr) {
		cout << "本家谱内不存在该成员！" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;

	cout << name << "的第一代子孙是：";

	int j = 0;
	for (auto i = familyMem->children.begin(); i != familyMem->children.end(); ++i, j++)
	{
		cout << " " << ((familyMem->children)[j])->name;
	}
	cout << endl;

	familyMem->children.clear();

}

/***************************************************************************
  函数名称：renameFamilyMem()
  功    能：重命名家庭成员
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tree::renameFamilyMem()
{
	cout << "请输入要更改姓名的人的目前姓名：";
	string name;
	cin >> name;
	treeNode* familyMem = search(name);
	if (familyMem == nullptr) {
		cout << "本家谱内不存在该成员" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	cin >> name;
	if (!count(name)) {
		cout << familyMem->name << "已更名为" << name << endl;
		familyMem->name = name;
	}
	else {
		cout << "姓名为" << name << "的成员已存在！" << endl;
	}
}

/***************************************************************************
  函数名称：searchAt(treeNode* root, const string& name)const
  功    能：查看当前结点是否为所需要查找的家族成员
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
treeNode* tree::searchAt(treeNode* root, const string& name)const
{
	//查看当前结点是否为所需要查找的家族成员
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
  函数名称：search(const string& name)const
  功    能：查看某家庭成员的位置
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：main()
  功    能：程序主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	cout << endl << "**                 家谱管理系统                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA --- 完善    家庭\t\t**" << endl;
	cout << "**\t\tB --- 添加家庭成员\t\t**" << endl;
	cout << "**\t\tC --- 解散局部家庭\t\t**" << endl;
	cout << "**\t\tD --- 更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE --- 退出    程序\t\t**" << endl;
	cout << "**\t\tF --- 打印家谱\t\t**" << endl;
	cout << "==================================================" << endl;
	
	char ch = '0';
	tree familyTree;

	familyTree.buildTree();

	while (1) {

		cout << endl << "请选择要执行的操作：";
		cin >> ch;
		if (cin.fail() || (ch < 'A' || ch > 'F')) {
			cout << "输入错误，请重新输入!" << endl;
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
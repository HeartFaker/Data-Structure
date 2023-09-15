#include<iostream>
#include<cstring>
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

//栈类由此开始

template<class Type>
class Stack
{
private:
	//定义链式栈
	linkList<Type> data;
public:
	//默认构造函数
	Stack();

	//判断是否栈空
	inline bool Isempty()const;

	//返回栈的大小
	inline int size()const;

	//入栈
	void push(const Type& i);
	//出栈
	void pop();

	//获取栈顶元素
	const Type& top()const;
};

//默认构造函数
template<class Type>
Stack<Type>::Stack()
{
	//无需构造对象
}

//判断栈是否为空
template<class Type>
inline bool Stack<Type>::Isempty()const
{
	return this->data.Isempty();
}

//入栈
template<class Type>
void Stack<Type>::push(const Type& i)
{
	this->data.push_rear(i);
}

//出栈
template<class Type>
void Stack<Type>::pop()
{
	this->data.erase_rear();
}

//获取栈顶元素
template<class Type>
const Type& Stack<Type>::top()const
{
	return this->data.rear->data;
}

//返回栈大小
template<class Type>
inline int Stack<Type>::size()const
{
	return this->data._size;
}

//栈类由此结束

/***************************************************************************
  函数名称：translation(const char* s)
  功    能：表达式转换函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void translation(const char* s)
{
	//定义栈存储表达式运算符
	Stack<char> ope;
	//压入终止字符
	ope.push('0');
	int isFirst = 0;
	for (int i = 0; s[i] != '\0'; ) {
		int j = 0;
		//跳过空格
		for (; s[i + j] != ' '&& s[i + j] != '\0'; j++)
			;
		//读取表达式运算数
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
	//将栈中剩余内容输出
	while (ope.size()!=1)
	{
		if (ope.top() != '(') {
			printf(" %c", ope.top());
		}
		ope.pop();
	}
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
	cout << "欢迎使用表达式转换程序！" << endl;
	while (1) {
		char expression[110];
		char s;
		cout << "请输入后缀表达式：" << endl;
		cin.getline(expression, 1024);
		translation(expression);
		while (1) {
			cout << endl << "是否继续运算?（y/n）";
			cin >> s;
			if (!cin.good() || (s != 'y' && s != 'n')) {
				cin.clear();
				cin.ignore(2147483648, '\n');
				cout << "输入错误,请重新输入!" << endl;
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
			cout << "欢迎下次再次使用!" << endl;
			exit(0);
		}
	}
	return 0;
}
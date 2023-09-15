#include<assert.h>
#include<iostream>
using namespace std;
template<class Type>
class Queue;

//建立带附加头结点的单链表结点类
template<class T>
struct LinkNode {

	//仅初始化指针成员的结点类构造函数
	LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }

	//初始化数据与指针成员的构造函数
	LinkNode(const T& item, LinkNode<T>* ptr = NULL) { data = item; link = ptr; }

	T data;  //表内数据
	LinkNode<T>* link;  //结点指针
};

//建立链表类
template<class T>
class List {
public:

	template<class Type>
	friend class Queue;

	//链表类构造函数
	List() { first = new LinkNode<T>; }
	List(const T& x) { first = new LinkNode<T>(x); }

	//复制构造函数
	List(List<T>& L);

	//置空链表
	void makeEmpty();

	//链表类析构函数
	~List();

	//计算链表的长度
	int Length()const;

	//返回附加头节点的地址
	LinkNode<T>* getHead()const { return first; }

	//在链表中查找含有数据x的结点
	LinkNode<T>* Search(T x);

	//搜索第i个元素的地址
	LinkNode<T>* locate(int i);

	//取出第i个元素的值
	bool getData(int i, T& x)const;

	//用x修改第i个元素的值
	void setData(int i, T& x);

	//在第i个元素后插入x
	bool Insert(int i, T& x);

	//删去第i个元素，x返回该元素的值
	bool Remove(int i, T& x);

	//判断表是否空，空则返回true
	bool Isempty()const
	{
		return first->link == NULL ? true : false;
	}

	//输出链表内所有结点
	void outputAll();

	//重载函数：赋值
	List<T>& operator = (List<T>& L);

	//后插法建立单链表
	void inputRear(T endTag);
	//前插法建立单链表
	void inputFront(T endTag);

	//在尾部插入新数据
	void insert_rear(const T x);

	//删除第一个数据结点
	void delete_first();

private:
	LinkNode<T>* first;  //单链表的表头指针
	LinkNode<T>* tail;   //单链表的表尾指针
};

/***************************************************************************
  函数名称：List<T>::List(List<T>& L)
  功    能：复制构造函数
  输入参数：List<T>& L
  返 回 值：
  说    明：
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
  函数名称：void List<T>::makeEmpty()
  功    能：置空链表，释放内存
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：List<T>::~List()
  功    能：链表类的析构函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
template<class T>
List<T>::~List()
{
	makeEmpty();
}

/***************************************************************************
  函数名称：List<T>::Length()const
  功    能：计算带附加头结点的单链表长度
  输入参数：
  返 回 值：return count;
  说    明：
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
  函数名称：LinkNode<T>* List<T>::Search(T x)
  功    能：在链表中搜索含有数据x的结点
  输入参数：T x
  返 回 值：查找成功时返回其结点地址，否则返回NULL
  说    明：
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
  函数名称：LinkNode<T>* List<T>::locate(int i)
  功    能：搜索第i个结点的地址
  输入参数：int i
  返 回 值：return current;
  说    明：
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
  函数名称：bool List<T>::getData(int i, T& x)const
  功    能：取出第i个结点的值
  输入参数：int i，T& x
  返 回 值：0/1
  说    明：
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
  函数名称：List<T>::setData(int i, T& x)
  功    能：用x修改第i个结点的值
  输入参数：int i，T& x
  返 回 值：
  说    明：
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
  函数名称：List<T>::Insert(int i, T& x)
  功    能：在第i个元素后插入x
  输入参数：int i, T& x
  返 回 值：return true OR false
  说    明：
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
		cerr << "存储分配错误！！" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

/***************************************************************************
  函数名称：List<T>::Remove(int i,T& x)
  功    能：将链表第i个位置的结点删除,通过引用型参数x返回该元素的值
  输入参数：int i, T& x
  返 回 值：return true OR false
  说    明：
***************************************************************************/
template<class T>
bool List<T>::Remove(int i, T& x)
{
	LinkNode<T>* current = locate(i - 1);
	if (current == NULL || current->link == NULL) {
		cerr << "删除不成功" << endl;
		return false;
	}
	LinkNode<T>* del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

/***************************************************************************
  函数名称：List::outputAll()
  功    能：输出所有链表内容
  输入参数：
  返 回 值：
  说    明：
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
函数名称：List<T>::operator=(List<T>& L)
功    能：重载赋值运算符
输入参数：
返 回 值：
说    明：
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
  函数名称：List<T>::inputRear(T endTag)
  功    能：后插法建立单链表
  输入参数：
  返 回 值：
  说    明：
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
			cerr << "存储分配错误" << endl;
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
  函数名称：List<T>::inputFront(T endTag)
  功    能：前插法建立单链表
  输入参数：
  返 回 值：
  说    明：
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
			cerr << "存储分配错误" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		cin >> val;
	}
	return;
}

//在尾部插入新数据
template<class Type>
void List<Type>::insert_rear(const Type data)
{
	//判断链表是否为空
	if (Isempty())
	{
		//建立新结点
		LinkNode<Type>* newNode = new LinkNode<Type>(data, first);

		//改变头指针和尾指针
		first->link = newNode;
		tail = newNode;
	}
	else
	{
		//建立新结点
		LinkNode<Type>* newNode = new LinkNode<Type>(data, tail);

		//改变尾指针
		tail->link = newNode;
		tail = newNode;
	}
}

// 删除头结点
template<class Type>
void List<Type>::delete_first()
{
	if (!Isempty())
	{
		//删除tail的后继结点
		LinkNode<Type>* delData = first->link;
		//判断尾结点
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

//定义队列类
template<class Type>
class Queue
{
private:
	//内部定义一个链表
	List<Type> data;

public:
	//构造函数
	//默认构造函数
	Queue();

	//判断队列是否为空
	inline bool empty()const;
	//返回队列大小
	inline int size()const;

	//入队
	void push(const Type& i);
	//出队
	void pop();

	//获取队首元素
	const Type& front()const;
	Type& front();
};

//默认构造函数
template<class Type>
Queue<Type>::Queue()
{

}

//判断队列是否为空
template<class Type>
inline bool Queue<Type>::empty()const
{
	return this->data.Isempty();
}

//返回队列大小
template<class Type>
inline int Queue<Type>::size()const
{
	return this->data.Length();
}

//入队
template<class Type>
void Queue<Type>::push(const Type& i)
{
	this->data.insert_rear(i);
}

//出队
template<class Type>
void Queue<Type>::pop()
{
	this->data.delete_first();
}

//获取队首元素
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
  函数名称：main()
  功    能：程序主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	int N;//顾客总数
	//直至输入正确
	while (1) {
		while (1)
		{
			cout << "请输入客户总数和各位客户的编号：";
			cin >> N;
			if (N <= 0)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入错误，请重新输入。" << endl;
			}
			else
				break;
		}
		Queue<int> queueA, queueB;
		//顾客入队
		for (int i = 1; i <= N; ++i)
		{
			int temp;
			cin >> temp;
			//偶数入B队，奇数入A队
			if (temp % 2 == 0)
				queueB.push(temp);
			else
				queueA.push(temp);
		}
		cout << "Output:";
		//出队
		while (!queueA.empty() || !queueB.empty())
		{
			//A业务处理完毕
			for (int i = 0; i < 2; ++i)
				if (!queueA.empty())
				{
					cout << queueA.front() << " ";
					queueA.pop();
				}
			//B业务处理完毕
			if (!queueB.empty())
			{
				cout << queueB.front() << " ";
				queueB.pop();
			}
		}
		char s = '0';
		while (1) {
			cout << endl << "是否继续?（y/n）";
			cin >> s;
			if (!cin.good() || (s != 'y' && s != 'n')) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入错误,请重新输入!" << endl;
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
			cout << "欢迎下次再次使用!" << endl;
			exit(0);
		}
	}
	return 0;
}
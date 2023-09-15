#include<iostream>
using namespace std;

template<class T>
class List;

//建立带附加头结点的单链表结点类
template<class T>
struct LinkNode {

	//重载输入输出运算符，并声明为结点类的友元函数
	friend std::istream& operator>>(std::istream& istr, LinkNode<T>& x);
	friend std::ostream& operator<<(std::ostream& ostr, const LinkNode<T>& x);

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
	bool IsEmpty()const
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

	//求有序链表的交集
	void intersection(List<T>& L);

private:
	LinkNode<T>* first;  //单链表的表头指针
};

/***************************************************************************
  函数名称：istream& operator>>(istream& istr, LinkNode<T>& x)
  功    能：重载输入运算符，整体输入结点类
  输入参数：istream& istr, LinkNode& x
  返 回 值：return istr;
  说    明：
***************************************************************************/
template<class T>
istream& operator>>(istream& istr, LinkNode<T>& x)
{
	istr >> x.data;
	return istr;
}

/***************************************************************************
  函数名称：ostream& operator<<(ostream& ostr, const LinkNode<T>& x)
  功    能：重载输出运算符，整体输出结点类
  输入参数：ostream& ostr, const LinkNode& x
  返 回 值：return ostr;
  说    明：
***************************************************************************/
template<class T>
ostream& operator<<(ostream& ostr, const LinkNode<T>& x)
{
	ostr << x.data << endl;
	return ostr;
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

/***************************************************************************
  函数名称：List<T>::intersection(List<T>& L)
  功    能：求两个有序链表的交集
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：main()
  功    能：程序主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	while (1) {
		List<int> list1, list2;
		cout << "请输入非降序链表1：";
		list1.inputRear(-1);
		cout << endl << "请输入非降序链表2：";
		list2.inputRear(-1);
		cout << endl;
		cout << "这两个有序链表的交集为：";
		list1.intersection(list2);
		char s;
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
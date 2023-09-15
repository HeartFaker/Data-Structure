#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

class examRegSys_list;

//建立链表结点类
class examRegSys_linkNode {
public:
	friend class examRegSys_list; //将链表类声明为结点类的友元类，方便访问
	friend std::istream& operator>>(std::istream& istr, examRegSys_linkNode& x);     //重载输入输出运算符，并声明为结点类的友元函数
	friend std::ostream& operator<<(std::ostream& ostr, const examRegSys_linkNode& x);
	examRegSys_linkNode(examRegSys_linkNode* ptr = NULL) {};  //结点类构造函数
	~examRegSys_linkNode() {};      //结点类析构函数
private:
	int examRegNum;    //考号
	char name[20];     //姓名
	char gender[5];    //性别
	int age;           //年龄
	char category[40]; //报考类别
	examRegSys_linkNode* link;  //结点指针
};

//建立链表类
class examRegSys_list {
private:
	examRegSys_linkNode* first;  //单链表的表头指针
	int sum;
public:
	examRegSys_list();                   //链表类构造函数
	~examRegSys_list();                  //链表类析构函数
	void setSum();                       //设定总人数
	void makeEmpty();                    //置空链表
	examRegSys_linkNode* locate(int i);  //定位链表中某一结点
	void outputAll();                    //打印链表所有结点
	void outputSingle(examRegSys_linkNode* x);          //根据地址输出某单个结点
	void inputRear();                    //后插法建立单链表
	void inputRear(examRegSys_linkNode* node);
	void choose();                        //确定用户输入的操作要求
	bool Insert(int i);                       //将新元素插入到链表中第i个结点后
	bool Remove(int i);                       //将链表中第i个元素删去
	examRegSys_linkNode* Search(int i);                       //在链表中查找含有数据i的结点，成功则返回其结点地址
	examRegSys_linkNode* Modify(int i);                       //在链表中查找含有数据i的结点，并对其重新输入进行修改
	void Summary(char statistic);                             //根据用户需求统计性别，年龄或报考类别
	bool Compare(const examRegSys_linkNode* current, char statistic, const char gender[5], const int age, const char cate[15]);
};

/***************************************************************************
  函数名称：My_strlen
  功    能：求字符串str的长度
  输入参数：str
  返 回 值：字符串长度
  说    明：
***************************************************************************/
int My_strlen(const char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		;
	return i;
}

/***************************************************************************
  函数名称：My_strcpy
  功    能：将字符串s2复制到s1中，并覆盖原内容，复制时包含\0
  输入参数：s1,s2
  返 回 值：0
  说    明：
***************************************************************************/
int My_strcpy(char s1[], const char s2[])
{
	int i, j;
	i = j = 0;
	for (int k = 0; k <= My_strlen(s1); k++) {
		s1[k] = '\0';
	}
	for (; i <= My_strlen(s2); i++, j++) {
		s1[j] = s2[i];
	}
	return 0;
}

/***************************************************************************
  函数名称：My_strcmp
  功    能：比较字符串s1和s2大小，英文字母区分大小写
  输入参数：s1，s2
  返 回 值：相等为0；不等则为第一个不等字符的ASCII差值
  说    明：
***************************************************************************/
int My_strcmp(const char s1[], const char s2[])
{
	int i = 0;
	while (1) {
		if (s1[i] != s2[i] || (s1[i] == '\0' && s2[i] == '\0')) {
			break;
		}
		i++;
	}
	if (i >= My_strlen(s1) || i >= My_strlen(s2)) {
		return 0;
	}
	else {
		return s1[i] - s2[i];
	}
}

/***************************************************************************
  函数名称：examRegSys_list::examRegSys_list()
  功    能：链表类的构造函数，为结点类分配空间
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
examRegSys_list::examRegSys_list()
{
	first = new examRegSys_linkNode;
	sum = 0;
}

/***************************************************************************
  函数名称：examRegSys_list::~examRegSys_list()
  功    能：链表类的析构函数，置空链表
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
examRegSys_list::~examRegSys_list()
{
	makeEmpty();
}

/***************************************************************************
  函数名称：examRegSys_list::setSum()
  功    能：用户输入报名总人数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void examRegSys_list::setSum()
{
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	while (1) {
		cin >> sum;
		if (!cin.good() || sum < 0) {
			cin.clear();
			cin.ignore(2147483648, '\n');
			continue;
		}
		else {
			break;
		}
	}
}

/***************************************************************************
  函数名称：void examRegSys_list::makeEmpty()
  功    能：置空链表，释放内存
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void examRegSys_list::makeEmpty()
{
	examRegSys_linkNode* q;
	while (first->link != NULL) {
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

/***************************************************************************
  函数名称：examRegSys_linkNode* examRegSys_list::locate(int i)
  功    能：定位到链表类内的某一结点
  输入参数：int i
  返 回 值：return current;
  说    明：
***************************************************************************/
examRegSys_linkNode* examRegSys_list::locate(int i)
{
	if (i < 0) {
		return NULL;
	}
	examRegSys_linkNode* current = first;
	int k = 0;
	while (current != NULL && k < i) {
		current = current->link;
		k++;
	}
	return current;
}

/***************************************************************************
  函数名称：examRegSys_list::outputAll()
  功    能：输出所有链表内容
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void examRegSys_list::outputAll()
{
	cout << endl << "考号      姓名      性别      年龄      报考类型" << endl;
	examRegSys_linkNode* current = first->link;
	while (current != NULL) {
		outputSingle(current);
		current = current->link;
	}
	return;
}

/***************************************************************************
  函数名称：examRegSys_list::outputSingle(examRegSys_linkNode* x)
  功    能：根据参数地址输出单个结点内容
  输入参数：examRegSys_linkNode* x
  返 回 值：
  说    明：
***************************************************************************/
void examRegSys_list::outputSingle(examRegSys_linkNode* x)
{
	cout << setiosflags(ios::left) << setw(10) << x->examRegNum << setw(10) << x->name
		<< setw(10) << x->gender << setw(10) << x->age << setw(10) << x->category << endl;
}

/***************************************************************************
  函数名称：examRegSys_list::inputRear()
  功    能：后插法建立单链表
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void examRegSys_list::inputRear()
{
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	examRegSys_linkNode* newNode, * last, node;
	int i = 0;
	makeEmpty();
	last = first;
	while (i < sum) {
		cin >> node;
		newNode = new examRegSys_linkNode(node);
		if (newNode == NULL) {
			cerr << "存储分配错误" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		i++;
	}
	last->link = NULL;
	return;
}

/***************************************************************************
  函数名称：istream& operator>>(istream& istr, examRegSys_linkNode& x)
  功    能：重载输入运算符，整体输入结点类
  输入参数：istream& istr, examRegSys_linkNode& x
  返 回 值：return istr;
  说    明：
***************************************************************************/
istream& operator>>(istream& istr, examRegSys_linkNode& x)
{
	istr >> x.examRegNum >> x.name >> x.gender >> x.age >> x.category;
	return istr;
}

/***************************************************************************
  函数名称：ostream& operator<<(ostream& ostr, const examRegSys_linkNode& x)
  功    能：重载输出运算符，整体输出结点类
  输入参数：ostream& ostr, const examRegSys_linkNode& x
  返 回 值：return ostr;
  说    明：
***************************************************************************/
ostream& operator<<(ostream& ostr, const examRegSys_linkNode& x)
{
	ostr << setiosflags(ios::left) << setw(10) << x.examRegNum << setw(10) << x.name
		<< setw(10) << x.gender << setw(10) << x.age << setw(10) << x.category << endl;
	return ostr;
};

/***************************************************************************
  函数名称：examRegSys_list::choose()
  功    能：确定用户输入的操作要求，并执行相关操作
  输入参数：
  返 回 值：return x;
  说    明：
***************************************************************************/
void examRegSys_list::choose()
{
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl << endl;
	cout << "请选择您要进行的操作：";
	int x = -1;
	int i = -1;
	char statistics = '1';
	while (1) {
		cin >> x;
		if (!cin.good() || x < 0 || x>5) {
			cin.clear();
			cin.ignore(2147483648, '\n');
			continue;
		}
		else {
			break;
		}
	}
	switch (x)
	{
		case 1:
			cout << "请输入您要插入的考生的位置：";
			while (1) {
				cin >> i;
				if (!cin.good()) {
					cin.clear();
					cin.ignore(2147483648, '\n');
					continue;
				}
				else {
					break;
				}
			}
			if (i == 0) {
				cout << "取消本次操作" << endl;
				return;
			}
			Insert(i);
			break;
		case 2:
			cout << "请输入您要删除的考生的位置：";
			while (1) {
				cin >> i;
				if (!cin.good()) {
					cin.clear();
					cin.ignore(2147483648, '\n');
					continue;
				}
				else {
					break;
				}
			}
			if (i == 0) {
				cout << "取消本次操作" << endl;
				return;
			}
			Remove(i);
			break;
		case 3:
			cout << "请输入要查找的考生的考号：";
			while (1) {
				cin >> i;
				if (!cin.good()) {
					cin.clear();
					cin.ignore(2147483648, '\n');
					continue;
				}
				else {
					break;
				}
			}
			if (i == 0) {
				cout << "取消本次操作" << endl;
				return;
			}
			cout << endl << "考号      姓名      性别      年龄      报考类型" << endl;
			Search(i);
			break;
		case 4:
			cout << "请输入要修改的考生的考号：";
			while (1) {
				cin >> i;
				if (!cin.good()) {
					cin.clear();
					cin.ignore(2147483648, '\n');
					continue;
				}
				else {
					break;
				}
			}
			if (i == 0) {
				cout << "取消本次操作" << endl;
				return;
			}
			Modify(i);
			cout << "修改结果如下：" << endl;
			break;
		case 5:
			cout << "请输入要统计的项目（a为性别，b为年龄，c为报考类别，0为取消本次操作）";
			while (1) {
				cin >> statistics;
				if (!cin.good() || (statistics != 'a' && statistics != 'b' && statistics != 'c' && statistics != '0')) {
					cin.clear();
					cin.ignore(2147483648, '\n');
					continue;
				}
				else {
					break;
				}
			}
			if (statistics == '0') {
				cout << "取消本次操作" << endl;
				return;
			}
			Summary(statistics);
			break;
		case 0:
			cout << "当前未选择操作，请重新选择" << endl;
			break;
		default:
			break;
	}
	cout << endl;
	outputAll();
	return;
}

/***************************************************************************
  函数名称：examRegSys_list::Insert(int i)
  功    能：将新元素插入到链表第i个位置
  输入参数：int i
  返 回 值：return true OR false
  说    明：
***************************************************************************/
bool examRegSys_list::Insert(int i)
{
	examRegSys_linkNode* current = locate(i - 1), node;
	if (current == NULL) {
		cout << "插入不成功" << endl;
		return false;
	}
	cout << "请依次输入要插入的考生的考生号，姓名，性别，年龄和报考类型！" << endl;
	cin >> node;
	examRegSys_linkNode* newNode = new examRegSys_linkNode(node);
	if (newNode == NULL) {
		cerr << "存储分配错误！！" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

/***************************************************************************
  函数名称：examRegSys_list::Remove(int i)
  功    能：将链表第i个位置的结点删除
  输入参数：int i
  返 回 值：return true OR false
  说    明：
***************************************************************************/
bool examRegSys_list::Remove(int i)
{
	examRegSys_linkNode* current = locate(i - 1);
	if (current == NULL || current->link == NULL) {
		cerr << "删除不成功" << endl;
		return false;
	}
	examRegSys_linkNode* del = current->link;
	current->link = del->link;
	cout << "你删除的考生信息是:  ";
	outputSingle(del);
	delete del;
	return true;
}

/***************************************************************************
  函数名称：examRegSys_list::Search(int x)
  功    能：在链表中搜索含有数据x的结点，并打印出来
  输入参数：int i
  返 回 值：查找成功时返回其结点地址，否则返回NULL
  说    明：
***************************************************************************/
examRegSys_linkNode* examRegSys_list::Search(int i)
{
	examRegSys_linkNode* current = first->link;
	while (current != NULL) {
		if (current->examRegNum == i) {
			break;
		}
		else {
			current = current->link;
		}
	}
	outputSingle(current);
	return current;
}

/***************************************************************************
  函数名称：examRegSys_list::Modify(int i)
  功    能：在链表中搜索含有数据i的结点，并修改其结点内容
  输入参数：int i
  返 回 值：查找成功时返回其结点地址，否则返回NULL
  说    明：
***************************************************************************/
examRegSys_linkNode* examRegSys_list::Modify(int i)
{
	examRegSys_linkNode* current = first->link, node;
	while (current != NULL) {
		if (current->examRegNum == i) {
			outputSingle(current);
			break;
		}
		else {
			current = current->link;
		}
	}
	if (current == NULL) {
		cerr << "查无此考号" << endl;
		return current;
	}
	cout << "请输入修改后的考生考号，姓名，性别，年龄和报考类别！" << endl;
	cin >> node;
	current->examRegNum = node.examRegNum;
	My_strcpy(current->name, node.name);
	My_strcpy(current->gender, node.gender);
	current->age = node.age;
	My_strcpy(current->category, node.category);
	return current;
}

/***************************************************************************
  函数名称：examRegSys_list::Summary(char statistic)
  功    能：根据用户的需要，统计链表内的性别，年龄和报考类别
  输入参数：char statistic
  返 回 值：
  说    明：
***************************************************************************/
void examRegSys_list::Summary(char statistic)
{
	char gender[5], cate[15];
	int age = 0;
	switch (statistic)
	{
		case 'a':
			cout << "请输入需要统计的性别：";
			cin >> gender;
			break;
		case 'b':
			cout << "请输入需要统计的年龄：";
			cin >> age;
			break;
		case 'c':
			cout << "请输入需要统计的报考类别：";
			cin >> cate;
			break;
		default:
			break;
	}
	int IfFound = 0;
	examRegSys_linkNode* current = first->link;
	while (current != NULL) {
		if (Compare(current, statistic, gender, age, cate)) {
			IfFound = 1;
			outputSingle(current);
		}
		current = current->link;
	}
	if (IfFound == 0) {
		cerr << "查无此考号" << endl;
		return;
	}
}

bool examRegSys_list::Compare(const examRegSys_linkNode* current, char statistic, const char gender[5], const int age, const char cate[15])
{
	switch (statistic)
	{
		case 'a':
			if (My_strcmp(current->gender, gender) == 0) {
				return true;
			}
			break;
		case 'b':
			if (current->age == age) {
				return true;
			}
			break;
		case 'c':
			if (My_strcmp(current->category, cate) == 0) {
				return true;
			}
			break;
		default:
			break;
	}
	return false;
}


int main()
{
	examRegSys_list list;
	/*
	char ch = '0';
	while (1) {
		cout << "请输入想要读取考生信息的方法（1-从文件读取/2-手动输入）";
		cin >> ch;
		if (cin.fail() || (ch != '1' && ch != '2')) {
			cin.clear();
			cin.ignore('/n', 1024);
			continue;
		}
		else {
			cin.clear();
			cin.ignore('/n', 1024);
			break;
		}
	}
	switch (ch) {

		case '1':
		{
			cout << "请输入要存储文件的名称(输入0代表读取默认文件)" << endl;
			string loadFile;
			cin >> loadFile;
			if (loadFile.length() == 0)
			{
				cout << "无效名称，自动读取名为Student.txt的文件" << endl;
				loadFile = "Student.txt";
			}
			else if (loadFile == "0")
			{
				cout << "开始读取默认文件" << endl;
				loadFile = "Student.txt";
			}
			else
			{
				loadFile += ".txt";
			}

			ifstream file(loadFile);
			examRegSys_linkNode* temp;
			cout << endl << "开始读取数据:" << endl;

			while (file.peek() != EOF)
			{
				file >> temp;
				list.inputRear(temp);
			}

			cout << "成功读取数据！" << endl;
			break;
		}
		case '2':
			list.setSum();
			list.inputRear();
			list.outputAll();
			break;
		default:
			break;
	}*/
	
	list.setSum();
	list.inputRear();
	list.outputAll();
	while (1)
	{
		list.choose();
	}
	return 0;
}
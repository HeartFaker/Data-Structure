#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

class examRegSys_list;

//������������
class examRegSys_linkNode {
public:
	friend class examRegSys_list; //������������Ϊ��������Ԫ�࣬�������
	friend std::istream& operator>>(std::istream& istr, examRegSys_linkNode& x);     //������������������������Ϊ��������Ԫ����
	friend std::ostream& operator<<(std::ostream& ostr, const examRegSys_linkNode& x);
	examRegSys_linkNode(examRegSys_linkNode* ptr = NULL) {};  //����๹�캯��
	~examRegSys_linkNode() {};      //�������������
private:
	int examRegNum;    //����
	char name[20];     //����
	char gender[5];    //�Ա�
	int age;           //����
	char category[40]; //�������
	examRegSys_linkNode* link;  //���ָ��
};

//����������
class examRegSys_list {
private:
	examRegSys_linkNode* first;  //������ı�ͷָ��
	int sum;
public:
	examRegSys_list();                   //�����๹�캯��
	~examRegSys_list();                  //��������������
	void setSum();                       //�趨������
	void makeEmpty();                    //�ÿ�����
	examRegSys_linkNode* locate(int i);  //��λ������ĳһ���
	void outputAll();                    //��ӡ�������н��
	void outputSingle(examRegSys_linkNode* x);          //���ݵ�ַ���ĳ�������
	void inputRear();                    //��巨����������
	void inputRear(examRegSys_linkNode* node);
	void choose();                        //ȷ���û�����Ĳ���Ҫ��
	bool Insert(int i);                       //����Ԫ�ز��뵽�����е�i������
	bool Remove(int i);                       //�������е�i��Ԫ��ɾȥ
	examRegSys_linkNode* Search(int i);                       //�������в��Һ�������i�Ľ�㣬�ɹ��򷵻������ַ
	examRegSys_linkNode* Modify(int i);                       //�������в��Һ�������i�Ľ�㣬������������������޸�
	void Summary(char statistic);                             //�����û�����ͳ���Ա�����򱨿����
	bool Compare(const examRegSys_linkNode* current, char statistic, const char gender[5], const int age, const char cate[15]);
};

/***************************************************************************
  �������ƣ�My_strlen
  ��    �ܣ����ַ���str�ĳ���
  ���������str
  �� �� ֵ���ַ�������
  ˵    ����
***************************************************************************/
int My_strlen(const char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		;
	return i;
}

/***************************************************************************
  �������ƣ�My_strcpy
  ��    �ܣ����ַ���s2���Ƶ�s1�У�������ԭ���ݣ�����ʱ����\0
  ���������s1,s2
  �� �� ֵ��0
  ˵    ����
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
  �������ƣ�My_strcmp
  ��    �ܣ��Ƚ��ַ���s1��s2��С��Ӣ����ĸ���ִ�Сд
  ���������s1��s2
  �� �� ֵ�����Ϊ0��������Ϊ��һ�������ַ���ASCII��ֵ
  ˵    ����
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
  �������ƣ�examRegSys_list::examRegSys_list()
  ��    �ܣ�������Ĺ��캯����Ϊ��������ռ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
examRegSys_list::examRegSys_list()
{
	first = new examRegSys_linkNode;
	sum = 0;
}

/***************************************************************************
  �������ƣ�examRegSys_list::~examRegSys_list()
  ��    �ܣ�������������������ÿ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
examRegSys_list::~examRegSys_list()
{
	makeEmpty();
}

/***************************************************************************
  �������ƣ�examRegSys_list::setSum()
  ��    �ܣ��û����뱨��������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void examRegSys_list::setSum()
{
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
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
  �������ƣ�void examRegSys_list::makeEmpty()
  ��    �ܣ��ÿ������ͷ��ڴ�
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�examRegSys_linkNode* examRegSys_list::locate(int i)
  ��    �ܣ���λ���������ڵ�ĳһ���
  ���������int i
  �� �� ֵ��return current;
  ˵    ����
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
  �������ƣ�examRegSys_list::outputAll()
  ��    �ܣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void examRegSys_list::outputAll()
{
	cout << endl << "����      ����      �Ա�      ����      ��������" << endl;
	examRegSys_linkNode* current = first->link;
	while (current != NULL) {
		outputSingle(current);
		current = current->link;
	}
	return;
}

/***************************************************************************
  �������ƣ�examRegSys_list::outputSingle(examRegSys_linkNode* x)
  ��    �ܣ����ݲ�����ַ��������������
  ���������examRegSys_linkNode* x
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void examRegSys_list::outputSingle(examRegSys_linkNode* x)
{
	cout << setiosflags(ios::left) << setw(10) << x->examRegNum << setw(10) << x->name
		<< setw(10) << x->gender << setw(10) << x->age << setw(10) << x->category << endl;
}

/***************************************************************************
  �������ƣ�examRegSys_list::inputRear()
  ��    �ܣ���巨����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void examRegSys_list::inputRear()
{
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	examRegSys_linkNode* newNode, * last, node;
	int i = 0;
	makeEmpty();
	last = first;
	while (i < sum) {
		cin >> node;
		newNode = new examRegSys_linkNode(node);
		if (newNode == NULL) {
			cerr << "�洢�������" << endl;
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
  �������ƣ�istream& operator>>(istream& istr, examRegSys_linkNode& x)
  ��    �ܣ����������������������������
  ���������istream& istr, examRegSys_linkNode& x
  �� �� ֵ��return istr;
  ˵    ����
***************************************************************************/
istream& operator>>(istream& istr, examRegSys_linkNode& x)
{
	istr >> x.examRegNum >> x.name >> x.gender >> x.age >> x.category;
	return istr;
}

/***************************************************************************
  �������ƣ�ostream& operator<<(ostream& ostr, const examRegSys_linkNode& x)
  ��    �ܣ���������������������������
  ���������ostream& ostr, const examRegSys_linkNode& x
  �� �� ֵ��return ostr;
  ˵    ����
***************************************************************************/
ostream& operator<<(ostream& ostr, const examRegSys_linkNode& x)
{
	ostr << setiosflags(ios::left) << setw(10) << x.examRegNum << setw(10) << x.name
		<< setw(10) << x.gender << setw(10) << x.age << setw(10) << x.category << endl;
	return ostr;
};

/***************************************************************************
  �������ƣ�examRegSys_list::choose()
  ��    �ܣ�ȷ���û�����Ĳ���Ҫ�󣬲�ִ����ز���
  ���������
  �� �� ֵ��return x;
  ˵    ����
***************************************************************************/
void examRegSys_list::choose()
{
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << endl << endl;
	cout << "��ѡ����Ҫ���еĲ�����";
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
			cout << "��������Ҫ����Ŀ�����λ�ã�";
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
				cout << "ȡ�����β���" << endl;
				return;
			}
			Insert(i);
			break;
		case 2:
			cout << "��������Ҫɾ���Ŀ�����λ�ã�";
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
				cout << "ȡ�����β���" << endl;
				return;
			}
			Remove(i);
			break;
		case 3:
			cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
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
				cout << "ȡ�����β���" << endl;
				return;
			}
			cout << endl << "����      ����      �Ա�      ����      ��������" << endl;
			Search(i);
			break;
		case 4:
			cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
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
				cout << "ȡ�����β���" << endl;
				return;
			}
			Modify(i);
			cout << "�޸Ľ�����£�" << endl;
			break;
		case 5:
			cout << "������Ҫͳ�Ƶ���Ŀ��aΪ�Ա�bΪ���䣬cΪ�������0Ϊȡ�����β�����";
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
				cout << "ȡ�����β���" << endl;
				return;
			}
			Summary(statistics);
			break;
		case 0:
			cout << "��ǰδѡ�������������ѡ��" << endl;
			break;
		default:
			break;
	}
	cout << endl;
	outputAll();
	return;
}

/***************************************************************************
  �������ƣ�examRegSys_list::Insert(int i)
  ��    �ܣ�����Ԫ�ز��뵽�����i��λ��
  ���������int i
  �� �� ֵ��return true OR false
  ˵    ����
***************************************************************************/
bool examRegSys_list::Insert(int i)
{
	examRegSys_linkNode* current = locate(i - 1), node;
	if (current == NULL) {
		cout << "���벻�ɹ�" << endl;
		return false;
	}
	cout << "����������Ҫ����Ŀ����Ŀ����ţ��������Ա�����ͱ������ͣ�" << endl;
	cin >> node;
	examRegSys_linkNode* newNode = new examRegSys_linkNode(node);
	if (newNode == NULL) {
		cerr << "�洢������󣡣�" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

/***************************************************************************
  �������ƣ�examRegSys_list::Remove(int i)
  ��    �ܣ��������i��λ�õĽ��ɾ��
  ���������int i
  �� �� ֵ��return true OR false
  ˵    ����
***************************************************************************/
bool examRegSys_list::Remove(int i)
{
	examRegSys_linkNode* current = locate(i - 1);
	if (current == NULL || current->link == NULL) {
		cerr << "ɾ�����ɹ�" << endl;
		return false;
	}
	examRegSys_linkNode* del = current->link;
	current->link = del->link;
	cout << "��ɾ���Ŀ�����Ϣ��:  ";
	outputSingle(del);
	delete del;
	return true;
}

/***************************************************************************
  �������ƣ�examRegSys_list::Search(int x)
  ��    �ܣ���������������������x�Ľ�㣬����ӡ����
  ���������int i
  �� �� ֵ�����ҳɹ�ʱ���������ַ�����򷵻�NULL
  ˵    ����
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
  �������ƣ�examRegSys_list::Modify(int i)
  ��    �ܣ���������������������i�Ľ�㣬���޸���������
  ���������int i
  �� �� ֵ�����ҳɹ�ʱ���������ַ�����򷵻�NULL
  ˵    ����
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
		cerr << "���޴˿���" << endl;
		return current;
	}
	cout << "�������޸ĺ�Ŀ������ţ��������Ա�����ͱ������" << endl;
	cin >> node;
	current->examRegNum = node.examRegNum;
	My_strcpy(current->name, node.name);
	My_strcpy(current->gender, node.gender);
	current->age = node.age;
	My_strcpy(current->category, node.category);
	return current;
}

/***************************************************************************
  �������ƣ�examRegSys_list::Summary(char statistic)
  ��    �ܣ������û�����Ҫ��ͳ�������ڵ��Ա�����ͱ������
  ���������char statistic
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void examRegSys_list::Summary(char statistic)
{
	char gender[5], cate[15];
	int age = 0;
	switch (statistic)
	{
		case 'a':
			cout << "��������Ҫͳ�Ƶ��Ա�";
			cin >> gender;
			break;
		case 'b':
			cout << "��������Ҫͳ�Ƶ����䣺";
			cin >> age;
			break;
		case 'c':
			cout << "��������Ҫͳ�Ƶı������";
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
		cerr << "���޴˿���" << endl;
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
		cout << "��������Ҫ��ȡ������Ϣ�ķ�����1-���ļ���ȡ/2-�ֶ����룩";
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
			cout << "������Ҫ�洢�ļ�������(����0�����ȡĬ���ļ�)" << endl;
			string loadFile;
			cin >> loadFile;
			if (loadFile.length() == 0)
			{
				cout << "��Ч���ƣ��Զ���ȡ��ΪStudent.txt���ļ�" << endl;
				loadFile = "Student.txt";
			}
			else if (loadFile == "0")
			{
				cout << "��ʼ��ȡĬ���ļ�" << endl;
				loadFile = "Student.txt";
			}
			else
			{
				loadFile += ".txt";
			}

			ifstream file(loadFile);
			examRegSys_linkNode* temp;
			cout << endl << "��ʼ��ȡ����:" << endl;

			while (file.peek() != EOF)
			{
				file >> temp;
				list.inputRear(temp);
			}

			cout << "�ɹ���ȡ���ݣ�" << endl;
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
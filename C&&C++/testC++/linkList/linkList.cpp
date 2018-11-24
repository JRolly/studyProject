#include <iostream>
#include <string>
using namespace std;

//链表
//c中使用struct创建结构体，在创建链表，分配和释放内存用malloc和free
//c++中使用类class，分配是释放内存用new 和 delete
//c++中对象的产生需要调用构造函数，消亡需要调用析构函数，malloc和free不能满足这两个基本要求
//所以在c++中不能使用


class book
{
public:
	int num;
	float price;
	book *next;

	bool check(string str);	//检查输入是否为数而不是字符（串）以避免进入死循环
	book *create();	//创建链表
	void showBook(book *head);	//显示
	void Delete(book *head, int num); //删除编号为num的结点
	void insert(book *head, int num, float price);	//插入编号为num的结点
	int getBookNum(book *head);	//统计数目
};
book *head = NULL;

//检查输入
bool book::check(string str)
{
	for (int i = 0; i < str.length(); i++)
		if ((str[i] > '9' || str[i] < '0') && str[i] != '.')
			return false;
	return true;
}

//创建链表
book *book::create()
{
	//p1和p2都指向新建的第一个结点
	//开始第一次输入
	book *p1 = new book;	//下一个结点的指针
	head = p1;
	book *p2 = p1;	//当前结点的指针
	string str;

	cout << "请输入图书编号，必须是数字，输入0返回主菜单" << endl;
	cin >> str;
	while (!check(str))
	{
		cout << "输入的不是数字，请重新输入,按0返回" << endl;
		cin >> str;
	}
	p1->num = atoi(str.c_str());		//需要将字符串转换为整数，string是c++的库，atoi是c的库，需要转换

	if (p1->num != 0)
	{
		cout << "请输入图书价格" << endl;
		cin >> str;
		while (!check(str))
		{
			cout << "输入的不是数字，请重新输入,按0返回" << endl;
			cin >> str;
		}
		p1->price = atof(str.c_str());
	}
	else
	{
		delete p1;
		p2 = NULL;
		head = NULL;
		return head;
	}
	//开始第2~n次输入
	while (p1->num != 0)
	{
		p2 = p1;
		p1 = new book;
		cout << "请输入图书编号，必须是数字，输入0返回主菜单" << endl;
		cin >> str;
		while (!check(str))
		{
			cout << "输入的不是数字，请重新输入,按0返回" << endl;
			cin >> str;
		}
		p1->num = atoi(str.c_str());		//需要将字符串转换为整数，string是c++的库，atoi是c的库，需要转换

		if (p1->num != 0)
		{
			cout << "请输入图书价格" << endl;
			cin >> str;
			while (!check(str))
			{
				cout << "输入的不是数字，请重新输入,按0返回" << endl;
				cin >> str;
			}
			p1->price = atof(str.c_str());
		}
		p2->next = p1;
	}
	delete p1;
	p2->next = NULL;
	return head;
}

//显示
void book::showBook(book *head)
{
	cout << "图书信息如下" << endl;
	while (head)
	{
		cout << "图书编号：" << head->num << "  ";
		cout << "图书价格：" << head->price << endl;
		head = head->next;
	}
}

//删除编号为num的结点
void book::Delete(book *head, int num)
{
	book *l;
	if (head->num == num)	//删除点为头结点
	{
		l = head;	//将头结点给l，将头结点指向头结点的下一个结点，改变全局的头结点信息，删除l（原本的头结点）
		head = head->next;
		::head = head;
		delete l;
		cout << "删除成功" << endl;
		return;
	}
	while (head)
	{
		if (head->next == NULL)	//只有一个头结点
		{
			cout << "找不到要删除的编号" << endl;
			return;
		}

		if (head->next->num == num)	//找到要删除的编号
		{
			l = head->next;		
			head->next = l->next;
			delete l;
			cout << "删除成功" << endl;
			return;
		}
		head = head->next;	//编号不匹配，将下一个结点改为当前头结点
	}
	cout << "找不到要删除的编号" << endl;
}

//插入
void book::insert(book *head, int num, float price)
{
	book *list = new book;	//新插入结点
	book *l;	//保存原表末尾结点
	while (head)
	{
		l = head;
		head = head->next;
	}
	list->num = num;
	list->price = price;
	list->next = NULL;
	l->next = list;		//新表末尾结点为list
}

//统计数目
int book::getBookNum(book *head)
{
	int num = 0;
	while (head)
	{
		num++;
		head = head->next;
	}
	return num;
}


void main()
{
	book a;
	int num;
	float price;
	a.create();
	a.showBook(head);
	cout << "输入需要删除的编号";
	cin >> num;
	a.Delete(head,num);
	a.showBook(head);
	cout << "输入需要插入的结点的信息" << endl;
	cout << "编号：";
	cin >> num;
	cout << "价格：";
	cin >>price;
	a.insert(head,num,price);
	a.showBook(head);
	cout << "有" << a.getBookNum(head) << "册书。" << endl;
}
#include <iostream>
#include <string>
using namespace std;

//����
//c��ʹ��struct�����ṹ�壬�ڴ�������������ͷ��ڴ���malloc��free
//c++��ʹ����class���������ͷ��ڴ���new �� delete
//c++�ж���Ĳ�����Ҫ���ù��캯����������Ҫ��������������malloc��free������������������Ҫ��
//������c++�в���ʹ��


class book
{
public:
	int num;
	float price;
	book *next;

	bool check(string str);	//��������Ƿ�Ϊ���������ַ��������Ա��������ѭ��
	book *create();	//��������
	void showBook(book *head);	//��ʾ
	void Delete(book *head, int num); //ɾ�����Ϊnum�Ľ��
	void insert(book *head, int num, float price);	//������Ϊnum�Ľ��
	int getBookNum(book *head);	//ͳ����Ŀ
};
book *head = NULL;

//�������
bool book::check(string str)
{
	for (int i = 0; i < str.length(); i++)
		if ((str[i] > '9' || str[i] < '0') && str[i] != '.')
			return false;
	return true;
}

//��������
book *book::create()
{
	//p1��p2��ָ���½��ĵ�һ�����
	//��ʼ��һ������
	book *p1 = new book;	//��һ������ָ��
	head = p1;
	book *p2 = p1;	//��ǰ����ָ��
	string str;

	cout << "������ͼ���ţ����������֣�����0�������˵�" << endl;
	cin >> str;
	while (!check(str))
	{
		cout << "����Ĳ������֣�����������,��0����" << endl;
		cin >> str;
	}
	p1->num = atoi(str.c_str());		//��Ҫ���ַ���ת��Ϊ������string��c++�Ŀ⣬atoi��c�Ŀ⣬��Ҫת��

	if (p1->num != 0)
	{
		cout << "������ͼ��۸�" << endl;
		cin >> str;
		while (!check(str))
		{
			cout << "����Ĳ������֣�����������,��0����" << endl;
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
	//��ʼ��2~n������
	while (p1->num != 0)
	{
		p2 = p1;
		p1 = new book;
		cout << "������ͼ���ţ����������֣�����0�������˵�" << endl;
		cin >> str;
		while (!check(str))
		{
			cout << "����Ĳ������֣�����������,��0����" << endl;
			cin >> str;
		}
		p1->num = atoi(str.c_str());		//��Ҫ���ַ���ת��Ϊ������string��c++�Ŀ⣬atoi��c�Ŀ⣬��Ҫת��

		if (p1->num != 0)
		{
			cout << "������ͼ��۸�" << endl;
			cin >> str;
			while (!check(str))
			{
				cout << "����Ĳ������֣�����������,��0����" << endl;
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

//��ʾ
void book::showBook(book *head)
{
	cout << "ͼ����Ϣ����" << endl;
	while (head)
	{
		cout << "ͼ���ţ�" << head->num << "  ";
		cout << "ͼ��۸�" << head->price << endl;
		head = head->next;
	}
}

//ɾ�����Ϊnum�Ľ��
void book::Delete(book *head, int num)
{
	book *l;
	if (head->num == num)	//ɾ����Ϊͷ���
	{
		l = head;	//��ͷ����l����ͷ���ָ��ͷ������һ����㣬�ı�ȫ�ֵ�ͷ�����Ϣ��ɾ��l��ԭ����ͷ��㣩
		head = head->next;
		::head = head;
		delete l;
		cout << "ɾ���ɹ�" << endl;
		return;
	}
	while (head)
	{
		if (head->next == NULL)	//ֻ��һ��ͷ���
		{
			cout << "�Ҳ���Ҫɾ���ı��" << endl;
			return;
		}

		if (head->next->num == num)	//�ҵ�Ҫɾ���ı��
		{
			l = head->next;		
			head->next = l->next;
			delete l;
			cout << "ɾ���ɹ�" << endl;
			return;
		}
		head = head->next;	//��Ų�ƥ�䣬����һ������Ϊ��ǰͷ���
	}
	cout << "�Ҳ���Ҫɾ���ı��" << endl;
}

//����
void book::insert(book *head, int num, float price)
{
	book *list = new book;	//�²�����
	book *l;	//����ԭ��ĩβ���
	while (head)
	{
		l = head;
		head = head->next;
	}
	list->num = num;
	list->price = price;
	list->next = NULL;
	l->next = list;		//�±�ĩβ���Ϊlist
}

//ͳ����Ŀ
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
	cout << "������Ҫɾ���ı��";
	cin >> num;
	a.Delete(head,num);
	a.showBook(head);
	cout << "������Ҫ����Ľ�����Ϣ" << endl;
	cout << "��ţ�";
	cin >> num;
	cout << "�۸�";
	cin >>price;
	a.insert(head,num,price);
	a.showBook(head);
	cout << "��" << a.getBookNum(head) << "���顣" << endl;
}
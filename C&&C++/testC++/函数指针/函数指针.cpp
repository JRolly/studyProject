#include <iostream>
#include <string>
using namespace std;

//����ָ��	�������� (��־��ָ�������) (�β��б�);
//			int (*func)(int)
//����һ��int��ָ�룬ָ��func�������ú�������һ��int�Ͳ���

//����ָ�����飬ָ������ָ������
//		void (*p[5])(int &)
//������һ����5��Ԫ�ص�����ָ�룬������ָ����ָ�ĺ�����һ��int���������ҷ���voidֵ
//�뺯��ָ�벻ͬ��ֻ��ָ�������Ĳ�ͬ

//����ָ��Ҳ������Ϊ�����Ĳ���
//		void func(void(*p)(int &), int &)
//����func��������������һ��������void(*p)(int &),��һ������ָ�룬��ָ��һ������һ��int�Ͳ���������voidֵ�ĺ�������һ����int�Ͳ���

//////////////////////////////////////////////////////////////////////////////////////////////////
//��typedef���Լ򻯺���ָ��������Ͷ���
//		typedef void (*vp)(float &, float &)
//��vp����Ϊһ������ָ�����ͣ������͵�ָ��ָ��һ����������float�����ò���������void�ĺ���
//		vp p;
//��p����Ϊһ��vp����ָ�����ͣ������͵�ָ��ָ��һ����������float�����ò���������void�ĺ���
//		void print(vp p,float &, float &)
//print������������������һ����vp���͵ĺ���ָ�룬����������float�͵�����
///////////////////////////////////////////////////////////////////////////////////////////////////


bool check(string str)
{
	for (int i = 0; i < str.length(); i++)
		if((str[i] > '9' || str[i] < '0') && (str[i] != '.'))
			return false;
	return true;
}

float triangle(float &x, float &y)
{
	return x*y*0.5;
}

float rectangle(float &x, float &y)
{
	return x*y;
}

void swap(float &x, float &y)
{
	float n;
	n = x;
	x = y;
	y = n;
}

void print(float &x, float &y)
{
	cout << "��Ϊ" << x << " " << "��Ϊ" << y << endl;
}

void get(float &a, float &b)
{
	cout << "������x����ֵ:";
	string str1;
	cin >> str1;
	while (!check(str1))
	{
		cout << "����Ĳ������֣�����������." << endl;
		cin >> str1;
	}
	a = atof(str1.c_str());
	cout << "������y����ֵ��";
	cin >> str1;
	while (!check(str1))
	{
		cout << "����Ĳ������֣�����������." << endl;
		cin >> str1;
	}
	b = atof(str1.c_str());
}

//void main()
//{
//	void (*p)(float &, float &);	//����һ������ָ��p����ָ��ָ��һ������voidֵ����������float�����ĺ���
//	float (*fp)(float & ,float &);
//	bool quit = false;
//	float a = 2,b = 3;
//	int choice;
//	while (quit == false)
//	{
//		cout << "(0)�˳� (1) �趨���� (2) ������ (3)������ ��4����������" << endl;
//		cin >> choice;
//		switch(choice)
//		{
//		case 1: p = get;	//��p��ָ������get���ú�����������float����������һ��voidֵ
//			break;
//		case 2: fp = triangle;
//			break;
//		case 3: fp = rectangle;
//		case 4: p = swap;
//			break;
//		default:
//			quit = true;
//			break;
//		}
//		if (quit) break;
//		if (choice == 1 || choice == 4)
//		{
//			print(a,b);
//			p(a,b);
//			print(a,b);
//		}
//		else if (choice == 2 || choice == 3)
//		{
//			print(a,b);
//			cout << "���Ϊ��" << fp(a,b) << endl;
//		}
//	}
//}
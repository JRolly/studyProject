#include <iostream>
using namespace std;

//���麯�� ��һ��������ʼ��Ϊ0 : virtual void show() = 0;
//�������麯������Ҳ�ǳ�����
//�κ�һ���ӳ��������������඼��̳д��麯�������ԣ����Ҫʵ�������󣬱��븲��ÿһ�����麯�������û�У���������Ҳ��һ��������

class shape
{
public:
	virtual double area() = 0;
};

class A:public shape
{
protected:
	double h,w;
public:
	A(double height, double width){h = height;w = width;}
	double area(){return h*w/2;}
};

class B:public A
{
public:
	B(double height,double width):A(height,width){}
	double area(){return h*w;}
};

class C:public shape
{
protected:
	double radius;
public:
	C(double r){radius = r;}
	double area(){return radius*radius*3.14;}
};

void main()
{
	shape *s;
	int choice = 0;
	while (choice < 9)
	{
		choice = 0;
		bool quite = false;
		cout << "(0)�˳� (1)������ (2) ������ (3)Բ" << endl;
		cout << "��ѡ��:";
		cin >> choice;
		switch (choice)
		{
		case 0:quite = true;
			break;
		case 1:s = new A(5.0,6.0);
			cout << "����������ǣ�" << s->area() << endl;
			break;
		case 2:s = new B(70.0,80.0);
			cout << "����������ǣ�" << s->area() << endl;
			break;
		case 3:s = new C(9.0);
			cout << "Բ������ǣ�" << s->area() << endl;
			break;
		default:
			cout << "������0��9֮�������" << endl;
			break;
		}
		if (choice < 4 && choice > 0)
			delete s;
		if (quite)
			break;
	}
}
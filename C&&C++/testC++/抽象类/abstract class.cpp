#include <iostream>
using namespace std;

//�����ֻ࣬��һ���ӿڣ���������̳����ķ�������û��ʲôʵ�ʵĹ���
//�����������һ������ĸ��� ������һ��������˳�����ֻ����Ϊ�������������࣬���ܴ����Լ��Ķ���

class shape
{
public:
	shape(){}
	virtual ~shape(){}
	virtual float length(){return 0;}
	virtual float area(){return 0;}
	virtual void show(){}
private:
};

class A:public shape
{
public:
	A(float i, float j):w(i),l(j){}
	virtual ~A(){}
	virtual float width(){return w;}
	virtual float length(){return l;}
	virtual float area(){return w*l;}
	virtual void show(){cout << "�����ε������" << area() << endl;}
protected:
	float w;
	float l;
};

class B:public A
{
public:
	B(float i, float j):A(i,j),w(i),l(j){}
	virtual ~B(){}
	virtual float width(){return w;}
	virtual float length(){return l;}
	virtual float area(){return w*l/2;}
	virtual void show(){cout << "�����ε������" << area() << endl;}
protected:
	float w;
	float l;
};

class C:public shape
{
public:
	C(float j):l(j){};
	virtual ~C(){}
	virtual float length(){return l;}
	virtual float area(){return 3.14*l*l;}
	virtual void show(){cout << "Բ�������" << area() << endl;}
protected:
	float l;
};

//void main()
//{
//	shape *p;
//	p = new A(2,3);
//	p->show();
//	delete p;
//	p = new B(4,5);
//	p->show();
//	delete p;
//	p = new C(1);
//	p->show();
//	delete p;
//}
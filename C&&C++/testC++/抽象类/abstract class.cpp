#include <iostream>
using namespace std;

//抽象类，只是一个接口，让派生类继承他的方法，并没有什么实际的功能
//抽象类代表着一个抽象的概念 而不是一个对象，因此抽象类只能做为基类来派生新类，不能创建自己的对象

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
	virtual void show(){cout << "正方形的面积是" << area() << endl;}
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
	virtual void show(){cout << "三角形的面积是" << area() << endl;}
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
	virtual void show(){cout << "圆的面积是" << area() << endl;}
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
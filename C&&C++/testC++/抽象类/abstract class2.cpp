#include <iostream>
using namespace std;

//纯虚函数 将一个函数初始化为0 : virtual void show() = 0;
//包含纯虚函数的类也是抽象类
//任何一个从抽象类派生的新类都会继承纯虚函数的特性，因此要实例化对象，必须覆盖每一个纯虚函数，如果没有，则派生类也是一个抽象类

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
		cout << "(0)退出 (1)三角形 (2) 正方形 (3)圆" << endl;
		cout << "请选择:";
		cin >> choice;
		switch (choice)
		{
		case 0:quite = true;
			break;
		case 1:s = new A(5.0,6.0);
			cout << "三角形面积是：" << s->area() << endl;
			break;
		case 2:s = new B(70.0,80.0);
			cout << "正方形面积是：" << s->area() << endl;
			break;
		case 3:s = new C(9.0);
			cout << "圆的面积是：" << s->area() << endl;
			break;
		default:
			cout << "请输入0到9之间的数字" << endl;
			break;
		}
		if (choice < 4 && choice > 0)
			delete s;
		if (quite)
			break;
	}
}
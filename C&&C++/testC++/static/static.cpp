#include <iostream>
using namespace std;

//类的静态成员变量和静态成员函数
//静态成员函数属于整个类，因此不能访问某个对象的成员变量，因为它没有指向该对象的this指针，不过可以访问该类的静态成员变量

class A
{
public:
	void static show(){cout << A::x << endl;x++;}
private:
	static int x;
};
int A::x = 0;

//可以通过对象来访问静态成员函数,   通过 对象->访问静态成员函数->访问静态成员变量
class B
{
public:
	void static show(){cout << B::n << endl; n++;}
private:
	static int n;
};
int B::n = 0;


void main()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		A::show();
	}

	B b;
	b.show();
}



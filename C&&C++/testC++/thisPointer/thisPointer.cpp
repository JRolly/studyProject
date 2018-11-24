#include <iostream>
using namespace std;

class A
{
public:
	int get()const{return i;}
	void set(int x)
	{
		this->i = x;
		cout << "this变量保存的地址：" << this << endl;
		//this变量保存对象的地址
		//this指针是指向对象的指针
	}
private:
	int i;
};

void main()
{
	A a;
	a.set(9);
	cout << "对象a的地址：" << &a << endl;
	cout << a.get() << endl;

	A b;
	b.set(999);
	cout << "对象b的地址：" << &b << endl;
	cout << b.get() << endl;
}
#include <iostream>
using namespace std;

class A
{
public:
	A(int i, int j):n(i),m(j){}
	A(A&t):n(t.n),m(t.m){}	//默认复制构造函数
	void print(){cout << n << m << endl;}
private:
	int n;
	int m;
};

void main()
{
	A a(2,4);
	a.print();
	A b(a);	//定义对象b，并将a做为参数，传递对象时会自动调用默认构造函数，将a的数据成员复制给b
	b.print();	
}
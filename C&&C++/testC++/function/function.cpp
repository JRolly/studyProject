#include <iostream>
using namespace std;

class A
{
public:
	A(int i, int j):n(i),m(j){}
	A(A&t):n(t.n),m(t.m){}	//Ĭ�ϸ��ƹ��캯��
	void print(){cout << n << m << endl;}
private:
	int n;
	int m;
};

void main()
{
	A a(2,4);
	a.print();
	A b(a);	//�������b������a��Ϊ���������ݶ���ʱ���Զ�����Ĭ�Ϲ��캯������a�����ݳ�Ա���Ƹ�b
	b.print();	
}
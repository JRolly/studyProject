#include <iostream>
using namespace std;

class A
{
public:
	int get()const{return i;}
	void set(int x)
	{
		this->i = x;
		cout << "this��������ĵ�ַ��" << this << endl;
		//this�����������ĵ�ַ
		//thisָ����ָ������ָ��
	}
private:
	int i;
};

void main()
{
	A a;
	a.set(9);
	cout << "����a�ĵ�ַ��" << &a << endl;
	cout << a.get() << endl;

	A b;
	b.set(999);
	cout << "����b�ĵ�ַ��" << &b << endl;
	cout << b.get() << endl;
}
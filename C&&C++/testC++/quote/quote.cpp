#include <iostream>
using namespace std;
//����
class A
{
public:
	A(int i){x = i;}
	A(const A&a){x = a.x;cout << "ִ�и��ƹ��캯��������һ������" << endl;} //��ֵ����һ������ʱ�����Զ�����Ĭ�Ϲ��캯��
	~A(){x = 0;cout << "ִ����������." << endl;} 
	int get()const{return x;}
	void set(int i){x = i;}
private:
	int x;
};

A func();
int main()
{
 	A &r = func();
	cout << "����a�ĸ�����ַ:" << &r << endl;
	cout << r.get() << endl;
	return 0;
}
A func()		//�˴�������A�����ã����Ƿ���һ�������ڵĶ�������ã��Ҳ������Ĭ�ϸ��ƹ��캯�������������е�r����һ�����ֵ
{
	cout << "����func������" << endl;
	A a(23);
	cout << "����a�ĵ�ַ��" << &a << endl;
	return a;
}
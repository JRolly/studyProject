#include <iostream>
using namespace std;

//ǳ�㸴��
//��һ������ĳ�Աָ�븴�Ƹ���һ������
//��������ĳ�Աָ��ָ��ͬһ���ڴ�
//ɾ��һ������ĳ�Աָ��ָ����ڴ�ʱ����һ������ĳ�Աָ���Ϊ Ұָ��
class A
{
public:
	A(){x = new int; *x = 5;}
	~A(){delete x; x = NULL;}
	A(const A&a)
	{
		cout << "���ƹ��캯��ִ��..." << endl; 
		this->x = a.x;		
	}
	void print()const{cout << *x << endl;}
	void set(int i){*x = i;}
private:
	int *x;
};

//void main()
//{
//	A *a = new A();
//	cout << "a:"; a->print(); cout << endl;
//	A b = (*a);	//���ø��ƹ��캯������ָ��aָ��Ķ��ж����Ƹ�ͬ��Ķ���b�� ����ָ��ָ����ͬһ���ڴ�
//	a->set(23);
//	cout << "b:"; b.print(); cout << endl;
//	b.set(33);
//	cout << "a:"; a->print(); cout << endl;
//	//delete a;	
//}


//��㸴�ƹ��캯��
//�����Լ��ĸ��ƹ��캯��
//�ں�����Ϊ��Ա���������ڴ�
//�ɶ���ĳ�Ա�������Ƶ��µ��ڴ��У���������ĳ�Ա����ӵ���Լ����ڴ����򣬻���Ӱ��
class B
{
public:
	B(){x = new int; *x = 5;}
	~B(){delete x; x = NULL;}
	B(const B&b)
	{
		cout << "���ƹ��캯��..." << endl;
		this->x = new int;
		*x = *(b.x);
	}
	void print()const{cout << *x << endl;}
	void set(int i){*x = i;}
private:
	int *x;
};

void main()
{
	B *a = new B();
	cout << "a:"; a->print(); cout << endl;
	B b = (*a);	//���ø��ƹ��캯����Ϊ�����Ķ���ĳ�Ա���������ڴ棬��������ĳ�Ա����ָ��ָ����Ե��ڴ�
	a->set(23);
	cout << "b:"; b.print(); cout << endl;
	b.set(33);
	cout << "a:"; a->print(); cout << endl;
	delete a;
}

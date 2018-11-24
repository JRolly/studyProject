#include <iostream>
using namespace std;

//浅层复制
//将一个对象的成员指针复制给另一个对象，
//两个对象的成员指针指向同一块内存
//删除一个对象的成员指针指向的内存时，另一个对象的成员指针变为 野指针
class A
{
public:
	A(){x = new int; *x = 5;}
	~A(){delete x; x = NULL;}
	A(const A&a)
	{
		cout << "复制构造函数执行..." << endl; 
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
//	A b = (*a);	//掉用复制构造函数，将指针a指向的堆中对象复制给同类的对象b， 两个指针指向了同一块内存
//	a->set(23);
//	cout << "b:"; b.print(); cout << endl;
//	b.set(33);
//	cout << "a:"; a->print(); cout << endl;
//	//delete a;	
//}


//深层复制构造函数
//创建自己的复制构造函数
//在函数中为成员变量分配内存
//旧对象的成员变量复制到新的内存中，两个对象的成员变量拥有自己的内存区域，互不影响
class B
{
public:
	B(){x = new int; *x = 5;}
	~B(){delete x; x = NULL;}
	B(const B&b)
	{
		cout << "复制构造函数..." << endl;
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
	B b = (*a);	//调用复制构造函数，为创建的对象的成员变量分配内存，两个对象的成员变量指针指向各自的内存
	a->set(23);
	cout << "b:"; b.print(); cout << endl;
	b.set(33);
	cout << "a:"; a->print(); cout << endl;
	delete a;
}

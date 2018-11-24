#include <iostream>
using namespace std;
//引用
class A
{
public:
	A(int i){x = i;}
	A(const A&a){x = a.x;cout << "执行复制构造函数来创建一个对象。" << endl;} //按值返回一个对象时，会自动调用默认构造函数
	~A(){x = 0;cout << "执行析构函数." << endl;} 
	int get()const{return x;}
	void set(int i){x = i;}
private:
	int x;
};

A func();
int main()
{
 	A &r = func();
	cout << "对象a的副本地址:" << &r << endl;
	cout << r.get() << endl;
	return 0;
}
A func()		//此处若返回A的引用，则是返回一个不存在的对象的引用，且不会调用默认复制构造函数，在主函数中的r将是一个随机值
{
	cout << "跳到func函数中" << endl;
	A a(23);
	cout << "对象a的地址：" << &a << endl;
	return a;
}
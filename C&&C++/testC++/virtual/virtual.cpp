#include <iostream>
using namespace std;

class father
{
public:
	father():age(33){cout << "父类构造函数初始化父亲年龄为：" << age << endl;}
	~father(){cout << "父类析构函数" << endl;}
	//void run()const{cout << "父亲能跑万米" << endl;}
	//虚函数，系统执行到关键字virtual的函数时 对自动判断是哪个 对象 调用了它，然后调用该对象的同名函数
	virtual void run()const{cout << "父亲能跑万米" << endl;}
private:
	int age;
};

class son:public father
{
public:
	son(){cout << "子类构造函数" << endl;}
	~son(){cout << "子类析构函数" << endl;}
	//一个函数被说明为虚函数，在派生类中覆盖该函数，那么这个函数也是虚函数，virtual可以神略，但写出来更易理解
	/*virtual*/void run()const{cout << "儿子能跑十万米" << endl;}
};

//void main()
//{
//	father *pfather = new son;	//创建子类对象，将子类对象赋值给父类指针
//	pfather->run();	//子类对象调用run函数，会在子类对象中调用
//	delete pfather;
//}
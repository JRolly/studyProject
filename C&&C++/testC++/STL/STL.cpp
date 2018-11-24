#include <iostream>
using namespace std;

//模版
//		template<class Type1，class Type2>
//	class关键字表示Type是类型
template<class Type>
//交换两个数,允许直接交换两个结构体的成员
void Tswap(Type &rx, Type &ry)
{
	rx += ry;
	ry = rx - ry;
	rx -= ry;
}

void change_demo()
{
	int x = 2, y = 3;
	cout << "交换前，x:" << x << ",y:" << y << endl;
	Tswap(x,y);
	cout << "交换后，x:" << x << ",y:" << y << endl;

	float a = 3.2, b = 7.8;
	cout << "交换前，a:" << a << ",b:" << b << endl;
	Tswap(a,b);
	cout << "交换后，a:" << a << ",b:" << b << endl;
}


//重载模版
//当需要交换的是数组或其他时，需要重载模版
template<class Type>
void Tswap(Type rx[], Type ry[], int n)
{
	cout << "调用Tswap(Type rx[], Type ry[], int n)函数\n";
	Type tmp;
	for (int i = 0; i < n; i++)
	{
		Type tmp = rx[i];
		rx[i] = ry[i];
		ry[i] = tmp;
	}
}

template<class Type>
void show(Type rx[], Type ry[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "num1[" << i << "]:" << rx[i] << " num2[" << i << "]:" << ry[i] << endl;
	}
}


//具体化函数模版，解决重载问题
//	在交换两个结构体成员时，如果交换所有信息，则可以通过一个模版来直接实现
//	如果只交换其中的部分成员，重载时因为参数一致会导致失败
//	通过具体化函数模版来解决问题
struct people
{
	char name[10];
	int age;
};
template<class Type>
void Swap(Type &a, Type &b)
{
	a += b;
	b = a - b;
	a -= b;
}
//void Swap(people &a, people &b)
template<>void Swap<people>(people &a, people &b)	//两者效果相同
{	//	告诉编译器不要使用Swap模版函数，而使用具体化的Swap函数来创建一个Swap函数。
	//	尖括号中的people指明了具体化的类型，小括号中使用该类型来声明两个参数
	int age;
	age = a.age;
	a.age = b.age;
	b.age = age;
}
void show(people &p)
{
	cout << p.name << "的年龄：" << p.age << endl;
}
void stl_fun()
{
	int i = 10, j = 20;
	cout << "初始化 i=" << i << " j=" << j << endl;
	cout << "执行Swap函数进行交换..." << endl;
	Swap(i,j);
	cout << "现在 i=" << i << " j=" << j << endl;

	people Jack = {"Jack",44};
	people Mike = {"Mike",23};
	cout << "成员交换前:" << endl;
	show(Jack);
	show(Mike);
	Swap(Jack,Mike);
	cout << "交换成员年龄后：" << endl;
	show(Jack);
	show(Mike);
}

//实例化模版函数
// template void Swap<people>(people &a, people &b)
//	命令编译器根据其他已有模版的 定义部分，创建参数类型为people的模版实例
//	由实例化模版创建的函数的定义部分是不可修改的
template<class Type>
void out(Type a){cout << a << endl;}
template void out<char>(char &);	//程序编译时根据上面的函数模版强制创建一个函数：void show(char &a){cout << a << endl;}
void stl_out()
{
	out(5);
}

//调用优先级
//	在函数名、参数类型、参数个数相同的情况下，普通函数 > 具体化函数模版 > 函数模版
template<class Type>
void chk(Type a){cout << "模版函数！" << endl;}
template<> void chk<int>(int a){ cout << "具体化模版函数！" << endl;}
void chk(int a){cout << "非模版函数" << endl;}
void stl_chk_priority()
{
	chk(5);
}


//main
void main()
 {
	//change_demo();

	//const int num = 10;
	//int num1[num] = {10,11,12,13,14,15,16,17,18,19};
	//int num2[num] = {0,1,2,3,4,5,6,7,8,9};
	//cout << "交换前：\n";
	//show(num1,num2,num);
	//Tswap(num1,num2,num);
	//cout << "交换后：\n";
	//show(num1,num2,num);

	//stl_fun();

	/*stl_out();*/

	stl_chk_priority();
}
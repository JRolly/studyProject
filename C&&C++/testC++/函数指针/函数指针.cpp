#include <iostream>
#include <string>
using namespace std;

//函数指针	函数类型 (标志符指针变量名) (形参列表);
//			int (*func)(int)
//声明一个int型指针，指向func函数，该函数带有一个int型参数

//函数指针数组，指向函数的指针数组
//		void (*p[5])(int &)
//声明了一个有5个元素的数组指针，该数组指针所指的函数有一个int参数，而且返回void值
//与函数指针不同的只是指针数量的不同

//函数指针也可以做为函数的参数
//		void func(void(*p)(int &), int &)
//函数func有两个参数，第一个参数是void(*p)(int &),是一个函数指针，它指向一个带有一个int型参数并返回void值的函数，另一个是int型参数

//////////////////////////////////////////////////////////////////////////////////////////////////
//用typedef可以简化函数指针的声明和定义
//		typedef void (*vp)(float &, float &)
//将vp声明为一个函数指针类型，该类型的指针指向一个带有两个float型引用参数并返回void的函数
//		vp p;
//将p声明为一个vp函数指针类型，该类型的指针指向一个带有两个float型引用参数并返回void的函数
//		void print(vp p,float &, float &)
//print函数有三个参数，第一个是vp类型的函数指针，另外两个是float型的引用
///////////////////////////////////////////////////////////////////////////////////////////////////


bool check(string str)
{
	for (int i = 0; i < str.length(); i++)
		if((str[i] > '9' || str[i] < '0') && (str[i] != '.'))
			return false;
	return true;
}

float triangle(float &x, float &y)
{
	return x*y*0.5;
}

float rectangle(float &x, float &y)
{
	return x*y;
}

void swap(float &x, float &y)
{
	float n;
	n = x;
	x = y;
	y = n;
}

void print(float &x, float &y)
{
	cout << "长为" << x << " " << "宽为" << y << endl;
}

void get(float &a, float &b)
{
	cout << "请输入x的新值:";
	string str1;
	cin >> str1;
	while (!check(str1))
	{
		cout << "输入的不是数字，请重新输入." << endl;
		cin >> str1;
	}
	a = atof(str1.c_str());
	cout << "请输入y的新值：";
	cin >> str1;
	while (!check(str1))
	{
		cout << "输入的不是数字，请重新输入." << endl;
		cin >> str1;
	}
	b = atof(str1.c_str());
}

//void main()
//{
//	void (*p)(float &, float &);	//声明一个函数指针p，该指针指向一个返回void值并带有两个float参数的函数
//	float (*fp)(float & ,float &);
//	bool quit = false;
//	float a = 2,b = 3;
//	int choice;
//	while (quit == false)
//	{
//		cout << "(0)退出 (1) 设定长宽 (2) 三角形 (3)正方形 （4）交换长宽" << endl;
//		cin >> choice;
//		switch(choice)
//		{
//		case 1: p = get;	//用p来指向函数名get，该函数带有两个float参数并返回一个void值
//			break;
//		case 2: fp = triangle;
//			break;
//		case 3: fp = rectangle;
//		case 4: p = swap;
//			break;
//		default:
//			quit = true;
//			break;
//		}
//		if (quit) break;
//		if (choice == 1 || choice == 4)
//		{
//			print(a,b);
//			p(a,b);
//			print(a,b);
//		}
//		else if (choice == 2 || choice == 3)
//		{
//			print(a,b);
//			cout << "面积为：" << fp(a,b) << endl;
//		}
//	}
//}
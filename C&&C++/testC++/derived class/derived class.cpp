//#include <iostream>
//using namespace std;
//
//class father
//{
//public:
//	father(int i){a = i; cout << "构造基类a的值：" << a << endl;}
//	~father(){cout << "析构基类的值：" << a << endl;}
//private:
//	int a;
//};
//
//class son:public father
//{
//public:
//	son(int i, int j);
//	~son(){cout << "析构子类b的值：" << b << endl;}
//private:
//	int b;
//};
//
//son::son(int i, int j):father(i)	//传递默认参数，构造
//{
//	b = j;
//	cout << "构造类b的值："<< b << endl;
//}
//
////void main()
////{
////	son b(1,2);
////}

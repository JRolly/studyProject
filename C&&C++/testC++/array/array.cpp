#include <iostream>
using namespace std;

class get
{
public:
	int a[5];
};

class area
{
public:
	~area(){cout << "执行析构函数释放内存" << endl;}
	int get()const{return length*width;}
	void set(int l, int w){length = l; width = w;}
private:
	int length;
	int width;
};
//void main()
//{
//	get one[5];	//数组对象，在get类中申明一个包含5个元素的数组对象，即创建了从 one[0]~one[5] 这5个对象
//	int i;
//	for (i = 0; i < 5; i++)
//	{
//		cin >> one[i].a[i];
//	}
//	for (i = 0; i < 5; i++)
//	{
//		cout << "one[" << i+1 << "]:";
//		cout << one[i].a[i] << endl;
//	}
//}

//void main()
//{
//	area *pone = new area[10];	//申明一个由10个area对象组成的数组，
//	int i;
//	for (i = 0; i < 10; i++)
//	{
//		pone[i].set(i,i*2);
//		cout << "area[" << i << "]:";
//		cout << pone[i].get() << endl;
//		cout << pone->get() << endl;
//		cout << endl;
//	}
//	delete [] pone;	//删除数组中的每个对象
//}
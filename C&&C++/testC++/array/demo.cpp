#include <iostream>
using namespace std;

class A
{
public:
	A(int l)
	{
		length = l;
		Size = new char[length];	//在堆中开辟空间，保存char型数组，长度为length，该空间的地址赋给成员指针变量Size
	}
	~A(){delete [] Size;}
	int getLength()const{return length;}
	//重载数组下标操作符 []
	char &operator[](int i);
	//杨辉三角
	void PascalTriangle();
private:
	int length;
	char *Size;
};

char &A::operator [](int i)
{
	if (i >= 0 && i < length)	//长度正确，返回Size[i]
		return Size[i];
	else						//否则返回char型数组的长度减1，即返回最后一个元素
	{
		cout << "\n超出范围.";
		return Size[length-1];
	}
}

//杨辉三角
void A::PascalTriangle()
{
	const int n = 10;
	int a[n][n];
	int i,j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if (j == 0 || j == i)
				a[i][j] = 1;
			else
				a[i][j] = a[i-1][j-1] + a[i-1][j];
			cout << a[i][j] << "  ";
		}
		cout << endl;
	}
}

void main()
{
	int i;
	A a(6);	//定义一个对象a，并调用带一个参数的构造函数，初始化length的长度为6，并在堆中开辟新空间，保存char型数组，长度为length
			//该空间的地址赋给Size
	char *ch = "hello12";
	for (i = 0; i < 8; i++)
	{
		a[i] = ch[i];
		cout << a[i];
	}
	cout << "\n";
	cout << a.getLength() << endl;
}
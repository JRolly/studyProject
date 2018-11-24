#include <iostream>
using namespace std;

//运算符重载 ： 返回类型 operator运算符(参数表){实现}

class num
{
public:
	num(){n = 1; cout << "构造函数执行..." << endl;}
	num(const num &s){this->n = s.n; cout << "复制构造函数执行..." << endl;}
	num(int i){n = i; cout << "构造函数执行..." << endl;}
	~num(){cout << "析构函数执行..." << endl;}
	int get()const{return n;}
	void set(int i){n = i;}
	void add(){n++;}
	//重载 前置自加运算符 ++i
	//运算符重载，this指针就是对象的标签，某个对象的成员变量也会被编译器自动贴上标签--this指针
	//将成员变量自加，然后返回成员变量的this指针
	//num operator++()	
	//{
	//	++n;
	//	return *this;
	//}
	//为避免按值返回时创建一个*this的临时副本，最好将operator++()的返回值定义为按别名返回
	//并且一般不会执行++++i这样的操作，有必要将返回值定义为常量
	const num &operator++()
	{
		++n;
		return *this;
	}

	//重载 后置自加运算符 i++
	//先建立一个临时对象，将原始对象的值复制到临时对象中，然后在将原始对象的值加1，最后返回临时对象
	//返回的是一个临时对象，所以必须按值返回，不能用别名的方式返回（不会创建副本，对象超出作用域被析构掉，返回一个空对象）
	//前置自加和后置自加一起使用时，函数的重载需要参数列表不同，这里的o只用做信号提示编译器，这两个函数不同
	num operator++(int o)
	{
		num tmp(*this);
		n++;
		return tmp;
	}

	//重载数组下标操作符 []
	char &operater[](int i)
	{
		if (i > 0 && i < length)
			return Size[i];
		else
		{
			cout << "\n超出范围。";
			return Size[length-1];
		}
	}

private:
	int n;
	int length;
	char *Size;
};

void main()
{
	num i;
	cout << "i:" << i.get() << endl;
	num x = ++i;
	cout << "i:" << i.get() << endl;
	cout << "x:" << x.get() << endl;

	x = i++;
	cout << "i:" << i.get() << endl;
	cout << "x:" << x.get() << endl;
}




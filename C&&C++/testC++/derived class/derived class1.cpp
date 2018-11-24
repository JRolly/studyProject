#include <iostream>
#include <string>
using namespace std;

//利用基类的构造函数初始化数据
class father
{
protected:
	string name;
	int tall;
public:
	father(string a, int i);
	father(){cout << "构造基类" << endl;}
	void print(){cout << name << "身高为：" << tall << endl;}
	~father(){cout << "释放基类对象" << endl;}
};

father::father(string a, int i)
{
	cout << "在基类的构造函数内" << endl;
	name = a;
	tall = i;
	print();
	cout << "离开基类构造函数" << endl;
}

class son:public father
{
public:
	son(string a, int i ,int j);
	void print1();
	~son(){cout << "释放子类对象" << endl;}
private:
	int weight;
};

son::son(std::string a, int i, int j):father(a,i)
{
	cout << "在子类构造函数中" << endl;
	//name = a;
	//tall = i;
	weight = j;
}
void son::print1()
{
	father::print();
	cout << "体重" << weight << endl;
}

void main()
{
	son a("Mike",188,70);
	a.print1();
	cout << "结束了" << endl;
}
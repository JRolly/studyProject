#include <iostream>
#include <string>
#include "TestC++.h"
using namespace std;

class rectangle
{
public:
	rectangle(){	cout << "构造一个长方形!\n";}
	rectangle(int l, int w){length = l;width = w;}
	int area(){return length*width;}
	void setVal(int v){val = v;}
	int getVal()const{return val;}
	~rectangle(){	cout << "析构函数调用成功！" << endl;}
private:
	int length;
	int width;
	int val;
};

void swap(int &ra, int &rb)
{
	ra +=rb;
	rb = ra - rb;
	ra -=rb;
}

char queue[10][3] = {0};
int cnt = 0;

void OutputMsg()
{
	char str[3] = {0};
	if (cnt != 0)
	{
		--cnt;
		memcpy(str, (char*)&queue[0], 3);
		
		for (int i = 0; i < 3; ++i)
		{
			cout << str[i];
		}
		cout<<endl;
		if (cnt != 0)
		{
			for (int i = 0; i < cnt; ++i)
			{
				strncpy(queue[i], queue[i+1], 3);
			}
		}	
	}
}

void InputMsg(string str)
{
	if (cnt < 10)
	{
		memcpy(queue[cnt], str.c_str(), 3);
		++cnt;
	}
	else
	{
		for (int i = 0; i < 9; ++i)
		{
			memcpy(queue[i], queue[i+1], 3);
		}
		memcpy(queue[cnt], str.c_str(), 3);
	}
}

void PrintMsg()
{
	char str[3] = {0};
	int n = 0;
	while(n < cnt)
	{
		memcpy(str, (char*)&queue[n++], 3);
		for (int i = 0; i < 3; ++i)
		{
			cout << str[i];
		}
		cout<<endl;
	}
}

void testQueue()
{
	string str;
	cout << "输入：" << endl;
	
	for (int i = 0; i < 3; ++i)
	{	
		cin >> str;
		InputMsg(str);
	}

	cout << "已有消息" <<endl;
	PrintMsg();

	cout << "取出一条消息..."<<endl;;
	OutputMsg();

	cout << "已有消息" <<endl;
	PrintMsg();


	cout << "输入消息：";
	while(cin >>str)
		InputMsg(str);

	cout << "已有消息" <<endl;
	PrintMsg();

	cout <<"取出所有消息"<<endl;

	while(cnt)
		OutputMsg();

	system("PAUSE");
}

void testMsg()
{
	CMsg msg;
	int iCach;
	string strCach;
	ST_MSG stCach;
	stCach.pSig = NULL;
	for (int i = 0; i < 2; ++i)
	{
		cout << "aa:";
		cin >> iCach;
		stCach.aa = iCach;
		cout << "bb:";
		cin >> iCach;
		stCach.bb = iCach;

		int signum = 0;
		cout << "sig Num：";
		cin >> signum;
		stCach.pSig = new ST_SIG[signum*sizeof(ST_SIG)];
		for (int i = 0; i < signum; ++i)
		{
			cout << "a：";
			cin >> iCach;
			stCach.pSig[i].a = iCach;
			cout << "b:";
			cin >> iCach;
			stCach.pSig[i].b = iCach;

			cout << "enum:";
			cin >> iCach;
			cout << "desc:";
			cin >> strCach;

			pair<map<int, string>::const_iterator, bool> ret =
				stCach.pSig[i].mapEnum.insert(make_pair(iCach, strCach));
			if (!ret.second)
			{
				cout << "Insert struct Error!"<< endl;
			}
		}	

		cout << "key";
		cin >> iCach;		
		pair<map<int, ST_MSG>::const_iterator, bool> r = 
			msg.m_mapMsg.insert(make_pair(iCach, stCach));
		if (!r.second)
		{
			cout << "Insert map Error!" << endl;
		}
	}

	map<int, ST_MSG>::const_iterator it = msg.m_mapMsg.begin();
	for (; it != msg.m_mapMsg.end(); ++it)
	{
		if (it->second.pSig != NULL)
			delete [] it->second.pSig;
	}
}

void testUnion()
{
	union
	{
		int i;
		char c[2];
	}a;
	a.c[0] = 10;
	a.c[1] = 1;
	cout << a.i << endl;
}

void main()
{
	//rectangle a(3,4);
	//rectangle b;
	//cout << "长方形面积是："<< a.area() << endl;

	//rectangle *c = new rectangle(5,6);
	//cout << "通过new关键字创建对象，并获取长方形面积：" << c->area() << endl;
	//(*c).setVal(12);
	////c->setVal(12);
	//cout << "设置变量val值为：" << c->getVal() << endl;
	//delete c;
	//c = 0;

	//int x = 3, y = 4;
	//cout << "交换前：x " << x << "y " << y << endl;
	//swap(x,y);
	//cout << "交换后：x " << x << "y " << y << endl;

	//testQueue();

	testUnion();

	system("PAUSE");
}

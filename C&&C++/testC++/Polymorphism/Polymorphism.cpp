#include <iostream>
using namespace std;

//多重继承
//多态
class human
{
public:
	human(int);
	virtual ~human(){cout << "析构人类" << endl;}
	virtual int walk()const{return itswalk;}
private:
	int itswalk;
};
human::human(int walk):itswalk(walk)
{
	cout << "创建人类" << endl;
}

class father:virtual public human
{
public:
	father(int walk, int wit);
	virtual ~father(){cout << "析构父亲" << endl;}
	virtual int wit()const{return itswit;}
protected:
	int itswit;
};
father::father(int walk, int wit):human(walk),itswit(wit)
{
	cout << "创建父亲" << endl;
}

class mother:virtual public human
{
public:
	mother(int walk, bool sex);
	virtual ~mother(){cout << "析构母亲" << endl;}
	virtual bool sex()const{return itsex;}
protected:
	bool itsex;
};
mother::mother(int walk, bool sex):human(walk),itsex(sex)
{
	cout << "创建母亲" << endl;
}

class son:public father,public mother
{
public:
	son(int walk, bool sex, int wit);
	void beautiful()const{cout << "儿子也很帅" << endl;}
	virtual ~son(){cout << "析构儿子" << endl;}
};
son::son(int walk, bool sex, int wit):human(walk),father(walk,wit),mother(walk,sex)
{
	cout << "创建儿子" << endl;
}

void main()
{
	son *ps = new son(80,true,100);
	ps->beautiful();
	cout << "一般人类的行走速度是" << ps->walk() << endl;
	if (ps->sex())
		cout << "母亲是女性" << endl;
	else
		cout << "无法确定性别" << endl;
	cout << "父亲的智商为" << ps->wit() << endl;
	delete ps;
	
}
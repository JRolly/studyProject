#include <iostream>
using namespace std;

//���ؼ̳�
//��̬
class human
{
public:
	human(int);
	virtual ~human(){cout << "��������" << endl;}
	virtual int walk()const{return itswalk;}
private:
	int itswalk;
};
human::human(int walk):itswalk(walk)
{
	cout << "��������" << endl;
}

class father:virtual public human
{
public:
	father(int walk, int wit);
	virtual ~father(){cout << "��������" << endl;}
	virtual int wit()const{return itswit;}
protected:
	int itswit;
};
father::father(int walk, int wit):human(walk),itswit(wit)
{
	cout << "��������" << endl;
}

class mother:virtual public human
{
public:
	mother(int walk, bool sex);
	virtual ~mother(){cout << "����ĸ��" << endl;}
	virtual bool sex()const{return itsex;}
protected:
	bool itsex;
};
mother::mother(int walk, bool sex):human(walk),itsex(sex)
{
	cout << "����ĸ��" << endl;
}

class son:public father,public mother
{
public:
	son(int walk, bool sex, int wit);
	void beautiful()const{cout << "����Ҳ��˧" << endl;}
	virtual ~son(){cout << "��������" << endl;}
};
son::son(int walk, bool sex, int wit):human(walk),father(walk,wit),mother(walk,sex)
{
	cout << "��������" << endl;
}

void main()
{
	son *ps = new son(80,true,100);
	ps->beautiful();
	cout << "һ������������ٶ���" << ps->walk() << endl;
	if (ps->sex())
		cout << "ĸ����Ů��" << endl;
	else
		cout << "�޷�ȷ���Ա�" << endl;
	cout << "���׵�����Ϊ" << ps->wit() << endl;
	delete ps;
	
}
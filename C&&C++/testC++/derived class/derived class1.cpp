#include <iostream>
#include <string>
using namespace std;

//���û���Ĺ��캯����ʼ������
class father
{
protected:
	string name;
	int tall;
public:
	father(string a, int i);
	father(){cout << "�������" << endl;}
	void print(){cout << name << "���Ϊ��" << tall << endl;}
	~father(){cout << "�ͷŻ������" << endl;}
};

father::father(string a, int i)
{
	cout << "�ڻ���Ĺ��캯����" << endl;
	name = a;
	tall = i;
	print();
	cout << "�뿪���๹�캯��" << endl;
}

class son:public father
{
public:
	son(string a, int i ,int j);
	void print1();
	~son(){cout << "�ͷ��������" << endl;}
private:
	int weight;
};

son::son(std::string a, int i, int j):father(a,i)
{
	cout << "�����๹�캯����" << endl;
	//name = a;
	//tall = i;
	weight = j;
}
void son::print1()
{
	father::print();
	cout << "����" << weight << endl;
}

void main()
{
	son a("Mike",188,70);
	a.print1();
	cout << "������" << endl;
}
#include <iostream>
using namespace std;

//��ľ�̬��Ա�����;�̬��Ա����
//��̬��Ա�������������࣬��˲��ܷ���ĳ������ĳ�Ա��������Ϊ��û��ָ��ö����thisָ�룬�������Է��ʸ���ľ�̬��Ա����

class A
{
public:
	void static show(){cout << A::x << endl;x++;}
private:
	static int x;
};
int A::x = 0;

//����ͨ�����������ʾ�̬��Ա����,   ͨ�� ����->���ʾ�̬��Ա����->���ʾ�̬��Ա����
class B
{
public:
	void static show(){cout << B::n << endl; n++;}
private:
	static int n;
};
int B::n = 0;


void main()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		A::show();
	}

	B b;
	b.show();
}



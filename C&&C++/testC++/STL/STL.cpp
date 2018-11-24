#include <iostream>
using namespace std;

//ģ��
//		template<class Type1��class Type2>
//	class�ؼ��ֱ�ʾType������
template<class Type>
//����������,����ֱ�ӽ��������ṹ��ĳ�Ա
void Tswap(Type &rx, Type &ry)
{
	rx += ry;
	ry = rx - ry;
	rx -= ry;
}

void change_demo()
{
	int x = 2, y = 3;
	cout << "����ǰ��x:" << x << ",y:" << y << endl;
	Tswap(x,y);
	cout << "������x:" << x << ",y:" << y << endl;

	float a = 3.2, b = 7.8;
	cout << "����ǰ��a:" << a << ",b:" << b << endl;
	Tswap(a,b);
	cout << "������a:" << a << ",b:" << b << endl;
}


//����ģ��
//����Ҫ�����������������ʱ����Ҫ����ģ��
template<class Type>
void Tswap(Type rx[], Type ry[], int n)
{
	cout << "����Tswap(Type rx[], Type ry[], int n)����\n";
	Type tmp;
	for (int i = 0; i < n; i++)
	{
		Type tmp = rx[i];
		rx[i] = ry[i];
		ry[i] = tmp;
	}
}

template<class Type>
void show(Type rx[], Type ry[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "num1[" << i << "]:" << rx[i] << " num2[" << i << "]:" << ry[i] << endl;
	}
}


//���廯����ģ�棬�����������
//	�ڽ��������ṹ���Աʱ���������������Ϣ�������ͨ��һ��ģ����ֱ��ʵ��
//	���ֻ�������еĲ��ֳ�Ա������ʱ��Ϊ����һ�»ᵼ��ʧ��
//	ͨ�����廯����ģ�����������
struct people
{
	char name[10];
	int age;
};
template<class Type>
void Swap(Type &a, Type &b)
{
	a += b;
	b = a - b;
	a -= b;
}
//void Swap(people &a, people &b)
template<>void Swap<people>(people &a, people &b)	//����Ч����ͬ
{	//	���߱�������Ҫʹ��Swapģ�溯������ʹ�þ��廯��Swap����������һ��Swap������
	//	�������е�peopleָ���˾��廯�����ͣ�С������ʹ�ø�������������������
	int age;
	age = a.age;
	a.age = b.age;
	b.age = age;
}
void show(people &p)
{
	cout << p.name << "�����䣺" << p.age << endl;
}
void stl_fun()
{
	int i = 10, j = 20;
	cout << "��ʼ�� i=" << i << " j=" << j << endl;
	cout << "ִ��Swap�������н���..." << endl;
	Swap(i,j);
	cout << "���� i=" << i << " j=" << j << endl;

	people Jack = {"Jack",44};
	people Mike = {"Mike",23};
	cout << "��Ա����ǰ:" << endl;
	show(Jack);
	show(Mike);
	Swap(Jack,Mike);
	cout << "������Ա�����" << endl;
	show(Jack);
	show(Mike);
}

//ʵ����ģ�溯��
// template void Swap<people>(people &a, people &b)
//	���������������������ģ��� ���岿�֣�������������Ϊpeople��ģ��ʵ��
//	��ʵ����ģ�洴���ĺ����Ķ��岿���ǲ����޸ĵ�
template<class Type>
void out(Type a){cout << a << endl;}
template void out<char>(char &);	//�������ʱ��������ĺ���ģ��ǿ�ƴ���һ��������void show(char &a){cout << a << endl;}
void stl_out()
{
	out(5);
}

//�������ȼ�
//	�ں��������������͡�����������ͬ������£���ͨ���� > ���廯����ģ�� > ����ģ��
template<class Type>
void chk(Type a){cout << "ģ�溯����" << endl;}
template<> void chk<int>(int a){ cout << "���廯ģ�溯����" << endl;}
void chk(int a){cout << "��ģ�溯��" << endl;}
void stl_chk_priority()
{
	chk(5);
}


//main
void main()
 {
	//change_demo();

	//const int num = 10;
	//int num1[num] = {10,11,12,13,14,15,16,17,18,19};
	//int num2[num] = {0,1,2,3,4,5,6,7,8,9};
	//cout << "����ǰ��\n";
	//show(num1,num2,num);
	//Tswap(num1,num2,num);
	//cout << "������\n";
	//show(num1,num2,num);

	//stl_fun();

	/*stl_out();*/

	stl_chk_priority();
}
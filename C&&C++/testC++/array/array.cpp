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
	~area(){cout << "ִ�����������ͷ��ڴ�" << endl;}
	int get()const{return length*width;}
	void set(int l, int w){length = l; width = w;}
private:
	int length;
	int width;
};
//void main()
//{
//	get one[5];	//���������get��������һ������5��Ԫ�ص�������󣬼������˴� one[0]~one[5] ��5������
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
//	area *pone = new area[10];	//����һ����10��area������ɵ����飬
//	int i;
//	for (i = 0; i < 10; i++)
//	{
//		pone[i].set(i,i*2);
//		cout << "area[" << i << "]:";
//		cout << pone[i].get() << endl;
//		cout << pone->get() << endl;
//		cout << endl;
//	}
//	delete [] pone;	//ɾ�������е�ÿ������
//}
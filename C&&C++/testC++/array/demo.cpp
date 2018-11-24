#include <iostream>
using namespace std;

class A
{
public:
	A(int l)
	{
		length = l;
		Size = new char[length];	//�ڶ��п��ٿռ䣬����char�����飬����Ϊlength���ÿռ�ĵ�ַ������Աָ�����Size
	}
	~A(){delete [] Size;}
	int getLength()const{return length;}
	//���������±������ []
	char &operator[](int i);
	//�������
	void PascalTriangle();
private:
	int length;
	char *Size;
};

char &A::operator [](int i)
{
	if (i >= 0 && i < length)	//������ȷ������Size[i]
		return Size[i];
	else						//���򷵻�char������ĳ��ȼ�1�����������һ��Ԫ��
	{
		cout << "\n������Χ.";
		return Size[length-1];
	}
}

//�������
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
	A a(6);	//����һ������a�������ô�һ�������Ĺ��캯������ʼ��length�ĳ���Ϊ6�����ڶ��п����¿ռ䣬����char�����飬����Ϊlength
			//�ÿռ�ĵ�ַ����Size
	char *ch = "hello12";
	for (i = 0; i < 8; i++)
	{
		a[i] = ch[i];
		cout << a[i];
	}
	cout << "\n";
	cout << a.getLength() << endl;
}
#include <iostream>
using namespace std;

//��������� �� �������� operator�����(������){ʵ��}

class num
{
public:
	num(){n = 1; cout << "���캯��ִ��..." << endl;}
	num(const num &s){this->n = s.n; cout << "���ƹ��캯��ִ��..." << endl;}
	num(int i){n = i; cout << "���캯��ִ��..." << endl;}
	~num(){cout << "��������ִ��..." << endl;}
	int get()const{return n;}
	void set(int i){n = i;}
	void add(){n++;}
	//���� ǰ���Լ������ ++i
	//��������أ�thisָ����Ƕ���ı�ǩ��ĳ������ĳ�Ա����Ҳ�ᱻ�������Զ����ϱ�ǩ--thisָ��
	//����Ա�����Լӣ�Ȼ�󷵻س�Ա������thisָ��
	//num operator++()	
	//{
	//	++n;
	//	return *this;
	//}
	//Ϊ���ⰴֵ����ʱ����һ��*this����ʱ��������ý�operator++()�ķ���ֵ����Ϊ����������
	//����һ�㲻��ִ��++++i�����Ĳ������б�Ҫ������ֵ����Ϊ����
	const num &operator++()
	{
		++n;
		return *this;
	}

	//���� �����Լ������ i++
	//�Ƚ���һ����ʱ���󣬽�ԭʼ�����ֵ���Ƶ���ʱ�����У�Ȼ���ڽ�ԭʼ�����ֵ��1����󷵻���ʱ����
	//���ص���һ����ʱ�������Ա��밴ֵ���أ������ñ����ķ�ʽ���أ����ᴴ�����������󳬳�������������������һ���ն���
	//ǰ���ԼӺͺ����Լ�һ��ʹ��ʱ��������������Ҫ�����б�ͬ�������oֻ�����ź���ʾ��������������������ͬ
	num operator++(int o)
	{
		num tmp(*this);
		n++;
		return tmp;
	}

	//���������±������ []
	char &operater[](int i)
	{
		if (i > 0 && i < length)
			return Size[i];
		else
		{
			cout << "\n������Χ��";
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




#include <iostream>
using namespace std;

class father
{
public:
	father():age(33){cout << "���๹�캯����ʼ����������Ϊ��" << age << endl;}
	~father(){cout << "������������" << endl;}
	//void run()const{cout << "������������" << endl;}
	//�麯����ϵͳִ�е��ؼ���virtual�ĺ���ʱ ���Զ��ж����ĸ� ���� ����������Ȼ����øö����ͬ������
	virtual void run()const{cout << "������������" << endl;}
private:
	int age;
};

class son:public father
{
public:
	son(){cout << "���๹�캯��" << endl;}
	~son(){cout << "������������" << endl;}
	//һ��������˵��Ϊ�麯�������������и��Ǹú�������ô�������Ҳ���麯����virtual�������ԣ���д�����������
	/*virtual*/void run()const{cout << "��������ʮ����" << endl;}
};

//void main()
//{
//	father *pfather = new son;	//����������󣬽��������ֵ������ָ��
//	pfather->run();	//����������run������������������е���
//	delete pfather;
//}
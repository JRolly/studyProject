#include "includeFile.h"
#include "declearFile.h"
using namespace std;

int main()
{
	string str;

	cout<<"Press \"Ctr + Z\" to end..."<<endl;
	while(cin>>str);
	cout<<"You have input:"<<str<<endl;

	cout<<"test findDeleteIsupper()..."<<endl;
	findDeleteIsupper(str);
	cout<<"After delete upper:"<<str<<endl;

	cout<<"test s_toupper()..."<<endl;
	s_toupper(str);
	cout<<"After toupper:"<<str<<endl;
	
	/*���Բ����ַ����е�һ������*/
	string sn("sf.a2b");
	int num = find_first_fingure(sn);	
	if(num != -1)
	{
		cout<<"sn:"<<sn<<"\tsn�е�һ��������:"<<num<<endl;		
	}
	else
	{
		cout<<"�ַ�����û������."<<endl;;
	}

	/*����ͳ������е�����Ŀ*/
	string sentence = "My name is Jaysi,from China,and I'm a CodeMonkey!";
	int count = statistical_word(sentence);
	cout<<"��䣺"<<sentence<<endl;
	cout<<"����й���"<<count<<"������."<<endl;

	system("PAUSE");
}

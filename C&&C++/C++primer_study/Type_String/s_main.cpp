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
	
	/*测试查找字符串中第一个数字*/
	string sn("sf.a2b");
	int num = find_first_fingure(sn);	
	if(num != -1)
	{
		cout<<"sn:"<<sn<<"\tsn中第一个数字是:"<<num<<endl;		
	}
	else
	{
		cout<<"字符串中没有数字."<<endl;;
	}

	/*测试统计语句中单词数目*/
	string sentence = "My name is Jaysi,from China,and I'm a CodeMonkey!";
	int count = statistical_word(sentence);
	cout<<"语句："<<sentence<<endl;
	cout<<"语句中共有"<<count<<"个单词."<<endl;

	system("PAUSE");
}

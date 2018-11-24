#include "IncludeFile.h"
#include "DeclearFile.h"
using namespace std;


int main()
{
	int ival;
	string str;
	/*存储pair对象的vector容器*/
	vector< pair<string, int> > pvec;
	read_pair(pvec);
	cout<<"输入数据为："<<endl;
	for(vector< pair<string, int> >::iterator pviter = pvec.begin();
		pviter != pvec.end(); pviter++)
	{
		cout<<(*pviter).first<<" "<<(*pviter).second<<endl;
	}


	/*测试单词转换*/
	cout<<endl<<"测试单词转换..."<<endl;
	trans_words();



	system("PAUSE");
}
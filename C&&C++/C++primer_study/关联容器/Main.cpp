#include "IncludeFile.h"
#include "DeclearFile.h"
using namespace std;


int main()
{
	int ival;
	string str;
	/*�洢pair�����vector����*/
	vector< pair<string, int> > pvec;
	read_pair(pvec);
	cout<<"��������Ϊ��"<<endl;
	for(vector< pair<string, int> >::iterator pviter = pvec.begin();
		pviter != pvec.end(); pviter++)
	{
		cout<<(*pviter).first<<" "<<(*pviter).second<<endl;
	}


	/*���Ե���ת��*/
	cout<<endl<<"���Ե���ת��..."<<endl;
	trans_words();



	system("PAUSE");
}
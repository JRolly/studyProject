/*
 * ���Ե���������
 */
#include "IncludeFile.h"
#include "DeclearFile.h"
using namespace std;


/*����string��int�����ݣ���ÿһ��洢��һ��pair�����У�Ȼ��pair����洢��vector������*/
void read_pair(vector< pair<string, int> > &pvec)
{
	string str;
	int ival;
	pair<string, int> sipr;
	cout<<"Enter a string and an integer(Ctrl+Z to end):"<<endl;
	while(cin>>str>>ival)
	{
		sipr = make_pair(str, ival);	/*����pair����*/
		pvec.push_back(sipr);	/*��pair�������vector����*/
	}
}


/*ʹ��map������ת�����ʣ��ļ�1.txtΪ�ֵ䣬�洢��Ӧ��key��value���ļ�2.txt�洢��Ҫת�������*/
void trans_words()
{
	string key, value;
	map<string, string> trans_word;

	/*���ֵ��ļ�����ʧ�����׳��쳣*/
	ifstream map_file = ifstream("1.txt", ios::in);
	if(!map_file)
	{
		throw runtime_error("no transformation file.");
	}

	/*���ֵ��ļ��е�key��value����map����*/
	while(map_file>>key>>value)
	{
		trans_word.insert(make_pair(key, value));
	}

	/*����Ҫת�����ļ�����ʧ�����׳��쳣*/
	ifstream input = ifstream("2.txt", ios::in);
	if(!input)
	{
		throw runtime_error("no input file.");
	}

	string line;
	/*��ȡ�����ļ���������ת��*/
	while(getline(input, line))
	{
		string word;
		bool firstword = true;
		istringstream stream(line);		//��ȡ���У�һ��һ������

		/*��ȡһ�����뵥�ʣ���map�ֵ��в��ң������ص�����*/
		while(stream>>word)
		{
			map<string, string>::const_iterator map_it =
				trans_word.find(word);

			/*���ҳɹ����滻��ǰ����*/
			if(map_it != trans_word.end())
				word = map_it->second;

			/*����ǵ�һ�����ʣ�����Ҫ����ո񣬷�֮����ո�*/
			if(firstword)
				firstword = false;
			else
				cout<<" ";

			cout<<word;
		}
		cout<<endl;
	}
}
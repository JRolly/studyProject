/*
 * 测试迭代器功能
 */
#include "IncludeFile.h"
#include "DeclearFile.h"
using namespace std;


/*读入string和int型数据，将每一组存储在一个pair对象中，然后将pair对象存储在vector容器里*/
void read_pair(vector< pair<string, int> > &pvec)
{
	string str;
	int ival;
	pair<string, int> sipr;
	cout<<"Enter a string and an integer(Ctrl+Z to end):"<<endl;
	while(cin>>str>>ival)
	{
		sipr = make_pair(str, ival);	/*创建pair对象*/
		pvec.push_back(sipr);	/*将pair对象存入vector容器*/
	}
}


/*使用map容器，转换单词，文件1.txt为字典，存储对应的key和value，文件2.txt存储需要转换的语句*/
void trans_words()
{
	string key, value;
	map<string, string> trans_word;

	/*打开字典文件，若失败则抛出异常*/
	ifstream map_file = ifstream("1.txt", ios::in);
	if(!map_file)
	{
		throw runtime_error("no transformation file.");
	}

	/*将字典文件中的key和value存入map容器*/
	while(map_file>>key>>value)
	{
		trans_word.insert(make_pair(key, value));
	}

	/*打开需要转换的文件，若失败则抛出异常*/
	ifstream input = ifstream("2.txt", ios::in);
	if(!input)
	{
		throw runtime_error("no input file.");
	}

	string line;
	/*读取输入文件，并进行转换*/
	while(getline(input, line))
	{
		string word;
		bool firstword = true;
		istringstream stream(line);		//读取本行，一次一个单词

		/*读取一个输入单词，在map字典中查找，并返回迭代器*/
		while(stream>>word)
		{
			map<string, string>::const_iterator map_it =
				trans_word.find(word);

			/*查找成功，替换当前单词*/
			if(map_it != trans_word.end())
				word = map_it->second;

			/*如果是第一个单词，则不需要输出空格，反之输出空格*/
			if(firstword)
				firstword = false;
			else
				cout<<" ";

			cout<<word;
		}
		cout<<endl;
	}
}
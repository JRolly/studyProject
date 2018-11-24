#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

/*�ж�s1�Ƿ�С��s2*/
bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

/*�ж��ַ���str�����Ƿ���ڵ���6*/
bool GT6(const string &str)
{
	return str.size() >= 6;
}

/*���������ַ������ظ����ʣ��Թ��˺�ĵ��ʰ��ֵ�˳��������ͳ�Ƴ��ȳ���6�ĵ���*/
void filter_vec(vector<string> &words)
{
	sort(words.begin(), words.end());
	vector<string>::iterator end_unique = 
					unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

void sort_vec(vector<string> &words)
{
	stable_sort(words.begin(), words.end(), isShorter);
}

vector<string>::size_type count_GT6(vector<string> &words)
{
	return count_if(words.begin(), words.end(), GT6);
}



/*���Թ���*/
void test_sortVec()
{
	string str;
	vector<string> words;

	cout<<"Enter some words(Press Ctr+Z to end):"<<endl;
	while(cin>>str)
	{	
		words.push_back(str);
	}
	filter_vec(words);
	sort_vec(words);
	vector<string>::size_type cnt = count_GT6(words);
	cout<<cnt<<" word 6 characters or long."<<endl;
	
	for(vector<string>::iterator it = words.begin();
			it != words.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
//
//void main()
//{
//	cout<<"���Թ������򵥴�..."<<endl;
//	test_sortVec();
//
//	system("PAUSE");
//}
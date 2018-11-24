#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

/*判断s1是否小于s2*/
bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

/*判断字符串str长度是否大于等于6*/
bool GT6(const string &str)
{
	return str.size() >= 6;
}

/*过滤输入字符串中重复单词，对过滤后的单词按字典顺序重排序，统计长度超过6的单词*/
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



/*测试功能*/
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
//	cout<<"测试过滤排序单词..."<<endl;
//	test_sortVec();
//
//	system("PAUSE");
//}
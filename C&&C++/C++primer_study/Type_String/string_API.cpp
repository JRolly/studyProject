/*
 * 测试string类型迭代器功能
 */
#include "includeFile.h"
#include "declearFile.h"
using namespace std;

/*
*	将输入字符串中的小写字母改为大写
*/
void s_toupper(string &str)
{
	for(string::iterator sit = str.begin();
		sit != str.end(); ++sit)
		*sit = toupper(*sit);
}


/*
*找到并删除输入字符串中的大写字符
*/
void findDeleteIsupper(string &str)
{
	for(string::iterator sit = str.begin();
		sit != str.end(); ++sit)
	{
		if(isupper(*sit))
		{
			str.erase(sit);
			--sit;
		}
	}
}


/*查找字符串中第一个数字*/
int find_first_fingure(string str)
{
	string numerics("0123456789");
	string::size_type pos = str.find_first_of(numerics);
	if(pos == string::npos)
	{
		return -1;
	}
	return atoi(&str[pos]);
}


/*统计语句中共有多少单词，并指出最长、最短单词，并输出*/
int statistical_word(string str)
{
	/*存放当前单词*/
	string word;
	/*单词个数*/
	int count = 0;
	/*用作分隔符的字符*/
	string separators(" \t;,\v\r\n\f");

	/*单词起始、结束位置*/
	string::size_type startPos = 0, endPos = 0;	
	/*语句中最长、短单词及下一个单词长度*/
	string::size_type maxLen, minLen, wordLen;	
	/*存放最长、短单词的容器*/
	vector<string> longestWords, shortestWords;

	/*每次循环处理语句中的一个单词*/
	while((startPos = str.find_first_not_of(separators,endPos)) 
			!= string::npos)
	{
		/*找到下一个单词的起始位置*/
		++count;

		/*找到下一个单词的结束位置*/
		endPos = str.find_first_of(separators,startPos);

		/*找不到出现下一个分隔符的位置，即这是最后一个单词*/
		if(endPos == string::npos)
		{
			wordLen = str.size() - startPos;
		}
		else
		{/*找到下一个出现分隔符的位置*/
			wordLen = endPos - startPos;
		}

		/*获取单词，存入word*/
		word.assign(str.begin() + startPos, str.begin() + startPos + wordLen);

		/*设置下次查找的起始位置*/
		startPos = str.find_first_not_of(separators,endPos);

		/*找到的是第一个单词*/
		if(count == 1)
		{
			maxLen = minLen = wordLen;
			longestWords.push_back(word);
			shortestWords.push_back(word);
		}
		else
		{
			/*当前单词比目前最长单词长*/
			if(wordLen > maxLen)
			{
				maxLen = wordLen;
				longestWords.clear();//清空存放最长单词容器
				longestWords.push_back(word);
			}
			else if(wordLen == maxLen) /*当前单词与最长单词一样长*/
			{
				longestWords.push_back(word);
			}

			/*当前单词比目前最短单词短*/
			if(wordLen < minLen)
			{
				minLen = wordLen;
				shortestWords.clear();
				shortestWords.push_back(word);
			}
			else if(wordLen == minLen) /*当前单词与最短单词一样长*/
			{
				shortestWords.push_back(word);
			}
		}//end else ... if(count == 1)
	}//end while((startPos = str.find_first_not_of(separators,endPos)) 	!= string::npos)

	vector<string>::iterator sit;
	/*输出最长单词*/
	sit = longestWords.begin();
	cout<<"最长单词：";
	while(sit != longestWords.end())
		cout<<*sit++<<endl;

	/*输出最短单词*/
	sit = shortestWords.begin();
	cout<<"最短单词：";
	while(sit != shortestWords.end())
		cout<<*sit++<<endl;

	/*返回单词个数*/
	return count;
}




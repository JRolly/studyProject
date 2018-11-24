/*
 * ����string���͵���������
 */
#include "includeFile.h"
#include "declearFile.h"
using namespace std;

/*
*	�������ַ����е�Сд��ĸ��Ϊ��д
*/
void s_toupper(string &str)
{
	for(string::iterator sit = str.begin();
		sit != str.end(); ++sit)
		*sit = toupper(*sit);
}


/*
*�ҵ���ɾ�������ַ����еĴ�д�ַ�
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


/*�����ַ����е�һ������*/
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


/*ͳ������й��ж��ٵ��ʣ���ָ�������̵��ʣ������*/
int statistical_word(string str)
{
	/*��ŵ�ǰ����*/
	string word;
	/*���ʸ���*/
	int count = 0;
	/*�����ָ������ַ�*/
	string separators(" \t;,\v\r\n\f");

	/*������ʼ������λ��*/
	string::size_type startPos = 0, endPos = 0;	
	/*���������̵��ʼ���һ�����ʳ���*/
	string::size_type maxLen, minLen, wordLen;	
	/*�������̵��ʵ�����*/
	vector<string> longestWords, shortestWords;

	/*ÿ��ѭ����������е�һ������*/
	while((startPos = str.find_first_not_of(separators,endPos)) 
			!= string::npos)
	{
		/*�ҵ���һ�����ʵ���ʼλ��*/
		++count;

		/*�ҵ���һ�����ʵĽ���λ��*/
		endPos = str.find_first_of(separators,startPos);

		/*�Ҳ���������һ���ָ�����λ�ã����������һ������*/
		if(endPos == string::npos)
		{
			wordLen = str.size() - startPos;
		}
		else
		{/*�ҵ���һ�����ַָ�����λ��*/
			wordLen = endPos - startPos;
		}

		/*��ȡ���ʣ�����word*/
		word.assign(str.begin() + startPos, str.begin() + startPos + wordLen);

		/*�����´β��ҵ���ʼλ��*/
		startPos = str.find_first_not_of(separators,endPos);

		/*�ҵ����ǵ�һ������*/
		if(count == 1)
		{
			maxLen = minLen = wordLen;
			longestWords.push_back(word);
			shortestWords.push_back(word);
		}
		else
		{
			/*��ǰ���ʱ�Ŀǰ����ʳ�*/
			if(wordLen > maxLen)
			{
				maxLen = wordLen;
				longestWords.clear();//��մ�����������
				longestWords.push_back(word);
			}
			else if(wordLen == maxLen) /*��ǰ�����������һ����*/
			{
				longestWords.push_back(word);
			}

			/*��ǰ���ʱ�Ŀǰ��̵��ʶ�*/
			if(wordLen < minLen)
			{
				minLen = wordLen;
				shortestWords.clear();
				shortestWords.push_back(word);
			}
			else if(wordLen == minLen) /*��ǰ��������̵���һ����*/
			{
				shortestWords.push_back(word);
			}
		}//end else ... if(count == 1)
	}//end while((startPos = str.find_first_not_of(separators,endPos)) 	!= string::npos)

	vector<string>::iterator sit;
	/*��������*/
	sit = longestWords.begin();
	cout<<"����ʣ�";
	while(sit != longestWords.end())
		cout<<*sit++<<endl;

	/*�����̵���*/
	sit = shortestWords.begin();
	cout<<"��̵��ʣ�";
	while(sit != shortestWords.end())
		cout<<*sit++<<endl;

	/*���ص��ʸ���*/
	return count;
}




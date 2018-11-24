/*
* 用于声明方法
*/

#ifndef __DECLEAR_H__
#define __DECLEAR_H__

#include "includeFile.h"

/*将输入字符串中小写字符转换为大写*/
void s_toupper(string &str);

/*找到并删除字符串中的大写字符*/
void findDeleteIsupper(string &str);

/*查找字符串中第一个数字*/
int find_first_fingure(string str);

/*统计语句中共有多少单词，并指出最长、最短单词，并输出*/
int statistical_word(string str);


#endif
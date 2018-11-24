/*
* 用于声明方法
*/

#ifndef __DECLEAR_H__
#define __DECLEAR_H__

#include "IncludeFile.h"

/*读入string和int型数据，将每一组存储在一个pair对象中，然后将pair对象存储在vector容器里*/
void read_pair(vector< pair<string,int> > &pvec);

/*使用map容器，转换单词，文件1.txt为字典，存储对应的key和value，文件2.txt存储需要转换的语句*/
void trans_words();

#endif
/*
*	学生健康信息登记表定义
*/

#ifndef __STUHEALTHLIST_H__
#define __STUHEALTHLIST_H__

#define NAMELEN	8	//姓名最大长度
#define CLASSLEN	4	//班级名最大长度

struct Stu
{
	char name[NAMELEN+1];
	long num;
	char sex;
	int age;
	char Class[CLASSLEN+1];
	int health;
};
typedef struct Stu ElemType;	//线表结构元素类型

struct LNode
{
	ElemType data;
	struct LNode *next;
};
typedef struct LNode *LinkList;

#endif __STUHEALTHLIST_H__	//end ifndef __STUHEALTHLIST_H__
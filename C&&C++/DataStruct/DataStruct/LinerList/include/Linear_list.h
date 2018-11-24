/*
*  linear_list,线性表
*/
#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__


//线性表的动态分配顺序存储结构
#define LIST_INIT_SIZE	100	//线性表存储空间的初始分配量
#define LISTINCREMENT	10	//线性表存储空间的分配增量

//Status code
#define TRUE			1
#define FALSE			-1
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1
#define OVERFLOW		-2

typedef int Status;		//函数的类型，值为函数结构状态代码
typedef int ElemType;	//用来表示数据类型

//Struct
typedef struct {
	ElemType *elem;		//存储空间基址
	int length;			//当前长度
	int listsize;		//当前分配的存储容量（sizeof(ElemType)）
}Sqlist;


#endif //end #ifndef __LINEAR_LIST_H__

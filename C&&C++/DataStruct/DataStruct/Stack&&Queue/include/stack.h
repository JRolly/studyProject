/*
*	栈的顺序存储表示
*/

#ifndef __STACK_H__
#define __STACK_H__

#include "Define.h"

#define STACK_INIT_SIZE	10	//存储空间初始分配量
#define STACKINCREMENT	2	//存储空间分配增量

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

#endif	//end #ifndef __STACK_H__
/*
*	ջ��˳��洢��ʾ
*/

#ifndef __STACK_H__
#define __STACK_H__

#include "Define.h"

#define STACK_INIT_SIZE	10	//�洢�ռ��ʼ������
#define STACKINCREMENT	2	//�洢�ռ��������

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

#endif	//end #ifndef __STACK_H__
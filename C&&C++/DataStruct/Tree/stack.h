/*
*	ջ��˳��洢��ʾ
*/

#ifndef __STACK_H__
#define __STACK_H__

//#include "Define.h"

#define STACK_INIT_SIZE	10	//�洢�ռ��ʼ������
#define STACKINCREMENT	2	//�洢�ռ��������

#include "Define.h"
#include "linkTree.h"

typedef BiTree SElemType;

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
Status StackTraverse(SqStack S, Status(*visit)(SElemType));


#endif	//end #ifndef __STACK_H__
//�������

#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <process.h>

//Status code
#define TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1
//#define OVERFLOW		-2   //��math.h��OVERFLOW����Ϊ-3��ȥ��

typedef int Status;		//���������ͣ�ֵΪ�����ṹ״̬����
typedef int Boolean;	//�������ͣ�ֵΪTRUE��FALSE
//typedef int ElemType;	//������ʾ��������
//typedef char SElemType;	//������ʾջ��������
typedef int QElemType;	//��ʾ������������

#endif  //end define __DEFINE_H__
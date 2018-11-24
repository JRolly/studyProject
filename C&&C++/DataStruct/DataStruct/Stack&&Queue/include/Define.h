//定义参数

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
//#define OVERFLOW		-2   //在math.h中OVERFLOW定义为-3，去掉

typedef int Status;		//函数的类型，值为函数结构状态代码
typedef int Boolean;	//布尔类型，值为TRUE或FALSE
//typedef int ElemType;	//用来表示数据类型
//typedef char SElemType;	//用来表示栈数据类型
typedef int QElemType;	//表示队列数据类型

#endif  //end define __DEFINE_H__
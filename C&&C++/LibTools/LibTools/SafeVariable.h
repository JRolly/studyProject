#ifndef __SAFE_VARIABLE_H__
#define __SAFE_VARIABLE_H__
//多线程安全变量定义

#include "Lock.h"


//多线程安全变量：int型和bool型
typedef struct _MINI_
{
	int m_nValue;	//安全变量
	MUTEX m_Lock;	//锁
}MINT, MBOOL;

/*安全变量操作方法*/
int MVarInit(MINT& mValue, int nValue=0);	//初始化
void MVarDestroy(MINT& mValue);	//销毁
int MVarGet(MINT& mValue);	//获取变量值
int MVarSet(MINT& mValue, int nValue);	//设置变量值
int MVarAdd(MINT& mValue, int nValue=1);	//变量加法，默认+1
int mVarDec(MINT& mValue, int nValue=1);	//变量减法，默认-1









#endif //__SAFE_VARIABLE_H__

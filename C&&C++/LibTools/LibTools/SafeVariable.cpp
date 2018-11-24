//线程安全变量方法实现
#include "SafeVariable.h"
#include "Lock.h"


/*安全变量操作方法*/

//初始化
int MVarInit(MINT& mValue, int nValue/*=0*/)	
{
	MUTEX_INIT(&mValue.m_Lock);
	mValue.m_nValue = nValue;
	return nValue;
}

//销毁
void MVarDestroy(MINT& mValue)
{
	MUTEX_LOCK(&mValue.m_Lock);
	MUTEX_UNLOCK(&mValue.m_Lock);
	MUTEX_DESTROY(&mValue.m_Lock);
}


//获取变量值
int MVarGet(MINT& (mValue))
{
	int nValue;
	MUTEX_LOCK(&mValue.m_Lock);
	nValue = mValue.m_nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nValue;
}


//设置变量值
int MVarSet(MINT& mValue, int nValue)
{
	MUTEX_LOCK(&mValue.m_Lock);
	mValue.m_nValue = nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nValue;
}


//变量加法，默认+1
int MVarAdd(MINT& mValue, int nValue/*=1*/)
{
	int nRet;
	MUTEX_LOCK(&mValue.m_Lock);
	mValue.m_nValue += nValue;
	nRet = mValue.m_nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nRet;
}


//变量减法，默认-1
int mVarDec(MINT& mValue, int nValue/*=1*/)
{
	int nRet;
	MUTEX_LOCK(&mValue.m_Lock);
	mValue.m_nValue -= nValue;
	nRet = mValue.m_nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nRet;
}






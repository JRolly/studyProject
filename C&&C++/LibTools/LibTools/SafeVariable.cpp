//�̰߳�ȫ��������ʵ��
#include "SafeVariable.h"
#include "Lock.h"


/*��ȫ������������*/

//��ʼ��
int MVarInit(MINT& mValue, int nValue/*=0*/)	
{
	MUTEX_INIT(&mValue.m_Lock);
	mValue.m_nValue = nValue;
	return nValue;
}

//����
void MVarDestroy(MINT& mValue)
{
	MUTEX_LOCK(&mValue.m_Lock);
	MUTEX_UNLOCK(&mValue.m_Lock);
	MUTEX_DESTROY(&mValue.m_Lock);
}


//��ȡ����ֵ
int MVarGet(MINT& (mValue))
{
	int nValue;
	MUTEX_LOCK(&mValue.m_Lock);
	nValue = mValue.m_nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nValue;
}


//���ñ���ֵ
int MVarSet(MINT& mValue, int nValue)
{
	MUTEX_LOCK(&mValue.m_Lock);
	mValue.m_nValue = nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nValue;
}


//�����ӷ���Ĭ��+1
int MVarAdd(MINT& mValue, int nValue/*=1*/)
{
	int nRet;
	MUTEX_LOCK(&mValue.m_Lock);
	mValue.m_nValue += nValue;
	nRet = mValue.m_nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nRet;
}


//����������Ĭ��-1
int mVarDec(MINT& mValue, int nValue/*=1*/)
{
	int nRet;
	MUTEX_LOCK(&mValue.m_Lock);
	mValue.m_nValue -= nValue;
	nRet = mValue.m_nValue;
	MUTEX_UNLOCK(&mValue.m_Lock);
	return nRet;
}






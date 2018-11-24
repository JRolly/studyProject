#ifndef __SAFE_VARIABLE_H__
#define __SAFE_VARIABLE_H__
//���̰߳�ȫ��������

#include "Lock.h"


//���̰߳�ȫ������int�ͺ�bool��
typedef struct _MINI_
{
	int m_nValue;	//��ȫ����
	MUTEX m_Lock;	//��
}MINT, MBOOL;

/*��ȫ������������*/
int MVarInit(MINT& mValue, int nValue=0);	//��ʼ��
void MVarDestroy(MINT& mValue);	//����
int MVarGet(MINT& mValue);	//��ȡ����ֵ
int MVarSet(MINT& mValue, int nValue);	//���ñ���ֵ
int MVarAdd(MINT& mValue, int nValue=1);	//�����ӷ���Ĭ��+1
int mVarDec(MINT& mValue, int nValue=1);	//����������Ĭ��-1









#endif //__SAFE_VARIABLE_H__

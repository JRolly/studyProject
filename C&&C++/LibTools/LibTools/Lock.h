#ifndef __LOCK_H__
#define	__LOCK_H__

#include <conio.h>
#include <windows.h>

//����������
#define MUTEX				CRITICAL_SECTION				//��������������
#define MUTEX_INIT(m)		InitializeCriticalSection(m)	//��ʼ����
#define MUTEX_LOCK(m)		EnterCriticalSection(m)			//����
#define MUTEX_UNLOCK(m)		LeaveCriticalSection(m)			//����
#define	MUTEX_DESTROY(m)	DeleteCriticalSection(m)		//������	


//������������
class CLock
{
public:
	CLock() { MUTEX_INIT(&m_Lock); }
	~CLock() { MUTEX_DESTROY(&m_Lock); }
public:
	void Lock() { MUTEX_LOCK(&m_Lock); }	//��������
	void UnLock() { MUTEX_UNLOCK(&m_Lock); }	//��������
private:
	MUTEX m_Lock;	//������
};








#endif	//__LOCK_H__

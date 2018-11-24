#ifndef __LOCK_H__
#define	__LOCK_H__

#include <conio.h>
#include <windows.h>

//锁操作定义
#define MUTEX				CRITICAL_SECTION				//定义锁变量类型
#define MUTEX_INIT(m)		InitializeCriticalSection(m)	//初始化锁
#define MUTEX_LOCK(m)		EnterCriticalSection(m)			//加锁
#define MUTEX_UNLOCK(m)		LeaveCriticalSection(m)			//解锁
#define	MUTEX_DESTROY(m)	DeleteCriticalSection(m)		//销毁锁	


//基本锁操作类
class CLock
{
public:
	CLock() { MUTEX_INIT(&m_Lock); }
	~CLock() { MUTEX_DESTROY(&m_Lock); }
public:
	void Lock() { MUTEX_LOCK(&m_Lock); }	//加锁操作
	void UnLock() { MUTEX_UNLOCK(&m_Lock); }	//解锁操作
private:
	MUTEX m_Lock;	//锁变量
};








#endif	//__LOCK_H__

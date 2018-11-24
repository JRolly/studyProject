////////////////////////////////////////////////////////////
//							������
////////////////////////////////////////////////////////////




#ifndef __LOCK_TOOLS_H__
#define __LOCK_TOOLS_H__

#include "IncludeDef.h"
//#include "DebugTools.h"


#ifdef WIN32 //Windows �¶���
	//��������������
	#define MUTEX CRITICAL_SECTION
	//�����ʼ�����Ĺ���
	#define MUTEXINIT(m) InitializeCriticalSection(m)
	//�������
	#define MUTEXLOCK(m) EnterCriticalSection(m)
	//�������
	#define MUTEXUNLOCK(m) LeaveCriticalSection(m)
	//����ݻ�����������
	#define MUTEXDESTROY(m) DeleteCriticalSection(m)
#else //Linux �¶���
	//��������������
	#define MUTEX pthread_mutex_t
	//�����ʼ�����Ĺ���
	#define MUTEXINIT(m) pthread_mutex_init(m, NULL)
	//�������
	#define MUTEXLOCK(m) pthread_mutex_lock(m)
	//�������
	#define MUTEXUNLOCK(m) pthread_mutex_unlock(m)
	//����ݻ�����������
	#define MUTEXDESTROY(m) pthread_mutex_destroy(m)
#endif

#ifdef WIN32
//
#else
//Linux ����ͨ��˯�ߺ����Ա�
	#define Sleep(ms) usleep(ms*1000)
#endif

class CMutexLock
{ 
public:
	CMutexLock(void){MUTEXINIT(&m_Lock);} //���캯������ʼ����
	~CMutexLock(void){MUTEXDESTROY(&m_Lock);} //�����������ݻ���
public:
	void Lock(){MUTEXLOCK(&m_Lock);} //��������
	void Unlock(){MUTEXUNLOCK(&m_Lock);} //��������
private:
	MUTEX m_Lock; //��������˽�У�
};



typedef struct _MINT_ //�������͵Ķ��̰߳�ȫ��Ԫ
{
	int m_nValue; //��������ֵ
	MUTEX m_MyLock; //����ʵ�ֱ�����C ����������
}MINT,MBOOL; //int �ͺ�bool ��ͬʱʵ��

//��ʼ��һ���̰߳�ȫ����,ͬʱ��������ֵ,��������ֵ
extern int MvarInit(MINT& (mValue),int nValue=0);
//�ݻ�һ���̰߳�ȫ����
extern void MvarDestroy(MINT& (mValue));
//����һ���̰߳�ȫ������ֵ,�������õ�ֵ
extern int MvarSet(MINT& (mValue),int nValue);
//�õ�һ���̰߳�ȫ������ֵ
extern int MvarGet(MINT& (mValue));
//�̰߳�ȫ�������ӷ�����,Ĭ��+1
extern int MvarADD(MINT& (mValue),int nValue=1);
//�̰߳�ȫ��������������,Ĭ��-1
extern int MvarDEC(MINT& (mValue),int nValue=1);

//����ȫ��ʹ����������ʵ��
//��ע�⣬�������й��з������ǵ���C �ķ���ʵ�֡�
class CMint //int �Ͷ��̰߳�ȫ������
{
public:
	CMint(int nVlaue=0){MvarInit(m_nValue,nVlaue);}
	~CMint(void){MvarDestroy(m_nValue);}
public:
	int Get(void){return MvarGet(m_nValue);}
	int Set(int nValue){return MvarSet(m_nValue,nValue);}
	int Add(int nValue=1){return MvarADD(m_nValue,nValue);}
	int Dec(int nValue=1){return MvarDEC(m_nValue,nValue);}
private:
	MINT m_nValue;
};

class CMbool //bool �Ͷ��̰߳�ȫ�ı�����
{
public:
	CMbool(bool nVlaue=false){MvarInit(m_nValue,nVlaue);}
	~CMbool(void){MvarDestroy(m_nValue);}
public: //ֻ�ṩGet ��Set ����
	int Get(void){return MvarGet(m_nValue);}
	int Set(bool nValue){return MvarSet(m_nValue,nValue);}
private:
	MBOOL m_nValue;
};


#if 0
//ģ�嶨��
#include <Afxmt.h> //����Windows ���߳̿��ͷ�ļ�
template <class MVAR_TYPE>
class MVAR
{ 
private:
	//Ϊ����Ӧ���еı������ͣ��˴�ʹ�ö�̬�ڴ�鱣���������
	//��ˣ��ڲ���������һ��ָ����������ָ�룬ͨ��ǿ��ָ������ת��ʵ�ַ���
	char* m_pBegin;
	CCriticalSection m_csLockHandle; //ʹ��Windows �ٽ�����ʵ����
public:
	//���캯��ʹ�ñ�׼C++��new ��ʽ�����ڴ�
	MVAR(){m_pBegin=new char[sizeof(MVAR_TYPE)];}
	//��������ʹ�ñ�׼C++��delete[]��ʽ�ͷ��ڴ�
	~MVAR(){delete[] m_pBegin;}
	//��ñ����ĳ��ȣ�Ҳ���ǻ�øñ������͵��ֽڿ�ȣ�sizeof��
	int GetLength(){return sizeof(MVAR_TYPE);}
	//���ñ�����ֵ
	MVAR_TYPE Set(MVAR_TYPE& value)
	{
		m_csLockHandle.Lock(); //���з��ʾ�ʹ���ٽ���������
		//��ע�⣬���еĿ�����������ʹ��memcpy������������ʹ����ĸ���
		memcpy(m_pBegin,(char*)&value,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return value;
	} 
	//��ȡ������ֵ
	MVAR_TYPE Get()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����=��ֱ�Ӹ�ֵ����
	MVAR_TYPE operator=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		myValue=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//���ذ�λ�������~
	MVAR_TYPE operator~()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue=~myValue;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����++����������ͣ�
	MVAR_TYPE operator++(int)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue++;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����++�������++�������Ҫ��������
	MVAR_TYPE operator++()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue++;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����--����������ͣ�
	MVAR_TYPE operator--(int)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue--;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����--�������--�����Ҳ��Ҫ��������
	MVAR_TYPE operator--()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue--;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����+��������ӷ�����
	MVAR_TYPE operator+(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue+=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����-���������������
	MVAR_TYPE operator-(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue-=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����*��������˷�����
	MVAR_TYPE operator*(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue*=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����/���������������
	MVAR_TYPE operator/(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue/=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����&���㷨and ����
	MVAR_TYPE operator&(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue&=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����|���㷨��or ����
	MVAR_TYPE operator|(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue|=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����^��������������
	MVAR_TYPE operator^(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue^=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����+=�����
	MVAR_TYPE operator+=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue+=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����-=�����
	MVAR_TYPE operator-=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue-=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����*=�����
	MVAR_TYPE operator*=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue*=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����/=�����
	MVAR_TYPE operator/=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue/=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����&=�����
	MVAR_TYPE operator&=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue&=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����|=�����
	MVAR_TYPE operator|=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue|=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//����^=����� 
	MVAR_TYPE operator^=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue^=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//����>��������Ƚ�����
	BOOL operator>(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue>value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	//����<��������Ƚ�����
	BOOL operator<(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue<value);
		m_csLockHandle.Unlock();
		return bRet;
	} 
	//����>=��������Ƚ�����
	BOOL operator>=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue>=value);
		m_csLockHandle.Unlock();
		return bRet;
	} 
	//����<=��������Ƚ�����
	BOOL operator<=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue<=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	//����==��������Ƚ�����
	BOOL operator==(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue==value);
		m_csLockHandle.Unlock();
		return bRet;
	} 
	//����!=��������Ƚ�����
	BOOL operator!=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue!=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
};

#endif

//��д�����
typedef struct _TOOLS_MULTI_READ_SINGLE_WRITE_LOCK_
{ //ע�������������ѭ�����������������е���������
	int m_nReadCount; //��������
	bool m_bWriteFlag; //д��־
	MUTEX m_Lock; //��Ϊ��д���������ҲӦ���Ƕ��̰߳�ȫ�ģ�
	//��ˣ���Ҫ����һ��������
}SToolsMultiReadSingleWriteLock; //�����µı������ͣ����Զ������
const ULONG SToolsMultiReadSingleWriteLockSize=
	sizeof(SToolsMultiReadSingleWriteLock);

//MRSW ��Multi Read and Signal Write������͵�д������д
//MRSWLock ǰ׺��ʾ��д�����
//�м�һ����_���ָ���������Ǻ����Ĺ�������Greate��������Destroy���ݻ٣��ȵ�
void MRSWLock_Create(SToolsMultiReadSingleWriteLock* pLock);
void MRSWLock_Destroy(SToolsMultiReadSingleWriteLock* pLock);
//��ȡд״̬
bool MRSWLock_GetWrite(SToolsMultiReadSingleWriteLock* pLock);
//��ȡ��������
int MRSWLock_GetRead(SToolsMultiReadSingleWriteLock* pLock);
//����д��������
void MRSWLock_EnableWrite(SToolsMultiReadSingleWriteLock* pLock);
//���˳�д������
void MRSWLock_DisableWrite(SToolsMultiReadSingleWriteLock* pLock);
//��������������ص�ǰ�Ķ�������ֵ
int MRSWLock_AddRead(SToolsMultiReadSingleWriteLock* pLock);
//���ض��������仯��Ľ��
int MRSWLock_DecRead(SToolsMultiReadSingleWriteLock* pLock);
//��תд
void MRSWLock_Read2Write(SToolsMultiReadSingleWriteLock* pLock);

//�߾���˯�ߺ�������������ģʽ���ٵ���
inline void ToolsMinSleep(void);

class CMultiReadSingleWriteLock
{
public:
	//���캯���������������Զ����ýṹ��ĳ�ʼ���ʹݻ�
	CMultiReadSingleWriteLock(){MRSWLock_Create(&m_Lock);}
	~CMultiReadSingleWriteLock(){MRSWLock_Destroy(&m_Lock);}
public:
	//��Ӧ�Ĺ��з�������ȫ�ǵ���C ���Եĺ���
	void EnableWrite(void){MRSWLock_EnableWrite(&m_Lock);}
	void DisableWrite(void){MRSWLock_DisableWrite(&m_Lock);}
	void Read2Write(void){MRSWLock_Read2Write(&m_Lock);}
	void DecRead(void){MRSWLock_DecRead(&m_Lock);}
	void AddRead(void){MRSWLock_AddRead(&m_Lock);}
	bool GetWrite(void){return MRSWLock_GetWrite(&m_Lock);}
	int GetRead(void){return MRSWLock_GetRead(&m_Lock);}
private:
	//˽�нṹ��
	SToolsMultiReadSingleWriteLock m_Lock;
};


//��д�������ȫ����
class CMRSWint
{ 
public:
	CMRSWint();
	~CMRSWint(){} //�������������κ���
public:
	int Get(void);
	int Set(int nValue);
	int Add(int nValue=1);
	int Dec(int nValue=1);
	int GetAndClean2Zero(void);
	int DecUnless0(int nValue=1); //������ǣ�-1
private:
	int m_nValue;
	CMultiReadSingleWriteLock m_Lock;
};

class CMRSWbool
{ 
public:
	CMRSWbool(){}
	~CMRSWbool(){}
public:
	//�õ�������ֵ���������ñ�����ֵ�����������Ͷ������
	bool Get(void){return (bool)m_nValue.Get();}
	bool Set(bool bFlag){return m_nValue.Set((int)bFlag);}
private:
	CMRSWint m_nValue; //�ڲ��ۺ�һ�����Ķ�������͵�д�������ȫ����
};



//����������
class CNonReentrant
{
public:
	CNonReentrant();
	~CNonReentrant(){} //�������������κ���
public:
	//����Ϊ���ʱ��
	// ���û�����ý����־�����ã���������
	// ����Ѿ����ý����־�������ã������ؼ�
	//����Ϊ�ٵ�ʱ��
	// ���ǳɹ���������
	bool Set(bool bRunFlag);
private:
	CMutexLock m_Lock; //��
	bool m_bAlreadRunFlag; //�ڲ��ı���ֵ
};



//�߳̿�����
class CThreadManager
{ 
private:
	//��ҿ���ע�⵽���߳̿��������������������ڲ�ѯ��
	//ֻ�����߳���ͣʱ���Ż��д�ڲ���ֵ��
	//��ˣ��˴��õ�ȫ���ǵ�д�������
	CMRSWbool m_bThreadContinue; //�̳߳����ı�־
	CMRSWint m_nThreadCount; //�̼߳�����
	//�ܶ�ʱ�����������Դ��룬������Ҫ����̲߳���
	//��Debug ��ӡ���ʱ�����ܻ���Ҫһ���������߳�ID��
	//�߳�ID ��Ҫ��Ψһ�Է��䣬��ˣ�����������������̰߳�ȫ���У��ܱ������߳̿���
	//��ҵ���޹أ������������ӡ��Ϣ�������ĸ��̣߳�
	//�����ṩһ���߳�ID �ṩ��������Ա���Ը�����Ҫ�����߳���ʹ�ã�
	//������һ����Ƕ��debug �Ѻù��ܡ�
	CMRSWint m_nThreadID;
public:
	CThreadManager(){} //���ڶ��̰߳�ȫ�����������ó�ʼ�����˴������ʼ��
	~CThreadManager(){CloseAll();} //�˳�ʱ�Զ��ر������߳�
	//�����߼�����ʵҲ�ǳ�ʼ���߼�
	//��ʹ���߳̿�����ǰ����һ��Ҫ�ȵ��ñ��ӿں���
	void Open(void)
	{
		CloseAll(); //Ϊ��ֹ������������ִ��һ��Close
		//��ʼ���߳̿��Ʊ���
		m_bThreadContinue.Set(true);
		m_nThreadCount.Set(0);
	} 
	//�ر������߳��߼�
	void CloseAll(void)
	{ //����߼��Ѿ����ּ��Σ��˴�����׸��
		m_bThreadContinue.Set(false);
		while(m_nThreadCount.Get()){ToolsMinSleep();}
	} 
	//����һ���߳�ǰ���̼߳�����+1�Ķ���
	int AddAThread(void){return m_nThreadCount.Add();}
	//�߳��˳�ǰ���̼߳�����-1 ����
	void DecAThread(void){m_nThreadCount.Dec();}
	//��ѯ�߳�ά�ֱ�����ֵ
	bool ThreadContinue(void){return m_bThreadContinue.Get();}
	//����̼߳�������ֵ
	int GetThreadCount(void){return m_nThreadCount.Get();}
	//����һ���߳�ID����Debug ʹ��
	int GetID(void) {return m_nThreadID.Add()-1;}
};



#endif	// __LOCK_TOOLS_H__
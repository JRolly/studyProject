////////////////////////////////////////////////////////////
//							�̳߳�
////////////////////////////////////////////////////////////


#ifndef __THREAD_TOOLS_H__
#define __THREAD_TOOLS_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "LockTools.h"


#define OPEN_THREAD_DELAY 250 //�¿��̵߳��ӳ�ms ��,Windows ��Linux ϵͳ,
//���߳�̫��Ļ�,��������߳�
//������һ���ӳ�,�����������>200ms
#define WHILE_THREAD_COUNT 10 //���n ���߳̿��еȴ����񣨾��������10��
//�ⲻ��Ӳ�Ե�,������߳��Ѿ�IDLE,
//���ܻ�������,�����ᶯ̬����
#define DEFAULT_THREAD_SLEEP 500 //ͨ��������߳�˯�߲���
#define THREAD_POOL_EXIT_CODE 10000 //�̳߳ص��߳�,�ӿ�ʼ�����˳���

//���߳�������
#ifdef _ARM_ //ARM Ƕ��ʽϵͳ
	#define THIS_POOLTHREAD_MAX 30 //Ƕ��ʽϵͳ�����30 ���߳�
#else //PC ��
	#ifdef WIN32
		#define THIS_POOLTHREAD_MAX 2000 //Windows �����2000 ���߳�
	#else // not WIN32
		#define THIS_POOLTHREAD_MAX 300 //Linux �����300 ���߳�
	#endif //WIN32
#endif

#define TPOOL_THREAD_STATE_NOT_RUN 0 //�̳߳��߳�״̬,�߳�δ����
#define TPOOL_THREAD_STATE_IDLE 1 //�̳߳��߳�״̬,�߳�����,����
#define TPOOL_THREAD_STATE_BUSY 2 //�̳߳��߳�״̬,�߳�����,������

#define _THREADPOOL_CAN_NOT_USE -2 //�̳߳�δ��ʼ�����޷�����
#define _THREADPOOL_OVERFLOW -1 //�̳߳������־,�޷�ע��
#define _THREADPOOL_PLEASE_WAIT 0 //�̳߳�Ŀǰû�б����߳�,��ȴ�
#define _THREADPOOL_OK 1 //�̳߳�ע��ɹ�



#ifdef WIN32 //Windows �¶���
	#include <process.h>
	//�߳̾������
	#define THREAD HANDLE
	//�߳�ID ����
	#define THREAD_ID unsigned
	//�߳���������ͳһ���ͣ�ע�⺯���ͺ��ʹ��
	#define THREAD_CREATE(func, args, thread, id) \
		thread = (HANDLE)_beginthreadex(NULL, 0, func, (PVOID)args, 0, &id);
	//�߳�����ʧ�ܺ󷵻ش����붨��
	#define THREAD_CREATE_ERROR NULL
	//�̺߳�����׼����
	#define THREAD_FUNC_DECL(func,args) unsigned __stdcall func(PVOID args)
	//������ͨ����Ҫ��Ȿ�ο��������ĺ�������Windows ��Linux ��һ�����˴�����ͳһ��
	#define _GetTimeOfDay GetTickCount
	//Windows ����С˯�߾��ȣ���ʵ��Ϊ10ms
	#define MIN_SLEEP 10
#else //Linux �¶���
	//�߳̾������
	#define THREAD pthread_t
	//�߳�ID ����
	#define THREAD_ID unsigned //unused for Posix Threads
	//�߳���������ͳһ���ͣ�ע�⺯���ͺ��ʹ��
	#define THREAD_CREATE(func, args, thread, id) \
		pthread_create(&thread, NULL, func, args);
	//�߳�����ʧ�ܺ󷵻ش����붨��
	#define THREAD_CREATE_ERROR -1
	//�̺߳�����׼����
	#define THREAD_FUNC_DECL(func,args) void * func(void *args)
	//#define Sleep(ms) usleep((__useconds_t)(ms*1000))
	//������ͨ����Ҫ��Ȿ�ο��������ĺ�������Windows ��Linux ��һ�����˴�����ͳһ��
	unsigned long GetTickCount(void);
	#include <sys/time.h>
	#define _GetTimeOfDay GetTickCount
	//Linux ��û��Sleep ������Ϊ�˱���ͳһ��̣�����Windows �¶���ú���
	#define Sleep(ms) usleep(ms*1000)
	#define MIN_SLEEP 1
#endif


#ifdef WIN32 //Windows �¶���
	//Windows ���д˺����������ظ�����
#else //Linux �¶���
	//��ñ��ο�������������
	inline unsigned long GetTickCount(void)
	{
		unsigned long lRet=0;
		struct timeval tv;
		gettimeofday(&tv,null);
		lRet=tv.tv_usec/1000;
		return lRet;
	} 
#endif



//�̳߳ػص�����ָ��
//ÿ���ص�������һ������Ȩ
//���н���,�̲߳����˳�,����IDLE ״̬
typedef void (*_TPOOL_CALLBACK)(
	void* pCallParam, //���������򴫽����Ĳ���ָ��
	MBOOL& bThreadContinue); //���ϵͳҪ�˳�,�̳߳ػ��޸����������ֵΪfalse
//DEMO: static void ThreadPoolCallback(void* pCallParam,MBOOL& bThreadContinue);


class CToolsThreadPool;

typedef struct _THREAD_TOKEN_
{
	int m_nExitCode; //����ֵ,Ҳ�Ǳ��߳��������̳߳صı��
	MINT m_nState; //�߳�״̬��
	THREAD m_hThread; //�߳̾��
	THREAD_ID m_nThreadID; //�߳�ID
	_TPOOL_CALLBACK m_pCallback; //�ص�����
	void* m_pCallParam; //�ص���������
	CToolsThreadPool* m_pThreadPoolObject; //ָ���̳߳ض����ָ��
}SThreadToken; //����ı�������
const unsigned long SThreadTokenSize=sizeof(SThreadToken); //�ṹ�峤�ȳ���


//�̳߳���
class CToolsThreadPool
{ 
public:
	CToolsThreadPool(CToolsLowDebug* pDebug); //��Ҫ����Debug ����ָ��
	~CToolsThreadPool();
public:
	//ע��һ�����̣߳�����״ֵ̬��״ֵ̬����������
	int ThreadPoolRegTask(
		_TPOOL_CALLBACK pCallback, //�ص�����ָ��
		void* pParam, //�����Ĳ���ָ��
		bool bWait4Success=TRUE); //�Ƿ�ȴ�ע��ɹ��ŷ���
	bool TPAllThreadIsIdle(void); //��������߳��Ƿ����
	bool ThreadPoolIsContinue(void); //����̳߳�����״̬
private:
	//��������ʵ�Ĳ���ϵͳ�̺߳������乹�ͺ�������
	static THREAD_FUNC_DECL(ThreadPoolThread,pParam); //�̳߳ط����߳�
	static THREAD_FUNC_DECL(ThreadPoolCtrlThread,pParam);//�̳߳ع����߳�
private:
	//�ڲ�����������û��ʹ�õ�Token
	int Search4NotUseToken(void);
	//�ڲ����������һ�������߳�
	int GetAIdleThread(void);
	//������ɾ���ע�ᶯ�����ڲ�������������ϸ����
	int ThreadPoolRegisterANewThread(
		_TPOOL_CALLBACK pCallback,
		void* pParam);
	int ThreadPoolRegisterANewThreadWhile(
		_TPOOL_CALLBACK pCallback,
		void* pParam);
private:
	SThreadToken m_TToken[THIS_POOLTHREAD_MAX]; //�̳߳����������̬����
	//���������������̳߳ذ�ȫ�˳����Ʋ�����int �͵ļ�����+bool �͵��̳߳�����־
	MBOOL m_bThreadContinue; //����Thread ������־
	MINT m_nThreadPoolThreadCount; //Thread ������
	//ͳ�Ʊ���
	MINT m_nThreadPoolIdleThreadCount; //���е��߳�����
	//�̳߳�û��ʹ��ǰ����C++���࣬����ֱ��ʹ��C �Ĵ����ṹ�����
	MUTEX m_RegisterLock; //�߳�ע���ٽ���
	CToolsLowDebug* m_pDebug; //Debug ����ָ��
};








#endif	// __THREAD_TOOLS_H__
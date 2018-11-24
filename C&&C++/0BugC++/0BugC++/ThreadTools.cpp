#include "ThreadTools.h"


CToolsThreadPool::CToolsThreadPool(CToolsLowDebug* pDebug)
{
	m_pDebug=pDebug; //����Debug ����ָ��
	TOOLS_DEBUG("CToolsThreadPool Start!\n"); //��ʾ������Ϣ
	THREAD_ID id; //ע�⣬�����������̵߳Ĳα���
	THREAD t; //�����ڱ�������ʾ������
	//ע�⣬������û��ʹ�������󣬶�ʹ�ô�C �����ṹ����ɡ�
	MUTEXINIT(&m_RegisterLock); //��ʼ���̳߳��ܵ�������
	MvarInit(m_bThreadContinue,true); //��ʼ��bThreadContinue ����
	MvarInit(m_nThreadPoolThreadCount,0); //��ʼ��nThreadCount ����
	MvarInit(m_nThreadPoolIdleThreadCount,0); //��ʼ�������߳�ͳ�Ʊ���
	//��ʼ������
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++)
	{
		//��Ȼ�������߳�û�б����߳̾���������ǵ�Ӧ���߳��Ժ�Ǳ�ڵ�����
		//���̵߳�����ṹ���У����Ǳ������߳̾�����߳�ID
		m_TToken[i].m_hThread=0;
		m_TToken[i].m_nThreadID=0;
		//����Ҫ��Ϊ�˵��Է��㣬Ϊÿ�������߳�����һ����ʽ���˳��룬Windows �£�
		//�̷߳��ؿ��Կ������ֵ
		m_TToken[i].m_nExitCode=THREAD_POOL_EXIT_CODE+i;
		//�����������ص�����ָ���͸������ָ�룬ע�⣬null ��ʾ��ǰ������
		//�����̼߳�ʹ������Ҳ����Idle �¿�ת��
		m_TToken[i].m_pCallback=null;
		m_TToken[i].m_pCallParam=null;
		//����һ������Ҫ���������̳߳��Լ���ָ�룬ԭ�������
		m_TToken[i].m_pThreadPoolObject=this;
		//��ʼ���߳�����Ԫ״̬������ע�⣬���̰߳�ȫ�ı�����C ģʽ
		MvarInit(m_TToken[i].m_nState,TPOOL_THREAD_STATE_NOT_RUN);
	} 
	id=0; //�����������߳�t=0;
	THREAD_CREATE(ThreadPoolCtrlThread,this,t,id);//ע�⣬�������̵߳Ĳ�����this
	Sleep(OPEN_THREAD_DELAY); //ǿ�Ƶȴ��������߳̿���
}

CToolsThreadPool::~CToolsThreadPool()
{
	//�ر��̣߳��������ȽϾ��䣬ǰ���Ѷ�γ��֣��˴�����׸��
	MvarSet(m_bThreadContinue,false);
	while(MvarGet(m_nThreadPoolThreadCount))
	{
		Sleep(MIN_SLEEP);
	}//�ȴ��ر������߳�
	//�ݻ������̲߳���ģ���״̬����
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++)
	{
		MvarDestroy(m_TToken[i].m_nState); //ֻ����һ����Ҫ�ݻ�
	} 
	MvarDestroy(m_bThreadContinue); //�ݻٸ��̰߳�ȫ����
	MvarDestroy(m_nThreadPoolThreadCount);
	MvarDestroy(m_nThreadPoolIdleThreadCount);
	MUTEXDESTROY(&m_RegisterLock); //�ݻٻ�����
	TOOLS_DEBUG("CToolsThreadPool Stop!\n"); //��ʾ�˳���Ϣ
}

//Ѱ��һ��û��ʹ�õ�Token
//�ҵ�,���ر��
//û���ҵ�(ȫ��������),����-1
int CToolsThreadPool::Search4NotUseToken(void)
{
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++) //���������������
	{
		if(TPOOL_THREAD_STATE_NOT_RUN==MvarGet(m_TToken[i].m_nState))
			return i; //�ҵ�������index
	} 
	return -1; //�Ҳ���������-1
}

//�������̣߳�ע�⣺����ĺ��������ǿ�ƽ̨���̺߳������壬ʹ�ú����
THREAD_FUNC_DECL(CToolsThreadPool::ThreadPoolCtrlThread,pParam)
{
	CToolsThreadPool* pThis=(CToolsThreadPool*)pParam; //��ϰ�ߣ����this ָ��
	//ע�⣬�˴������̼߳�������һ��˵�����̳߳ص�ʹ�������ǳ���ʹ��
	//���������߳�����ʵ�������еĻ��ᣬ��ˣ��̼߳�����������+1�������Ƿ��ڹ��캯��
	MvarADD(pThis->m_nThreadPoolThreadCount);
	int nIdleThread=0; //�����̼߳���
	int nNotRunThread=0; //δ�����̼߳���
	//��ע�������ѭ�����ο�bThreadContinue
	while(MvarGet(pThis->m_bThreadContinue))
	{
		//��õ�ǰ���е��߳���
		nIdleThread=MvarGet(pThis->m_nThreadPoolIdleThreadCount);
		if(WHILE_THREAD_COUNT>nIdleThread)
		{
			//������õĿ����̲߳���10,��Ҫ��ӣ��������·����߳�
			//����ǰ����Ҫ���ҵ����е�����飬�Ҳ�����Ҳ��������
			nNotRunThread=pThis->Search4NotUseToken();
			if(-1!=nNotRunThread)
			{
				//�����߳�
				THREAD_CREATE(ThreadPoolThread, //�������߳���
					//ע�⣬�˴����������ݿ�ָ����Ϊ���������������̣߳�
					//��ˣ�ÿ���������̣߳�����ά��һ���������ݿ�
					&(pThis->m_TToken[nNotRunThread]),
					//ע�⣬�˴������˷������̵߳ľ����ID
					pThis->m_TToken[nNotRunThread].m_hThread,
					pThis->m_TToken[nNotRunThread].m_nThreadID);
				//���û����������,������˵���˴����ٱ���
			}
		} 
		Sleep(OPEN_THREAD_DELAY); //һ��Ҫ�ȹ� 250ms
	} 
	MvarDEC(pThis->m_nThreadPoolThreadCount); //�˳�ʱ���̼߳�����-1
#ifdef WIN32 //����Linux ��Windows ���ַ�ʽ�˳�
		return THREAD_POOL_EXIT_CODE-1;
#else // not WIN32
		return null;
#endif
}

//�����߳�
THREAD_FUNC_DECL(CToolsThreadPool::ThreadPoolThread,pParam)
{
	//������ʷԭ�򣬴˴���һ�����壬�˴���pThis �����̳߳ض���ָ��
	//����������ָ�룬�����̳߳ؿ������磬���ڡ����ء�ԭ�򣬴˴�û����������
	//�̳߳ض���ָ�룬�˴���ʾΪ��pThis->m_pThreadPoolObject
	SThreadToken* pThis=(SThreadToken*)pParam;
	//������������ΪIdle ״̬
	MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_IDLE);
	//�̼߳�����+1
	MvarADD(pThis->m_pThreadPoolObject->m_nThreadPoolThreadCount);
	//Idle �̼߳�����+1
	MvarADD(pThis->m_pThreadPoolObject->m_nThreadPoolIdleThreadCount);
	//ע������غ�ѭ����������bThreadContinue �������Ա�������յ��˳�����
	while(MvarGet(pThis->m_pThreadPoolObject->m_bThreadContinue))
	{
		//ȡ����
		switch(MvarGet(pThis->m_nState))
		{
		case TPOOL_THREAD_STATE_NOT_RUN:
		//���״̬��ʾû���߳�Ϊ�������񣬵����ڱ��߳��Ѿ�����
		//�����Ȼ�������״̬,�϶������ˣ���ʾ�ⲿ����״̬���ò���
		//�������������,�Զ����Ǹ��޲�һ�¾�OK
		//�޲��ķ�����������ΪIdle ״̬
		MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_IDLE);
		//ע��˴�û��break
		case TPOOL_THREAD_STATE_IDLE: //û������
		default:
			//��������˯��
			break;
		case TPOOL_THREAD_STATE_BUSY: //Register ��������
			//��ע��һ��ϸ�ڣ�����û�а�Idle ������-1��
			//������ΪRegister �������������������������ϸ����
			if(pThis->m_pCallback) //����ǲ������������
			{
				//��ִ��Ȩ�����µ�����һ�Σ�����ע���������
				pThis->m_pCallback(pThis->m_pCallParam,
					pThis->m_pThreadPoolObject->m_bThreadContinue);
				//�����߳���+1
				MvarADD(pThis->m_pThreadPoolObject-> //----a
					m_nThreadPoolIdleThreadCount);
			} 
			break;
		};
		//�������߳�����
		if(WHILE_THREAD_COUNT< //----b
			MvarGet(pThis->m_pThreadPoolObject->m_nThreadPoolIdleThreadCount))
			break; //��������̳߳����޶�,��������ѭ�����˳��Լ�
		//���й������꣬���Լ���ΪIdle ״̬
		if(TPOOL_THREAD_STATE_IDLE!=MvarGet(pThis->m_nState)) //----c
			MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_IDLE);
		Sleep(DEFAULT_THREAD_SLEEP); //˯�ߣ��ȴ��´�����
	}
	//�˳�����
	//Idle ������-1
	MvarDEC(pThis->m_pThreadPoolObject->m_nThreadPoolIdleThreadCount); //----d
	//�߳��ܼ�����-1
	MvarDEC(pThis->m_pThreadPoolObject->m_nThreadPoolThreadCount);
	//�����������״̬����Ϊ��ȷ��ֵ��û���߳�Ϊ�����
	MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_NOT_RUN);
#ifdef WIN32 //���ַ�ʽ�˳�
	return pThis->m_nExitCode;
#else // not WIN32
	return null;
#endif
}

//���һ�����е��̱߳��
//����޿���,�򷵻�-1
int CToolsThreadPool::GetAIdleThread(void)
{
	int nRet=-1;
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++) //��������
	{ //ע�⣬��������Idle һ��״̬
		if(TPOOL_THREAD_STATE_IDLE==MvarGet(m_TToken[i].m_nState))
		{
			nRet=i;
			break; //�ҵ�����
		}
	} 
	return nRet; //û�ҵ������ܷ���-1
}

//ע��һ��������
//��ע��,�������ٽ�������,�̰߳�ȫ
//ע��ɹ�,����_THREADPOOL_OK�����򷵻�����������
int CToolsThreadPool::ThreadPoolRegisterANewThread(
	_TPOOL_CALLBACK pCallback, //����ص�����ָ��
	void* pParam) //͸�����������ָ��
{
	int nRet=_THREADPOOL_PLEASE_WAIT; //����ֵ���ó�ֵ
	MUTEXLOCK(&m_RegisterLock); //����
	int nIdleThread=GetAIdleThread(); //ȡ��Idle ���̱߳��
	if(0>nIdleThread)
	{ //û���ҵ�Idle �����߳�
		if(THIS_POOLTHREAD_MAX==MvarGet(m_nThreadPoolThreadCount))
		{
			//û�п����߳�,���߳������Ѿ��ﵽ����,����OverFlow ��־
			nRet=_THREADPOOL_OVERFLOW;
		} 
		else
		{
			//û�п����߳�,�����ǻ�û�����ü�����,������ߵȴ�
			nRet=_THREADPOOL_PLEASE_WAIT;
		}
	} 
	else
	{
		//�ҵ������߳�,�������
		m_TToken[nIdleThread].m_pCallback=pCallback; //������Կ�����ν�
		m_TToken[nIdleThread].m_pCallParam=pParam; //������ӵ���������
		MvarSet(m_TToken[nIdleThread].m_nState, //ע�⣬������鱻����Ϊ
			TPOOL_THREAD_STATE_BUSY); //busy����ˣ����ᱻ�ٴ�
		//����µ�����
		MvarDEC(m_nThreadPoolIdleThreadCount); //ǰ��������Idle ������-1
		nRet=_THREADPOOL_OK; //���سɹ���־
	} 
	MUTEXUNLOCK(&m_RegisterLock); //����
	return nRet;
}

//һ��Ҫע��ɹ�,���Եȴ��µ�Idle �̱߳��������߳���������������OverFlow������ѭ���ȴ�
int CToolsThreadPool::ThreadPoolRegisterANewThreadWhile(
	_TPOOL_CALLBACK pCallback, //����ص�����ָ��
	void* pParam) //͸�����������ָ��
{
	int nRet;
	while(1) //��ѭ���ȴ�
	{ //������һ��������ʼע��
		nRet=ThreadPoolRegisterANewThread(pCallback,pParam);
		//ע��ɹ��������̳߳������������
		if(_THREADPOOL_PLEASE_WAIT!=nRet) break;
		Sleep(OPEN_THREAD_DELAY); //����һ��,�µ��߳̾��Ѿ�������
	} 
	return nRet;
}

int CToolsThreadPool::ThreadPoolRegTask(
	_TPOOL_CALLBACK pCallback, //����ص�����ָ��
	void* pParam, //͸�����������ָ��
	bool bWait4Success) //�Ƿ���Ҫ�ȴ�ע��ɹ�
{
	if(bWait4Success) //���ݱ�־�����ò�ͬ�ĺ���
		return ThreadPoolRegisterANewThreadWhile(pCallback,pParam);
	else
		return ThreadPoolRegisterANewThread(pCallback,pParam);
}










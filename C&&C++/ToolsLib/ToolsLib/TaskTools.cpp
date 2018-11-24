#include "TaskTools.h"



//��һ��ָ��ע�ᵽ�ڴ�أ��ڴ��Ĭ���ھۺϹ�������
#define TOOLS_REGISTER(pPoint,szInfo) \
	m_pToolsBaseLib->m_pMemPool->Register(pPoint,szInfo)
//��һ��ָ����ڴ�ط�ע�ᣬ�ڴ��Ĭ���ھۺϹ�������
#define TOOLS_UNREGISTER(pPoint) \
	m_pToolsBaseLib->m_pMemPool->UnRegister(pPoint)
//��һ������ָ����ִ�з�ע�ᣬ�ٴݻ٣�����ÿ�
#define TOOLS_DEL_OBJ(p) \
	if(p){TOOLS_UNREGISTER(p);delete p;p=null;}




CToolsTaskPool::CToolsTaskPool(CToolsBaseLibrary* pToolsBaseLib,
	int nMaxThread)
{
	m_pToolsBaseLib=pToolsBaseLib; //����ۺϹ�����ָ��
	m_pDebug=m_pToolsBaseLib->m_pDebug; //�ӾۺϹ������л��debug ����ָ�룬
	//�������ʹ��
	m_nMaxThread=nMaxThread; //��������߳���
	pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool(): Start!\n"); //��ӡ������Ϣ
	m_bThreadContinue.Set(true); //�̹߳��������ʼ��
	m_nThreadCount.Set(0);
	m_nThreadID.Set(0); //����ID ���Ӹ���ֵ0
	//ʵ�����������
	m_pTaskQueue=new CToolsMemoryQueueWithLock(
		m_pToolsBaseLib->m_pDebug, //����debug ����ָ��
		m_pToolsBaseLib->m_pMemPool, //�����ڴ��ָ��
		"ToolsTaskPool"); //Ӧ����
	if(m_pTaskQueue)
	{ //ע�ᵽ�ڴ�ؽ��й���Ԥ���˳�ʱ�����ͷ�
		TOOLS_REGISTER(m_pTaskQueue,"CToolsTaskPool::m_pTaskQueue");
	}
	//ʵ�����̳߳�
	m_pThreadPool=new CToolsThreadPool(m_pToolsBaseLib->m_pDebug);
	if(m_pThreadPool)
	{ //ע�ᵽ�ڴ�ؽ��й���
		TOOLS_REGISTER(m_pThreadPool,"CToolsTaskPool::m_pThreadPool");
	} 
	if(ICanWork()) //�ж�ǰ���new �����Ƿ����
	{ //���������߳�
		if(!m_pThreadPool->ThreadPoolRegTask(TaskCtrlThread,this))
		{ //������־����������½�����ϸ����
			m_pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool:: start ctrl thread %d fail!\n");
		} 
		else
			m_nThreadCount.Add(); //���ע��ɹ����̼߳�����+1
	}
}


CToolsTaskPool::~CToolsTaskPool()
{
	//�Ա�׼��ʽ�˳����������������߳�
	m_bThreadContinue.Set(false);
	while(m_nThreadCount.Get()){Sleep(100);}
	TOOLS_DEL_OBJ(m_pThreadPool); //ɾ������ĺ�
	TOOLS_DEL_OBJ(m_pTaskQueue);
	m_pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool(): Stop!\n"); //��ӡ�˳���Ϣ
}


bool CToolsTaskPool::ICanWork(void)
{ //��Ҫ���������к��̳߳ض����Ƿ��ʼ��
	if(!m_pThreadPool) return false;
	if(!m_pTaskQueue) return false;
	return true;
}
void CToolsTaskPool::PrintInfo(void)
{ //��ӡ��ǰ�߳����������飬�������Ա�۲�
	TOOLS_PRINTF("task pool: thread count=%d, task in queue=%d\n",
		m_nThreadCount.Get(),m_pTaskQueue->GetTokenCount());
}

void CToolsTaskPool::TaskCtrlThread(
	void* pCallParam, //���������򴫽����Ĳ���ָ��
	MBOOL& bThreadContinue) //���ϵͳҪ�˳�,�̳߳ػ��޸����������ֵΪfalse
{
	CToolsTaskPool* pThis=(CToolsTaskPool*)pCallParam;
	int i=0;
	for(i=0;i<pThis->m_nMaxThread;i++) //��������߳�����ѭ�����������߳�
	{
		if(!pThis->m_pThreadPool->ThreadPoolRegTask(
			TaskServiceThread,pThis))
		{ //����ʧ�ܣ���ӡ������Ϣ���˳�����
			pThis->m_pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool:: start service thread %d fail!\n",i);
			break;
		} 
		else
			pThis->m_nThreadCount.Add(); //�����ɹ����߳���+1
	} 
	pThis->m_nThreadCount.Dec(); //������ɣ��Լ��˳�������̼߳�����-1
}


//�����������ݽṹSTaskPoolToken ָ�룬
//��������ص��������������߼٣����ؼ٣���ʾ�������Ѿ�����
bool CToolsTaskPool::TaskServiceThreadDoIt(STaskPoolToken& Task)
{
	bool bCallbackRet= //ִ�лص�����������÷���ֵ
		Task.m_pCallback(Task.m_pUserParam,Task.m_nUserStatus);
	if(!bCallbackRet) return bCallbackRet; //�������ֵΪ�٣�ֱ�ӷ��أ���ʾ�������
	//������񷵻��棬��ʾ������δ��������Ҫ�����ƻ�������У��ȴ��´�����
	bCallbackRet=RegisterATaskDoIt(&Task); //��ͼ����ע�ᵽ�������
	if(!bCallbackRet) //���ע��ʧ�ܣ���������ʾ����ʧ
	{
		TOOLS_DEBUG("CToolsTaskPool::TaskServiceThreadDoIt(): a task need \
			continue, but add 2 queue fail! task lost!\n");
		dbg_bin((char*)&Task,STaskPoolTokenSize);// TOOLS_DEBUG_BIN((char*)&Task,STaskPoolTokenSize);	?????������ôʵ�ֵ�
	} 
	return bCallbackRet; //���������
}

void CToolsTaskPool::TaskServiceThread(
	void* pCallParam, //���������򴫽����Ĳ���ָ��
	MBOOL& bThreadContinue) //���ϵͳҪ�˳�,�̳߳ػ��޸����������ֵΪfalse
{
	int nQueueRet=0;
	STaskPoolToken Task;
	char* szTask=(char*)&Task;
	//��ñ�����ָ��
	CToolsTaskPool* pThis=(CToolsTaskPool*)pCallParam;
	int nID=pThis->m_nThreadID.Add()-1;
	//���Ǵ�ӡ�������߳������źţ�ͨ��ע�͵����ã�����ʱ����ʹ�á�
	//pThis->XGSyslog("CToolsTaskPool::TaskServiceThread(): %d Start!\n",nID);
		while(MvarGet(bThreadContinue)) //ע�Ȿѭ������׼���̳߳��߳��غ�ѭ��
		{ //�������ӵ��жϣ��Ա��жϱ�������˳���־
			if(!pThis->m_bThreadContinue.Get())
				goto CToolsTaskPool_TaskServiceThread_End_Process;
			//���Դ���������е�����һ�����񣬲�ִ��
			nQueueRet=pThis->m_pTaskQueue->GetAndDeleteFirst(
				szTask,STaskPoolTokenSize);
			if(STaskPoolTokenSize==nQueueRet) //��������ɹ�����ʾ������
			{
				pThis->TaskServiceThreadDoIt(Task); //������һ����ִ��
			} 
			Sleep(MIN_SLEEP); //ϰ����˯
		}
CToolsTaskPool_TaskServiceThread_End_Process:
		pThis->m_nThreadCount.Dec(); //�˳�ʱ���̼߳�����-1
		//���Ǵ�ӡ�������߳�ֹͣ�źţ�ͨ��ע�͵����ã�����ʱ����ʹ�á�
		//pThis->XGSyslog("CToolsTaskPool::TaskServiceThread(): %d Stop!\n",nID);
}

bool CToolsTaskPool::RegisterATaskDoIt(STaskPoolToken* pToken,int nLimit)
{
	bool bRet=false;
	if(STaskPoolTokenSize==m_pTaskQueue->AddLast( //һ�ε��͵Ķ���AddLast ��Ϊ
		(char*)pToken,STaskPoolTokenSize),nLimit)
		bRet=true;
	return bRet;
}

bool CToolsTaskPool::RegisterATask(
	_TASKPOOL_CALLBACK pCallback, //����ص�����ָ��
	void* pUserParam) //�������ָ��
{
	STaskPoolToken Token; //׼��һ���ṹ��ʵ��
	if(!ICanWork()) return false;
	if(!pCallback) return false;
	Token.m_pCallback=pCallback; //���ṹ��
	Token.m_pUserParam=pUserParam;
	Token.m_nUserStatus=0; //ע��˴���״̬����Ϊ0
	return RegisterATaskDoIt(&Token,m_nMaxThread); //��������ĺ��������ע��
}






//��������ҪӦ����Щ������Ƭ�ε����񣬼�ֻ��һ���ص����������񣬿���ֱ��ע��������
bool CToolsTaskRun::StartTask(_TASKPOOL_CALLBACK pCallback, void* pCallParam, char* szAppName)
{ //��ʵ����һ�������������󣬵�������ĺ������ע������
	CToolsTaskRunInfo InfoObj;
	InfoObj.AddTask(pCallback,pCallParam); //ֱ�ӽ�����������ӵ���������
	return StartTask(&InfoObj,szAppName);
} 
//��������ҪӦ��ʹ�������������󣬲����������������Ӧ�ã�ע����������
bool CToolsTaskRun::StartTask(CToolsTaskRunInfo* pInfoObject, char* szAppName)
{
	return StartTask(pInfoObject->GetInfoPoint(),szAppName);
}

//�����������������������ڲ������ݽṹ�壬������յ�������������
//��ע�⣬������ʹ����Զ�Ѵ��Σ�����������Զ�Ѵ��εĲ���������ǰ�������Ľṹ��
//SToolsTeskRunTaskCallbackParam
bool CToolsTaskRun::StartTask(SToolsTaskRunInfo* pInfoStruct, char* szAppName)
{
	bool bRet=false; //׼������ֵ
	if(!m_ThreadManager.ThreadContinue()) //���������δ������������
		m_ThreadManager.Open();
	//��ע�������ʼ׼��Զ�Ѵ��εĲ����ṹ����������ʹ�����ڴ�ض�̬���롣
	//�ڴ�ص�ָ���ǴӾۺϹ������л�õġ�
	SToolsTeskRunTaskCallbackParam* pParam=(SToolsTeskRunTaskCallbackParam*)
		m_pToolsBaseLib->m_pMemPool->Malloc(SToolsTeskRunTaskCallbackParamSize,"CToolsTaskRun::pParam");
	if(pParam) //�ڴ�����ɹ�������ִ�У����򷵻ؼ�
	{
		pParam->m_pToolsBaseLib=m_pToolsBaseLib; //�ۺϹ�����ָ��
		pParam->m_pThis=this; //������ָ��
		pParam->m_nRunIndex=0; //״̬����0
		if(szAppName) //����ⲿ�ṩ��Ӧ����
			SafeStrcpy(pParam->m_szAppName, //����Ӧ����
				szAppName,
				TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
		else //�������Ӧ����
			TOOLS_CLEAN_CHAR_BUFFER(pParam->m_szAppName);
		//ע�⣬����ʹ��������������ճ�������ԣ�ճ�ϵ��������������������ݽṹ��
		CToolsTaskRunInfo InfoObj(&(pParam->m_Info));
		//Ŀ���ǵ���CopyFrom �������ⲿ������������
		InfoObj.CopyFrom(pInfoStruct);
		//���þۺϹ������е�����ض���ע������
		//ע�⣬ע�����Ǳ����ṩ�ı�׼����ִ���壬������������������
		//�ṩ����ִ�У�����ִ��Ӧ�ò��������á�
		bRet=m_pToolsBaseLib->m_pTaskPool->RegisterATask(
			ToolsTeskRunTaskCallback, //���Ǳ����������
			pParam); //Ӧ�ò�ע�������������
		//�ᱻ���ν���ִ��
		if(bRet)
		{
			m_ThreadManager.AddAThread(); //����ɹ����̼߳�����+1
			if(szAppName) //�����Ӧ��������ӡ��ʾ
				m_pToolsBaseLib->m_pLog->_XGSyslog("%s Start...\n",pParam->m_szAppName);
		}
	} return bRet;
}


void CToolsTaskRun::StopAll(void)
{
	m_ThreadManager.CloseAll();
}

void CToolsTaskRun::PrintInfo(void)
{
	TOOLS_PRINTF("task run: task count=%d\n",
	m_ThreadManager.GetThreadCount()); //��ӡ�߳�����
}

bool CToolsTaskRun::ToolsTeskRunTaskCallback(void* pCallParam,int& nStatus)
{
	bool bCallbackRet=false; //��¼�û�����Ƭ�εĵ��ý��
	bool bGotoNextStatus=true; //������һ״̬�ı�־
	SToolsTeskRunTaskCallbackParam* pParam= //ǿ��ָ������ת������ò���ָ��
		(SToolsTeskRunTaskCallbackParam*)pCallParam;
	if(!pParam) return false; //��������ƣ����û�в�������ֹ
	CToolsTaskRun* pThis=pParam->m_pThis; //������ã���ñ���ָ��pThis
	switch(nStatus) //���״̬����������ṩ��
	{
	case 0: 
		///���Ǳ���������ִ�д���
		if(pParam->m_Info.m_nTaskCount > pParam->m_nRunIndex)
		{ //ֻҪӦ�ò�����Ƭ��û�б���ѯ��ϣ�һֱ�ڱ�Ƭ��ִ��
			bGotoNextStatus=false; //���=false�����ǲ�ϣ����ת
			//����Ļص�����ϸ��
			bCallbackRet= //ȡ��Ӧ�ò�Ƭ�εĻص����
			//����Ӧ�ò�״̬��pParam->m_nRunIndex�����ú��ʵ�Ƭ��
			pParam->m_Info.m_CallbackArray[pParam->m_nRunIndex](
				pParam->m_Info.m_pCallParam,//����͸���Ĳ���ָ��
				pParam->m_nRunIndex); //������ؼ������ע��˴�û�а�
									  //�̳߳�״̬��nStatus ����Ӧ�ò�
									  //����ģ�飬����ʹ���Լ���״̬��
									  //���֡���ƭ������͸����ƵĹؼ�
									  //��������صĶ��壬���Ӧ�ó������Ƭ�η���false����ʾ��ϣ��������һƬ��
									  //��ˣ�������Ӧ�ó���״̬����+1 ����
			if(!bCallbackRet) pParam->m_nRunIndex++;			
			//ע�������ƣ����Ƿǳ��ؼ���һ������StopAll �����ã������󼴽��˳�ʱ
			//��������⵽�������������Ǽ򵥰�nStatus+1 ���˳�
			//���ǿ�ʼ����Ӧ������Ƭ�Σ�����Ӧ�ó����״̬��pParam->m_nRunIndex �ۼ�
			//����ǿ��ִ����Ӧ������Ƭ�����е�ÿһ����
			//���գ����������ΪӦ������ִ����϶��رգ��������ڴ���Ϊϵͳ�˳��ر�
			//������֤�����ڲ�����Դй©�������
			if(!pThis->m_ThreadManager.ThreadContinue())
				pParam->m_nRunIndex++;
		} 
		//���Ӧ�ó���Ƭ���Ѿ�ִ����ϣ��򱾺���״̬��+1����ת����һƬ�ν�������
		else bGotoNextStatus=true;
		break;
	default: //exit
		//�����Ӧ��������ӡ�˳���ʾ
		if(0<strlen(pParam->m_szAppName))
			pThis->m_pToolsBaseLib->m_pLog->_XGSyslog("%s Stop!\n",pParam->m_szAppName);
		pThis->m_ThreadManager.DecAThread(); //�̼߳�����-1
		pThis->m_pToolsBaseLib->m_pMemPool->Free(pParam); //�ͷŲ����ṹ��
		return false; //���ؼ٣���������
	}
	if(bGotoNextStatus) nStatus++; //����ǰ���жϣ�����������״̬
	return true; //�����棬���˳�����
}






























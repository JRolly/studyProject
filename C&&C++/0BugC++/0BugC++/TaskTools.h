////////////////////////////////////////////////////////////
//							�����
////////////////////////////////////////////////////////////

#ifndef __TASK_TOOLS_H__
#define __TASK_TOOLS_H__

#include "IncludeDef.h"
#include "DebugTools.h"
#include "MemQueue.h"
//#include "LogTools.h"
#include "BaseLib.h"

#define TASK_POOL_TOKEN_MAX (16*1024) //���ͬʱ����������
#define DEFAULT_THREAD_MAX (30) //Ĭ���߳���





//����ػص���������
//����ֵtrue ��������false ֹͣ����
typedef bool (*_TASKPOOL_CALLBACK)(void* pCallParam, //��������ָ��
	int& nStatus); //�������״̬��
//DEMO bool TaskCallback(void* pCallParam, int& nStatus);



//����غ������ݽṹ
typedef struct _TASK_POOL_TOKEN_
{
	_TASKPOOL_CALLBACK m_pCallback; //�ص�����ָ��
	void* m_pUserParam; //���û����ݵĻص���������������Ϊnull
	int m_nUserStatus; //�����û����ݵ�һ��״ֵ̬����ʼֵĬ����0
}STaskPoolToken;
//���ݽṹ����
const int STaskPoolTokenSize=sizeof(STaskPoolToken);



//�������
class CToolsTaskPool
{
public:
	CToolsTaskPool(
		CToolsBaseLibrary* pToolsBaseLib, //�����Ĺ��߾ۺ���ָ��
		int nMaxThread=DEFAULT_THREAD_MAX); //����߳���
	~CToolsTaskPool();
public:
	bool ICanWork(void); //��������ƣ������б�־
	void PrintInfo(void); //���ݴ�ӡ��Debug ��
public:
	//ע��һ�������񣬷���TaskID
	bool RegisterATask(_TASKPOOL_CALLBACK pCallback, //�ص�����ָ��
		void* pUserParam=null); //�ص���������
private:
	//��ʵ���ڲ�ע�ắ��
	bool RegisterATaskDoIt(STaskPoolToken* pToken,int nLimit=-1);
	//�������߳�
	bool TaskServiceThreadDoIt(STaskPoolToken& Task);
	static void TaskServiceThread(void* pCallParam,
		MBOOL& bThreadContinue);
	//�������߳�
	static void TaskCtrlThread(void* pCallParam,
		MBOOL& bThreadContinue);
private:
	CMRSWbool m_bThreadContinue; //������Դ��̹߳������
	CMRSWint m_nThreadCount; //���������˳������߳�
	CToolsMemoryQueueWithLock* m_pTaskQueue; //�����������
	CToolsThreadPool* m_pThreadPool; //�̳߳�ָ��
private:
	int m_nMaxThread; //����������ı������
	CMRSWint m_nThreadID; //����ID ����
	CToolsLowDebug* m_pDebug; //debug ����ָ��
	CToolsBaseLibrary* m_pToolsBaseLib; //�ۺϹ�����ָ��
};


#define TOOLS_TASK_RUN_MAX_TASK 16 //��ಽ����
typedef struct _TOOLS_TASK_RUN_INFO_
{
	int m_nTaskCount; //�ܹ����ٲ���
	void* m_pCallParam; //���õĻص���������
	//�����ص���������
	_TASKPOOL_CALLBACK m_CallbackArray[TOOLS_TASK_RUN_MAX_TASK];
}SToolsTaskRunInfo;
const ULONG SToolsTaskRunInfoSize=sizeof(SToolsTaskRunInfo);


class CToolsTaskRun;
typedef struct _ToolsTeskRunTaskCallback_Param_
{
	SToolsTaskRunInfo m_Info; //���������ṹ��
	CToolsBaseLibrary* m_pToolsBaseLib; //�����ۺϹ�����ָ��
	CToolsTaskRun* m_pThis; //�������������ָ��
	int m_nRunIndex; //��ǰִ�еĲ���
	char m_szAppName[TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE]; //Ӧ����
}SToolsTeskRunTaskCallbackParam;
const ULONG SToolsTeskRunTaskCallbackParamSize= //�ṹ�峤�ȳ���
	sizeof(SToolsTeskRunTaskCallbackParam);



class CToolsTaskRunInfo
{
public:
	//����ʹ��SToolsTeskRunTaskCallbackParam �ṹ���Σ�ʵ��ճ�ϵĹ��캯��
	//ʹ��m_pInfo ָ�룬ָ��ָ��SToolsTeskRunTaskCallbackParam �е�m_Info
	CToolsTaskRunInfo(SToolsTeskRunTaskCallbackParam* pParam)
	{
		m_pInfo=&(pParam->m_Info);
		Init(m_pInfo); //��ʼ��
	} 
	//����ֱ��ճ�ϵ��ⲿ��һ��SToolsTaskRunInfo �ṹ��ʵ�������ع��캯��
	//ʹ��m_pInfo ָ�룬ָ��ָ����Ľṹ��ָ��
	CToolsTaskRunInfo(SToolsTaskRunInfo* pInfo)
	{
		m_pInfo=pInfo;
		Init(m_pInfo); //��ʼ��
	} 
	//�����Թ�������������ʹ��m_pInfo����ʹ�ñ����Դ���������
	CToolsTaskRunInfo()
	{
		m_pInfo=null;
		Init(&m_Info); //��ʼ��
	}
	~CToolsTaskRunInfo(){} //�����������ݻ�����
private:
	static void Init(SToolsTaskRunInfo* pInfo) //��ʼ������
	{
		pInfo->m_nTaskCount=0; //��������������
		pInfo->m_pCallParam=null; //����ָ�����
		int i=0;
		for(i=0;i<TOOLS_TASK_RUN_MAX_TASK;i++) //���16 ���ص�����ָ��
		pInfo->m_CallbackArray[i]=null;
	}
public:
	SToolsTaskRunInfo* GetInfoPoint(void)
	{
		if(m_pInfo) //���ȷ���m_pInfo
			return m_pInfo;
		else
			return &m_Info; //���򷵻�m_Info �ĵ�ַ
	}
public:
	void SetCallbackParam(void* pCallParam)
	{
		if(m_pInfo) //ע���Ⱥ�˳������ʹ��m_pInfo
			m_pInfo->m_pCallParam=pCallParam;
		else
			m_Info.m_pCallParam=pCallParam;
	}	
public:
	//�������һ���ص���������ͬ������ķ���������������ĵ����ص�������ӷ���
	bool AddTask(_TASKPOOL_CALLBACK pCallback,void* pCallParam)
	{
		if(pCallParam) SetCallbackParam(pCallParam); //�в����������ò���
		return AddTask(pCallback); //������һ����������ص�ָ��
	}

	bool AddTask(_TASKPOOL_CALLBACK pCallback)
	{
		if(m_pInfo) //����ʹ��m_pInfo
		{ //���ص����������Ƿ��ޣ����򷵻�false���ܾ����
			if(TOOLS_TASK_RUN_MAX_TASK<=m_pInfo->m_nTaskCount) return false;
			//��ӵ�����ĩβ
			m_pInfo->m_CallbackArray[m_pInfo->m_nTaskCount]=pCallback;
			//���������+1
			m_pInfo->m_nTaskCount++;
			return true;
		} 
		else //��	m_pInfo ���ã���ʹ��m_Info
		{ //���ص����������Ƿ��ޣ����򷵻�false���ܾ����
			if(TOOLS_TASK_RUN_MAX_TASK<=m_Info.m_nTaskCount) return false;
			//��ӵ�����ĩβ
			m_Info.m_CallbackArray[m_Info.m_nTaskCount]=pCallback;
			//���������+1
			m_Info.m_nTaskCount++;
			return true;
		}
	}
public:
	void CopyFrom(SToolsTaskRunInfo* pInfo)
		{
		char* pMyInfo=null; //������Ч�Ŀ���Ŀ�����
		if(m_pInfo) pMyInfo=(char*)m_pInfo;
		else pMyInfo=(char*)&m_Info;
		//�����Ƹ�ʽ����
		memcpy(pMyInfo,(char*)pInfo,SToolsTaskRunInfoSize);
	}
public:
	SToolsTaskRunInfo m_Info; //��Ϊ�������������ʵ�壬��������
	SToolsTaskRunInfo* m_pInfo; //��Ϊճ�����������ָ�룬ָ���ⲿ����

};


class CToolsTaskRun
{ 
public:
	//���캯���ܼ򵥣����Ǳ���ۺϹ�����ָ�뱸�ü��ɡ�
	CToolsTaskRun(CToolsBaseLibrary* pToolsBaseLib){m_pToolsBaseLib=pToolsBaseLib;}
	//��������Ҳ�Ǽ򵥹ر���������
	~CToolsTaskRun(){StopAll();}
public:
	//����һ�����������ж�����أ��������
	bool StartTask(
		_TASKPOOL_CALLBACK pCallback, //����Ƭ�λص�����
		void* pCallParam=null, //�ص���������ָ��
		char* szAppName=null); //Ӧ����������Ϊ�գ�
	//����Info ���������������
	bool StartTask(
		SToolsTaskRunInfo* pInfoStruct, //���������������ݽṹ��
		char* szAppName=null); //Ӧ����������Ϊ�գ�
	bool StartTask(
		CToolsTaskRunInfo* pInfoObject, //������������ָ��
		char* szAppName=null); //Ӧ����������Ϊ�գ�
	//ֹͣ���������˳�ʱ�ã�ע�⣬�������º��˳���ÿ�������ÿ��Ƭ�ζ����õ�ִ��
	void StopAll(void);
	//���ߺ������ж��Ƿ���������
	bool IsRunning(void) {return m_ThreadManager.ThreadContinue();}
	//���ߺ���������߳���������
	int GetThreadCount(void) {return m_ThreadManager.GetThreadCount();}
	//���ߺ�������ӡ�ڲ���Ϣ��Э��debug �����ܹ۲�
	void PrintInfo(void);
private:
	//����ĵ�����ִ�лص���������ʵ����������ص�һ������ص�
	//�����ڲ��߼�ʵ���˴���Ƭ�ε����������ת��
	static bool ToolsTeskRunTaskCallback(void* pCallParam,int& nStatus);
	//����ʹ�����߳̿������򻯲���
	CThreadManager m_ThreadManager;
	//����ľۺϹ�����ָ��
	CToolsBaseLibrary* m_pToolsBaseLib;
};





#endif // __TASK_TOOLS_H__



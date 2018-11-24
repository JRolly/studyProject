////////////////////////////////////////////////////////////
//							任务池
////////////////////////////////////////////////////////////

#ifndef __TASK_TOOLS_H__
#define __TASK_TOOLS_H__

#include "IncludeDef.h"
#include "DebugTools.h"
#include "MemQueue.h"
//#include "LogTools.h"
#include "BaseLib.h"

#define TASK_POOL_TOKEN_MAX (16*1024) //最多同时并发任务数
#define DEFAULT_THREAD_MAX (30) //默认线程数





//任务池回调函数构型
//返回值true 继续运行false 停止运行
typedef bool (*_TASKPOOL_CALLBACK)(void* pCallParam, //代传参数指针
	int& nStatus); //程序控制状态机
//DEMO bool TaskCallback(void* pCallParam, int& nStatus);



//任务池核心数据结构
typedef struct _TASK_POOL_TOKEN_
{
	_TASKPOOL_CALLBACK m_pCallback; //回调函数指针
	void* m_pUserParam; //替用户传递的回调函数参数，可以为null
	int m_nUserStatus; //代替用户传递的一个状态值，初始值默认是0
}STaskPoolToken;
//数据结构长度
const int STaskPoolTokenSize=sizeof(STaskPoolToken);



//任务池类
class CToolsTaskPool
{
public:
	CToolsTaskPool(
		CToolsBaseLibrary* pToolsBaseLib, //依赖的工具聚合类指针
		int nMaxThread=DEFAULT_THREAD_MAX); //最大线程数
	~CToolsTaskPool();
public:
	bool ICanWork(void); //防御性设计，可运行标志
	void PrintInfo(void); //内容打印，Debug 用
public:
	//注册一个新任务，返回TaskID
	bool RegisterATask(_TASKPOOL_CALLBACK pCallback, //回调函数指针
		void* pUserParam=null); //回调函数参数
private:
	//真实的内部注册函数
	bool RegisterATaskDoIt(STaskPoolToken* pToken,int nLimit=-1);
	//服务者线程
	bool TaskServiceThreadDoIt(STaskPoolToken& Task);
	static void TaskServiceThread(void* pCallParam,
		MBOOL& bThreadContinue);
	//管理者线程
	static void TaskCtrlThread(void* pCallParam,
		MBOOL& bThreadContinue);
private:
	CMRSWbool m_bThreadContinue; //任务池自带线程管理变量
	CMRSWint m_nThreadCount; //可以自行退出所属线程
	CToolsMemoryQueueWithLock* m_pTaskQueue; //核心任务队列
	CToolsThreadPool* m_pThreadPool; //线程池指针
private:
	int m_nMaxThread; //最大任务数的保存变量
	CMRSWint m_nThreadID; //任务ID 种子
	CToolsLowDebug* m_pDebug; //debug 对象指针
	CToolsBaseLibrary* m_pToolsBaseLib; //聚合工具类指针
};


#define TOOLS_TASK_RUN_MAX_TASK 16 //最多步动作
typedef struct _TOOLS_TASK_RUN_INFO_
{
	int m_nTaskCount; //总共多少步骤
	void* m_pCallParam; //共用的回调函数参数
	//动作回调函数数组
	_TASKPOOL_CALLBACK m_CallbackArray[TOOLS_TASK_RUN_MAX_TASK];
}SToolsTaskRunInfo;
const ULONG SToolsTaskRunInfoSize=sizeof(SToolsTaskRunInfo);


class CToolsTaskRun;
typedef struct _ToolsTeskRunTaskCallback_Param_
{
	SToolsTaskRunInfo m_Info; //任务描述结构体
	CToolsBaseLibrary* m_pToolsBaseLib; //基本聚合工具类指针
	CToolsTaskRun* m_pThis; //任务运行体对象指针
	int m_nRunIndex; //当前执行的步距
	char m_szAppName[TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE]; //应用名
}SToolsTeskRunTaskCallbackParam;
const ULONG SToolsTeskRunTaskCallbackParamSize= //结构体长度常量
	sizeof(SToolsTeskRunTaskCallbackParam);



class CToolsTaskRunInfo
{
public:
	//这是使用SToolsTeskRunTaskCallbackParam 结构传参，实现粘合的构造函数
	//使用m_pInfo 指针，指针指向SToolsTeskRunTaskCallbackParam 中的m_Info
	CToolsTaskRunInfo(SToolsTeskRunTaskCallbackParam* pParam)
	{
		m_pInfo=&(pParam->m_Info);
		Init(m_pInfo); //初始化
	} 
	//这是直接粘合到外部的一个SToolsTaskRunInfo 结构体实例的重载构造函数
	//使用m_pInfo 指针，指针指向传入的结构体指针
	CToolsTaskRunInfo(SToolsTaskRunInfo* pInfo)
	{
		m_pInfo=pInfo;
		Init(m_pInfo); //初始化
	} 
	//这是以工具类启动，不使用m_pInfo，而使用本类自带的数据区
	CToolsTaskRunInfo()
	{
		m_pInfo=null;
		Init(&m_Info); //初始化
	}
	~CToolsTaskRunInfo(){} //析构函数不摧毁数据
private:
	static void Init(SToolsTaskRunInfo* pInfo) //初始化动作
	{
		pInfo->m_nTaskCount=0; //动作计数器归零
		pInfo->m_pCallParam=null; //参数指针清空
		int i=0;
		for(i=0;i<TOOLS_TASK_RUN_MAX_TASK;i++) //清空16 个回调函数指针
		pInfo->m_CallbackArray[i]=null;
	}
public:
	SToolsTaskRunInfo* GetInfoPoint(void)
	{
		if(m_pInfo) //优先返回m_pInfo
			return m_pInfo;
		else
			return &m_Info; //否则返回m_Info 的地址
	}
public:
	void SetCallbackParam(void* pCallParam)
	{
		if(m_pInfo) //注意先后顺序，优先使用m_pInfo
			m_pInfo->m_pCallParam=pCallParam;
		else
			m_Info.m_pCallParam=pCallParam;
	}	
public:
	//这是添加一个回调函数，连同其参数的方法，调用了下面的单独回调函数添加方法
	bool AddTask(_TASKPOOL_CALLBACK pCallback,void* pCallParam)
	{
		if(pCallParam) SetCallbackParam(pCallParam); //有参数，则设置参数
		return AddTask(pCallback); //调用下一函数，处理回调指针
	}

	bool AddTask(_TASKPOOL_CALLBACK pCallback)
	{
		if(m_pInfo) //优先使用m_pInfo
		{ //检查回调函数总数是否超限，是则返回false，拒绝添加
			if(TOOLS_TASK_RUN_MAX_TASK<=m_pInfo->m_nTaskCount) return false;
			//添加到数组末尾
			m_pInfo->m_CallbackArray[m_pInfo->m_nTaskCount]=pCallback;
			//数组计数器+1
			m_pInfo->m_nTaskCount++;
			return true;
		} 
		else //无	m_pInfo 可用，则使用m_Info
		{ //检查回调函数总数是否超限，是则返回false，拒绝添加
			if(TOOLS_TASK_RUN_MAX_TASK<=m_Info.m_nTaskCount) return false;
			//添加到数组末尾
			m_Info.m_CallbackArray[m_Info.m_nTaskCount]=pCallback;
			//数组计数器+1
			m_Info.m_nTaskCount++;
			return true;
		}
	}
public:
	void CopyFrom(SToolsTaskRunInfo* pInfo)
		{
		char* pMyInfo=null; //查找有效的拷贝目标对象
		if(m_pInfo) pMyInfo=(char*)m_pInfo;
		else pMyInfo=(char*)&m_Info;
		//二进制格式拷贝
		memcpy(pMyInfo,(char*)pInfo,SToolsTaskRunInfoSize);
	}
public:
	SToolsTaskRunInfo m_Info; //作为工具类的数据区实体，保存数据
	SToolsTaskRunInfo* m_pInfo; //作为粘合类的数据区指针，指向外部数据

};


class CToolsTaskRun
{ 
public:
	//构造函数很简单，就是保存聚合工具类指针备用即可。
	CToolsTaskRun(CToolsBaseLibrary* pToolsBaseLib){m_pToolsBaseLib=pToolsBaseLib;}
	//析构函数也是简单关闭所有任务。
	~CToolsTaskRun(){StopAll();}
public:
	//启动一个任务，这里有多个重载，方便调用
	bool StartTask(
		_TASKPOOL_CALLBACK pCallback, //任务片段回调函数
		void* pCallParam=null, //回调函数参数指针
		char* szAppName=null); //应用名（可以为空）
	//利用Info 描述启动多次任务
	bool StartTask(
		SToolsTaskRunInfo* pInfoStruct, //任务描述核心数据结构体
		char* szAppName=null); //应用名（可以为空）
	bool StartTask(
		CToolsTaskRunInfo* pInfoObject, //任务描述对象指针
		char* szAppName=null); //应用名（可以为空）
	//停止所有任务，退出时用，注意，这里是温和退出，每个任务的每个片段都将得到执行
	void StopAll(void);
	//工具函数，判断是否在运行中
	bool IsRunning(void) {return m_ThreadManager.ThreadContinue();}
	//工具函数，获得线程总数计数
	int GetThreadCount(void) {return m_ThreadManager.GetThreadCount();}
	//工具函数，打印内部信息，协助debug 或性能观测
	void PrintInfo(void);
private:
	//最核心的任务执行回调函数，这实际上是任务池的一个任务回调
	//但其内部逻辑实现了代码片段到完整任务的转换
	static bool ToolsTeskRunTaskCallback(void* pCallParam,int& nStatus);
	//这里使用了线程控制锁简化操作
	CThreadManager m_ThreadManager;
	//保存的聚合工具类指针
	CToolsBaseLibrary* m_pToolsBaseLib;
};





#endif // __TASK_TOOLS_H__



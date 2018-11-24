#include "TaskTools.h"



//将一根指针注册到内存池，内存池默认在聚合工具类中
#define TOOLS_REGISTER(pPoint,szInfo) \
	m_pToolsBaseLib->m_pMemPool->Register(pPoint,szInfo)
//将一根指针从内存池反注册，内存池默认在聚合工具类中
#define TOOLS_UNREGISTER(pPoint) \
	m_pToolsBaseLib->m_pMemPool->UnRegister(pPoint)
//将一根对象指针先执行反注册，再摧毁，最后置空
#define TOOLS_DEL_OBJ(p) \
	if(p){TOOLS_UNREGISTER(p);delete p;p=null;}




CToolsTaskPool::CToolsTaskPool(CToolsBaseLibrary* pToolsBaseLib,
	int nMaxThread)
{
	m_pToolsBaseLib=pToolsBaseLib; //保存聚合工具类指针
	m_pDebug=m_pToolsBaseLib->m_pDebug; //从聚合工具类中获得debug 对象指针，
	//方便后续使用
	m_nMaxThread=nMaxThread; //保存最大线程数
	pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool(): Start!\n"); //打印启动信息
	m_bThreadContinue.Set(true); //线程管理变量初始化
	m_nThreadCount.Set(0);
	m_nThreadID.Set(0); //任务ID 种子赋初值0
	//实例化任务队列
	m_pTaskQueue=new CToolsMemoryQueueWithLock(
		m_pToolsBaseLib->m_pDebug, //传入debug 对象指针
		m_pToolsBaseLib->m_pMemPool, //传入内存池指针
		"ToolsTaskPool"); //应用名
	if(m_pTaskQueue)
	{ //注册到内存池进行管理，预防退出时忘了释放
		TOOLS_REGISTER(m_pTaskQueue,"CToolsTaskPool::m_pTaskQueue");
	}
	//实例化线程池
	m_pThreadPool=new CToolsThreadPool(m_pToolsBaseLib->m_pDebug);
	if(m_pThreadPool)
	{ //注册到内存池进行管理
		TOOLS_REGISTER(m_pThreadPool,"CToolsTaskPool::m_pThreadPool");
	} 
	if(ICanWork()) //判断前面的new 动作是否完成
	{ //启动管理线程
		if(!m_pThreadPool->ThreadPoolRegTask(TaskCtrlThread,this))
		{ //这是日志输出，后面章节有详细介绍
			m_pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool:: start ctrl thread %d fail!\n");
		} 
		else
			m_nThreadCount.Add(); //如果注册成功，线程计数器+1
	}
}


CToolsTaskPool::~CToolsTaskPool()
{
	//以标准方式退出本对象所属所有线程
	m_bThreadContinue.Set(false);
	while(m_nThreadCount.Get()){Sleep(100);}
	TOOLS_DEL_OBJ(m_pThreadPool); //删除对象的宏
	TOOLS_DEL_OBJ(m_pTaskQueue);
	m_pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool(): Stop!\n"); //打印退出信息
}


bool CToolsTaskPool::ICanWork(void)
{ //主要检查任务队列和线程池对象是否初始化
	if(!m_pThreadPool) return false;
	if(!m_pTaskQueue) return false;
	return true;
}
void CToolsTaskPool::PrintInfo(void)
{ //打印当前线程数和任务书，方便程序员观察
	TOOLS_PRINTF("task pool: thread count=%d, task in queue=%d\n",
		m_nThreadCount.Get(),m_pTaskQueue->GetTokenCount());
}

void CToolsTaskPool::TaskCtrlThread(
	void* pCallParam, //这是主程序传进来的参数指针
	MBOOL& bThreadContinue) //如果系统要退出,线程池会修改这个参数的值为false
{
	CToolsTaskPool* pThis=(CToolsTaskPool*)pCallParam;
	int i=0;
	for(i=0;i<pThis->m_nMaxThread;i++) //根据最大线程数，循环启动服务线程
	{
		if(!pThis->m_pThreadPool->ThreadPoolRegTask(
			TaskServiceThread,pThis))
		{ //启动失败，打印报警信息，退出启动
			pThis->m_pToolsBaseLib->m_pLog->_XGSyslog("CToolsTaskPool:: start service thread %d fail!\n",i);
			break;
		} 
		else
			pThis->m_nThreadCount.Add(); //启动成功，线程数+1
	} 
	pThis->m_nThreadCount.Dec(); //任务完成，自己退出，因此线程计数器-1
}


//传入任务数据结构STaskPoolToken 指针，
//根据任务回调情况，返回真或者假，返回假，表示该任务已经结束
bool CToolsTaskPool::TaskServiceThreadDoIt(STaskPoolToken& Task)
{
	bool bCallbackRet= //执行回调函数，并获得返回值
		Task.m_pCallback(Task.m_pUserParam,Task.m_nUserStatus);
	if(!bCallbackRet) return bCallbackRet; //如果返回值为假，直接返回，表示任务结束
	//如果任务返回真，表示任务尚未结束，需要重新推回任务队列，等待下次运行
	bCallbackRet=RegisterATaskDoIt(&Task); //试图重新注册到任务队列
	if(!bCallbackRet) //如果注册失败，报警，表示任务丢失
	{
		TOOLS_DEBUG("CToolsTaskPool::TaskServiceThreadDoIt(): a task need \
			continue, but add 2 queue fail! task lost!\n");
		dbg_bin((char*)&Task,STaskPoolTokenSize);// TOOLS_DEBUG_BIN((char*)&Task,STaskPoolTokenSize);	?????这里怎么实现的
	} 
	return bCallbackRet; //返回最后结果
}

void CToolsTaskPool::TaskServiceThread(
	void* pCallParam, //这是主程序传进来的参数指针
	MBOOL& bThreadContinue) //如果系统要退出,线程池会修改这个参数的值为false
{
	int nQueueRet=0;
	STaskPoolToken Task;
	char* szTask=(char*)&Task;
	//获得本对象指针
	CToolsTaskPool* pThis=(CToolsTaskPool*)pCallParam;
	int nID=pThis->m_nThreadID.Add()-1;
	//这是打印本服务线程启动信号，通常注释掉不用，调试时可能使用。
	//pThis->XGSyslog("CToolsTaskPool::TaskServiceThread(): %d Start!\n",nID);
		while(MvarGet(bThreadContinue)) //注意本循环，标准的线程池线程守候循环
		{ //额外增加的判断，以便判断本任务池退出标志
			if(!pThis->m_bThreadContinue.Get())
				goto CToolsTaskPool_TaskServiceThread_End_Process;
			//尝试从任务队列中弹出第一个任务，并执行
			nQueueRet=pThis->m_pTaskQueue->GetAndDeleteFirst(
				szTask,STaskPoolTokenSize);
			if(STaskPoolTokenSize==nQueueRet) //如果弹出成功，表示有任务
			{
				pThis->TaskServiceThreadDoIt(Task); //调用上一函数执行
			} 
			Sleep(MIN_SLEEP); //习惯性睡
		}
CToolsTaskPool_TaskServiceThread_End_Process:
		pThis->m_nThreadCount.Dec(); //退出时，线程计数器-1
		//这是打印本服务线程停止信号，通常注释掉不用，调试时可能使用。
		//pThis->XGSyslog("CToolsTaskPool::TaskServiceThread(): %d Stop!\n",nID);
}

bool CToolsTaskPool::RegisterATaskDoIt(STaskPoolToken* pToken,int nLimit)
{
	bool bRet=false;
	if(STaskPoolTokenSize==m_pTaskQueue->AddLast( //一次典型的队列AddLast 行为
		(char*)pToken,STaskPoolTokenSize),nLimit)
		bRet=true;
	return bRet;
}

bool CToolsTaskPool::RegisterATask(
	_TASKPOOL_CALLBACK pCallback, //传入回调函数指针
	void* pUserParam) //传入参数指针
{
	STaskPoolToken Token; //准备一个结构体实例
	if(!ICanWork()) return false;
	if(!pCallback) return false;
	Token.m_pCallback=pCallback; //填充结构体
	Token.m_pUserParam=pUserParam;
	Token.m_nUserStatus=0; //注意此处，状态机置为0
	return RegisterATaskDoIt(&Token,m_nMaxThread); //调用上面的函数，完成注册
}






//本重载主要应对那些单任务片段的任务，即只有一个回调函数的任务，可以直接注入启动。
bool CToolsTaskRun::StartTask(_TASKPOOL_CALLBACK pCallback, void* pCallParam, char* szAppName)
{ //先实例化一个任务描述对象，调用下面的函数完成注册任务
	CToolsTaskRunInfo InfoObj;
	InfoObj.AddTask(pCallback,pCallParam); //直接将任务数据添加到任务描述
	return StartTask(&InfoObj,szAppName);
} 
//本重载主要应对使用任务描述对象，并完成了任务描述的应用，注入启动任务
bool CToolsTaskRun::StartTask(CToolsTaskRunInfo* pInfoObject, char* szAppName)
{
	return StartTask(pInfoObject->GetInfoPoint(),szAppName);
}

//本函数利用任务描述对象内部的数据结构体，完成最终的任务启动工作
//请注意，本函数使用了远堆传参，来启动任务。远堆传参的参数，就是前文所述的结构体
//SToolsTeskRunTaskCallbackParam
bool CToolsTaskRun::StartTask(SToolsTaskRunInfo* pInfoStruct, char* szAppName)
{
	bool bRet=false; //准备返回值
	if(!m_ThreadManager.ThreadContinue()) //如果本对象未启动，则启动
		m_ThreadManager.Open();
	//请注意这里，开始准备远堆传参的参数结构体数据区，使用了内存池动态申请。
	//内存池的指针是从聚合工具类中获得的。
	SToolsTeskRunTaskCallbackParam* pParam=(SToolsTeskRunTaskCallbackParam*)
		m_pToolsBaseLib->m_pMemPool->Malloc(SToolsTeskRunTaskCallbackParamSize,"CToolsTaskRun::pParam");
	if(pParam) //内存申请成功，继续执行，否则返回假
	{
		pParam->m_pToolsBaseLib=m_pToolsBaseLib; //聚合工具类指针
		pParam->m_pThis=this; //本对象指针
		pParam->m_nRunIndex=0; //状态机归0
		if(szAppName) //如果外部提供了应用名
			SafeStrcpy(pParam->m_szAppName, //拷贝应用名
				szAppName,
				TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
		else //否则清空应用名
			TOOLS_CLEAN_CHAR_BUFFER(pParam->m_szAppName);
		//注意，这里使用了任务描述的粘合类特性，粘合到参数区的任务描述数据结构上
		CToolsTaskRunInfo InfoObj(&(pParam->m_Info));
		//目的是调用CopyFrom 来拷贝外部传入的任务参数
		InfoObj.CopyFrom(pInfoStruct);
		//调用聚合工具类中的任务池对象，注册任务
		//注意，注册是是本类提供的标准任务执行体，该任务会解析任务描述
		//提供二次执行，真正执行应用层的任务调用。
		bRet=m_pToolsBaseLib->m_pTaskPool->RegisterATask(
			ToolsTeskRunTaskCallback, //这是本对象的任务
			pParam); //应用层注册的任务在这里
		//会被二次解析执行
		if(bRet)
		{
			m_ThreadManager.AddAThread(); //如果成功，线程计数器+1
			if(szAppName) //如果有应用名，打印提示
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
	m_ThreadManager.GetThreadCount()); //打印线程总数
}

bool CToolsTaskRun::ToolsTeskRunTaskCallback(void* pCallParam,int& nStatus)
{
	bool bCallbackRet=false; //记录用户任务片段的调用结果
	bool bGotoNextStatus=true; //跳到下一状态的标志
	SToolsTeskRunTaskCallbackParam* pParam= //强制指针类型转换，获得参数指针
		(SToolsTeskRunTaskCallbackParam*)pCallParam;
	if(!pParam) return false; //防御性设计，如果没有参数，终止
	CToolsTaskRun* pThis=pParam->m_pThis; //方便调用，获得本类指针pThis
	switch(nStatus) //这个状态机是任务池提供的
	{
	case 0: 
		///这是本函数的主执行代码
		if(pParam->m_Info.m_nTaskCount > pParam->m_nRunIndex)
		{ //只要应用层任务片段没有被轮询完毕，一直在本片段执行
			bGotoNextStatus=false; //这个=false，就是不希望跳转
			//这里的回调请仔细看
			bCallbackRet= //取得应用层片段的回调结果
			//根据应用层状态机pParam->m_nRunIndex，调用合适的片段
			pParam->m_Info.m_CallbackArray[pParam->m_nRunIndex](
				pParam->m_Info.m_pCallParam,//这是透传的参数指针
				pParam->m_nRunIndex); //这里最关键，大家注意此处没有把
									  //线程池状态机nStatus 传入应用层
									  //代码模块，而是使用自己的状态机
									  //这种“欺骗”，是透明设计的关键
									  //根据任务池的定义，如果应用程序代码片段返回false，表示其希望跳到下一片段
									  //因此，这里做应用程序状态机的+1 动作
			if(!bCallbackRet) pParam->m_nRunIndex++;			
			//注意这个设计，这是非常关键的一步。当StopAll 被调用，本对象即将退出时
			//本函数检测到这个结果，并不是简单把nStatus+1 做退出
			//而是开始步进应用任务片段，即把应用程序的状态机pParam->m_nRunIndex 累加
			//这是强制执行完应用任务片段序列的每一步。
			//最终，本任务会因为应用任务执行完毕而关闭，而不是在此因为系统退出关闭
			//这样保证不至于产生资源泄漏等情况。
			if(!pThis->m_ThreadManager.ThreadContinue())
				pParam->m_nRunIndex++;
		} 
		//如果应用程序片段已经执行完毕，则本函数状态机+1，跳转到下一片段结束任务
		else bGotoNextStatus=true;
		break;
	default: //exit
		//如果有应用名，打印退出提示
		if(0<strlen(pParam->m_szAppName))
			pThis->m_pToolsBaseLib->m_pLog->_XGSyslog("%s Stop!\n",pParam->m_szAppName);
		pThis->m_ThreadManager.DecAThread(); //线程计数器-1
		pThis->m_pToolsBaseLib->m_pMemPool->Free(pParam); //释放参数结构体
		return false; //返回假，结束任务
	}
	if(bGotoNextStatus) nStatus++; //根据前文判断，调整本函数状态
	return true; //返回真，不退出任务
}






























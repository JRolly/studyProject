#include "ThreadTools.h"


CToolsThreadPool::CToolsThreadPool(CToolsLowDebug* pDebug)
{
	m_pDebug=pDebug; //保存Debug 对象指针
	TOOLS_DEBUG("CToolsThreadPool Start!\n"); //显示开启信息
	THREAD_ID id; //注意，开启管理者线程的参变量
	THREAD t; //函数内变量，表示不保存
	//注意，这里面没有使用锁对象，而使用纯C 的锁结构体完成。
	MUTEXINIT(&m_RegisterLock); //初始化线程池总的锁对象
	MvarInit(m_bThreadContinue,true); //初始化bThreadContinue 变量
	MvarInit(m_nThreadPoolThreadCount,0); //初始化nThreadCount 变量
	MvarInit(m_nThreadPoolIdleThreadCount,0); //初始化空闲线程统计变量
	//初始化数组
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++)
	{
		//虽然管理者线程没有保存线程句柄，但考虑到应用线程以后潜在的需求，
		//在线程的任务结构体中，还是保留了线程句柄和线程ID
		m_TToken[i].m_hThread=0;
		m_TToken[i].m_nThreadID=0;
		//这主要是为了调试方便，为每条服务线程设置一个显式的退出码，Windows 下，
		//线程返回可以看到这个值
		m_TToken[i].m_nExitCode=THREAD_POOL_EXIT_CODE+i;
		//任务描述，回调函数指针和透传参数指针，注意，null 表示当前无任务，
		//服务线程即使启动，也是在Idle 下空转。
		m_TToken[i].m_pCallback=null;
		m_TToken[i].m_pCallParam=null;
		//这是一个很重要的描述，线程池自己的指针，原因后述。
		m_TToken[i].m_pThreadPoolObject=this;
		//初始化线程任务单元状态变量，注意，多线程安全的变量，C 模式
		MvarInit(m_TToken[i].m_nState,TPOOL_THREAD_STATE_NOT_RUN);
	} 
	id=0; //开启管理者线程t=0;
	THREAD_CREATE(ThreadPoolCtrlThread,this,t,id);//注意，管理者线程的参数是this
	Sleep(OPEN_THREAD_DELAY); //强制等待管理者线程开启
}

CToolsThreadPool::~CToolsThreadPool()
{
	//关闭线程，这个段落比较经典，前文已多次出现，此处不再赘述
	MvarSet(m_bThreadContinue,false);
	while(MvarGet(m_nThreadPoolThreadCount))
	{
		Sleep(MIN_SLEEP);
	}//等待关闭所有线程
	//摧毁所有线程参数模块的状态变量
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++)
	{
		MvarDestroy(m_TToken[i].m_nState); //只有这一个需要摧毁
	} 
	MvarDestroy(m_bThreadContinue); //摧毁各线程安全变量
	MvarDestroy(m_nThreadPoolThreadCount);
	MvarDestroy(m_nThreadPoolIdleThreadCount);
	MUTEXDESTROY(&m_RegisterLock); //摧毁基本锁
	TOOLS_DEBUG("CToolsThreadPool Stop!\n"); //显示退出信息
}

//寻找一个没有使用的Token
//找到,返回编号
//没有找到(全部用满了),返回-1
int CToolsThreadPool::Search4NotUseToken(void)
{
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++) //遍历整个数组查找
	{
		if(TPOOL_THREAD_STATE_NOT_RUN==MvarGet(m_TToken[i].m_nState))
			return i; //找到，返回index
	} 
	return -1; //找不到，返回-1
}

//管理者线程，注意：这里的函数声明是跨平台的线程函数定义，使用宏完成
THREAD_FUNC_DECL(CToolsThreadPool::ThreadPoolCtrlThread,pParam)
{
	CToolsThreadPool* pThis=(CToolsThreadPool*)pParam; //老习惯，获得this 指针
	//注意，此处增加线程计数器，一般说来，线程池的使用者总是长期使用
	//即管理者线程总有实例化运行的机会，因此，线程计数器在其中+1，而不是放在构造函数
	MvarADD(pThis->m_nThreadPoolThreadCount);
	int nIdleThread=0; //空闲线程计数
	int nNotRunThread=0; //未运行线程计数
	//请注意这个死循环，参考bThreadContinue
	while(MvarGet(pThis->m_bThreadContinue))
	{
		//获得当前空闲的线程数
		nIdleThread=MvarGet(pThis->m_nThreadPoolIdleThreadCount);
		if(WHILE_THREAD_COUNT>nIdleThread)
		{
			//如果备用的空闲线程不够10,需要添加，则启动新服务线程
			//启动前，需要先找到空闲的任务块，找不到，也不启动。
			nNotRunThread=pThis->Search4NotUseToken();
			if(-1!=nNotRunThread)
			{
				//启动线程
				THREAD_CREATE(ThreadPoolThread, //服务者线程名
					//注意，此处把任务数据块指针作为参数传给服务者线程，
					//因此，每个服务者线程，仅能维护一个任务数据块
					&(pThis->m_TToken[nNotRunThread]),
					//注意，此处保存了服务者线程的句柄和ID
					pThis->m_TToken[nNotRunThread].m_hThread,
					pThis->m_TToken[nNotRunThread].m_nThreadID);
				//如果没有启动起来,下轮再说，此处不再报错
			}
		} 
		Sleep(OPEN_THREAD_DELAY); //一定要等够 250ms
	} 
	MvarDEC(pThis->m_nThreadPoolThreadCount); //退出时，线程计数器-1
#ifdef WIN32 //按照Linux 和Windows 两种方式退出
		return THREAD_POOL_EXIT_CODE-1;
#else // not WIN32
		return null;
#endif
}

//服务线程
THREAD_FUNC_DECL(CToolsThreadPool::ThreadPoolThread,pParam)
{
	//由于历史原因，此处有一点歧义，此处的pThis 不是线程池对象指针
	//而是任务块的指针，由于线程池开发较早，出于“尊重”原则，此处没有做更动。
	//线程池对象指针，此处表示为：pThis->m_pThreadPoolObject
	SThreadToken* pThis=(SThreadToken*)pParam;
	//刚启动，设置为Idle 状态
	MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_IDLE);
	//线程计数器+1
	MvarADD(pThis->m_pThreadPoolObject->m_nThreadPoolThreadCount);
	//Idle 线程计数器+1
	MvarADD(pThis->m_pThreadPoolObject->m_nThreadPoolIdleThreadCount);
	//注意这个守候循环，检索了bThreadContinue 参量，以便配合最终的退出动作
	while(MvarGet(pThis->m_pThreadPoolObject->m_bThreadContinue))
	{
		//取任务
		switch(MvarGet(pThis->m_nState))
		{
		case TPOOL_THREAD_STATE_NOT_RUN:
		//这个状态表示没有线程为任务块服务，但现在本线程已经启动
		//如果仍然看到这个状态,肯定出错了，表示外部程序状态设置不对
		//但这个错误不严重,自动进那个修补一下就OK
		//修补的方法就是设置为Idle 状态
		MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_IDLE);
		//注意此处没有break
		case TPOOL_THREAD_STATE_IDLE: //没有命令
		default:
			//这是正常睡眠
			break;
		case TPOOL_THREAD_STATE_BUSY: //Register 下任务了
			//请注意一个细节，这里没有把Idle 计数器-1，
			//这是因为Register 函数做了这个动作，后文有详细描述
			if(pThis->m_pCallback) //检查是不是真的有任务
			{
				//将执行权交给新的任务（一次），请注意参数传递
				pThis->m_pCallback(pThis->m_pCallParam,
					pThis->m_pThreadPoolObject->m_bThreadContinue);
				//空闲线程数+1
				MvarADD(pThis->m_pThreadPoolObject-> //----a
					m_nThreadPoolIdleThreadCount);
			} 
			break;
		};
		//检查空闲线程总数
		if(WHILE_THREAD_COUNT< //----b
			MvarGet(pThis->m_pThreadPoolObject->m_nThreadPoolIdleThreadCount))
			break; //如果备用线程超出限额,则跳出死循环，退出自己
		//所有工作做完，把自己置为Idle 状态
		if(TPOOL_THREAD_STATE_IDLE!=MvarGet(pThis->m_nState)) //----c
			MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_IDLE);
		Sleep(DEFAULT_THREAD_SLEEP); //睡眠，等待下次任务
	}
	//退出流程
	//Idle 计数器-1
	MvarDEC(pThis->m_pThreadPoolObject->m_nThreadPoolIdleThreadCount); //----d
	//线程总计数器-1
	MvarDEC(pThis->m_pThreadPoolObject->m_nThreadPoolThreadCount);
	//把任务区块的状态设置为正确的值（没有线程为其服务）
	MvarSet(pThis->m_nState,TPOOL_THREAD_STATE_NOT_RUN);
#ifdef WIN32 //两种方式退出
	return pThis->m_nExitCode;
#else // not WIN32
	return null;
#endif
}

//获得一个空闲的线程编号
//如果无空闲,则返回-1
int CToolsThreadPool::GetAIdleThread(void)
{
	int nRet=-1;
	int i;
	for(i=0;i<THIS_POOLTHREAD_MAX;i++) //遍历检索
	{ //注意，仅仅检索Idle 一个状态
		if(TPOOL_THREAD_STATE_IDLE==MvarGet(m_TToken[i].m_nState))
		{
			nRet=i;
			break; //找到跳出
		}
	} 
	return nRet; //没找到，可能返回-1
}

//注册一个新任务
//请注意,这里有临界区保护,线程安全
//注册成功,返回_THREADPOOL_OK，否则返回其他错误码
int CToolsThreadPool::ThreadPoolRegisterANewThread(
	_TPOOL_CALLBACK pCallback, //任务回调函数指针
	void* pParam) //透传的任务参数指针
{
	int nRet=_THREADPOOL_PLEASE_WAIT; //返回值设置初值
	MUTEXLOCK(&m_RegisterLock); //加锁
	int nIdleThread=GetAIdleThread(); //取得Idle 的线程编号
	if(0>nIdleThread)
	{ //没有找到Idle 服务线程
		if(THIS_POOLTHREAD_MAX==MvarGet(m_nThreadPoolThreadCount))
		{
			//没有空闲线程,而线程总数已经达到上限,返回OverFlow 标志
			nRet=_THREADPOOL_OVERFLOW;
		} 
		else
		{
			//没有空闲线程,仅仅是还没有来得及开启,请调用者等待
			nRet=_THREADPOOL_PLEASE_WAIT;
		}
	} 
	else
	{
		//找到空闲线程,添加任务
		m_TToken[nIdleThread].m_pCallback=pCallback; //这里可以看出如何将
		m_TToken[nIdleThread].m_pCallParam=pParam; //任务添加到任务区块
		MvarSet(m_TToken[nIdleThread].m_nState, //注意，本任务块被设置为
			TPOOL_THREAD_STATE_BUSY); //busy，因此，不会被再次
		//添加新的任务
		MvarDEC(m_nThreadPoolIdleThreadCount); //前文所述，Idle 计数器-1
		nRet=_THREADPOOL_OK; //返回成功标志
	} 
	MUTEXUNLOCK(&m_RegisterLock); //解锁
	return nRet;
}

//一定要注册成功,可以等待新的Idle 线程被管理者线程启动，除非遇到OverFlow，否则循环等待
int CToolsThreadPool::ThreadPoolRegisterANewThreadWhile(
	_TPOOL_CALLBACK pCallback, //任务回调函数指针
	void* pParam) //透传的任务参数指针
{
	int nRet;
	while(1) //死循环等待
	{ //调用上一函数，开始注册
		nRet=ThreadPoolRegisterANewThread(pCallback,pParam);
		//注册成功，或者线程池溢出，都返回
		if(_THREADPOOL_PLEASE_WAIT!=nRet) break;
		Sleep(OPEN_THREAD_DELAY); //最多等一会,新的线程就已经建立了
	} 
	return nRet;
}

int CToolsThreadPool::ThreadPoolRegTask(
	_TPOOL_CALLBACK pCallback, //任务回调函数指针
	void* pParam, //透传的任务参数指针
	bool bWait4Success) //是否需要等待注册成功
{
	if(bWait4Success) //根据标志，调用不同的函数
		return ThreadPoolRegisterANewThreadWhile(pCallback,pParam);
	else
		return ThreadPoolRegisterANewThread(pCallback,pParam);
}










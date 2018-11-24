////////////////////////////////////////////////////////////
//							线程池
////////////////////////////////////////////////////////////


#ifndef __THREAD_TOOLS_H__
#define __THREAD_TOOLS_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "LockTools.h"


#define OPEN_THREAD_DELAY 250 //新开线程的延迟ms 数,Windows 和Linux 系统,
//开线程太快的话,会出现死线程
//必须有一个延迟,经验参数建议>200ms
#define WHILE_THREAD_COUNT 10 //最多n 条线程空闲等待任务（经验参数：10）
//这不是硬性的,如果有线程已经IDLE,
//可能会比这个多,但随后会动态调整
#define DEFAULT_THREAD_SLEEP 500 //通常建议的线程睡眠参数
#define THREAD_POOL_EXIT_CODE 10000 //线程池的线程,从开始设置退出码

//总线程数上限
#ifdef _ARM_ //ARM 嵌入式系统
	#define THIS_POOLTHREAD_MAX 30 //嵌入式系统下最大30 条线程
#else //PC 机
	#ifdef WIN32
		#define THIS_POOLTHREAD_MAX 2000 //Windows 下最大2000 条线程
	#else // not WIN32
		#define THIS_POOLTHREAD_MAX 300 //Linux 下最大300 条线程
	#endif //WIN32
#endif

#define TPOOL_THREAD_STATE_NOT_RUN 0 //线程池线程状态,线程未运行
#define TPOOL_THREAD_STATE_IDLE 1 //线程池线程状态,线程运行,空闲
#define TPOOL_THREAD_STATE_BUSY 2 //线程池线程状态,线程运行,有任务

#define _THREADPOOL_CAN_NOT_USE -2 //线程池未初始化，无法工作
#define _THREADPOOL_OVERFLOW -1 //线程池溢出标志,无法注册
#define _THREADPOOL_PLEASE_WAIT 0 //线程池目前没有备用线程,请等待
#define _THREADPOOL_OK 1 //线程池注册成功



#ifdef WIN32 //Windows 下定义
	#include <process.h>
	//线程句柄类型
	#define THREAD HANDLE
	//线程ID 类型
	#define THREAD_ID unsigned
	//线程启动函数统一构型，注意函数型宏的使用
	#define THREAD_CREATE(func, args, thread, id) \
		thread = (HANDLE)_beginthreadex(NULL, 0, func, (PVOID)args, 0, &id);
	//线程启动失败后返回错误码定义
	#define THREAD_CREATE_ERROR NULL
	//线程函数标准构型
	#define THREAD_FUNC_DECL(func,args) unsigned __stdcall func(PVOID args)
	//工程中通常需要检测本次开机以来的毫秒数，Windows 和Linux 不一样，此处予以统一。
	#define _GetTimeOfDay GetTickCount
	//Windows 下最小睡眠精度，经实测为10ms
	#define MIN_SLEEP 10
#else //Linux 下定义
	//线程句柄类型
	#define THREAD pthread_t
	//线程ID 类型
	#define THREAD_ID unsigned //unused for Posix Threads
	//线程启动函数统一构型，注意函数型宏的使用
	#define THREAD_CREATE(func, args, thread, id) \
		pthread_create(&thread, NULL, func, args);
	//线程启动失败后返回错误码定义
	#define THREAD_CREATE_ERROR -1
	//线程函数标准构型
	#define THREAD_FUNC_DECL(func,args) void * func(void *args)
	//#define Sleep(ms) usleep((__useconds_t)(ms*1000))
	//工程中通常需要检测本次开机以来的毫秒数，Windows 和Linux 不一样，此处予以统一。
	unsigned long GetTickCount(void);
	#include <sys/time.h>
	#define _GetTimeOfDay GetTickCount
	//Linux 下没有Sleep 函数，为了便于统一编程，仿照Windows 下定义该函数
	#define Sleep(ms) usleep(ms*1000)
	#define MIN_SLEEP 1
#endif


#ifdef WIN32 //Windows 下定义
	//Windows 下有此函数，无需重复定义
#else //Linux 下定义
	//获得本次开机以来毫秒数
	inline unsigned long GetTickCount(void)
	{
		unsigned long lRet=0;
		struct timeval tv;
		gettimeofday(&tv,null);
		lRet=tv.tv_usec/1000;
		return lRet;
	} 
#endif



//线程池回调函数指针
//每个回调函数有一次运行权
//运行结束,线程并不退出,进入IDLE 状态
typedef void (*_TPOOL_CALLBACK)(
	void* pCallParam, //这是主程序传进来的参数指针
	MBOOL& bThreadContinue); //如果系统要退出,线程池会修改这个参数的值为false
//DEMO: static void ThreadPoolCallback(void* pCallParam,MBOOL& bThreadContinue);


class CToolsThreadPool;

typedef struct _THREAD_TOKEN_
{
	int m_nExitCode; //返回值,也是本线程在整个线程池的编号
	MINT m_nState; //线程状态机
	THREAD m_hThread; //线程句柄
	THREAD_ID m_nThreadID; //线程ID
	_TPOOL_CALLBACK m_pCallback; //回调函数
	void* m_pCallParam; //回调函数参数
	CToolsThreadPool* m_pThreadPoolObject; //指向线程池对象的指针
}SThreadToken; //定义的变量类型
const unsigned long SThreadTokenSize=sizeof(SThreadToken); //结构体长度常量


//线程池类
class CToolsThreadPool
{ 
public:
	CToolsThreadPool(CToolsLowDebug* pDebug); //需要传入Debug 对象指针
	~CToolsThreadPool();
public:
	//注册一个新线程，返回状态值，状态值后文有叙述
	int ThreadPoolRegTask(
		_TPOOL_CALLBACK pCallback, //回调函数指针
		void* pParam, //代传的参数指针
		bool bWait4Success=TRUE); //是否等待注册成功才返回
	bool TPAllThreadIsIdle(void); //检查所有线程是否空闲
	bool ThreadPoolIsContinue(void); //检查线程池运行状态
private:
	//这里是真实的操作系统线程函数，其构型后文叙述
	static THREAD_FUNC_DECL(ThreadPoolThread,pParam); //线程池服务线程
	static THREAD_FUNC_DECL(ThreadPoolCtrlThread,pParam);//线程池管理线程
private:
	//内部函数，检索没有使用的Token
	int Search4NotUseToken(void);
	//内部函数，获得一个空闲线程
	int GetAIdleThread(void);
	//这是完成具体注册动作的内部函数，后文详细叙述
	int ThreadPoolRegisterANewThread(
		_TPOOL_CALLBACK pCallback,
		void* pParam);
	int ThreadPoolRegisterANewThreadWhile(
		_TPOOL_CALLBACK pCallback,
		void* pParam);
private:
	SThreadToken m_TToken[THIS_POOLTHREAD_MAX]; //线程池任务参数静态数组
	//这两个参数就是线程池安全退出控制参数，int 型的计数器+bool 型的线程持续标志
	MBOOL m_bThreadContinue; //所有Thread 继续标志
	MINT m_nThreadPoolThreadCount; //Thread 计数器
	//统计变量
	MINT m_nThreadPoolIdleThreadCount; //空闲的线程数量
	//线程池没有使用前述的C++锁类，而是直接使用C 的纯锁结构体完成
	MUTEX m_RegisterLock; //线程注册临界区
	CToolsLowDebug* m_pDebug; //Debug 对象指针
};








#endif	// __THREAD_TOOLS_H__
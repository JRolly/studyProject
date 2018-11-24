
////////////////////////////////////////////////////////////
//							聚合工具
////////////////////////////////////////////////////////////

#ifndef _BASE_LIB_H__
#define _BASE_LIB_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "LogTools.h"
#include "MemoryTools.h"
#include "ThreadTools.h"
//#include "TaskTools.h"

#define MAIN_LOOP_DELAY 2 //2 秒一次main loop
#define TOOLS_APP_LOG_PATH_NAME_SIZE 256
#define TOOLS_APP_TEMP_PATH_NAME_SIZE 256

#define DEFAULT_THREAD_MAX 30

typedef void(*_BASE_LIBRARY_PRINT_INFO_CALLBACK)(void* pCallParam);
//static void BaseLibraryPrintInfoCallback(void* pCallParam);

//typedef void(*_APP_INFO_OUT_CALLBACK)(char* szInfo, void* pCallParam);
//static void ApplicationInfomationOutCallback(char* szInfo,void* pCallParam);

class CToolsTaskPool;
class CToolsTaskRun;
class TOOLSLIB_API CToolsBaseLibrary
{
public:
	CToolsBaseLibrary(char* szAppName, //应用名
		char* szLogPath, //日志路径
		char* szTempPath, //临时文件路径
		int nTaskPoolThreadMax = DEFAULT_THREAD_MAX, //任务池最大线程数
		bool bDebug2TTYFlag = true, //Debug 输出到屏幕开关
		_BASE_LIBRARY_PRINT_INFO_CALLBACK pPrintInfoCallback = null, //info 屏幕输出回调指针
		void* pPrintInfoCallbackParam = null, //info 回调参数指针
		_APP_INFO_OUT_CALLBACK pInfoOutCallback = null, //应用程序输出回调
		void* pInfoOutCallbackParam = null); //应用程序输出回调参数指针
	~CToolsBaseLibrary(); //析构函数
public:
	//应用名的备份保存
	char m_szAppName[TOOLS_APPLICATION_NAME_SIZE];
	//日志路径
	char m_szLogPathName[TOOLS_APP_LOG_PATH_NAME_SIZE];
	//临时文件路径
	char m_szTempPathName[TOOLS_APP_TEMP_PATH_NAME_SIZE];
	//日志模块
	CToolsLog* m_pLog;
	//内存池
	CToolsMemoryPoolWithLock* m_pMemPool;
	//线程池
	CToolsTaskPool* m_pTaskPool;
	//线程池的运行体
	CToolsTaskRun* m_pTaskRun;
	//内核级Debug，每次运行写一个文件，覆盖上次的
	CToolsLowDebug* m_pDebug;
private:
	//Info 打印任务
	static bool InfoPrintTaskCallback(void* pCallParam, int& nStatus);
	time_t m_tLastPrint;
	//打印信息的回调函数
	_BASE_LIBRARY_PRINT_INFO_CALLBACK m_pPrintInfoCallback;
	void* m_pPrintInfoCallbackParam; //回调函数参数指针
#ifdef WIN32
	bool m_bSocketInitFlag;
	WSADATA m_wsaData;
#endif
};













#endif // _BASE_LIB_H__

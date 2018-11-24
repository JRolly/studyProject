
////////////////////////////////////////////////////////////
//							�ۺϹ���
////////////////////////////////////////////////////////////

#ifndef _BASE_LIB_H__
#define _BASE_LIB_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "LogTools.h"
#include "MemoryTools.h"
#include "ThreadTools.h"
//#include "TaskTools.h"

#define MAIN_LOOP_DELAY 2 //2 ��һ��main loop
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
	CToolsBaseLibrary(char* szAppName, //Ӧ����
		char* szLogPath, //��־·��
		char* szTempPath, //��ʱ�ļ�·��
		int nTaskPoolThreadMax = DEFAULT_THREAD_MAX, //���������߳���
		bool bDebug2TTYFlag = true, //Debug �������Ļ����
		_BASE_LIBRARY_PRINT_INFO_CALLBACK pPrintInfoCallback = null, //info ��Ļ����ص�ָ��
		void* pPrintInfoCallbackParam = null, //info �ص�����ָ��
		_APP_INFO_OUT_CALLBACK pInfoOutCallback = null, //Ӧ�ó�������ص�
		void* pInfoOutCallbackParam = null); //Ӧ�ó�������ص�����ָ��
	~CToolsBaseLibrary(); //��������
public:
	//Ӧ�����ı��ݱ���
	char m_szAppName[TOOLS_APPLICATION_NAME_SIZE];
	//��־·��
	char m_szLogPathName[TOOLS_APP_LOG_PATH_NAME_SIZE];
	//��ʱ�ļ�·��
	char m_szTempPathName[TOOLS_APP_TEMP_PATH_NAME_SIZE];
	//��־ģ��
	CToolsLog* m_pLog;
	//�ڴ��
	CToolsMemoryPoolWithLock* m_pMemPool;
	//�̳߳�
	CToolsTaskPool* m_pTaskPool;
	//�̳߳ص�������
	CToolsTaskRun* m_pTaskRun;
	//�ں˼�Debug��ÿ������дһ���ļ��������ϴε�
	CToolsLowDebug* m_pDebug;
private:
	//Info ��ӡ����
	static bool InfoPrintTaskCallback(void* pCallParam, int& nStatus);
	time_t m_tLastPrint;
	//��ӡ��Ϣ�Ļص�����
	_BASE_LIBRARY_PRINT_INFO_CALLBACK m_pPrintInfoCallback;
	void* m_pPrintInfoCallbackParam; //�ص���������ָ��
#ifdef WIN32
	bool m_bSocketInitFlag;
	WSADATA m_wsaData;
#endif
};













#endif // _BASE_LIB_H__

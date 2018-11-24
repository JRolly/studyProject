#include "BaseLib.h"
#include "TaskTools.h"


CToolsBaseLibrary::CToolsBaseLibrary(
	char* szAppName,
	char* szLogPath,
	char* szTempPath,
	int nTaskPoolThreadMax,
	bool bDebug2TTYFlag,
	_BASE_LIBRARY_PRINT_INFO_CALLBACK pPrintInfoCallback,
	void* pPrintInfoCallbackParam,
	_APP_INFO_OUT_CALLBACK pInfoOutCallback,
	void* pInfoOutCallbackParam)
{
	m_pDebug = null; //��ָ���������ֵnull
	m_pTaskPool = null; //����Ԥ��ĳ����ʼ������ʧ�ܺ�
	m_pMemPool = null; //��ת�����º���ָ��û�и�ֵ
	m_pLog = null; //��Ϊ��Ұָ�롱
				   //�������·���ַ�����ֵ
	SafeStrcpy(m_szAppName, szAppName, TOOLS_APPLICATION_NAME_SIZE);
	SafeStrcpy(m_szLogPathName, szLogPath, TOOLS_APP_LOG_PATH_NAME_SIZE);
	SafeStrcpy(m_szTempPathName, szTempPath, TOOLS_APP_TEMP_PATH_NAME_SIZE);
	//������Ϣ��ӡ�ص��������ָ��
	m_pPrintInfoCallback = pPrintInfoCallback;
	m_pPrintInfoCallbackParam = pPrintInfoCallbackParam;
	//��ʼ�����������
	srand((unsigned int)time(NULL));
#ifdef WIN32
	{ //ע�⣬�������޶������򣬿�����ʱ�������
		m_bSocketInitFlag = false;
		WORD wVersionRequested;
		int err;
		wVersionRequested = MAKEWORD(2, 2);
		err = WSAStartup(wVersionRequested, &m_wsaData);
		if (err != 0)
		{
			TOOLS_DEBUG("Socket init fail!\n");
		}
		else m_bSocketInitFlag = true;
	}
#else // Non-Windows
#endif

	//��ʼ��Debug����
	m_pDebug = new CToolsLowDebug(m_szLogPathName,
		m_szAppName,
		bDebug2TTYFlag,
		pInfoOutCallback,
		pInfoOutCallbackParam);
	if (!m_pDebug) return;
	//��ʼ��һ����Ϣ�����Hello World�����Ǳ���ϰ�ߣ�ÿ������һ��������ӡ�����Ϣ
	TOOLS_DEBUG("------------------------------------------\n");
	//TOOLS_DEBUG("Hello World!\n");

	//��ʼ���ڴ��
	m_pMemPool = new CToolsMemoryPoolWithLock(m_pDebug);
	if (!m_pMemPool)
	{ //���ʧ�ܣ������Ѿ��ܴ�ӡDebug ��Ϣ��
		TOOLS_DEBUG("CToolsBaseLibrary(): m_pMemPool new fail!\n");
		return;
	}

	//��ʼ����־ϵͳ
	m_pLog = new CToolsLog(m_pDebug, m_pMemPool,
		m_szLogPathName, //ע�⣬����ʹ����־·��
		m_szAppName);
	if (m_pLog)
	{ //ע�⣬��ʱ�Ѿ����������ڴ�ص�ע�����
		m_pMemPool->Register(m_pLog, "CToolsBaseLibrary::m_pLog");
	}

	//��ʼ������ؼ�ִ����
	m_pTaskPool = new CToolsTaskPool(this, nTaskPoolThreadMax);
	if (m_pTaskPool)
	{ //ע�⣬��ʱ�Ѿ����������ڴ�ص�ע�����
		m_pMemPool->Register(m_pTaskPool, "CToolsBaseLibrary::m_pTaskPool");
	}	
	m_pTaskRun = new CToolsTaskRun(this);
	if (m_pTaskRun)
	{ //ע�⣬��ʱ�Ѿ����������ڴ�ص�ע�����
		m_pMemPool->Register(m_pTaskRun, "CToolsBaseLibrary::m_pTaskRun");
	}

	TimeSetNow(m_tLastPrint); //��ʱ����
	 //ע�⣬����ص������Ĳ����Ǳ�����ָ��
	if (!m_pTaskRun->StartTask(InfoPrintTaskCallback, this))
	{ //ʧ���򱨾�
		m_pLog->_XGSyslog("CToolsBaseLibrary:: start print info task fail!\n");
	} 
	//�ۺϹ�����������ϱ�־��Ҳ��Ӧ�ó����߼���ʼ������־
	TOOLS_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

CToolsBaseLibrary::~CToolsBaseLibrary()
{ //����ϰ�ߣ�����Ӧ�ó����߼���ʼ�˳��ı�־������ڹ��캯���е����
	TOOLS_DEBUG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	//����һ�����ɣ��˳�ʱ������ϲ�����չ���ģ��Ļ��֣���ӡһЩ����
	//��ĳ��ģ���̳߳���bug�����˳��߼��ܿ����ܵ�Ӱ�죬�����˳�ʱ����
	//��ʱֻҪ�򵥹۲����ִ򵽼����Ϳ��������ж���������һ�����������⣬����debug
	TOOLS_PRINTF("1\n");
	//�����ڴ�صĹرձ�־���ڴ���Free ������ֱ���ͷţ����������ڴ�ջ���ӿ��������
	m_pMemPool->SetCloseFlag();
	TOOLS_PRINTF("2\n");
	TOOLS_PRINTF("3\n");
	if (m_pTaskRun) //�˳��̳߳������壬ע�����з�ע�ᶯ��
	{
		m_pMemPool->UnRegister(m_pTaskRun);
		delete m_pTaskRun;
		m_pTaskRun = null;
	} 
	TOOLS_PRINTF("4\n");
	TOOLS_PRINTF("5\n");
	if (m_pTaskPool) //�˳��̳߳أ�ע�����з�ע�ᶯ��
	{
		m_pMemPool->UnRegister(m_pTaskPool);
		delete m_pTaskPool;
		m_pTaskPool = null;
	}
	TOOLS_PRINTF("6\n");
	if (m_pLog) //�˳�Log ��־ģ�飬ע�����з�ע�ᶯ��
	{
		m_pMemPool->UnRegister(m_pLog);
		delete m_pLog;
		m_pLog = null;
	}
	TOOLS_PRINTF("7\n");
	if (m_pMemPool) //�˳��ڴ��
	{
		delete m_pMemPool;
		m_pMemPool = null;
	}
	TOOLS_PRINTF("8\n");
	//TOOLS_DEBUG("Bye World!\n"); //����ϰ�ߣ����ټ������硱
	TOOLS_DEBUG("------------------------------------------\n");
	if (m_pDebug) //�˳�Debug ����
	{
		delete m_pDebug;
		m_pDebug = null;
	} 
	TOOLS_PRINTF("9\n");
#ifdef WIN32
	if (m_bSocketInitFlag)
	{
		if (LOBYTE(m_wsaData.wVersion) != 2 ||
			HIBYTE(m_wsaData.wVersion) != 2)
		{
			WSACleanup();
		} 
		m_bSocketInitFlag = false;
	}
#else // Non-Windows
#endif
}

bool CToolsBaseLibrary::InfoPrintTaskCallback(void* pCallParam, int& nStatus)
{ //ǿ��ָ������ת������ñ�����ָ��
	CToolsBaseLibrary* pThis = (CToolsBaseLibrary*)pCallParam;
	//����Ƿ��Ѿ��ȵ�2 �룬���򷵻�
	if (TimeIsUp(pThis->m_tLastPrint, MAIN_LOOP_DELAY))
	{
		TimeSetNow(pThis->m_tLastPrint); //���µ�ǰʱ��
		TOOLS_PRINTF("*******************************************\n");
		pThis->m_pTaskPool->PrintInfo(); //��ӡ�������Ϣ
		pThis->m_pTaskRun->PrintInfo(); //��ӡ�������������Ϣ
		pThis->m_pMemPool->PrintInfo(); //��ӡ�ڴ����Ϣ
		if (pThis->m_pPrintInfoCallback) //�ص�Ӧ�ò��ӡ����
			pThis->m_pPrintInfoCallback(pThis->m_pPrintInfoCallbackParam);
		TOOLS_PRINTF("*******************************************\n");
		TOOLS_PRINTF("\n");
	} 
	return true; //�����棬��Զѭ��
}













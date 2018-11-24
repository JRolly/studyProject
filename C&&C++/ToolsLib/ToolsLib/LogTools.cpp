#include "LogTools.h"


CToolsLog::CToolsLog(CToolsLowDebug* pDebug, //����������
	CToolsMemoryPoolWithLock* pMemPool,
	char* szLogPath,
	char* szAppName,
	int nHoldFileMax,
	bool bSyslogFlag,
	bool bDebugFlag,
	bool bDebug2Flag,
	bool bDebug3Flag,
	bool bPrintf2ScrFlag)
{
	m_pDebug = pDebug; //����Debug ����ָ��
	m_pMemPool = pMemPool; //�����ڴ��ָ��
						   //��ע�⣬�����Debug �����л�����ػص�������Ϣ
	m_pInfoOutCallback = m_pDebug->m_pInfoOutCallback;
	m_pInfoOutCallbackParam = m_pDebug->m_pInfoOutCallbackParam;
	//����debug ���������־
	TOOLS_DEBUG("CToolsLog: Start!\n");
	//�����־�ļ�����׼�ַ�����������Ҫʹ�������·������Ӧ�������ɻ�����
	//��·���ǡ�/var����Ӧ�����ǡ�test_project����
	//���׼��Ϊ��/var/test_project����
	//�������Ժ���ļ�����������������������ʱ���ʵ��
	//�磺/var/test_project_Thu_Jul_16_14_31_44_2009.log
	FULL_NAME(szLogPath, szAppName, m_szFilePath, "");
	//�����־�ļ���Ŀ¼�ı����ļ���
	//�磺/var/test_project.info
	FULL_NAME(szLogPath, szAppName, m_szFileInfoName, "info");
	//��յ�ǰ�ļ���������
	TOOLS_CLEAN_CHAR_BUFFER(m_szFileName);
	//��ǰ�ļ��ߴ�����Ϊ0
	m_nFileSize = 0;
	m_bSyslogFlag = bSyslogFlag; //����Debug ���𿪹ر���
	m_bDebugFlag = bDebugFlag; //Ϊfalse �ļ��𽫲��ᱻ���
	m_bDebug2Flag = bDebug2Flag;
	m_bDebug3Flag = bDebug3Flag;
	m_bPrintf2ScrFlag = bPrintf2ScrFlag; //������Ļ�������
	m_nHoldFileMax = nHoldFileMax; //����������ļ�����
	m_pFileInfoQueue = new CToolsMemoryQueue( //ʵ�����ļ�Ŀ¼���ж���
		pDebug,
		m_pMemPool,
		"CToolsLog::m_pFileInfoQueue");
	if (m_pFileInfoQueue) //��������ɹ���ע�ᵽ�ڴ��
	{
		m_pMemPool->Register(m_pFileInfoQueue,
			"CToolsLog::m_pFileInfoQueue");
	} 
	m_pFileInfoQueue->ReadFromFile(m_szFileInfoName); //�����ϴα������ļ�����Ϣ
	MakeFileName(); //���ݵ�ǰʱ���������һ���ļ���
}

CToolsLog::~CToolsLog()
{
	if (m_pFileInfoQueue) //����ļ�Ŀ¼���ж���
	{
		m_pFileInfoQueue->Write2File(m_szFileInfoName); //���ǰ�ȱ���������
		m_pMemPool->UnRegister(m_pFileInfoQueue); //��ע�����ָ��
		delete m_pFileInfoQueue; //ɾ������
		m_pFileInfoQueue = null;
	} 
	TOOLS_DEBUG("CToolsLog: Stop!\n"); //Debug ���
}

void CToolsLog::GetFileName(void) //��ȡ��ǰ�ļ���
{
	time_t tNow; //��ǰʱ�������
	unsigned long ulDeltaT = 0; //��t ����
	if ('\0' == m_szFileName[0]) //����ǵ�һ���������ļ���Ϊ��
	{
		MakeFileName(); //������������ļ���������
		goto CToolsLog_GetFileName_End_Porcess;
	} 
	time(&tNow); //��õ�ǰʱ��
	ulDeltaT = (unsigned long)tNow - m_tFileNameMake; //�����t
	if (LOG_FILE_CHANGE_NAME_PRE_SECONDS <= ulDeltaT)
	{
		MakeFileName(); //�����t ����3600 �룬�����ļ�������
		goto CToolsLog_GetFileName_End_Porcess;
	} 
	if (LOG_FILE_SIZE_MAX <= m_nFileSize) //�����ǰ�ļ���С�ߴ糬��1G
	{
		MakeFileName(); //�����ļ�������
		goto CToolsLog_GetFileName_End_Porcess;
	}
CToolsLog_GetFileName_End_Porcess:
	return;
}

void CToolsLog::MakeFileName(void) //����һ�����ļ���
{
	char szTemp[LOG_ITEM_LENGTH_MAX]; //��ʱ������
	MakeATimeString(szTemp, LOG_ITEM_LENGTH_MAX); //���ʱ����ַ���
		FixFileInfo(); //ά���ļ��ܸ��������꣨Ĭ��72 ����
	int nLen = SafePrintf( //ע�⿴��䣬���ù��캯���е���������
		m_szFileName, //����ʱ����������ټ��ϡ�.log����׺
		FILENAME_STRING_LENGTH * 2, //������־�ļ���
		"%s_%s.log",
		m_szFilePath,
		szTemp);
	nLen++; //ϰ�ߣ�����+1���������\0����λ��
			//���µ��ļ�����ӵ�����
	int nAddLastRet = m_pFileInfoQueue->AddLast(m_szFileName, nLen);
	if (0 >= nAddLastRet)
	{ //����һ������ķ���������������ˣ��ڴ治���ã���ɾ���ʼ�����ļ���
	  //�ͷ��ڴ�ռ䣬����Ԥ��������ҵ��̫��æ�������ڴ治���ã������޷���ӵ�
	  //��ܴ�ʩ����Ҳ���ַǹؼ�ģ��Ϊ�ؼ�ҵ��ģ����·��˼ά
		DeleteFirstFile();
		DeleteFirstFile();
		DeleteFirstFile();
		//ɾ������֮�����³������
		nAddLastRet = m_pFileInfoQueue->AddLast(m_szFileName, nLen);
		//�����ʱ�����Ȼʧ�ܣ�Ͷ������־����һ�����û�й�ϵ��
	}
	m_nFileSize = 0; //���ļ��������ļ�����Ϊ0
	//�����߼����´���һ���ļ������ļ�ͷ�ȴ�ӡһ���ļ��������Ϣ�������Ժ�ĸ��ٲ���
	time(&m_tFileNameMake);
	{ //�������Ƿ�ҵ���ӡ����˲�ϣ���������Ļ��������ʱ����Ļ���عر�
		bool bPrint2Scr = m_bPrintf2ScrFlag;
		m_bPrintf2ScrFlag = false;
		_Printf("Tools. base libeary log file %s\n", m_szFileName);
		_Printf("-----------------------------------------------\n");
		m_bPrintf2ScrFlag = bPrint2Scr; //�����ϣ���Ļ���ػָ�ԭֵ
	}
}

int CToolsLog::MakeATimeString(char* szBuffer, int nBufferSize)
{
	int i = 0;
	time_t t;
	struct tm *pTM = NULL;
	int nLength = 0;
	if (LOG_TIME_STRING_MAX>nBufferSize) //���������
		goto CToolsLog_MakeATimeString_End_Porcess;
	time(&t); //��õ�ǰʱ��
	pTM = localtime(&t); //�򵱵�ǰʱ����ʱ����ַ���
	nLength = SafePrintf(szBuffer, LOG_ITEM_LENGTH_MAX, "%s", asctime(pTM));
	//ʱ����ַ����뻺����
	//localtime ���ɵ��ַ�������Դ�һ����\n�������س������ⲻ���ں����Ĵ�ӡ
	//�������������ǰ��һ�����������س���������һ��С���顣
	szBuffer[nLength - 1] = '\0';
	//�ļ�����һ�����ƣ�һ�㲻Ҫ�пո񣬡�:���ַ����������һ�£�
	//��ʱ����еķǷ��ַ����ı�ɸ�ϵͳ���ܽ��ܵġ�_���»���
	for (i = 0; i<nLength; i++)
	{
		if (' ' == szBuffer[i]) szBuffer[i] = '_';
		if (':' == szBuffer[i]) szBuffer[i] = '_';
	}
CToolsLog_MakeATimeString_End_Porcess:
	return nLength; //�����ܳ���
}

void CToolsLog::FixFileInfo(void) //ά���ļ��ܸ���������
{
	int nAddLastRet = 0;
	//��ע�⣬���ﲻ��if������һ��while�������ĳ��ԭ�򣬳���ܶ���ļ�
	//�������ѭ�����ɣ������ɵؽ������ļ�ɾ����ֻ��72 ����
	//�ܶ�ʱ��ά�����鲻���ޣ�����ʹ���������
	while (m_pFileInfoQueue->GetTokenCount() >= m_nHoldFileMax)
	{
		DeleteFirstFile();
	}
}

void CToolsLog::DeleteFirstFile(void) //ɾ����һ���ļ�
{
	char szFirstFile[FILENAME_STRING_LENGTH]; //�ļ���������
	int nFirstFileNameLen = 0; //�ļ����ַ�������
	//���ļ��������У�������һ���ļ���
	nFirstFileNameLen = m_pFileInfoQueue->GetAndDeleteFirst(
		szFirstFile, FILENAME_STRING_LENGTH);
	if (0 >= nFirstFileNameLen) //ʧ�ܷ���
		goto CToolsLog_DeleteFirstFile_End_Process;
	CToolsLowDebug::DeleteAFile(szFirstFile); //��ʵ��ɾ���ļ�
CToolsLog_DeleteFirstFile_End_Process:
	return;
}

int CToolsLog::_XGSyslog(char *szFormat, ...)
{ //��αȽϾ��䣬��κ�������ģ�飬����׸��
	char szBuf[LOG_ITEM_LENGTH_MAX];
	int nMaxLength = LOG_ITEM_LENGTH_MAX;
	int nListCount = 0;
	va_list pArgList;
	va_start(pArgList, szFormat);
	nListCount += Linux_Win_vsnprintf(szBuf + nListCount,
		nMaxLength - nListCount, szFormat, pArgList);
	va_end(pArgList);
	if (nListCount>(nMaxLength - 1)) nListCount = nMaxLength - 1;
	*(szBuf + nListCount) = '\0';
	if (m_bSyslogFlag) //������ش�
	{
		m_Lock.Lock(); //����
		{
			_Printf("%s", szBuf); //��ʵִ�д�ӡ
		}
		m_Lock.Unlock(); //����
	}
	return nListCount; //���س���
}

int CToolsLog::_XGDebug(char *szFormat, ...)
{ //��αȽϾ��䣬��κ�������ģ�飬����׸��
	char szBuf[LOG_ITEM_LENGTH_MAX];
	int nMaxLength = LOG_ITEM_LENGTH_MAX;
	int nListCount = 0;
	va_list pArgList;
	va_start(pArgList, szFormat);
	nListCount += Linux_Win_vsnprintf(szBuf + nListCount,
		nMaxLength - nListCount, szFormat, pArgList);
	va_end(pArgList);
	if (nListCount>(nMaxLength - 1)) nListCount = nMaxLength - 1;
	*(szBuf + nListCount) = '\0';
	if (m_bDebugFlag) //������ش�
	{
		m_Lock.Lock(); //����
		{
			_Printf("%s", szBuf); //��ʵִ�д�ӡ;
		} 
		m_Lock.Unlock(); //����
	} 
	return nListCount; //���س���
}

int CToolsLog::_XGDebug2(char *szFormat, ...)
{ //��αȽϾ��䣬��κ�������ģ�飬����׸��
	char szBuf[LOG_ITEM_LENGTH_MAX];
	int nMaxLength = LOG_ITEM_LENGTH_MAX;
	int nListCount = 0;
	va_list pArgList;
	va_start(pArgList, szFormat);
	nListCount += Linux_Win_vsnprintf(szBuf + nListCount,
		nMaxLength - nListCount, szFormat, pArgList);
	va_end(pArgList);
	if (nListCount>(nMaxLength - 1)) nListCount = nMaxLength - 1;
	*(szBuf + nListCount) = '\0';
	if (m_bDebug2Flag) //������ش�
	{
		m_Lock.Lock(); //����
		{
			_Printf("%s", szBuf); //��ʵִ�д�ӡ
		} 
		m_Lock.Unlock(); //����
	} 
	return nListCount; //���س���
}

int CToolsLog::_XGDebug3(char *szFormat, ...)
{ //��αȽϾ��䣬��κ�������ģ�飬����׸��
	char szBuf[LOG_ITEM_LENGTH_MAX];
	int nMaxLength = LOG_ITEM_LENGTH_MAX;
	int nListCount = 0;
	va_list pArgList;
	va_start(pArgList, szFormat);
	nListCount += Linux_Win_vsnprintf(szBuf + nListCount,
		nMaxLength - nListCount, szFormat, pArgList);
	va_end(pArgList);
	if (nListCount>(nMaxLength - 1)) nListCount = nMaxLength - 1;
	*(szBuf + nListCount) = '\0';
	if (m_bDebug3Flag) //������ش�
	{
		m_Lock.Lock(); //����
		{
			_Printf("%s", szBuf); //��ʵִ�д�ӡ;
		} 
		m_Lock.Unlock(); //����
	} 
	return nListCount; //���س���
}


int CToolsLog::_Printf(char *szFormat, ...)
{
	char szTime[LOG_ITEM_LENGTH_MAX];
	char szTemp[LOG_ITEM_LENGTH_MAX];
	char szBuf[LOG_ITEM_LENGTH_MAX];
	int nMaxLength = LOG_ITEM_LENGTH_MAX;
	int nListCount = 0;
	time_t t;
	struct tm *pTM = NULL;
	int nLength = 0;
	//��õ�ǰʱ���������MakeATimeString ���Ѿ��н���
	time(&t);
	pTM = localtime(&t);
	nLength = SafePrintf(szTemp, LOG_ITEM_LENGTH_MAX, "%s", asctime(pTM));
	szTemp[nLength - 1] = '\0';
	SafePrintf(szTime, LOG_ITEM_LENGTH_MAX, "[%s] ", szTemp);
	//��αȽϾ��䣬��κ�������ģ�飬����׸��
	va_list pArgList;
	va_start(pArgList, szFormat);
	nListCount += Linux_Win_vsnprintf(szBuf + nListCount,
		nMaxLength - nListCount, szFormat, pArgList);
	va_end(pArgList);
	if (nListCount>(nMaxLength - 1)) nListCount = nMaxLength - 1;
	*(szBuf + nListCount) = '\0';
	//�õ���ǰʹ�õ��ļ���
	GetFileName();
	//����debug �Ĺ��ܺ�����ֱ�ӽ���Ϣ������ļ�
	nListCount = dbg2file(m_szFileName, "a+", "%s%s", szTime, szBuf);
	if (m_bPrintf2ScrFlag) //�����Ļ������ش���
	{
		TOOLS_PRINTF("%s%s", szTime, szBuf); //�������Ļ
	} 
	if (m_pInfoOutCallback) //������غ�������
	{ //��������غ���
		char szInfoOut[APP_INFO_OIT_STRING_MAX];
		SafePrintf(szInfoOut,APP_INFO_OIT_STRING_MAX,
			"%s%s",szTime,szBuf);
		m_pInfoOutCallback(szInfoOut,m_pInfoOutCallbackParam);
	} 
	m_nFileSize += nListCount; //�������Ҫ���޶��ļ�����
	//ά��ģ����Ҫ���ֵ�ж��ļ���С
	//�Ƿ񳬱�
	return nListCount; //����������ֽ���
}

void CToolsLog::_XGDebug4Bin(char* pBuffer, int nLength)
{
	m_Lock.Lock(); //����
	{
		GetFileName(); //����ļ���
		dbg2file(m_szFileName, "a+", pBuffer, nLength);
		//dbg2file4bin(m_szFileName, "a+", pBuffer, nLength); //������ļ�
		dbg_bin(pBuffer, nLength); //�������Ļ
	} 
	m_Lock.Unlock(); //����
}
////////////////////////////////////////////////////////////
//							Log��־������
////////////////////////////////////////////////////////////

#ifndef __LOG_TOOLS_H__
#define __LOG_TOOLS_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "MemoryTools.h"
#include "MemQueue.h"


#define LOG_FILE_SIZE_MAX (1*1024*1024*1024) //ÿ����־�ļ����1G
#define LOG_ITEM_LENGTH_MAX (2*1024) //����log ��󳤶�2k
#define LOG_FILE_CHANGE_NAME_PRE_SECONDS (60*60) //��־�ļ�1 Сʱ����һ������
#define LOG_FILE_INFO_BUFFER_SIZE (256*1024) //��־Ŀ¼��󳤶�(����ɾ��)
#define LOF_FILE_DEFAULT_HOLD 72 //һ�㱣��3 �������
#define LOG_TIME_STRING_MAX 128 //ʱ����ַ�������



//typedef void(*_APP_INFO_OUT_CALLBACK)(char* szInfo, void* pCallParam);


//���ߵ���־����ϵͳ�����ںܶ�ϵͳ�����Լ�����־ϵͳ���˴��Ա��ߵ�Ӣ�������Σ���������
#define FILENAME_STRING_LENGTH 256 //�ļ�������
class CToolsLog
{
public: //��̬���ߺ�����
		//����ʱ����ַ���
		static int MakeATimeString(char* szBuffer, int nBufferSize);
public: //���캯������������
	CToolsLog(CToolsLowDebug* pDebug, //debug ����ָ�루log Ҳ��Ҫdebug��
		CToolsMemoryPoolWithLock* pMemPool, //�ڴ��ָ�룬�ڴ����Ҫ��
		char* szLogPath, //��־·��
		char* szAppName, //Ӧ������������־�ļ���
		int nHoldFileMax = LOF_FILE_DEFAULT_HOLD,//�������ٸ��ļ�
		bool bSyslogFlag = true, //��־���𿪹أ�true �򿪣�����ر�
		bool bDebugFlag = true,
		bool bDebug2Flag = false,
		bool bDebug3Flag = false,
		bool bPrintf2ScrFlag = true); //�Ƿ��ӡ����Ļ����
	~CToolsLog(); //��������
public: //�����������
	void _XGDebug4Bin(char* pBuffer, int nLength);//���������
	int _XGSyslog(char *szFormat, ...); //Syslog �������κ���
	int _XGDebug(char *szFormat, ...); //Debug �������κ���
	int _XGDebug2(char *szFormat, ...); //Debug2 �������κ���
	int _XGDebug3(char *szFormat, ...); //Debug3 �������κ���
public: //���ر�������Ӧ���캯���Ŀ���
	bool m_bSyslogFlag;
	bool m_bDebugFlag;
	bool m_bDebug2Flag;
	bool m_bDebug3Flag;
private: //�ڲ����ܺ���
	int _Printf(char *szFormat, ...); //����ĵĴ�ӡ���ģ�飬��κ���
	void DeleteFirstFile(void); //ɾ�����ϵ��ļ�
	void FixFileInfo(void); //�޶��ļ���Ŀ¼����
	void MakeFileName(void); //����ʱ����ļ���С�������ļ���
	void GetFileName(void); //��õ�ǰ���õ��ļ���
private: //�ڲ�˽�б�����
	CMutexLock m_Lock; //�̰߳�ȫ��
	char m_szFilePath[FILENAME_STRING_LENGTH]; //�ļ�·��
	char m_szFileName[(FILENAME_STRING_LENGTH * 2)];//�ļ���
	unsigned long m_nFileSize; //��ǰ�ļ���С
	time_t m_tFileNameMake; //�����ļ�����ʱ���
	int m_nHoldFileMax; //�����ļ������������캯������
	_APP_INFO_OUT_CALLBACK m_pInfoOutCallback; //Ӧ�ó�����������ص�����
	void* m_pInfoOutCallbackParam; //͸���Ļص�����ָ��
	bool m_bPrintf2ScrFlag; //�Ƿ��ӡ����Ļ�Ŀ���
	char m_szFileInfoName[FILENAME_STRING_LENGTH];//�ļ���
	CToolsLowDebug* m_pDebug; //Debug ����ָ��
	CToolsMemoryPoolWithLock* m_pMemPool; //�ڴ�ض���ָ��
	CToolsMemoryQueue* m_pFileInfoQueue; //�ļ�������
};






#endif // __LOG_TOOLS_H__


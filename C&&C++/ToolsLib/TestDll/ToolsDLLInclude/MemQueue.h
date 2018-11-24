
////////////////////////////////////////////////////////////
//							����
////////////////////////////////////////////////////////////



#ifndef __MEM_QUEUE_H__
#define __MEM_QUEUE_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "BufferTools.h"


#define TOOLS_CHAIN_TOKEN_MAX 1024
#define TOOLS_APPLICATION_NAME_SIZE	256

//MemQueue ����ڵ����ݽṹ
typedef struct _TOOLS_QUEUE_TOKEN_HEAD_
{
	int m_nDataLength; //�洢��ҵ�����ݳ���
	char* m_pBuffer; //ָ��ҵ�����ݿ��ָ��
	struct _TOOLS_QUEUE_TOKEN_HEAD_* m_pNext; //ָ����һ�ڵ��ָ��
}SToolsQueueTokenHead; //������µĽṹ���������
//����ϰ�ߣ�д��ṹ�壬���������䳤�ȳ���������������ڴ����롣
const ULONG SToolsQueueTokenHeadSize=sizeof(SToolsQueueTokenHead);


//��̬�ڴ������
class TOOLSLIB_API CToolsMemoryQueue
{ 
private:
	//����MemQueue ʹ�ö�̬�ڴ���䣬��������û�����Ƶ�
	//������֪�����������κ����ݽṹ����Ӧ���б߽磬������ܻ����bug
	//����ʹ��һ���ڲ�������ǿ�н綨�߽�ֵ��Ϊ������󳤶���������
	int m_nMaxToken; //����Token ����
	int m_nTokenCount; //��������ЧToken ����
	SToolsQueueTokenHead* m_pHead; //����ͷָ��
	SToolsQueueTokenHead* m_pLast; //�������ӣ�����βָ��
	CToolsLowDebug* m_pDebug; //debug ����ָ��
	CToolsMemoryPoolWithLock* m_pMemPool; //�ڴ��ָ�루���������ڴ�أ�
	char m_szAppName[TOOLS_APPLICATION_NAME_SIZE];
public:
	CToolsMemoryQueue(CToolsLowDebug* pDebug,//debug ����ָ��
		CToolsMemoryPoolWithLock* pMemPool, //�ڴ��ָ��
		char* szAppName, //Ӧ�����������������
		int nMaxToken=TOOLS_CHAIN_TOKEN_MAX); //���Token ����
	~CToolsMemoryQueue();

public:
	bool ICanWork(void); //���̫��Ϥ�˰ɣ��Ƿ���Թ�����־
	void CleanAll(void); //�������Token���������
	int GetFirstLength(void); //��õ�һ��Token ���ݳ���
	//���ܺ�Ŀ��ͬPopBuffer
	int GetTokenCount(void){return m_nTokenCount;} //�������Token ����������
	void PrintInside(void); //������ӡ���ж����ڲ�Token ����
public:
	int AddLast(char* szData, //����ָ��
		int nDataLength, //���ݳ���
		int nLimit=-1); //����Ϊ�˷�ֹ�ݹ��ȹ���������������
	int GetFirst(char* szBuffer,int nBufferSize);
	int GetFirst(CToolsBuffer* pBuffer);
	bool DeleteFirst(void);
	int GetAndDeleteFirst(char* szBuffer,int nBufferSize);
	int GetAndDeleteFirst(CToolsBuffer* pBuffer);
public:
	//��ǰ�浯��һ�����ݣ���nBufferSize ��װ��PopBuffer ������Ϊ׼
	int PopFromFirst(char* szBuffer,int nBufferSize);
	//��PopBuffer ���������������������ݣ�׷�ӵ�����ĩβ
	int Push2Last(char* szData,int nDataLength);
public:
	void Write2File(char* szFileName); //��������д�����
	int ReadFromFile(char* szFileName); //�������ݴӴ��̶���
private:
	void PrintAToken(SToolsQueueTokenHead* pToken);
	void WriteAToken2File(SToolsQueueTokenHead* pToken,FILE* fp);
	int PopFromFirst4ToolsPopBuffer(CToolsPopBuffer* pPopBuffer);
	int AddLast2ThisToken(SToolsQueueTokenHead* pToken,char* szData,int nDataLength);
	SToolsQueueTokenHead* GetAToken(void);
	bool DeleteATokenAndHisNext(SToolsQueueTokenHead* pToken);
	static bool PushDataCallback(char* szData, int nDataLength,	void* pCallParam);
};

/////////////////////////////////////
//MemQueue ���̰߳�ȫ��װ��
class TOOLSLIB_API CToolsMemoryQueueWithLock
{ 
public:
	CToolsMemoryQueueWithLock(CToolsLowDebug* pDebug,
		CToolsMemoryPoolWithLock* pMemPool,
		char* szAppName,
		int nMaxToken=TOOLS_CHAIN_TOKEN_MAX);
	~CToolsMemoryQueueWithLock();
public:
	bool ICanWork(void); //��Ӧ���ֹ��з�����
	int AddLast(char* szData,int nDataLength);
	int GetFirst(CToolsBuffer* pBuffer);
	int GetFirst(char* szBuffer,int nBufferSize);
	int GetFirstLength(void);
	int GetTokenCount(void);
	int GetAndDeleteFirst(char* szBuffer,int nBufferSize);
	int PopFromFirst(char* szBuffer,int nBufferSize);
	int Push2Last(char* szData,int nDataLength);
	void CleanAll(void);
	bool DeleteFirst(void);
	void Write2File(char* szFileName);
	int ReadFromFile(char* szFileName);
	void PrintInside(void);
private:
	CToolsMemoryPoolWithLock* m_pMemPool;
	CToolsMemoryQueue* m_pQueue; //MemQueue �ľۺ϶���
	CMultiReadSingleWriteLock m_Lock; //�̰߳�ȫ����Ϊ�˱�֤Ч�ʣ�
	//�˴�ʹ���˵�д�����
	char m_szAppName[TOOLS_APPLICATION_NAME_SIZE]; //�����AppName
};


#endif // __MEM_QUEUE_H__

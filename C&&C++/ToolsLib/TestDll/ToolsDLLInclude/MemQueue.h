
////////////////////////////////////////////////////////////
//							队列
////////////////////////////////////////////////////////////



#ifndef __MEM_QUEUE_H__
#define __MEM_QUEUE_H__


#include "IncludeDef.h"
#include "DebugTools.h"
#include "BufferTools.h"


#define TOOLS_CHAIN_TOKEN_MAX 1024
#define TOOLS_APPLICATION_NAME_SIZE	256

//MemQueue 链表节点数据结构
typedef struct _TOOLS_QUEUE_TOKEN_HEAD_
{
	int m_nDataLength; //存储的业务数据长度
	char* m_pBuffer; //指向业务数据块的指针
	struct _TOOLS_QUEUE_TOKEN_HEAD_* m_pNext; //指向下一节点的指针
}SToolsQueueTokenHead; //定义的新的结构体变量类型
//笔者习惯，写完结构体，立即声明其长度常量，方便后续的内存申请。
const ULONG SToolsQueueTokenHeadSize=sizeof(SToolsQueueTokenHead);


//动态内存队列类
class TOOLSLIB_API CToolsMemoryQueue
{ 
private:
	//由于MemQueue 使用动态内存分配，理论上是没有限制的
	//但我们知道，程序中任何数据结构，都应该有边界，否则可能会造成bug
	//这里使用一个内部变量，强行界定边界值，为队列最大长度做个上限
	int m_nMaxToken; //最大的Token 限制
	int m_nTokenCount; //队列中有效Token 个数
	SToolsQueueTokenHead* m_pHead; //队列头指针
	SToolsQueueTokenHead* m_pLast; //加速因子，队列尾指针
	CToolsLowDebug* m_pDebug; //debug 对象指针
	CToolsMemoryPoolWithLock* m_pMemPool; //内存池指针（本类依赖内存池）
	char m_szAppName[TOOLS_APPLICATION_NAME_SIZE];
public:
	CToolsMemoryQueue(CToolsLowDebug* pDebug,//debug 对象指针
		CToolsMemoryPoolWithLock* pMemPool, //内存池指针
		char* szAppName, //应用名，这里代队列名
		int nMaxToken=TOOLS_CHAIN_TOKEN_MAX); //最大Token 上限
	~CToolsMemoryQueue();

public:
	bool ICanWork(void); //这个太熟悉了吧，是否可以工作标志
	void CleanAll(void); //清除所有Token，队列清空
	int GetFirstLength(void); //获得第一个Token 数据长度
	//功能和目的同PopBuffer
	int GetTokenCount(void){return m_nTokenCount;} //获得所有Token 总数，内联
	void PrintInside(void); //遍历打印所有队列内部Token 数据
public:
	int AddLast(char* szData, //数据指针
		int nDataLength, //数据长度
		int nLimit=-1); //这是为了防止递归层度过深做的特殊限制
	int GetFirst(char* szBuffer,int nBufferSize);
	int GetFirst(CToolsBuffer* pBuffer);
	bool DeleteFirst(void);
	int GetAndDeleteFirst(char* szBuffer,int nBufferSize);
	int GetAndDeleteFirst(CToolsBuffer* pBuffer);
public:
	//从前面弹出一批数据，以nBufferSize 能装下PopBuffer 的数据为准
	int PopFromFirst(char* szBuffer,int nBufferSize);
	//从PopBuffer 的数据区，弹出所有数据，追加到队列末尾
	int Push2Last(char* szData,int nDataLength);
public:
	void Write2File(char* szFileName); //队列数据写入磁盘
	int ReadFromFile(char* szFileName); //队列数据从磁盘读出
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
//MemQueue 的线程安全封装类
class TOOLSLIB_API CToolsMemoryQueueWithLock
{ 
public:
	CToolsMemoryQueueWithLock(CToolsLowDebug* pDebug,
		CToolsMemoryPoolWithLock* pMemPool,
		char* szAppName,
		int nMaxToken=TOOLS_CHAIN_TOKEN_MAX);
	~CToolsMemoryQueueWithLock();
public:
	bool ICanWork(void); //对应各种公有方法名
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
	CToolsMemoryQueue* m_pQueue; //MemQueue 的聚合对象
	CMultiReadSingleWriteLock m_Lock; //线程安全锁，为了保证效率，
	//此处使用了单写多读锁
	char m_szAppName[TOOLS_APPLICATION_NAME_SIZE]; //保存的AppName
};


#endif // __MEM_QUEUE_H__

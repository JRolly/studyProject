// TestDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <string>
#include <direct.h>

//tools
#include "IncludeDef.h"
#include "DebugTools.h"
#include "LockTools.h"
#include "MemoryTools.h"
#include "SocketTools.h"
#include "BufferTools.h"
#include "MemQueue.h"
#include "ThreadTools.h"
#include "TaskTools.h"
#include "LogTools.h"
#include "BaseLib.h"

using namespace std;

#ifdef DEBUG
#pragma comment(lib, ".\\lib\\Debug\\ToolsLibD.lib")
#else
#pragma comment(lib, ".\\lib\\Release\\ToolsLibR.lib")
#endif


typedef struct {
	int m_nTestINT;
	char m_szTestC[MAX_PATH];
	string m_szTestSTR;
}STestSt;

static void ThreadTest(void* pCallParam, MBOOL& bThreadContinue);
bool TaskTest(void* pCallParam, int& nStatus);

void TestDebugTools(char* pFilePath, CToolsLowDebug* pDbg);
void TestMemTools(CToolsLowDebug* pDbg, CToolsMemoryPoolWithLock* pMem);
void TestMemQueue(CToolsLowDebug* pDbg, CToolsMemoryPoolWithLock* pMem, CToolsMemoryQueue* pQueue);
void TestThreadTools(CToolsLowDebug* pDbg, CToolsThreadPool* pT);
void TestTaskTools(CToolsTaskRun* ptask);
void TestBaselib(CToolsBaseLibrary* pbaselib);
void TestLog(CToolsBaseLibrary* pbaselib);


int main()
{
	char szFilePath[256] = {0};
	CToolsBaseLibrary* pbaselib;
	//CToolsLowDebug* pLowDbg;
	//CToolsMemoryPoolWithLock* pMem;
	CToolsMemoryQueue* pQueue;
	//CToolsThreadPool* pT;
	//CToolsTaskRun* ptask;

	string szInputBuf;
	cout << "Input log name:";
	cin >> szInputBuf;

	pbaselib = new CToolsBaseLibrary("Main", getcwd(szFilePath,_MAX_PATH), getcwd(szFilePath,_MAX_PATH));
	//pLowDbg = new CToolsLowDebug(getcwd(szFilePath,_MAX_PATH), szInputBuf.c_str(), true);
	//pMem = new CToolsMemoryPoolWithLock(pLowDbg);
	pQueue = new CToolsMemoryQueue(pbaselib->m_pDebug, pbaselib->m_pMemPool,  "Test MemQueue");
	//pT = new CToolsThreadPool(pLowDbg);
	//ptask = new CToolsTaskRun(pbaselib);

	//Test Debug Tools
	//TestDebugTools(szFilePath, pLowDbg);

	//Test Memory tools
	//TestMemTools(pLowDbg, pMem);

	//Test MemQueue tools
	TestMemQueue(pbaselib->m_pDebug, pbaselib->m_pMemPool, pQueue);

	//Test Thread tools
	//TestThreadTools(pLowDbg, pT);

	//Test Task Tools
	//TestTaskTools(ptask);

	//Test Base Lib
	TestBaselib(pbaselib);

	system("PAUSE");

	getchar();
	return 0;
}

void TestDebugTools(char* pFilePath, CToolsLowDebug* pDbg)
{
	cout << pDbg->GetTrueFileName(pFilePath) << endl;
	pDbg->Debug2File("Test Func Debug2File()\n");
	pDbg->Debug2File4Bin(pFilePath, _MAX_PATH);	
}

void TestMemTools(CToolsLowDebug* pDbg, CToolsMemoryPoolWithLock* pMem)
{
	char* pTestChar = (char*)pMem->Malloc(9*sizeof(char), "Test Malloc() 9\n");
	if (!pTestChar)
		return;
	memset(pTestChar, 0, 9*sizeof(char));
	pDbg->Debug2File4Bin(pTestChar, 9*sizeof(char));

	pTestChar = (char*)pMem->ReMalloc(pTestChar, 23*sizeof(char));
	if (!pTestChar)
		return;

	STestSt* pSTestSt = (STestSt*)pMem->Malloc(sizeof(STestSt)*3, "Test Struct\n");
	pSTestSt[0].m_nTestINT = 1;
	pSTestSt[0].m_szTestSTR = "feff";

	//test socket
	Linux_Win_SOCKET s[10];
	Linux_Win_Socket_Init();
	for (int i=0; i<10; ++i)
	{
		s[i] = socket(Linux_Win_F_INET, SOCK_DGRAM, IPPROTO_UDP);
		pMem->RegisterSocket(s[i], "socket");
	}
	for (int i=0; i<10; ++i)
		pMem->CloseSocket(s[i]);

	pMem->PrintInfo();
	pMem->PrintTree();
	pMem->m_pMemPool->PrintInfo();
	pMem->m_pMemPool->PrintStack();

	Linux_Win_Socket_Exit();
	pMem->Free(pTestChar);
}

void TestMemQueue(CToolsLowDebug* pDbg, CToolsMemoryPoolWithLock* pMem, CToolsMemoryQueue* pQueue)
{
	CToolsBuffer* pq1 = new CToolsBuffer(pMem);
	//pq1->m_pData = (char*)pMem->Malloc(256, "pq1");
	CToolsBuffer* pq2 = new CToolsBuffer(pMem);
	//pq2->m_pData = (char*)pMem->Malloc(256, "pq2");

	pq1->StrCopyFrom("this is queue content 1.");
	//strcpy(pq1, "this is queue content 1.");
	pQueue->AddLast(pq1->m_pData, strlen(pq1->m_pData));
	pQueue->AddLast("this is queue content 2.", 100);

	pQueue->PrintInside();
	//pQueue->GetAndDeleteFirst(pq2->m_pData, pQueue->GetFirstLength());
	pQueue->GetFirst(pq1);
	cout << pq1->m_pData <<endl;
	//cout << pq2->m_pData <<endl;

	pQueue->CleanAll();
	pQueue->PrintInside();
}

static void ThreadTest(void* pCallParam, MBOOL& bThreadContinue)
{
	int i = 10;
	while (i)
	{
		--i;
		cout << "ThreadTest output...\n";
		Sleep(1000);
	}	
}
void TestThreadTools(CToolsLowDebug* pDbg, CToolsThreadPool* pT)
{
	pT->ThreadPoolRegTask(ThreadTest, NULL);
	//pT->ThreadPoolRegTask(ThreadTest, NULL);
}

bool TaskTest(void* pCallParam, int& nStatus)
{
	cout << "Test Task output...\n";
	return true;
}
void TestTaskTools(CToolsTaskRun* ptask)
{
	ptask->StartTask(TaskTest, NULL, "TestTask");
	Sleep(1000);
	cout << "Test Task output: thread count = " << ptask->GetThreadCount() << endl;
	cout << "Task is running? " << ptask->IsRunning() << endl;
	ptask->PrintInfo();
	ptask->StopAll();
}

void TestLog(CToolsBaseLibrary* pbaselib)
{
	CToolsLog* plogobj = pbaselib->m_pLog;
	plogobj->m_bDebugFlag = true;
	plogobj->m_bDebug2Flag = true;
	plogobj->m_bDebug3Flag = true;
	plogobj->m_bSyslogFlag = true;

	plogobj->_XGDebug("Test _XGDebug()...\n");
	plogobj->_XGDebug2("Test _XGDebug2()...\n");
	plogobj->_XGDebug3("Test _XGDebug3()...\n");
	plogobj->_XGDebug4Bin("Test _XGDebug4()...\n", 100);
	plogobj->_XGSyslog("Test _XGSyslog()...\n");
}

void TestBaselib(CToolsBaseLibrary* pbaselib)
{
	char szFilePath[256] = {0};

	//Test Debug Tools
	cout << "=============Test Debug output start==================" << endl;
	TestDebugTools(getcwd(szFilePath,MAX_PATH), pbaselib->m_pDebug);
	cout << "=============Test Debug output end  ==================" << endl;

	cout << endl;

	cout << "=============Test MemTools output start==================" << endl;
	//Test Memory tools
	TestMemTools(pbaselib->m_pDebug, pbaselib->m_pMemPool);
	cout << "=============Test MemTools output end==================" << endl;

	cout << endl;

	cout << "=============Test TaskTools output start==================" << endl;
	//Test Task Tools
	TestTaskTools(pbaselib->m_pTaskRun);
	cout << "=============Test TaskTools output end==================" << endl;

	cout << endl;

	cout << "=============Test LogTools output start==================" << endl;
	//Test Log Tools
	TestLog(pbaselib);
	cout << "=============Test LogTools output end==================" << endl;

	cout << endl;
}








// int _tmain(int argc, _TCHAR* argv[])
// {
// 	CToolsBaseLibrary* pBaseLib;// = new CToolsBaseLibrary()
// 
// 
// 	getchar();
// 	return 0;
// }


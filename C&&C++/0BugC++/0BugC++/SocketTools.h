////////////////////////////////////////////////////////////
//							Socket工具
////////////////////////////////////////////////////////////

#ifndef __SOCKET_TOOLS_H__
#define __SOCKET_TOOLS_H__


#include "IncludeDef.h"
#include "DebugTools.h"

#define TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE	1024

//管理的最大指针个数，PC 平台一般建议10000，
//但嵌入式平台，要根据具体情况分析，一般不建议超过1024
#ifndef TOOLS_MEMORY_REGISTER_MAX
#define TOOLS_MEMORY_REGISTER_MAX 10000
#endif

#ifdef WIN32 //Windows 下定义
	#include <winsock.h>
	//定义Socket 套接字变量类型
	#define Linux_Win_SOCKET SOCKET
	//标准的Socket 关闭函数，不过，由于后文资源池接管了关闭动作，此处隐去定义
	//#define Linux_Win_CloseSocket closesocket
	//协议族命名约定
	#define Linux_Win_AF_INET AF_INET
	//非法的socket 表示值定义
	#define Linux_Win_InvalidSocket INVALID_SOCKET
	//标准socket 错误返回码
	#define Linux_Win_SocketError SOCKET_ERROR
	//setsockopt 第4 个变量类型定义
	#define Linux_Win_SetSockOptArg4UseType const char
	//getsockopt 第4 个变量类型定义
	#define Linux_Win_GetSockOptArg4UseType char
	//send recv 函数的最后一个参数类型
	#define Linux_Win_SendRecvLastArg 0
	//注意此处，所有的错误返回码定名，Windows 平台向向标准的伯克利socket 规范靠拢。
	#define EWOULDBLOCK WSAEWOULDBLOCK //10035
	#define EINPROGRESS WSAEINPROGRESS
	#define EALREADY WSAEALREADY
	#define ENOTSOCK WSAENOTSOCK
	#define EDESTADDRREQ WSAEDESTADDRREQ
	#define EMSGSIZE WSAEMSGSIZE
	#define EPROTOTYPE WSAEPROTOTYPE
	#define ENOPROTOOPT WSAENOPROTOOPT
	#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
	#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
	#define EOPNOTSUPP WSAEOPNOTSUPP
	#define EPFNOSUPPORT WSAEPFNOSUPPORT
	#define EAFNOSUPPORT WSAEAFNOSUPPORT
	#define EADDRINUSE WSAEADDRINUSE
	#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
	#define ENETDOWN WSAENETDOWN
	#define ENETUNREACH WSAENETUNREACH
	#define ENETRESET WSAENETRESET
	#define ECONNABORTED WSAECONNABORTED //10053
	#define ECONNRESET WSAECONNRESET //10054
	#define ENOBUFS WSAENOBUFS
	#define EISCONN WSAEISCONN
	#define ENOTCONN WSAENOTCONN
	#define ESHUTDOWN WSAESHUTDOWN
	#define ETOOMANYREFS WSAETOOMANYREFS
	#define ETIMEDOUT WSAETIMEDOUT
	#define ECONNREFUSED WSAECONNREFUSED
	#define ELOOP WSAELOOP
	#define EHOSTDOWN WSAEHOSTDOWN
	#define EHOSTUNREACH WSAEHOSTUNREACH
	#define EPROCLIM WSAEPROCLIM
	#define EUSERS WSAEUSERS
	#define EDQUOT WSAEDQUOT
	#define ESTALE WSAESTALE
	#define EREMOTE WSAEREMOTE
#else //Linux 下定义
	//定义Socket 套接字变量类型
	#define Linux_Win_SOCKET int
	//标准的Socket 关闭函数，不过，由于后文资源池接管了关闭动作，此处隐去定义
	//#define Linux_Win_CloseSocket close
	//协议族命名约定
	#define Linux_Win_AF_INET AF_INET
	//非法的socket 表示值定义
	#define Linux_Win_InvalidSocket -1
	//标准socket 错误返回码
	#define Linux_Win_SocketError -1
	//setsockopt 第4 个变量类型定义
	#define Linux_Win_SetSockOptArg4UseType void
	//getsockopt 第4 个变量类型定义
	#define Linux_Win_GetSockOptArg4UseType void
	//send recv 函数的最后一个参数类型
	#define Linux_Win_SendRecvLastArg MSG_NOSIGNAL
#endif



//请注意，Windows 下和Linux 下，错误的socket 表示值不一样，需要条件编译分别确定
#ifdef WIN32
#define Linux_Win_InvalidSocket INVALID_SOCKET
#else // not WIN32
#define Linux_Win_InvalidSocket -1
#endif
//判断socket 是否合法的通用函数，这个函数设置的目的是收拢所有的判断，方便以后修改
inline bool SocketIsOK(Linux_Win_SOCKET nSocket)
{
	//某些系统的socket 判断，是以0~65535 的绝对值判断，这里实现，暂时不用
	// if(0>nSocket) return false;
	// if(65535<nSocket) return false;
	//原则上，只要不等于Linux_Win_InvalidSocket 的其他整数，均可视为合法socket
	if(Linux_Win_InvalidSocket==nSocket) return false;
	return true;
} 
//真实地关闭一个socket
inline void _Linux_Win_CloseSocket(Linux_Win_SOCKET nSocket)
{
	if(!SocketIsOK(nSocket)) return;
#ifdef WIN32
	closesocket(nSocket);
#else // not WIN32
	close(nSocket);
#endif
}



/*
由于Windows 在起停socket 传输应用时，需要额外的初始化和结束代码，因此，
在开发独立的传输程序时，参考下列代码设计，在程序的开始和结束处添加相应代码
*/
#if defined(_MSC_VER)
	static WSADATA wsaData; //中间Socket 信息保存变量
	#pragma comment(lib,"wsock32") //dll 库调用准备
#else // not WIN32
#endif
inline void Linux_Win_Socket_Init() //win 32 socket 初始化代码
{ 
#ifdef WIN32
	WORD wVersionRequested;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		//输出错误信息给用户，提醒初始化失败
		TOOLS_DEBUG("Socket init fail!\n");
	}
#else // not WIN32
#endif
} 
inline void Linux_Win_Socket_Exit() //win32 socket 结束代码
{ 
#ifdef WIN32
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 )
	{
		//输出错误信息给用户，提醒版本不对
		WSACleanup();
		TOOLS_DEBUG("Socket version error!\n");
	}
#else // not WIN32
#endif
}



//核心管理数据结构
typedef struct _TOOLS_SOCKET_REGISTER_
{
	Linux_Win_SOCKET m_nSocket; //保存的socket
	char m_szInfo[TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE]; //说明文字，长度同上
} SToolsSocketRegister;

//结构体尺寸常量
const ULONG SToolsSocketRegisterSize=sizeof(SToolsSocketRegister);
//socket 注册管理类
class CSocketRegister
{ 
public:
	CSocketRegister(CToolsLowDebug* pDebug); //构造函数，传入debug 对象指针
	~CSocketRegister();
public:
	void PrintInfo(void); //信息打印函数
public:
	//注册一个socket，以及其说明文字
	void Add(Linux_Win_SOCKET s,char* szInfo=null);
	//反注册一个socket，如果内部没找到，返回false
	bool Del(Linux_Win_SOCKET s);
private:
	CToolsLowDebug* m_pDebug; //debug 对象指针
	CMutexLock m_Lock; //锁，这里同样使用普通锁
	//保存注册信息的结构体数组，大小也同内存指针注册类
	SToolsSocketRegister m_RegisterArray[TOOLS_MEMORY_REGISTER_MAX];
	//管理变量
	int m_nUseMax;
	//统计变量
	Linux_Win_SOCKET m_nMaxSocket; //注册过的最大socket，
	int m_nSocketUseCount; //在用的socket 总数
};


#endif	// __SOCKET_TOOLS_H__
////////////////////////////////////////////////////////////
//							Socket����
////////////////////////////////////////////////////////////

#ifndef __SOCKET_TOOLS_H__
#define __SOCKET_TOOLS_H__


#include "IncludeDef.h"
#include "DebugTools.h"

#define TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE	1024

//��������ָ�������PC ƽ̨һ�㽨��10000��
//��Ƕ��ʽƽ̨��Ҫ���ݾ������������һ�㲻���鳬��1024
#ifndef TOOLS_MEMORY_REGISTER_MAX
#define TOOLS_MEMORY_REGISTER_MAX 10000
#endif

#ifdef WIN32 //Windows �¶���
	#include <winsock.h>
	//����Socket �׽��ֱ�������
	#define Linux_Win_SOCKET SOCKET
	//��׼��Socket �رպ��������������ں�����Դ�ؽӹ��˹رն������˴���ȥ����
	//#define Linux_Win_CloseSocket closesocket
	//Э��������Լ��
	#define Linux_Win_AF_INET AF_INET
	//�Ƿ���socket ��ʾֵ����
	#define Linux_Win_InvalidSocket INVALID_SOCKET
	//��׼socket ���󷵻���
	#define Linux_Win_SocketError SOCKET_ERROR
	//setsockopt ��4 ���������Ͷ���
	#define Linux_Win_SetSockOptArg4UseType const char
	//getsockopt ��4 ���������Ͷ���
	#define Linux_Win_GetSockOptArg4UseType char
	//send recv ���������һ����������
	#define Linux_Win_SendRecvLastArg 0
	//ע��˴������еĴ��󷵻��붨����Windows ƽ̨�����׼�Ĳ�����socket �淶��£��
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
#else //Linux �¶���
	//����Socket �׽��ֱ�������
	#define Linux_Win_SOCKET int
	//��׼��Socket �رպ��������������ں�����Դ�ؽӹ��˹رն������˴���ȥ����
	//#define Linux_Win_CloseSocket close
	//Э��������Լ��
	#define Linux_Win_AF_INET AF_INET
	//�Ƿ���socket ��ʾֵ����
	#define Linux_Win_InvalidSocket -1
	//��׼socket ���󷵻���
	#define Linux_Win_SocketError -1
	//setsockopt ��4 ���������Ͷ���
	#define Linux_Win_SetSockOptArg4UseType void
	//getsockopt ��4 ���������Ͷ���
	#define Linux_Win_GetSockOptArg4UseType void
	//send recv ���������һ����������
	#define Linux_Win_SendRecvLastArg MSG_NOSIGNAL
#endif



//��ע�⣬Windows �º�Linux �£������socket ��ʾֵ��һ������Ҫ��������ֱ�ȷ��
#ifdef WIN32
#define Linux_Win_InvalidSocket INVALID_SOCKET
#else // not WIN32
#define Linux_Win_InvalidSocket -1
#endif
//�ж�socket �Ƿ�Ϸ���ͨ�ú���������������õ�Ŀ������£���е��жϣ������Ժ��޸�
inline bool SocketIsOK(Linux_Win_SOCKET nSocket)
{
	//ĳЩϵͳ��socket �жϣ�����0~65535 �ľ���ֵ�жϣ�����ʵ�֣���ʱ����
	// if(0>nSocket) return false;
	// if(65535<nSocket) return false;
	//ԭ���ϣ�ֻҪ������Linux_Win_InvalidSocket ������������������Ϊ�Ϸ�socket
	if(Linux_Win_InvalidSocket==nSocket) return false;
	return true;
} 
//��ʵ�عر�һ��socket
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
����Windows ����ͣsocket ����Ӧ��ʱ����Ҫ����ĳ�ʼ���ͽ������룬��ˣ�
�ڿ��������Ĵ������ʱ���ο����д�����ƣ��ڳ���Ŀ�ʼ�ͽ����������Ӧ����
*/
#if defined(_MSC_VER)
	static WSADATA wsaData; //�м�Socket ��Ϣ�������
	#pragma comment(lib,"wsock32") //dll �����׼��
#else // not WIN32
#endif
inline void Linux_Win_Socket_Init() //win 32 socket ��ʼ������
{ 
#ifdef WIN32
	WORD wVersionRequested;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		//���������Ϣ���û������ѳ�ʼ��ʧ��
		TOOLS_DEBUG("Socket init fail!\n");
	}
#else // not WIN32
#endif
} 
inline void Linux_Win_Socket_Exit() //win32 socket ��������
{ 
#ifdef WIN32
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 )
	{
		//���������Ϣ���û������Ѱ汾����
		WSACleanup();
		TOOLS_DEBUG("Socket version error!\n");
	}
#else // not WIN32
#endif
}



//���Ĺ������ݽṹ
typedef struct _TOOLS_SOCKET_REGISTER_
{
	Linux_Win_SOCKET m_nSocket; //�����socket
	char m_szInfo[TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE]; //˵�����֣�����ͬ��
} SToolsSocketRegister;

//�ṹ��ߴ糣��
const ULONG SToolsSocketRegisterSize=sizeof(SToolsSocketRegister);
//socket ע�������
class CSocketRegister
{ 
public:
	CSocketRegister(CToolsLowDebug* pDebug); //���캯��������debug ����ָ��
	~CSocketRegister();
public:
	void PrintInfo(void); //��Ϣ��ӡ����
public:
	//ע��һ��socket���Լ���˵������
	void Add(Linux_Win_SOCKET s,char* szInfo=null);
	//��ע��һ��socket������ڲ�û�ҵ�������false
	bool Del(Linux_Win_SOCKET s);
private:
	CToolsLowDebug* m_pDebug; //debug ����ָ��
	CMutexLock m_Lock; //��������ͬ��ʹ����ͨ��
	//����ע����Ϣ�Ľṹ�����飬��СҲͬ�ڴ�ָ��ע����
	SToolsSocketRegister m_RegisterArray[TOOLS_MEMORY_REGISTER_MAX];
	//�������
	int m_nUseMax;
	//ͳ�Ʊ���
	Linux_Win_SOCKET m_nMaxSocket; //ע��������socket��
	int m_nSocketUseCount; //���õ�socket ����
};


#endif	// __SOCKET_TOOLS_H__
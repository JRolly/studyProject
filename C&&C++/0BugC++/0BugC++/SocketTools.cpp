#include "SocketTools.h"

//构造函数
CSocketRegister::CSocketRegister(CToolsLowDebug* pDebug)
{
	m_pDebug=pDebug; //保存debug 对象指针
	//初始化各种变量
	m_nMaxSocket=Linux_Win_InvalidSocket;
	m_nSocketUseCount=0;
	m_nUseMax=0;
	int i=0;
	for(i=0;i<TOOLS_MEMORY_REGISTER_MAX;i++)
	{
		//同上，我们以一个结构体中保留的socket= Linux_Win_InvalidSocket
		//作为结构体未使用的标志
		m_RegisterArray[i].m_nSocket=Linux_Win_InvalidSocket;
		TOOLS_CLEAN_CHAR_BUFFER(m_RegisterArray[i].m_szInfo);
	}
}

//析构函数
CSocketRegister::~CSocketRegister()
{
	int i=0;
	m_Lock.Lock();
	{
		TOOLS_DEBUG("CSocketRegister: Max Socket Count=%d, Max Socket=%d\n",
			m_nUseMax,m_nMaxSocket); //打印关键信息
		for(i=0;i<m_nUseMax;i++)
		{
			if(SocketIsOK(m_RegisterArray[i].m_nSocket))
			{
				//退出时，如果发现有在用的socket，报警，并代为释放
				TOOLS_DEBUG("***** Socket Lost: [%d] - %s\n",
					m_RegisterArray[i].m_nSocket,
					m_RegisterArray[i].m_szInfo);
				//这是释放Socket 的语句
				_Linux_Win_CloseSocket(m_RegisterArray[i].m_nSocket);
			}
		}
	} 
	m_Lock.Unlock();
}

//Socket 注册管理模块的注册函数
void CSocketRegister::Add(Linux_Win_SOCKET s,char* szInfo)
{
	int i=0;
	m_Lock.Lock(); //加锁
	{
		//统计行为，统计最大的socket 值供查阅
		if(!SocketIsOK(m_nMaxSocket)) m_nMaxSocket=s;
		else if(s>m_nMaxSocket) m_nMaxSocket=s;
		//先试图修改，遍历使用区域
		for(i=0;i<m_nUseMax;i++)
		{
			if(m_RegisterArray[i].m_nSocket==s)
			{
				if(szInfo) //拷贝说明文字
					SafeStrcpy(m_RegisterArray[i].m_szInfo,
					szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
				//注意，修改不是添加，因此，这里的socket 使用统计不增加
				//m_nSocketUseCount++;
				goto CSocketRegister_Add_End_Process;
			}
		}
		//再试图插入
		for(i=0;i<m_nUseMax;i++)
		{
			if(!SocketIsOK(m_RegisterArray[i].m_nSocket))
			{
				m_RegisterArray[i].m_nSocket=s;
				if(szInfo) //拷贝说明文字
					SafeStrcpy(m_RegisterArray[i].m_szInfo,
					szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
				//这是实实在在的添加到空区，因此，统计变量+1
				m_nSocketUseCount++;
				goto CSocketRegister_Add_End_Process;
			}
		} 
		//最后无空区可以使用呢，试图追加到最后
		if(TOOLS_MEMORY_REGISTER_MAX>m_nUseMax)
		{
			m_RegisterArray[m_nUseMax].m_nSocket=s;
			if(szInfo) //拷贝说明文字
				SafeStrcpy(m_RegisterArray[m_nUseMax].m_szInfo,
				szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
			//使用区域指针+1
			m_nUseMax++;
			//统计变量+1
			m_nSocketUseCount++;
		} 
		//注册区满了，报警，并发的socket 数量超限，程序员有必要扩大缓冲区
		else 
			TOOLS_DEBUG("CSocketRegister::Add(): Pool is full!\n");
	}
CSocketRegister_Add_End_Process:
	m_Lock.Unlock(); //解锁
}

//反注册函数，即将一个socket 的注册信息，从内部管理数据区删除
bool CSocketRegister::Del(Linux_Win_SOCKET s)
{
	bool bRet=false;
	int i=0;
	m_Lock.Lock(); //加锁
	{
		for(i=0;i<m_nUseMax;i++)
		{
			//遍历使用区，检索socket
			if(m_RegisterArray[i].m_nSocket==s)
			{
				//注意清空动作，把socket 置为Linux_Win_InvalidSocket
				//这项，下次Add 可以重复使用该空区
				m_RegisterArray[i].m_nSocket=Linux_Win_InvalidSocket;
				TOOLS_CLEAN_CHAR_BUFFER(m_RegisterArray[i].m_szInfo);
				//修订统计变量，并发socket 数量-1
				m_nSocketUseCount--;
				bRet=true;
				goto CSocketRegister_Del_End_Process;
			}
		}
	}
CSocketRegister_Del_End_Process:
	m_Lock.Unlock(); //解锁
	return bRet;
}

//内部信息打印函数
void CSocketRegister::PrintInfo(void)
{
	m_Lock.Lock(); //加锁
	{
		TOOLS_PRINTF("socket pool: %d / %d, biggest=%d\n",
			m_nSocketUseCount, //并发的socket 数量统计
			m_nUseMax+1, //内存结构体数组使用量标示
			m_nMaxSocket); //统计到的最大socket
	} 
	m_Lock.Unlock(); //解锁
}




#include "SocketTools.h"

//���캯��
CSocketRegister::CSocketRegister(CToolsLowDebug* pDebug)
{
	m_pDebug=pDebug; //����debug ����ָ��
	//��ʼ�����ֱ���
	m_nMaxSocket=Linux_Win_InvalidSocket;
	m_nSocketUseCount=0;
	m_nUseMax=0;
	int i=0;
	for(i=0;i<TOOLS_MEMORY_REGISTER_MAX;i++)
	{
		//ͬ�ϣ�������һ���ṹ���б�����socket= Linux_Win_InvalidSocket
		//��Ϊ�ṹ��δʹ�õı�־
		m_RegisterArray[i].m_nSocket=Linux_Win_InvalidSocket;
		TOOLS_CLEAN_CHAR_BUFFER(m_RegisterArray[i].m_szInfo);
	}
}

//��������
CSocketRegister::~CSocketRegister()
{
	int i=0;
	m_Lock.Lock();
	{
		TOOLS_DEBUG("CSocketRegister: Max Socket Count=%d, Max Socket=%d\n",
			m_nUseMax,m_nMaxSocket); //��ӡ�ؼ���Ϣ
		for(i=0;i<m_nUseMax;i++)
		{
			if(SocketIsOK(m_RegisterArray[i].m_nSocket))
			{
				//�˳�ʱ��������������õ�socket������������Ϊ�ͷ�
				TOOLS_DEBUG("***** Socket Lost: [%d] - %s\n",
					m_RegisterArray[i].m_nSocket,
					m_RegisterArray[i].m_szInfo);
				//�����ͷ�Socket �����
				_Linux_Win_CloseSocket(m_RegisterArray[i].m_nSocket);
			}
		}
	} 
	m_Lock.Unlock();
}

//Socket ע�����ģ���ע�ắ��
void CSocketRegister::Add(Linux_Win_SOCKET s,char* szInfo)
{
	int i=0;
	m_Lock.Lock(); //����
	{
		//ͳ����Ϊ��ͳ������socket ֵ������
		if(!SocketIsOK(m_nMaxSocket)) m_nMaxSocket=s;
		else if(s>m_nMaxSocket) m_nMaxSocket=s;
		//����ͼ�޸ģ�����ʹ������
		for(i=0;i<m_nUseMax;i++)
		{
			if(m_RegisterArray[i].m_nSocket==s)
			{
				if(szInfo) //����˵������
					SafeStrcpy(m_RegisterArray[i].m_szInfo,
					szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
				//ע�⣬�޸Ĳ�����ӣ���ˣ������socket ʹ��ͳ�Ʋ�����
				//m_nSocketUseCount++;
				goto CSocketRegister_Add_End_Process;
			}
		}
		//����ͼ����
		for(i=0;i<m_nUseMax;i++)
		{
			if(!SocketIsOK(m_RegisterArray[i].m_nSocket))
			{
				m_RegisterArray[i].m_nSocket=s;
				if(szInfo) //����˵������
					SafeStrcpy(m_RegisterArray[i].m_szInfo,
					szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
				//����ʵʵ���ڵ���ӵ���������ˣ�ͳ�Ʊ���+1
				m_nSocketUseCount++;
				goto CSocketRegister_Add_End_Process;
			}
		} 
		//����޿�������ʹ���أ���ͼ׷�ӵ����
		if(TOOLS_MEMORY_REGISTER_MAX>m_nUseMax)
		{
			m_RegisterArray[m_nUseMax].m_nSocket=s;
			if(szInfo) //����˵������
				SafeStrcpy(m_RegisterArray[m_nUseMax].m_szInfo,
				szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
			//ʹ������ָ��+1
			m_nUseMax++;
			//ͳ�Ʊ���+1
			m_nSocketUseCount++;
		} 
		//ע�������ˣ�������������socket �������ޣ�����Ա�б�Ҫ���󻺳���
		else 
			TOOLS_DEBUG("CSocketRegister::Add(): Pool is full!\n");
	}
CSocketRegister_Add_End_Process:
	m_Lock.Unlock(); //����
}

//��ע�ắ��������һ��socket ��ע����Ϣ�����ڲ�����������ɾ��
bool CSocketRegister::Del(Linux_Win_SOCKET s)
{
	bool bRet=false;
	int i=0;
	m_Lock.Lock(); //����
	{
		for(i=0;i<m_nUseMax;i++)
		{
			//����ʹ����������socket
			if(m_RegisterArray[i].m_nSocket==s)
			{
				//ע����ն�������socket ��ΪLinux_Win_InvalidSocket
				//����´�Add �����ظ�ʹ�øÿ���
				m_RegisterArray[i].m_nSocket=Linux_Win_InvalidSocket;
				TOOLS_CLEAN_CHAR_BUFFER(m_RegisterArray[i].m_szInfo);
				//�޶�ͳ�Ʊ���������socket ����-1
				m_nSocketUseCount--;
				bRet=true;
				goto CSocketRegister_Del_End_Process;
			}
		}
	}
CSocketRegister_Del_End_Process:
	m_Lock.Unlock(); //����
	return bRet;
}

//�ڲ���Ϣ��ӡ����
void CSocketRegister::PrintInfo(void)
{
	m_Lock.Lock(); //����
	{
		TOOLS_PRINTF("socket pool: %d / %d, biggest=%d\n",
			m_nSocketUseCount, //������socket ����ͳ��
			m_nUseMax+1, //�ڴ�ṹ������ʹ������ʾ
			m_nMaxSocket); //ͳ�Ƶ������socket
	} 
	m_Lock.Unlock(); //����
}




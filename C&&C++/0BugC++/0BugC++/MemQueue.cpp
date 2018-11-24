#include "MemQueue.h"


//���캯������ʼ�����б���
CToolsMemoryQueue::CToolsMemoryQueue(
	CToolsLowDebug* pDebug,
	CToolsMemoryPoolWithLock* pMemPool,
	char* szAppName,
	int nMaxToken)
{
	m_nMaxToken=nMaxToken; //�������Token ����
	m_pLast=null; //ע�⣬�˴���������m_pLast ������Ϊnull
	m_pDebug=pDebug; //����debug ����ָ��
	m_pMemPool=pMemPool; //�����ڴ��ָ��
	SafeStrcpy(m_szAppName,szAppName, //����AppName
		TOOLS_APPLICATION_NAME_SIZE);
	m_pHead=null; //ע�⣬m_pHead ������Ϊnull����ʾ��Token
	m_nTokenCount=0; //Token ������������Ϊ0
}
//����������������е�Token���ͷ�������ڴ�
CToolsMemoryQueue::~CToolsMemoryQueue()
{
	if(m_pHead)
	{
		DeleteATokenAndHisNext(m_pHead);//�˴��ݹ��ͷ�
		m_pHead=null;
	}
}

bool CToolsMemoryQueue::ICanWork(void)
{
	if(!m_pDebug) return false; //���debug ����ָ��
	if(!m_pMemPool) return false; //����ڴ��ָ��
	return true;
}

void CToolsMemoryQueue::CleanAll(void)
{
	if(!ICanWork()) return; //���������
	while(DeleteFirst()){} //ѭ��ɾ����һ������ֱ������Ϊ��
	//ע�⣬�����DeleteFirst ����ɾ�����
}

int CToolsMemoryQueue::GetFirstLength(void)
{
	int nRet=0;
	if(m_pHead) //���ICanWork Ϊ��m_pHead ��ȻΪnull
	{
		nRet=m_pHead->m_nDataLength; //ȡ����һ��Token �ĳ���
	}
	return nRet;
}

//˽�к�������ӡĳһ��ָ����Token�����ҵݹ�������е�Token
void CToolsMemoryQueue::PrintAToken(SToolsQueueTokenHead* pToken)
{
	if(!pToken) return; //��������ƣ��ݹ������־
	TOOLS_PRINTF("Queue Token: pToken:%p, \
					 Buffer=%p, Length=%d, m_pNext=%p\n",
					 pToken, //Token ָ��
					 pToken->m_pBuffer, //���ݻ�����ָ��
					 pToken->m_nDataLength, //���ݳ���
					 pToken->m_pNext); //��һToken ָ��
	if(pToken->m_pBuffer) //�Զ����Ʒ�ʽ��ʽ�����ҵ������
		dbg_bin(pToken->m_pBuffer,pToken->m_nDataLength);
	if(pToken->m_pNext) //�ݹ�
		PrintAToken(pToken->m_pNext);
}

//��ӡ���е�Token ���ݣ����к������
void CToolsMemoryQueue::PrintInside(void)
{
	if(!ICanWork()) return; //���������
	//������йؼ���Ϣ
	TOOLS_PRINTF("Queue: Token Count=%d, Head=0x%p, Last=0x%p\n",
		m_nTokenCount, //Token ����
		m_pHead, //����ͷToken ָ��
		m_pLast); //����βToken ָ��
	if(m_pHead) //�Ӷ���ͷ��ʼ�ݹ�
		PrintAToken(m_pHead);
}

//���ɾ���ɹ��������棬���򷵻ؼ�
bool CToolsMemoryQueue::DeleteATokenAndHisNext(
	SToolsQueueTokenHead* pToken) //��C ���ã������Token ָ��
{
	bool bRet=false; //׼������ֵ
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_DeleteATokenAndHisNext_End_Process;
	if(pToken->m_pNext) //ע�⣬�����m_pNext���ݹ�ɾ��
	{
		DeleteATokenAndHisNext(pToken->m_pNext);
		pToken->m_pNext=null;
	} 
	if(pToken->m_pBuffer) //��ʼɾ��������
	{
		m_pMemPool->Free(pToken->m_pBuffer);//���ڴ���ͷ����ݻ�����
		pToken->m_nDataLength=0; //���б�������ֵ
		pToken->m_pBuffer=null;
	} 
	m_pMemPool->Free((void*)pToken); //���ڴ���ͷ�Token ͷ�ṹ�建����
	m_nTokenCount--; //Token �ܼ�����-1
	bRet=true;
CToolsMemoryQueue_DeleteATokenAndHisNext_End_Process:
	m_pLast=null; //ɾ����������������β�������仯
	//��������ʧЧ�������Ҫ���
	return bRet;
}

//����һ��Token ͷ�ڴ����򣬲���ʼ��������Token ָ��
SToolsQueueTokenHead* CToolsMemoryQueue::GetAToken(void)
{
	SToolsQueueTokenHead* pToken=null; //׼������ֵ
	char* pTokenBuffer=null; //׼����ʱָ��
	char szNameBuffer[256]; //׼��˵�����ֻ�����
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_GetAToken_End_Process;
	//��ʽ��˵�����֣�ע�������õ���AppName
	SafePrintf(szNameBuffer,256,"%s::Token_Head",m_szAppName);
	//��ʼ����Token ͷ�ڴ��
	pTokenBuffer=(char*)m_pMemPool->Malloc( //��ע���˵�����ֵ�ʹ��
		SToolsQueueTokenHeadSize,szNameBuffer);
	if(!pTokenBuffer)
	{ //����ʧ�ܣ�����null
		TOOLS_DEBUG("%s::GetAToken(): ma lloc new token fail!\n",m_szAppName);
		goto CToolsMemoryQueue_GetAToken_End_Process;
	} 
	//ǿ��ָ������ת���������뵽�Ķ����ƻ�����ָ��ת����Token ͷ�ṹ��ָ��
	pToken=(SToolsQueueTokenHead*)pTokenBuffer;
	pToken->m_nDataLength=0; //��ʼ�����̣�����ֵ
	pToken->m_pNext=null;
	pToken->m_pBuffer=null;
	m_nTokenCount++; //Token ����+1
CToolsMemoryQueue_GetAToken_End_Process:
	return pToken;
}

//�����ݱ��浽һ��Token�������Token �Ѿ��������ݣ�
//��������˳������Ѱ�ң�ֱ���ҵ�һ���յ�Token�������ݷ������С�
//����ɹ����������ݳ��ȣ����ʧ�ܣ�����0
int CToolsMemoryQueue::AddLast2ThisToken(
	SToolsQueueTokenHead* pToken, //��Ҫ�����Token ͷָ��
	char* szData, //��Ҫ�洢���ݵ�ָ��
	int nDataLength) //��Ҫ�洢�����ݵĳ���
{
	int nRet=0; //׼������ֵ
	char szNameBuffer[256]; //׼��˵�����ֻ�����
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
	if(!pToken->m_pBuffer)
	{
		//�����Token δ������Ч���ݣ��򱣴浽�Լ���
		SafePrintf(szNameBuffer,256, //��ʽ���ڴ��˵������
			"%s::pToken->m_pBuffer",
			m_szAppName);
		pToken->m_pBuffer=(char*)m_pMemPool->Malloc( //���ڴ�������ڴ��
			nDataLength,szNameBuffer);
		if(!pToken->m_pBuffer)
		{ //����ʧ�ܣ�����
			TOOLS_DEBUG("%s::AddLast2ThisToken(): \
					   ma lloc pToken->m_pBuffer fail!\n",
					   m_szAppName);
			goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
		} 
		memcpy(pToken->m_pBuffer,szData,nDataLength); //����ҵ�����ݵ��ڴ��
		pToken->m_nDataLength=nDataLength; //���Token ͷ�еĹ�����Ϣ
		nRet=nDataLength; //������ֵ��ֵ
		m_pLast=pToken; //�����������(m_pLast ά��)
		goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
	}
	else
	{
		//�������¼�
		if(!pToken->m_pNext)
		{
			//���ָ���¼ҵ���ָ��Ϊ�գ�������GetAToken ����һ��ͷ�ҽ�
			pToken->m_pNext=GetAToken();
			if(!pToken->m_pNext)
			{ //����ʧ�ܱ���
				TOOLS_DEBUG("%s::AddLast2ThisToken(): ma lloc \
						   pToken->m_pNext fail!\n",
						   m_szAppName);
				goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
			}
		} 
		if(pToken->m_pNext) //�ݹ����
			nRet=AddLast2ThisToken(pToken->m_pNext,szData,nDataLength);
	}
CToolsMemoryQueue_AddLast2ThisToken_End_Process:
	return nRet;
}

//������ӵ����ݳ��ȣ�ʧ�ܷ���0
int CToolsMemoryQueue::AddLast(
	char* szData, //��ӵ�����ָ��
	int nDataLength, //���ݳ���
	int nLimit) //���Ԫ���ƣ�-1 ��ʾ������
{
	int nRet=0; //׼������ֵ����ֵΪ0
	if(!ICanWork()) //��������ƣ����������ϣ�ֱ�ӷ���0
		goto CToolsMemoryQueue_AddLast_End_Process;
	if(0>=nLimit) //Ӧ������ֵ
	{ //����������
		if(m_nMaxToken<=m_nTokenCount) //������ʱ����m_nMaxToken ��Ϊ�߽�����
			goto CToolsMemoryQueue_AddLast_End_Process;
	} 
	else
	{
		//����������
		if(nLimit<=m_nTokenCount) //�����nLimit����ʹ�������������
			goto CToolsMemoryQueue_AddLast_End_Process;
	} 
	if(!m_pHead)
	{
		m_pHead=GetAToken(); //������ͷ��һ�γ�ʼ��
		if(!m_pHead)
		{
			TOOLS_DEBUG("%s::AddLast(): ma lloc m_pHead fail!\n",
				m_szAppName);
			goto CToolsMemoryQueue_AddLast_End_Process;
		}
	}
	if(m_pLast) //�������ӿ�ʼ�����ã������ֵ��ֱ������
	{
		nRet=AddLast2ThisToken(m_pLast,szData,nDataLength);
	} 
	else if(m_pHead) //�������������ֵ������ͳģʽ����������
	{
		nRet=AddLast2ThisToken(m_pHead,szData,nDataLength);
	}
CToolsMemoryQueue_AddLast_End_Process:
	return nRet;
}

//�����ͨ������������ȡ��Ӧ�ò㱣֤����������
//������ȡ���ݵ���ʵ���ȣ���һ�����ϲ㻺�����Ĵ�С��
int CToolsMemoryQueue::GetFirst(char* szBuffer,int nBufferSize)
{
	int nRet=0; //׼������ֵ����
	//�˴���ʼ���������
	if(!ICanWork())
		goto CToolsMemoryQueue_GetFirst_End_Process;
	if(!m_pHead) //��������Ƿ�������
		goto CToolsMemoryQueue_GetFirst_End_Process;
	if(!m_pHead->m_pBuffer) //����һ��Token �Ƿ�������
	{
		TOOLS_DEBUG("%s::GetFirst(): m_pHead->m_pBuffer=null\n",
			m_szAppName);
		goto CToolsMemoryQueue_GetFirst_End_Process;
	} 
	if(m_pHead->m_nDataLength>nBufferSize) //�������Ļ������Ƿ��㹻
	{
		TOOLS_DEBUG("%s::GetFirst(): m_pHead->m_nDataLength > nBufferSize\n",
			m_szAppName);
		goto CToolsMemoryQueue_GetFirst_End_Process;
	}
	memcpy(szBuffer,m_pHead->m_pBuffer,m_pHead->m_nDataLength); //��������
		nRet=m_pHead->m_nDataLength; //����ֵ��ֵ
CToolsMemoryQueue_GetFirst_End_Process:
	return nRet;
}
//�������Buffer ��������ȡ����
int CToolsMemoryQueue::GetFirst(CToolsBuffer* pBuffer)
{
	if(!ICanWork()) return 0; //���������
	if(!pBuffer) return 0;
	//������һ������ɹ���
	return pBuffer->BinCopyFrom(m_pHead->m_pBuffer,m_pHead->m_nDataLength);
}

//ɾ����һ��Token���п���ʧ�ܣ���Ϊ���п���Ϊ�գ�ʧ�ܷ��ؼ٣��ɹ�������
bool CToolsMemoryQueue::DeleteFirst(void)
{
	bool bRet=false; //׼������ֵ
	SToolsQueueTokenHead* pSecond=null; //׼��ָ��ڶ�Token ����ʱָ��
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_DeleteFirst_End_Process;
	if(!m_pHead)
		goto CToolsMemoryQueue_DeleteFirst_End_Process;
	//ע�⣬����ȡFirst �б�����Socond ָ�룬���м䱣��
	pSecond=m_pHead->m_pNext;
	//m_pHead ��m_pNext ��Ϊ��ֵ�����Ǹ������������Ԫ�ص����ӹ�ϵ
	m_pHead->m_pNext=null;
	//Ȼ�����DeleteATokenAndHisNext ���ɾ������������ĸ��ѣ���˲���Ӱ������Token
	bRet=DeleteATokenAndHisNext(m_pHead);
	if(bRet)
	{
		m_pHead=pSecond; //���¸�m_pHead �ҽӵڶ�Token
		//��ɶ�ԭ��First �ļ�������
		//��ʱ��ԭ��Second ��ΪFirst
		if(!m_pHead) //������һ��������
			m_pLast=null; //�������ɾ���Ѹö���ɾ�գ�
		//��Ҫ����������ӣ������´β���ʧ��
	}
	else
	{ //���ɾ��ʧ�ܣ��������һ�㲻̫���ܣ����ڱ���������������ʵִ�У�
		//�����лָ�ԭ״�����벻�����ڱ������ڲ���ɱ��������ڴ�й©������ӡ����
		TOOLS_DEBUG("%s::DeleteFirst(): delete m_pHead fail!\n",
			m_szAppName);
		m_pHead->m_pNext=pSecond; //ɾ��ʧ�ܣ����ûָ���ȥ
	}
CToolsMemoryQueue_DeleteFirst_End_Process:
	return bRet;
}

int CToolsMemoryQueue::GetAndDeleteFirst(char* szBuffer,int nBufferSize)
{
	int nRet=GetFirst(szBuffer,nBufferSize);
	if(nRet) DeleteFirst();
	return nRet;
} 
int CToolsMemoryQueue::GetAndDeleteFirst(CToolsBuffer* pBuffer)
{
	int nRet=GetFirst(pBuffer);
	if(nRet) DeleteFirst();
	return nRet;
}


//���ص����������ܳ��ȣ�����ע�⣬����PopBuffer ��AllBytes��������ҵ�����ݳ��Ⱥ�
int CToolsMemoryQueue::PopFromFirst4ToolsPopBuffer(
	CToolsPopBuffer* pPopBuffer) //�贫��PopBuffer ָ��
{
	int nRet=0; //׼������ֵ����
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	if(!m_pHead)
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	if(!m_pHead->m_pBuffer) //��Ҳ�Ƿ�������ƣ�����First �Ƿ�������
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): \
				   m_pHead->m_pBuffer=null\n",
				   m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(!m_pHead->m_nDataLength) //��������ƣ�����First ���ݳߴ��Ƿ�Ϸ�
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): \
				   m_pHead->m_nDataLength=0\n",
				   m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(!pPopBuffer) //��������PopBuffer �Ƿ�Ϸ�
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): pPopBuffer=null\n",
			m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	}
	//û��ʹ��GetAndDeleteFirst ֮��ĺ���������ֱ�ӷ��ʽṹ���ڲ�����
	//����Ԥ�����PopBuffer ���ˣ������������ݲ��ô�������Ҳ������ν�Ķ�̬�ڴ����
	nRet=pPopBuffer->AddLast(m_pHead->m_pBuffer,m_pHead->m_nDataLength);
	if(m_pHead->m_nDataLength!=nRet)
	{
		//����buffer װ����
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(!DeleteFirst()) //ɾ��First
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): DeleteFirst fail\n",
			m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(m_pHead) //ע��˴��ĵݹ��߼����������µ�
		nRet+=PopFromFirst4ToolsPopBuffer(pPopBuffer);
CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process:
	return nRet;
}

//����ͨ����������PopBuffer ��ʽ�������
int CToolsMemoryQueue::PopFromFirst(char* szBuffer,int nBufferSize)
{
	int nCopyBytes=0; //׼������ֵ
	//׼��һ��PopBuffer ����ע�⣬ճ�����á�
	CToolsPopBuffer PopBuffer(szBuffer,nBufferSize);
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_PopFromFirst_End_Process;
	if(m_pHead)
	{ //������һ����ʵ�ִ��
		nCopyBytes=PopFromFirst4ToolsPopBuffer(&PopBuffer);
		if(nCopyBytes) //������������ݣ����ݳ���!=0��
			//ȡPopBuffer ��AllBytes ��Ϊ����ֵ
			nCopyBytes=PopBuffer.GetAllBytes();//�����ʵ����Ҫ���͵��ֽ���
	}
CToolsMemoryQueue_PopFromFirst_End_Process:
	return nCopyBytes;
}

//���ܵ���һ��PopBuffer ��ʽ����������飬����MemQueue �Ķ���ĩβ
//��������������ֽڳ�����ʧ�ܷ���0
int CToolsMemoryQueue::Push2Last(char* szData,int nDataLength)
{
	int nRet=0;
	CToolsPopBuffer PopBuffer(szData,nDataLength,false); //�˴�ճ��
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_Push2Last_End_Process;
	//��ʼ����PopBuffer �Ĺ��ܣ�ʵ�ֱ���ѭ��
	//��ע��ص�������this ָ�����
	PopBuffer.MoveAllData(PushDataCallback,this);
CToolsMemoryQueue_Push2Last_End_Process:
	return nRet;
}

//�ص�����������bool ֵ���������false������ѭ�����˳���������ܻᶪʧ��
bool CToolsMemoryQueue::PushDataCallback(
	char* szData, //�������������ַ
	int nDataLength, //�������ݳ���
	void* pCallParam) //�����Ĳ���ָ�룬����ǰ���this
{
	//���ߵ�ϰ�ߣ�һ�����ڻص�����������this ָ����Ϊ͸������
	//�ڻص������ڲ���һ���֮ΪpThis������������ͨ��Ա������this
	//�ص�����һ���룬��һ���¾���ǿ��ָ������ת��������pThis��������á�
	CToolsMemoryQueue* pThis=
		(CToolsMemoryQueue*)pCallParam;
	//�˴�Ϊ����ʵ����pThis ָ�����this����ˣ����õ��Ǳ������AddLast
	int nRet=pThis->AddLast(szData,nDataLength);
	//�ɹ�������thre������������ֱ�����ݱ�������
	if(nDataLength==nRet) return true;
	else
	{ //ʧ�ܣ������Ƕ������ˣ�����false����ֹ������
		/*pThis->*/TOOLS_DEBUG("%s::PushDataCallback(): I am full!\n",
			pThis->m_szAppName);
		return false;
	}
}

//��ָ��Token ������д���ļ�
void CToolsMemoryQueue::WriteAToken2File(
	SToolsQueueTokenHead* pToken, //ָ����Token ָ��
	FILE* fp) //ָ�����ļ�ָ��
{
	if(!ICanWork()) return; //���������
	if(!fp) return;
	if(!pToken) return;
	if(!pToken->m_pBuffer) return;
	if(!pToken->m_nDataLength) return;
	//д����̣����ڴ���д�룬ͨ�������ڷ����������˳��ڼ䣬���Ѿ������ݱ�������Ŭ��
	//��ʱ����д���ٳ���bug��û���κΰ취�ٱ������ݣ�ֻ�ܶ�ʧ����
	//��ˣ��˴�������У�飬�������д��ʧ�ܣ�����ʧ����
	//��д��ÿ��Token �����ݳ���
	fwrite((void*)&(pToken->m_nDataLength),sizeof(int),1,fp);
	//��д��ÿ��Token ��ʵ������
	fwrite((void*)pToken->m_pBuffer,sizeof(char),pToken->m_nDataLength,fp);
	if(pToken->m_pNext) //�ݹ鵽��һToken
		WriteAToken2File(pToken->m_pNext,fp);
}

//���ǹ��з�����ں���
void CToolsMemoryQueue::Write2File(char* szFileName)//������ļ���
{
	FILE* fp=null;
	if(!ICanWork()) return; //���������
	if(!m_pHead) return;
	if(!GetTokenCount()) return; //�������Ϊ�գ�ֱ�ӷ���
	fp=fopen(szFileName,"wb"); //���ļ�
	if(fp)
	{
		//���ȣ������п�����Ϣд����̣��Ա����ʱֱ��ʹ��
		fwrite((void*)&m_nTokenCount,sizeof(int),1,fp);
		//��ʼ���������ݹ麯������ʼ��Token д��
		WriteAToken2File(m_pHead,fp);
		fclose(fp); //�ر��ļ�
	}
}

//��һ������Dump �ļ��ж������ݣ����ض����Token ����
int CToolsMemoryQueue::ReadFromFile(char* szFileName)
{
	FILE* fp=null;
	int n=0;
	int i=0;
	int nReadTokenCount=0;
	int nDataLength=0;
	char* pTempBuffer=null;
	char szNameBuffer[256];
	if(!ICanWork()) //���������
		goto CToolsMemoryQueue_ReadFromFile_End_Process;
	SafePrintf(szNameBuffer,256, //�����ڴ�����˵������
		"%s::ReadFromFile::pTempBuffer",m_szAppName);
	//������ʱ��������������ʱ��������Ҫ��ѭ���ж��ReMalloc����ˣ���ʼֻ����1Byte ����
	pTempBuffer=(char*)m_pMemPool->Malloc(1,szNameBuffer);
	fp=fopen(szFileName,"rb"); //���ļ�
	if(!fp) //ʧ������ת����
		goto CToolsMemoryQueue_ReadFromFile_End_Process;
	//������п���ͷ����TokenCount ��Ϣ
	n=fread((void*)&nReadTokenCount,sizeof(int),1,fp);
	if(1>n)
	{
		TOOLS_DEBUG("%s::ReadFromFile(): read token count fail!\n",m_szAppName);
		goto CToolsMemoryQueue_ReadFromFile_End_Process;
	}
	for(i=0;i<nReadTokenCount;i++) //��ʼ��һ��������Token
	{
		//���ȶ�����ǰToken �����ݳ���
		n=fread((void*)&(nDataLength),sizeof(int),1,fp);
		if(1>n)
		{
			TOOLS_DEBUG("%s::ReadFromFile(): %d / %d, read data length fail!\n",
				m_szAppName,i,nReadTokenCount);
			goto CToolsMemoryQueue_ReadFromFile_End_Process;
		} 
		if(0>nDataLength)
		{
			TOOLS_DEBUG("%s::ReadFromFile(): %d / %d, nDataLength=%d < 0!\n",
				m_szAppName,i,nReadTokenCount,nDataLength);
			goto CToolsMemoryQueue_ReadFromFile_End_Process;
		} 
		//����ReMalloc�����ݶ����nDataLength ���·��仺�������Ա��������
		pTempBuffer=(char*)m_pMemPool->ReMalloc(
		pTempBuffer, //ԭ�е���ʱ��������ַ
		nDataLength, //�µ����ݳ���
		false); //����������������ϱ�����
		//������追��������
		if(!pTempBuffer)
		{
			TOOLS_DEBUG("%s::ReadFromFile(): rema lloc pTempBuffer fail!\n",
				m_szAppName);
			goto CToolsMemoryQueue_ReadFromFile_End_Process;
		} 
		//׼���������ɹ�����ʼ�����Token ����
		n=fread((void*)pTempBuffer,sizeof(char),nDataLength,fp);
		if(nDataLength>n)
		{
			TOOLS_DEBUG("%s::ReadFromFile(): read data fail!\n",m_szAppName);
			goto CToolsMemoryQueue_ReadFromFile_End_Process;
		} 
		//����ɹ���AddLast ��ӵ����
		if(!AddLast(pTempBuffer,nDataLength)) break;
	}
CToolsMemoryQueue_ReadFromFile_End_Process: //������ת��ǩ
	if(pTempBuffer) //�����ʱ������
	{
		m_pMemPool->Free(pTempBuffer);
		pTempBuffer=null;
	} 
	if(fp) //�ر��ļ�
	{
		fclose(fp);
		fp=null;
	} 
	return nReadTokenCount; //���ض����Token ����
}



/////////////////////////////////////
//MemQueue ���̰߳�ȫ��װ��

//���캯������ע�⣬������MemQueue ��ȫһ��
CToolsMemoryQueueWithLock::CToolsMemoryQueueWithLock(
	CToolsLowDebug* pDebug,
	CToolsMemoryPoolWithLock* pMemPool,
	char* szAppName,
	int nMaxToken)
{
	//����AppName
	SafeStrcpy(m_szAppName,szAppName,TOOLS_APPLICATION_NAME_SIZE);
	m_pMemPool=pMemPool; //�����ڴ��ָ�룬��������Ҫ��
	m_pQueue=new CToolsMemoryQueue(pDebug, //ʵ������װ����
		pMemPool,m_szAppName,nMaxToken);
	if(m_pQueue)
	{
		char szNameBuffer[256];
		//���ʵ�����ɹ�������ͼ���ڴ��ע��������ʵ��ָ�����
		//ע��ǰ��������AppName ����˵������
		SafePrintf(szNameBuffer,256,"%s::m_pQueue",m_szAppName);
		m_pMemPool->Register(m_pQueue,szNameBuffer);
	}
}

//�����������ݻٷ�װ����
CToolsMemoryQueueWithLock::~CToolsMemoryQueueWithLock()
{
	m_Lock.EnableWrite(); //�˴��Ǵ�д���������ʹ��д��
	{
		if(m_pQueue)
		{
			m_pMemPool->UnRegister(m_pQueue); //�ⲿ��ע�����Ҫ�������ڴ�ر���
			delete m_pQueue; //�ݻٶ���
			m_pQueue=null; //ϰ�ߣ������ݻٺ���������ֵ
		}
	} 
	m_Lock.DisableWrite();
}

bool CToolsMemoryQueueWithLock::ICanWork(void)
{
	if(!m_pMemPool) return false;
	if(!m_pQueue) return false;
	bool bRet=false;
	m_Lock.AddRead();
	{
		bRet=m_pQueue->ICanWork();
	} 
	m_Lock.DecRead();
	return bRet;
}

int CToolsMemoryQueueWithLock::GetFirst(CToolsBuffer* pBuffer)
{
	int nRet=0;
	m_Lock.AddRead();
	{
		nRet=m_pQueue->GetFirst(pBuffer);
	}
	m_Lock.DecRead();
	return nRet;
}

int CToolsMemoryQueueWithLock::GetFirst(char* szBuffer,int nBufferSize)
{
	int nRet=0;
	m_Lock.AddRead();
	{
		nRet=m_pQueue->GetFirst(szBuffer,nBufferSize);
	}
	m_Lock.DecRead();
	return nRet;
}

int CToolsMemoryQueueWithLock::GetFirstLength(void)
{
	int nRet=0;
	m_Lock.AddRead();
	{
		nRet=m_pQueue->GetFirstLength();
	} 
	m_Lock.DecRead();
	return nRet;
}

int CToolsMemoryQueueWithLock::GetTokenCount(void)
{
	int nRet=0;
	m_Lock.AddRead();
	{
		nRet=m_pQueue->GetTokenCount();
	}
	m_Lock.DecRead();
	return nRet;
}

void CToolsMemoryQueueWithLock::Write2File(char* szFileName)
{
	m_Lock.AddRead();
	{
		m_pQueue->Write2File(szFileName);
	} 
	m_Lock.DecRead();
}

void CToolsMemoryQueueWithLock::PrintInside(void)
{
	m_Lock.AddRead();
	{
		m_pQueue->PrintInside();
	} 
	m_Lock.DecRead();
}

int CToolsMemoryQueueWithLock::AddLast(char* szData,int nDataLength)
{
	int nRet=0;
	m_Lock.EnableWrite();
	{
		nRet=m_pQueue->AddLast(szData,nDataLength);
	} 
	m_Lock.DisableWrite();
	return nRet;
}

bool CToolsMemoryQueueWithLock::DeleteFirst(void)
{
	bool bRet=0;
	m_Lock.EnableWrite();
	{
		bRet=m_pQueue->DeleteFirst();
	} 
	m_Lock.DisableWrite();
	return bRet;
} 
int CToolsMemoryQueueWithLock::GetAndDeleteFirst(
	char* szBuffer,
	int nBufferSize)
{
	int nRet=0;
	m_Lock.EnableWrite();
	{
		nRet=m_pQueue->GetAndDeleteFirst(szBuffer,nBufferSize);
	} 
	m_Lock.DisableWrite();
	return nRet;
}

int CToolsMemoryQueueWithLock::PopFromFirst(char* szBuffer,int nBufferSize)
{
	int nRet=0;
	m_Lock.EnableWrite();
	{
		nRet=m_pQueue->PopFromFirst(szBuffer,nBufferSize);
	} 
	m_Lock.DisableWrite();
	return nRet;
}
int CToolsMemoryQueueWithLock::Push2Last(char* szData,int nDataLength)
{
	int nRet=0;
	m_Lock.EnableWrite();
	{
		nRet=m_pQueue->Push2Last(szData,nDataLength);
	} 
	m_Lock.DisableWrite();
	return nRet;
}

void CToolsMemoryQueueWithLock::CleanAll(void)
{
	m_Lock.EnableWrite();
	{
		m_pQueue->CleanAll();
	}
	m_Lock.DisableWrite();
}

int CToolsMemoryQueueWithLock::ReadFromFile(char* szFileName)
{
	int nRet=0;
	m_Lock.EnableWrite();
	{
		nRet=m_pQueue->ReadFromFile(szFileName);
	}
	m_Lock.DisableWrite();
	return nRet;
}












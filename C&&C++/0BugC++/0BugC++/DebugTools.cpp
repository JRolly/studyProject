#include "IncludeDef.h"
#include "DebugTools.h"


//��ȫ���ַ�����������
//������˳���ţ�Ŀ�ĵ�ַ��Դ��ַ������������ֽ���
void SafeStrcpy(char *pDest, char *pSource,int nCount)
{
	int nLen=(int)strlen(pSource)+1; //���Դ�ַ������ȣ�+1 ��֤��\0��
	if(!pDest) goto SafeStrcpy_END_PROCESS; //������ʩ�����Ŀ���ַ�Ƿ�
	if(!pSource) goto SafeStrcpy_END_PROCESS; //�������������������
	if(nLen>nCount) nLen=nCount; //�����д��������
	memcpy(pDest,pSource,nLen); //ʵʩ����
	*(pDest+nLen-1)='\0'; //�ֹ���ӡ�\0��
SafeStrcpy_END_PROCESS: //���ǽ�����
	return;
}


//��ȫ�ı���������
//szBuf: �û�ָ�������������
//nMaxLength���û�ָ��������������ߴ�
//szFormat����ʽ������ַ�������Σ������Ƕ����
//����������ַ�������strlen �ĳ��ȣ����������ġ�\0����
int SafePrintf(char* szBuf,int nMaxLength,char *szFormat, ...)
{
	int nListCount=0;
	va_list pArgList;
	//�˴�����ȫ�Է�������ֹ�û�����Ƿ��Ļ����������³����ڴ˱�����
	if (!szBuf) goto SafePrintf_END_PROCESS;
	//�˴�����ϵͳѭ��������ÿ����ʽ������ַ���
	va_start (pArgList,szFormat);
	nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
		nMaxLength-nListCount,szFormat,pArgList);
	va_end(pArgList);
	//ʵ�ֻ��������ޱ���
	if(nListCount>(nMaxLength-1)) nListCount=nMaxLength-1;
	//�˹���ӡ�\0����ȷ�����100%��׼C �ַ���
	*(szBuf+nListCount)='\0';
SafePrintf_END_PROCESS:
	return nListCount;
}


//��ָ���Ļ��������һ��ʱ����ַ���
//szBuf: �û�ָ�������������
//nMaxLength���û�ָ��������������ߴ�
//����������ַ�������strlen �ĳ��ȣ����������ġ�\0����
int GetATimeStamp(char* szBuf,int nMaxLength)
{
	time_t t;
	struct tm *pTM=NULL;
	int nLength=0;
	time(&t);
	pTM = localtime(&t);
	nLength=SafePrintf(szBuf,nMaxLength,"%s",asctime(pTM));
	//�����Ǹ���Ҫ�ļ��ɣ�asctime(pTM)�������ַ��������Զ����ϻس�����
	//�������ܶ�ĸ�ʽ�������������
	//�˴��˸�����ַ�����Ŀ���ǹ��˵�����س�����
	szBuf[nLength-1]='\0';
	return nLength;
}


//��ָ���Ļ��������һ��ʱ����ַ���
// szFileName: �û�ָ��������ļ�
// szMode���������ļ��򿪷�ʽ�����ַ�����һ�㽨�顱a+��
//����������ַ�������strlen �ĳ��ȣ����������ġ�\0����
int dbg2file(char* szFileName,char* szMode, char *szFormat, ...)
{
	//ǰ��κ�SafePrintf ����һģһ��
	char szBuf[DEBUG_BUFFER_LENGTH];
	char szTime[256];
	int nListCount=0;
	va_list pArgList;
	va_start (pArgList,szFormat);
	nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
		DEBUG_BUFFER_LENGTH-nListCount,szFormat,pArgList);
	va_end(pArgList);
	if(nListCount>(DEBUG_BUFFER_LENGTH-1))
		nListCount=DEBUG_BUFFER_LENGTH-1;
	*(szBuf+nListCount)='\0';
	//�ڴ˿�ʼ��ʽ�����������Ŀ���豸
	GetATimeStamp(szTime,256);
	FILE* fp;
	fp=fopen(szFileName,szMode);
	if(fp)
	{
		nListCount=fprintf(fp,"[%s] %s", szTime,szBuf); //�ļ���ӡ
		CON_PRINTF("[%s] %s\n", szTime,szBuf); //��Ļ��ӡ
		fclose(fp);
	} else nListCount=0;
	return nListCount;
}


//�����ʽ
//0000 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 xxxxxxxxxxxxxxxx
//��ASCII ��ʽ��ʾ��������
int dbg_bin_ascii(char* pPrintBuffer,char* pBuffer,int nLength)
{
	//�ڲ�������ֻ�б��߱��˵ĺ������õĺ�����һ�㲻д��������ƣ����ּ�ࡣ
	int i;
	int nCount=0;
	for(i=0;i<nLength;i++) //���עfor ��д�����������е�for �������ģʽ
	{
		//ASCII �ַ����У�����ʾ�ַ�����>32
		if(32<=*(pBuffer+i)) //���ע����д���
			nCount+=SafePrintf(pPrintBuffer+nCount,256,
			"%c",*(pBuffer+i));
		else
			//������ʾ�ַ��ԡ�.������ռλ�����ָ�ʽ���룬�ұ������
			nCount+=SafePrintf(pPrintBuffer+nCount,256,".");
		//���ָ�������ݲ��ǿ�����ʾ��ASCII �ַ�����ʾ��.��
	} 
	return nCount;
} 


//��ʮ�����Ʒ�ʽ��ʾָ�����������ݡ�
int dbg_bin_hex(char* pPrintBuffer,char* pBuffer,int nLength)
{
	int i=0;
	int j=0;
	int nCount=0;
	//һ���Ƚϸ��ӵĴ�ӡѭ������Ȼ�ܳ��������Ǻܼ�
	for(i=0;i<nLength;i++)
	{
		nCount+=SafePrintf(pPrintBuffer+nCount,256,
			"%02X ",(unsigned char)*(pBuffer+i));
		j++;
		if(4==j)
		{
			j=0;
			nCount+=SafePrintf(pPrintBuffer+nCount,256," ");
		}
	} 
	if(16>nLength) //ÿ�д�ӡ16 �ֽ�
	{
		for(;i<16;i++)
		{
			nCount+=SafePrintf(pPrintBuffer+nCount,256," ");
			j++;
			if(4==j)
			{
				j=0;
				nCount+=SafePrintf(pPrintBuffer+nCount,256," ");
			}
		}
	}
	return nCount;
}


//****************��������ں���
//��16 �ֽ�Ϊһ�У���ʽ������������������ݡ�
void dbg_bin(char* pBuffer,int nLength)
{
	int nAddr=0;
	int nLineCount=0;
	int nBufferCount=nLength;
	int n=0;
	char szLine[256]; //�л���
	if(0<nLength)
	{
		while(1)
		{
			n=0;
			n+=SafePrintf(szLine+n,256-n,"%p - ",pBuffer+nAddr);
			nLineCount=16;
			if(nBufferCount<nLineCount) nLineCount=nBufferCount;
			n+=dbg_bin_hex(szLine+n,pBuffer+nAddr,nLineCount);
			n+=dbg_bin_ascii(szLine+n,pBuffer+nAddr,nLineCount);
			CON_PRINTF ("%s\n",szLine);
			nAddr+=16;
			nBufferCount-=16;
			if(0>=nBufferCount) break;
		} 
		CON_PRINTF ("\n");
	} 
	else CON_PRINTF ("dbg_bin error length=%d\n",nLength);
}



//��æ�X
unsigned long SCountSubGetX(SCountSub& CountSub)
{
	return CountSub.m_lXEnd-CountSub.m_lXBegin;
} 

//���ó�ʼֵ
void SCountSubSetBegin(SCountSub& CountSub,unsigned long n)
{
	CountSub.m_lXBegin=n;
} 

//���ý���ֵ
unsigned long SCountSubSetEnd(SCountSub& CountSub,unsigned long n)
{
	CountSub.m_lXEnd=n;
	return SCountSubGetX(CountSub);
}

//��ʼ��
void SCountReset(SCount& Count,unsigned long n)
{
	Count.m_Sum=n;
	Count.m_Sub.m_lXBegin=0;
	Count.m_Sub.m_lXEnd=0;
} 

//����ͳ��ƽ��ֵ
unsigned long SCountSum(SCount& Count)
{
	unsigned long X=SCountSubGetX(Count.m_Sub);
	if(0==Count.m_Sum) Count.m_Sum=X; //��ֵ���Ϊ0,��ֱ�Ӹ�ֵ,�������
	else Count.m_Sum=(Count.m_Sum+X)/2; //����ͳ��ƽ��ֵ
	return Count.m_Sum;
} 

//����Sum ֵ
unsigned long SCountGetSum(SCount& Count)
{
	return Count.m_Sum;
}

//���ص�ǰ�Ħ�X
unsigned long SCountGetX(SCount& Count)
{
	return SCountSubGetX(Count.m_Sub);
}

//���ÿ�ʼ
void SCountSetBegin(SCount& Count,unsigned long n)
{
	SCountSubSetBegin(Count.m_Sub,n);
}

//���ý���ֵ,��������,���Զ��ˢ��
unsigned long SCountSetEnd(SCount& Count,unsigned long n)
{
	return SCountSubSetEnd(Count.m_Sub,n);
}


#ifdef WIN32 //����Windows ����Ч
int SafeScanf(char* szBuffer, //�������뻺����ָ��
	int nLength) //�������뻺��������
{
	char ch; //���һ��������ַ�
	int i = 0; //������ָ��
	while (1)
	{
		if (kbhit()) //���ް���������
		{
			ch = getch(); //�еĻ���ʹ��getch ������ü���������ַ�
			if ('\r' == ch) break; //�س�������ѭ��
			if ('\n' == ch) break;
			if (nLength>(i + 1)) //���Ȳ����޵Ļ�ִ���߼�
			{ //i+1 ��Ϊ�˸����ġ�\0������λ��
				if (32>ch) //���˵������ַ�
					goto CToolsBaseLibrary_SafeScanf_Loop;
				else if (32 == ch)
				{ //���˵���������ǰ�Ŀո�
					if (!i) //�硱 exit now��������˳ɡ�exit now��
						goto CToolsBaseLibrary_SafeScanf_Loop;
				} 
				TOOLS_PRINTF("%c", ch); //����Ч�ַ���ӡ����Ļ
				*(szBuffer + i) = ch; //��Ч�ַ���ӵ�������
				i++; //������ָ��+1
			}
		CToolsBaseLibrary_SafeScanf_Loop:
			continue;
		}
		Sleep(50); //�κ�ѭ����Ӧ����Sleep����Լ����������
	} //50ms ��ѭ����������´�����
	TOOLS_PRINTF("\n"); //����������س���
	*(szBuffer + i) = '\0'; //�ַ����������'\0'
	return i; //������Ч�ַ�����strlen �ĳ��ȣ�������'\0'��
}
#else // not WIN32
#endif




/**************************************/
/*          �ײ�debug��ʵ��           */
/**************************************/


CToolsLowDebug::CToolsLowDebug(const char* szPathName,
	const char* szAppName,
	bool bPrint2TTYFlag,
	_APP_INFO_OUT_CALLBACK pInfoOutCallback,
	void* pInfoOutCallbackParam)
{
	//�����ص�����ָ�룬��ҵ��������
	m_pInfoOutCallback=pInfoOutCallback;
	m_pInfoOutCallbackParam=pInfoOutCallbackParam;
	//�����������Ļ�ı�־����ҵ�����ο�
	m_bPrint2TTYFlag=bPrint2TTYFlag;
	//ƴ������ļ���
	if(szAppName)
		FULL_NAME(szPathName,szAppName,m_szFileName,"dbg")
	else //����������ļ�
		m_szFileName[0]='\0';
	//��ɾ���ϴε����кۼ������������������
	DeleteAFile(m_szFileName);
	Debug2File("CToolsLowDebug: Start!\n"); //һ���򵥵��������ҿ�ʼ������
}

CToolsLowDebug::~CToolsLowDebug()
{
	Debug2File("CToolsLowDebug: Stop!\n");
}

char* CToolsLowDebug::GetTrueFileName(char* szBuffer)
{
	char* pRet=szBuffer;
	int nLen=strlen(szBuffer);
	int i=0;
	for(i=nLen-1;i>=0;i--) //�����������ע�⣬�����ϴ��룬��̫�����޴�ԭ��
	{
		//�����߼����ҵ�������һ��·��������������Դ���Ϊ�ļ�����ʼ��
		if('\\'==*(szBuffer+i)) //���ǵ�Windows ��·�������
		{
			pRet=(szBuffer+i+1);
			break;
		} 
		if('/'==*(szBuffer+i)) //���ǵ�Unix ��Linux ��·�������
		{
			pRet=(szBuffer+i+1);
			break;
		}
	} 
	return pRet; //���ص����ҵ��ĵ㣬��������ͬһ���������÷���ֵ����Ҫ�ͷ�
}

void CToolsLowDebug::DeleteAFile(char* szFileName)
{
	remove(szFileName);
}

int CToolsLowDebug::Debug2File(char *szFormat, ...)
{
	//ע�⣬��������ʱ����û���ڴ�ظ����ˣ���̬�ڴ����룬ԭ����Ӧ�ñ���
	//��������ڴ���Ƭ���˴�ʹ�þ�̬����ʵ��buffer���ڸ���ջ������
	//��Ҳ��Ϊʲô�������������������ַ������ȵ�ԭ��
	char szBuf[DEBUG_BUFFER_LENGTH]; //׼�����buffer
	char szTemp[DEBUG_BUFFER_LENGTH]; //ʱ����û����м�buffer
	char szTime[DEBUG_BUFFER_LENGTH]; //ʱ�����buffer
	FILE* fp=null; //�ļ�ָ�룬��C ģʽ����
	int nListCount=0;
	va_list pArgList;
	time_t t;
	struct tm *pTM=NULL;
	int nLength=0;
	//���ǹ���ʱ���
	time(&t);
	pTM = localtime(&t);
	nLength=SafePrintf(szTemp,DEBUG_BUFFER_LENGTH,"%s",asctime(pTM));
	szTemp[nLength-1]='\0';
	SafePrintf(szTime,DEBUG_BUFFER_LENGTH,"[%s] ",szTemp);
	//ע�⣬�˴���ʼ����������Դ˱�֤���̵߳��ð�ȫ
	m_Lock.Lock();
	{ //ϰ����д�����Դ����ź����������綨����������Ŀ��
		//������������Ǵ�SafePrintf ���������ģ�һ���߼��Ŀ������ԣ�
		//Ҳ���Ը�����Ҫ,ֱ�ӿ��������ʵ�֣���һ����Ҫд�ɺ������
		va_start (pArgList,szFormat);
		nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
			DEBUG_BUFFER_LENGTH-nListCount,szFormat,pArgList);
		va_end(pArgList);
		if(nListCount>(DEBUG_BUFFER_LENGTH-1))
			nListCount=DEBUG_BUFFER_LENGTH-1;
		*(szBuf+nListCount)='\0';
		//��ʼ��ʵ�����
		fp=fopen(m_szFileName,"a+");
		//��ע�������߼������ڱ�����ʹ�����������ֻ����һ���˳���
		//�������û��ʹ��goto����ˣ�����ʹ��if Ƕ�ף�ȷ�������м�����
		if(fp)
		{ //������ļ�
			nListCount=fprintf(fp,"%s%s",szTime,szBuf);
			if(m_bPrint2TTYFlag)
			{ //������Ҫ���������̨
				TOOLS_PRINTF("%s%s",szTime,szBuf);
				if(m_pInfoOutCallback)
				{ //ע��˴����ص��������Ҫ���ϲ����
					//ע�⣬����Ϊ��ӣ�û��ʹ��ǰ�ı�����Ŀǰ�Ǽ���bug ��
					char szInfoOut[APP_INFO_OIT_STRING_MAX];
					SafePrintf(szInfoOut,APP_INFO_OIT_STRING_MAX,
						"%s%s",szTime,szBuf);
					m_pInfoOutCallback(szInfoOut, //ע�������ַ��������ص�
						m_pInfoOutCallbackParam); //͸����ָ��
				}
			} 
			fclose(fp);
		} 
		else
		{
			nListCount=0;
		}
	} 
	m_Lock.Unlock(); //��	��
	return nListCount; //����������ֽ����������ַ�����������������ϰ��
}

void CToolsLowDebug::Debug2File4Bin(char* pBuffer,int nLength)
{
	m_Lock.Lock();
	{ //ע����������Լ���ǰ�ĵĴ������á�
		//dbg2file4bin(m_szFileName,"a+",pBuffer,nLength);
		dbg2file(m_szFileName,"a+",pBuffer,nLength);	//??????�Ƿ���������������
		if(m_bPrint2TTYFlag) dbg_bin(pBuffer,nLength);
	} 
	m_Lock.Unlock();
}
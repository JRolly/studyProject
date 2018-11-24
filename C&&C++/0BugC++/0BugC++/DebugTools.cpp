#include "IncludeDef.h"
#include "DebugTools.h"


//安全的字符串拷贝函数
//参数按顺序排：目的地址，源地址，拷贝的最大字节数
void SafeStrcpy(char *pDest, char *pSource,int nCount)
{
	int nLen=(int)strlen(pSource)+1; //获得源字符串长度，+1 保证’\0’
	if(!pDest) goto SafeStrcpy_END_PROCESS; //保护措施，如果目标地址非法
	if(!pSource) goto SafeStrcpy_END_PROCESS; //则放弃服务，跳到结束点
	if(nLen>nCount) nLen=nCount; //避免读写出界的设计
	memcpy(pDest,pSource,nLen); //实施拷贝
	*(pDest+nLen-1)='\0'; //手工添加’\0’
SafeStrcpy_END_PROCESS: //这是结束点
	return;
}


//安全的变参输出函数
//szBuf: 用户指定的输出缓冲区
//nMaxLength：用户指定的输出缓冲区尺寸
//szFormat：格式化输出字符串（变参，可以是多个）
//返回输出的字符总数（strlen 的长度，不包括最后的’\0’）
int SafePrintf(char* szBuf,int nMaxLength,char *szFormat, ...)
{
	int nListCount=0;
	va_list pArgList;
	//此处做安全性防护，防止用户输入非法的缓冲区，导致程序在此崩溃。
	if (!szBuf) goto SafePrintf_END_PROCESS;
	//此处开启系统循环，解析每条格式化输出字符串
	va_start (pArgList,szFormat);
	nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
		nMaxLength-nListCount,szFormat,pArgList);
	va_end(pArgList);
	//实现缓冲区超限保护
	if(nListCount>(nMaxLength-1)) nListCount=nMaxLength-1;
	//人工添加’\0’，确保输出100%标准C 字符串
	*(szBuf+nListCount)='\0';
SafePrintf_END_PROCESS:
	return nListCount;
}


//向指定的缓冲区输出一个时间戳字符串
//szBuf: 用户指定的输出缓冲区
//nMaxLength：用户指定的输出缓冲区尺寸
//返回输出的字符总数（strlen 的长度，不包括最后的’\0’）
int GetATimeStamp(char* szBuf,int nMaxLength)
{
	time_t t;
	struct tm *pTM=NULL;
	int nLength=0;
	time(&t);
	pTM = localtime(&t);
	nLength=SafePrintf(szBuf,nMaxLength,"%s",asctime(pTM));
	//这里是个重要的技巧，asctime(pTM)产生的字符串最后会自动带上回车符，
	//这给后面很多的格式化输出带来不便
	//此处退格结束字符串，目的是过滤掉这个回车符。
	szBuf[nLength-1]='\0';
	return nLength;
}


//向指定的缓冲区输出一个时间戳字符串
// szFileName: 用户指定的输出文件
// szMode：常见的文件打开方式描述字符串，一般建议”a+”
//返回输出的字符总数（strlen 的长度，不包括最后的’\0’）
int dbg2file(char* szFileName,char* szMode, char *szFormat, ...)
{
	//前半段和SafePrintf 几乎一模一样
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
	//在此开始正式的输出到各个目标设备
	GetATimeStamp(szTime,256);
	FILE* fp;
	fp=fopen(szFileName,szMode);
	if(fp)
	{
		nListCount=fprintf(fp,"[%s] %s", szTime,szBuf); //文件打印
		CON_PRINTF("[%s] %s\n", szTime,szBuf); //屏幕打印
		fclose(fp);
	} else nListCount=0;
	return nListCount;
}


//输出格式
//0000 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 xxxxxxxxxxxxxxxx
//以ASCII 方式显示数据内容
int dbg_bin_ascii(char* pPrintBuffer,char* pBuffer,int nLength)
{
	//内部函数，只有笔者本人的函数调用的函数，一般不写防御性设计，保持简洁。
	int i;
	int nCount=0;
	for(i=0;i<nLength;i++) //请关注for 的写法，笔者所有的for 都是这个模式
	{
		//ASCII 字符表中，可显示字符代码>32
		if(32<=*(pBuffer+i)) //请关注常量写左边
			nCount+=SafePrintf(pPrintBuffer+nCount,256,
			"%c",*(pBuffer+i));
		else
			//不可显示字符以”.”代替占位，保持格式整齐，且避免出错
			nCount+=SafePrintf(pPrintBuffer+nCount,256,".");
		//如果指定的内容不是可以显示的ASCII 字符，显示’.’
	} 
	return nCount;
} 


//以十六进制方式显示指定数据区内容。
int dbg_bin_hex(char* pPrintBuffer,char* pBuffer,int nLength)
{
	int i=0;
	int j=0;
	int nCount=0;
	//一个比较复杂的打印循环，虽然很长，但还是很简单
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
	if(16>nLength) //每行打印16 字节
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


//****************这是主入口函数
//以16 字节为一行，格式化输出二进制数据内容。
void dbg_bin(char* pBuffer,int nLength)
{
	int nAddr=0;
	int nLineCount=0;
	int nBufferCount=nLength;
	int n=0;
	char szLine[256]; //行缓冲
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



//获得ΔX
unsigned long SCountSubGetX(SCountSub& CountSub)
{
	return CountSub.m_lXEnd-CountSub.m_lXBegin;
} 

//设置初始值
void SCountSubSetBegin(SCountSub& CountSub,unsigned long n)
{
	CountSub.m_lXBegin=n;
} 

//设置结束值
unsigned long SCountSubSetEnd(SCountSub& CountSub,unsigned long n)
{
	CountSub.m_lXEnd=n;
	return SCountSubGetX(CountSub);
}

//初始化
void SCountReset(SCount& Count,unsigned long n)
{
	Count.m_Sum=n;
	Count.m_Sub.m_lXBegin=0;
	Count.m_Sub.m_lXEnd=0;
} 

//计算统计平均值
unsigned long SCountSum(SCount& Count)
{
	unsigned long X=SCountSubGetX(Count.m_Sub);
	if(0==Count.m_Sum) Count.m_Sum=X; //初值如果为0,则直接赋值,避免误差
	else Count.m_Sum=(Count.m_Sum+X)/2; //计算统计平均值
	return Count.m_Sum;
} 

//返回Sum 值
unsigned long SCountGetSum(SCount& Count)
{
	return Count.m_Sum;
}

//返回当前的ΔX
unsigned long SCountGetX(SCount& Count)
{
	return SCountSubGetX(Count.m_Sub);
}

//设置开始
void SCountSetBegin(SCount& Count,unsigned long n)
{
	SCountSubSetBegin(Count.m_Sub,n);
}

//设置结束值,单纯更新,可以多次刷新
unsigned long SCountSetEnd(SCount& Count,unsigned long n)
{
	return SCountSubSetEnd(Count.m_Sub,n);
}


#ifdef WIN32 //仅在Windows 下有效
int SafeScanf(char* szBuffer, //给定输入缓冲区指针
	int nLength) //给定输入缓冲区长度
{
	char ch; //最近一次输入的字符
	int i = 0; //缓冲区指针
	while (1)
	{
		if (kbhit()) //有无按键被按下
		{
			ch = getch(); //有的话，使用getch 函数获得键盘输入的字符
			if ('\r' == ch) break; //回车键跳出循环
			if ('\n' == ch) break;
			if (nLength>(i + 1)) //长度不超限的话执行逻辑
			{ //i+1 是为了给最后的’\0’留出位置
				if (32>ch) //过滤掉控制字符
					goto CToolsBaseLibrary_SafeScanf_Loop;
				else if (32 == ch)
				{ //过滤掉命令输入前的空格
					if (!i) //如” exit now”，会过滤成”exit now”
						goto CToolsBaseLibrary_SafeScanf_Loop;
				} 
				TOOLS_PRINTF("%c", ch); //将有效字符打印到屏幕
				*(szBuffer + i) = ch; //有效字符添加到缓冲区
				i++; //缓冲区指针+1
			}
		CToolsBaseLibrary_SafeScanf_Loop:
			continue;
		}
		Sleep(50); //任何循环均应该有Sleep，相对键盘输入而言
	} //50ms 的循环检测间隔，绰绰有余
	TOOLS_PRINTF("\n"); //跳出后，输出回车符
	*(szBuffer + i) = '\0'; //字符串后面添加'\0'
	return i; //返回有效字符数（strlen 的长度，不包含'\0'）
}
#else // not WIN32
#endif




/**************************************/
/*          底层debug类实现           */
/**************************************/


CToolsLowDebug::CToolsLowDebug(const char* szPathName,
	const char* szAppName,
	bool bPrint2TTYFlag,
	_APP_INFO_OUT_CALLBACK pInfoOutCallback,
	void* pInfoOutCallbackParam)
{
	//保留回调函数指针，供业务函数调用
	m_pInfoOutCallback=pInfoOutCallback;
	m_pInfoOutCallbackParam=pInfoOutCallbackParam;
	//保留输出到屏幕的标志，供业务函数参考
	m_bPrint2TTYFlag=bPrint2TTYFlag;
	//拼接输出文件名
	if(szAppName)
		FULL_NAME(szPathName,szAppName,m_szFileName,"dbg")
	else //允许不输出到文件
		m_szFileName[0]='\0';
	//先删除上次的运行痕迹，避免两次输出干扰
	DeleteAFile(m_szFileName);
	Debug2File("CToolsLowDebug: Start!\n"); //一个简单的声明，我开始工作了
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
	for(i=nLen-1;i>=0;i--) //逆向检索，请注意，这是老代码，不太符合无错化原则
	{
		//基本逻辑，找到右数第一个路径间隔符跳出，以此作为文件名开始点
		if('\\'==*(szBuffer+i)) //考虑到Windows 的路径间隔符
		{
			pRet=(szBuffer+i+1);
			break;
		} 
		if('/'==*(szBuffer+i)) //考虑到Unix 和Linux 的路径间隔符
		{
			pRet=(szBuffer+i+1);
			break;
		}
	} 
	return pRet; //返回的是找到的点，缓冲区是同一缓冲区，该返回值不需要释放
}

void CToolsLowDebug::DeleteAFile(char* szFileName)
{
	remove(szFileName);
}

int CToolsLowDebug::Debug2File(char *szFormat, ...)
{
	//注意，这个类设计时，还没有内存池概念，因此，动态内存申请，原则上应该避免
	//以免出现内存碎片。此处使用静态数组实现buffer，在浮动栈建立。
	//这也是为什么这个类必须声明最大输出字符串长度的原因
	char szBuf[DEBUG_BUFFER_LENGTH]; //准备输出buffer
	char szTemp[DEBUG_BUFFER_LENGTH]; //时间戳置换的中间buffer
	char szTime[DEBUG_BUFFER_LENGTH]; //时间戳的buffer
	FILE* fp=null; //文件指针，以C 模式工作
	int nListCount=0;
	va_list pArgList;
	time_t t;
	struct tm *pTM=NULL;
	int nLength=0;
	//这是构建时间戳
	time(&t);
	pTM = localtime(&t);
	nLength=SafePrintf(szTemp,DEBUG_BUFFER_LENGTH,"%s",asctime(pTM));
	szTemp[nLength-1]='\0';
	SafePrintf(szTime,DEBUG_BUFFER_LENGTH,"[%s] ",szTemp);
	//注意，此处开始进入加锁，以此保证跨线程调用安全
	m_Lock.Lock();
	{ //习惯性写法，以大括号和缩进清晰界定加锁区域，醒目。
		//下面这个段落是从SafePrintf 拷贝出来的，一个逻辑的可重用性，
		//也可以根据需要,直接拷贝代码段实现，不一定非要写成宏或函数。
		va_start (pArgList,szFormat);
		nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
			DEBUG_BUFFER_LENGTH-nListCount,szFormat,pArgList);
		va_end(pArgList);
		if(nListCount>(DEBUG_BUFFER_LENGTH-1))
			nListCount=DEBUG_BUFFER_LENGTH-1;
		*(szBuf+nListCount)='\0';
		//开始真实的输出
		fp=fopen(m_szFileName,"a+");
		//请注意下面逻辑，由于本函数使用了锁，因此只能有一个退出点
		//这里笔者没有使用goto，因此，必须使用if 嵌套，确保不会中间跳出
		if(fp)
		{ //输出到文件
			nListCount=fprintf(fp,"%s%s",szTime,szBuf);
			if(m_bPrint2TTYFlag)
			{ //根据需要输出至控制台
				TOOLS_PRINTF("%s%s",szTime,szBuf);
				if(m_pInfoOutCallback)
				{ //注意此处，回调输出给需要的上层调用
					//注意，本段为后加，没有使用前文变量，目前是减少bug 率
					char szInfoOut[APP_INFO_OIT_STRING_MAX];
					SafePrintf(szInfoOut,APP_INFO_OIT_STRING_MAX,
						"%s%s",szTime,szBuf);
					m_pInfoOutCallback(szInfoOut, //注意把输出字符串传给回调
						m_pInfoOutCallbackParam); //透传的指针
				}
			} 
			fclose(fp);
		} 
		else
		{
			nListCount=0;
		}
	} 
	m_Lock.Unlock(); //解	锁
	return nListCount; //返回输出的字节数，所有字符串构造和输出函数的习惯
}

void CToolsLowDebug::Debug2File4Bin(char* pBuffer,int nLength)
{
	m_Lock.Lock();
	{ //注意加锁区域，以及对前文的代码重用。
		//dbg2file4bin(m_szFileName,"a+",pBuffer,nLength);
		dbg2file(m_szFileName,"a+",pBuffer,nLength);	//??????是否是其他函数调用
		if(m_bPrint2TTYFlag) dbg_bin(pBuffer,nLength);
	} 
	m_Lock.Unlock();
}
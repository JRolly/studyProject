#include "BufferTools.h"
#include "BaseLib.h"

/////////////////////////////
///动态Buffer
#ifdef	BUFFER_DYNAMIC

CToolsBuffer::CToolsBuffer(CToolsMemoryPoolWithLock* pMemPool)
{
	m_pMemPool=pMemPool; //保存内存池指针
	m_pData=null; //注意此处，动态内存块指针并未分配，先保持空
	m_nDataLength=0; //长度也保持为0
}
CToolsBuffer::~CToolsBuffer()
{
	SetSize(0); //SetSize 为0，表示清除动态内存块，下文有介绍
}

//由于动态内存申请，可能会失败，因此返回bool 量，成功为真，失败返回假
bool CToolsBuffer::SetSize(int nSize) //给定新的大小
{
	if(!m_pMemPool) return false; //防御性设计，如果内存池指针为空，无法工作
	m_nDataLength=nSize; //先给缓冲区长度赋值
	if(0==m_nDataLength) //注意析构函数中的SetSize(0)，此处处理
	{ //如果设置大小为0，表示释放缓冲区
		if(m_pData)
		{
			m_pMemPool->Free(m_pData); //内存池释放
			m_pData=null; //释放后立即赋初值null，避免下文误用
		} 
		return true; //这也是操作成功，返回真
	} 
	//此处开始，新设置的缓冲期长度，一定不为0
	if(!m_pData) //如果原指针为空，表示没有数据，需要Malloc
	{
		//请注意这里对内存池Malloc 函数的调用，这也算是内存池的应用实例
		//内存池申请的指针都是void*，这符合C 语言malloc 的规范，
		//而本类的指针都是字符串型，因此需要做强制指针类型转换
		m_pData=(char*)m_pMemPool->Malloc(
		m_nDataLength, //申请的内存块长度
		"CToolsBuffer::m_pData"); //注意，这里特别声明申请者身份
		//一旦发生内存泄漏，本对象退出时忘了释放
		//内存池的报警机制即会激活，打印这个字符串
		if(!m_pData) //请注意，这里二次判断，是判断申请是否成功
		{
			m_nDataLength=0; //没有成功，则把长度赋为0
			return false; //申请失败，返回假
		} 
		else return true; //成功就返回真
	}
	else //这是原有m_pData 不为空，就是已经有一个内存区的情况
	{
		//使用ReMalloc 函数做内存区域再调整，默认，拷贝原有内容
		//请注意，这里是内存池ReMalloc 功能的实例，将原有指针传入
		//经过ReMalloc 修饰后，返回新的指针，注意强制指针类型转换
		m_pData=(char*)m_pMemPool->ReMalloc(m_pData,m_nDataLength);
		if(!m_pData)
		{
			m_nDataLength=0; //申请失败，返回假
			return false;
		} 
		else return true; //成功返回真
	}
}

bool CToolsBuffer::InsertSpace2Head(int nAddBytes)
{
	bool bRet=false; //预设返回值
	int nNewSize=0; //新的空间大小变量
	char* pBuffer=null; //先定义一个新的二进制缓冲区指针
	if(!m_pMemPool) //防御性设计，防止内存池为空
		goto CToolsBuffer_InsertSpace2Head_End_Process;
	nNewSize=m_nDataLength+nAddBytes; //求得新的长度
	//请注意这里，申请一个临时缓冲区，其长度等于原长度+增加的长度
	pBuffer=(char*)m_pMemPool->Malloc(nNewSize,
		"CToolsBuffer::InsertSpace2Head():pBuffer"); //请注意这段说明文字
	if(!pBuffer) //缓冲区申请失败，跳转返回假
		goto CToolsBuffer_InsertSpace2Head_End_Process;
	//此处为防御性设计，如果原有缓冲区为空，则不做后续的拷贝动作
	if((m_pData)&&(m_nDataLength))
	{ //这是将原有缓冲区内容拷贝到临时缓冲区后半部分，与新增加字节构成一个整体
		memcpy(pBuffer+nAddBytes,m_pData,m_nDataLength);
	}
	//当所有准备工作完成，调用本对象的二进制拷贝函数，将临时缓冲区内容拷贝会本对象
	//二进制拷贝函数，后文有介绍，当然，其拷贝成功与否，也作为本函数的返回值
	bRet=BinCopyFrom(pBuffer,nNewSize);
CToolsBuffer_InsertSpace2Head_End_Process:
	//不管是否成功拷贝，释放临时缓冲区
	if(pBuffer)
	{
		m_pMemPool->Free(pBuffer);
		pBuffer=null;
	} 
	return bRet; //返回操作结果
}

//从前拷贝函数
void CopyFromHead(char* pD,char* pS,int nSize)
{
	int i=0;
	for(i=0;i<nSize;i++) //循环是从头到尾
	{
		*(pD+i)=*(pS+i);
	}
} 
//从后拷贝函数
void CopyFromTail(char* pD,char* pS,int nSize)
{
	int i=0;
	for(i=nSize-1;i>=0;i--) //循环是从尾到头
	{
		*(pD+i)=*(pS+i);
	}
}

//在后面插入空白
bool CToolsBuffer::AddSpace2Tail(int nAddBytes)
{
	return SetSize(m_nDataLength+nAddBytes);
}

//从前面剪切掉一段数据
void CToolsBuffer::CutHead(int nBytes)
{
	//防御性设计，如果给出的剪切空间大于原有缓冲区，则直接清空。
	if(m_nDataLength<=nBytes) SetSize(0);
	else
	{ //这是从后向前Move，因此，直接调用memecpy 完成。
		memcpy(m_pData,m_pData+nBytes,m_nDataLength-nBytes);
		//大家请注意，这里笔者没有再SetSize，由于内存池的原理，
		//ReMalloc 一个比较小的空间，一般都是直接返回原指针，
		//因此，此处也不多此一举了，直接就把空间长度修改为较小的长度即可
		m_nDataLength-=nBytes;
	}
}

//从后面剪切掉一段数据
void CToolsBuffer::CutTail(int nBytes)
{
	//防御性设计，剪切太多，直接清空
	if(m_nDataLength<=nBytes) SetSize(0);
	//同上，减小直接修改长度参数
	else m_nDataLength-=nBytes;
}

//返回拷贝的字节数，拷贝失败，返回0
int CToolsBuffer::BinCopyTo(
char* szBuffer, //调用者给出缓冲区指针
int nBufferSize) //调用者给出缓冲区大小
{ //防御性设计
	if(!m_pData) return 0; //如果内部无数据，返回0
	if(!m_nDataLength) return 0;
	if(nBufferSize<m_nDataLength) return 0; //如果给定缓冲区小于本数据缓冲区，返回0
	memcpy(szBuffer,m_pData,m_nDataLength);//执行拷贝动作
	return m_nDataLength; //返回拷贝的字节长度
}

//拷贝一个二进制缓冲区的数据
int CToolsBuffer::BinCopyFrom(char* szData,int nDataLength)
{
	//防御性设计，如果给定的参数非法，清空本地数据，返回0
	if((!szData)||(0>=nDataLength))
	{
		SetSize(0);
		return 0;
	} 
	if(!SetSize(nDataLength)) return 0; 
	//重新设置
	memcpy(m_pData,szData,m_nDataLength);
	return m_nDataLength;
} 
//拷贝同类，另外一个对象的数据
int CToolsBuffer::BinCopyFrom(CToolsBuffer* pBuffer)
{ //这里调用上一函数完成功能，注意工具类的用法，直接访问目标内部数据区
	return BinCopyFrom(pBuffer->m_pData,pBuffer->m_nDataLength);
}

//拷贝一个整数到本对象，执行网络字节序，破坏原有数据
bool CToolsBuffer::SetInt(int n)
{
	int nSave=htonl(n); //以临时变量求得给定整数的网络字节序
	//拷贝到本地缓冲区，带SetSize
	return BinCopyFrom((char*)&nSave,sizeof(int));
} 
//以整数本地字节序求得缓冲区最开始4Bytes 构成的整数的值，求值失败，返回0
int CToolsBuffer::GetInt(void)
{
	//防御性设计，如果本对象没有存储数据，或者存储的数据不到一个整数位宽4Bytes，返回0
	if(!m_pData) return 0;
	if(!sizeof(int)>m_nDataLength) return 0;
	return ntohl(*(int*)m_pData); //以头4Bytes 数据，求得本地字节序返回
}

bool CToolsBuffer::SetShort(short n)
{
	short sSave=htons(n);
	return BinCopyFrom((char*)&sSave,sizeof(short));//拷贝的字节数变成短整型位宽
}
short CToolsBuffer::GetShort(void)
{
	if(!m_pData) return 0;
	if(sizeof(short)>m_nDataLength) return 0; //注意，此处的范围变成短整型的位宽
	return ntohs(*(short*)m_pData);
}

bool CToolsBuffer::SetChar(char n)
{
	return BinCopyFrom(&n,sizeof(char)); //位宽1Byte
} 
char CToolsBuffer::GetChar(void)
{
	if(!m_pData) return 0;
	if(sizeof(char)>m_nDataLength) return 0; //位宽1Byte
	return *(char*)m_pData;
}

int CToolsBuffer::AddData(char* szData,int nDataLength)
{
	if((!m_pData)||(0>=m_nDataLength))
	{ //防御性设计，如果原有数据为空，则直接执行拷贝动作
		return BinCopyFrom(szData,nDataLength);
	} 
	int nOldSize=m_nDataLength;
	 //保留原有大小
	int nNewSize=m_nDataLength+nDataLength; //求得新的大小
	if(!SetSize(nNewSize)) return 0; //SetSize，其逻辑保留原有数据
	//注意，失败返回0
	memcpy(m_pData+nOldSize,szData,nDataLength); //拷贝新数据到原有数据末尾
	return m_nDataLength; //返回新的大小
}

int CToolsBuffer::InsertData2Head(char* szData,int nDataLength)
{
	if((!m_pData)||(0>=m_nDataLength))
	{ //防御性设计，如果原有数据为空，则直接执行拷贝动作
		return BinCopyFrom(szData,nDataLength);
	} 
	//先在前插入足够空区，保证后续拷贝动作能成功。
	//根据InsertSpace2Head 逻辑，原有数据可以获得保留
	if(!InsertSpace2Head(nDataLength)) return 0;
	//拷贝新数据到开始，注意拷贝的长度是新数据的长度，因此，不会破坏后续的原有数据
	memcpy(m_pData,szData,nDataLength);
	return m_nDataLength; //返回新的大小
}

int CToolsBuffer::StrCopyFrom(char* szString)
{
	int n=strlen(szString); //先求出目标字符串的长度
	n++; //长度+1，包括’\0’的位置
	return BinCopyFrom(szString,n); //调用二进制拷贝函数完成动作
}

//变参设计，返回打印的字符串总字节数(包含’\0’的位宽)
int CToolsBuffer::Printf(char* szFormat,...)
{
	//这一段在很多变参函数中都出现过，此处不再赘述
	char szBuf[TOOLS_BUFFER_STRING_MAX];
	int nListCount=0;
	va_list pArgList;
	va_start (pArgList,szFormat);
		nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
	TOOLS_BUFFER_STRING_MAX-nListCount,szFormat,pArgList);
	va_end(pArgList);
	if(nListCount>(TOOLS_BUFFER_STRING_MAX-1))
		nListCount=TOOLS_BUFFER_STRING_MAX-1;
	*(szBuf+nListCount)='\0';
	//最后调用StrCopyFrom，将缓冲区内容拷贝到本对象
	return StrCopyFrom(szBuf);
}

//二进制比较
int CToolsBuffer::memcmp(char* szData,int nDataLength)
{ //防御性设计
	if(!m_pData) return -1;
	if(!m_nDataLength) return -1;
	if(!szData) return -1;
	if(m_nDataLength<nDataLength) return -1;
	//使用C 标准库的memcmp 完成功能
	int nRet=::memcmp(m_pData,szData,nDataLength);
	return nRet;
} 
//文本型比较
int CToolsBuffer::strcmp(char* szString)
{ //防御性设计
	if(!m_pData) return -1;
	if(!m_nDataLength) return -1;
	if(!szString) return -1;
	//使用C 标准库的strcmp 完成功能
	int nRet=::strcmp(m_pData,szString);
	return nRet;
}


#else
//////////////////////////////
//静态Buffer

CToolsBuffer::CToolsBuffer(CToolsBaseLibrary* pToolsBaseLib)
{
	m_pMemPool=pToolsBaseLib->m_pMemPool; //保留内存池对象
	m_nDataLength=0; //数据长度为0
} 
CToolsBuffer::CToolsBuffer(CToolsMemoryPoolWithLock* pMemPool)
{
	m_pMemPool=pMemPool; //保留内存池对象
	m_nDataLength=0; //数据长度为0
} 
bool CToolsBuffer::IHaveData(void) //已有数据标志
{ //由于使用静态数组，m_pData 永远有意义，因此，此处仅判断m_nDataLength 的值
	if(0>=m_nDataLength) return false;
	return true;
}

bool CToolsBuffer::SetSize(int nSize)
{
	if(TOOLS_SAFE_BUFFER_MAX_SIZE<nSize)
	{ //如果超界，报警，返回假，即告知调用者分配失败
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::SetSize(): ERROR! nSize=%d\n",nSize);
		return false;
	} 
	m_nDataLength=nSize; //数据长度置为设置尺寸，
						//这其实还是把m_nDataLength 作为缓冲区大小提示
	return true;
}

bool CToolsBuffer::InsertSpace2Head(int nAddBytes)
{
	if(0>=m_nDataLength)
	{ //如果没有原始数据，则视为设置缓冲区大小
		m_nDataLength=nAddBytes;
		return true;
	}
	//这个计算相对复杂，首先缓冲区最大尺寸恒定，因此，它与原有数据的差值，是新插入空区的
	//最大可能值，因此，此处必须做判断
	if(nAddBytes>(TOOLS_SAFE_BUFFER_MAX_SIZE-m_nDataLength))
	{ //条件不满足，则报警返回
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::InsertSpace2Head(): ERROR! nAddBytes=%d, m_nDataLength=%d, too big!\n",
			nAddBytes,m_nDataLength);
		return false;
	}
	{
		//注意此处的大括号，是限定变量szBuffer 的作用范围
		char szBuffer[TOOLS_SAFE_BUFFER_MAX_SIZE];
		memset(szBuffer, '\0', TOOLS_SAFE_BUFFER_MAX_SIZE);
		//第一次，把原有数据拷贝到新缓冲区，已经偏移了nAddBytes 的位置
		memcpy(szBuffer+nAddBytes,m_pData,m_nDataLength);
		m_nDataLength+=nAddBytes;
		//第二次，将新缓冲区有效数据拷贝回本对象缓冲区
		memcpy(m_pData,szBuffer,m_nDataLength);
		//之所以这么复杂的拷贝，主要就是为了规避前文所述的“从前拷贝”和“从后拷贝”问题
	} 
	return true;
}

bool CToolsBuffer::AddSpace2Tail(int nAddBytes) //在后面插入空白
{
	if(0>=m_nDataLength)
	{ //如果没有原始数据，则视为设置缓冲区大小
		m_nDataLength=nAddBytes;
		return true;
	} 
	//判断新设置的尺寸大小是否合适
	if(nAddBytes>(TOOLS_SAFE_BUFFER_MAX_SIZE-m_nDataLength))
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::AddSpace2Tail(): ERROR! nAddBytes=%d, m_nDataLength=%d, too big!\n",
			nAddBytes,m_nDataLength);
		return false;
	} 
	m_nDataLength+=nAddBytes;	//后面追加比较简单，修改m_nDataLength 的值即可
	return true;
}

void CToolsBuffer::CutHead(int nBytes) //从前面剪切掉一段数据
{
	if(0>=m_nDataLength)
	{ //没有原始数据，剪切无意义，报警，宣告失败
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::CutHead(): ERROR! m_nDataLength=%d, too small!\n",
			m_nDataLength);
		m_nDataLength=0;
		return;
	} 
	if(nBytes>m_nDataLength)
	{ //如果剪切的数据长度大于原始数据长度，报警
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::CutHead(): ERROR! m_nDataLength=%d, nBytes=%d,too small!\n",
			m_nDataLength,nBytes);
		m_nDataLength=0;
		return;
	}
	m_nDataLength-=nBytes; //求出新的数据长度
							//后面数据向前拷贝，“挤出”原有数据
	memcpy(m_pData,m_pData+nBytes,m_nDataLength);
	return;
}

void CToolsBuffer::CutTail(int nBytes) //从后面剪切掉一段数据
{
	if(0>=m_nDataLength)
	{ //没有原始数据，剪切无意义，报警，宣告失败
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::CutTail(): ERROR! m_nDataLength=%d, too small!\n",
			m_nDataLength);
		m_nDataLength=0;
		return;
	} 
	if(nBytes>m_nDataLength)
	{ //如果剪切的数据长度大于原始数据长度，报警
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::CutTail(): ERROR! m_nDataLength=%d, nBytes=%d,too small!\n",
			m_nDataLength,nBytes);
		m_nDataLength=0;
		return;
	}
	m_nDataLength-=nBytes; //缩短长度就是剪切尾部
	return;
}

int CToolsBuffer::BinCopyTo(char* szBuffer,int nBufferSize)
{
	//防御性设计，条件不满足则报警，返回0，表示没有拷贝成功
	if(m_nDataLength>nBufferSize)
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::BinCopyTo(): ERROR! nBufferSize=%d,m_nDataLength=%d\n",
			nBufferSize,m_nDataLength);
		return 0;
	} 
	if(!szBuffer)
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::BinCopyTo(): ERROR! szBuffer=null\n");
		return 0;
	} 
	//执行真实的拷贝逻辑
	memcpy(szBuffer,m_pData,m_nDataLength);
	return m_nDataLength; //返回拷贝的字节数
}

int CToolsBuffer::BinCopyFrom(char* szData,int nDataLength)
{
	//防御性设计
	if(TOOLS_SAFE_BUFFER_MAX_SIZE<nDataLength)
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::BinCopyFrom(): ERROR! nDataLength=%d, too big!\n",
			nDataLength);
		return 0;
	} 
	if(!szData)
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::BinCopyTo(): ERROR! szData=null\n");
		return 0;
	} 
	if(0>=nDataLength)
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::BinCopyTo(): ERROR! 0>=nDataLength\n");
		return 0;
	} 
	//真实的拷贝动作
	memcpy(m_pData,szData,nDataLength);
	m_nDataLength=nDataLength;
	return m_nDataLength; //返回拷贝的字节数
} 

int CToolsBuffer::BinCopyFrom(CToolsBuffer* pBuffer)
{ //拷贝另外一个buffer
	return BinCopyFrom(pBuffer->m_pData,pBuffer->m_nDataLength);
}

bool CToolsBuffer::SetInt(int n) //设置一个整数，网络格式
{
	int nSave=htonl(n);
	return BinCopyFrom((char*)&nSave,sizeof(int));
} 
int CToolsBuffer::GetInt(void) //获得一个整数，返回本地格式
{
	if(0>=m_nDataLength) return 0;
	int* pData=(int*)m_pData;
	int nRet=*pData;
	return ntohl(nRet);
}

bool CToolsBuffer::SetShort(short n) //设置一个短整数，网络格式
{
	short sSave=htons(n);
	return BinCopyFrom((char*)&sSave,sizeof(short));
} 
short CToolsBuffer::GetShort(void) //获得一个短整数，返回本地格式
{
	if(0>=m_nDataLength) return 0;
	short* pData=(short*)m_pData;
	short sRet=*pData;
	return ntohs(sRet);
} 
bool CToolsBuffer::SetChar(char n) //设置一个字节
{
	*m_pData=n;
	m_nDataLength=sizeof(char);
	return true;
} 
char CToolsBuffer::GetChar(void) //得到m_pData 第一个字节的值
{
	return *m_pData;
}

//二进制数据追加函数
//追加数据到最后，返回新的数据长度
int CToolsBuffer::AddData(char* szData,int nDataLength)
{
	int nNewSize=m_nDataLength+nDataLength; //求得新的尺寸
	if(TOOLS_SAFE_BUFFER_MAX_SIZE<nNewSize) //防御性判断
	{
		m_pMemPool->m_pDebug->Debug2File(
			"CToolsBuffer::AddData(): ERROR! m_nDataLength=%d,nDataLength=%d, too big!\n",
			m_nDataLength,nDataLength);
		return 0;
	} 
	//做真实的拷贝动作
	memcpy(m_pData+m_nDataLength,szData,nDataLength);
	m_nDataLength=nNewSize;
	return m_nDataLength;
}

//插入数据到最前面，返回新的数据长度
int CToolsBuffer::InsertData2Head(char* szData,int nDataLength)
{
	if(!InsertSpace2Head(nDataLength)) //先试图插入空白到最前
	{
		m_pMemPool->m_pDebug->Debug2File("CToolsBuffer::InsertData2Head():ERROR! m_nDataLength=%d, nDataLength=%d, too big!\n",
			m_nDataLength,nDataLength);
		return 0;
	} 
	memcpy(m_pData,szData,nDataLength); //成功则拷贝
	return m_nDataLength;
}

int CToolsBuffer::StrCopyFrom(char* szString) //拷贝一个字符串到内部
{
	int nDataLength=strlen(szString)+1; //求出字符串数据长度，
	//+1 表示包含’\0’
	return BinCopyFrom(szString,nDataLength); //调用BinCopyFrom 完成拷贝
} 

int CToolsBuffer::Printf(char* szFormat,...) //变参打印构造一个字符串 
{
	char szBuf[TOOLS_SAFE_BUFFER_MAX_SIZE]; //注意，最大长度为静态buffer
	//的最大长度
	int nListCount=0;
	va_list pArgList;
	va_start (pArgList,szFormat);
	nListCount+=Linux_Win_vsnprintf(szBuf+nListCount,
		TOOLS_SAFE_BUFFER_MAX_SIZE-nListCount,szFormat,pArgList);
	va_end(pArgList);
	if(nListCount>(TOOLS_SAFE_BUFFER_MAX_SIZE-1))
		nListCount=TOOLS_SAFE_BUFFER_MAX_SIZE-1;
	*(szBuf+nListCount)='\0';
	//以上为变参处理段落，已经多处出现，此处不再赘述
	return StrCopyFrom(szBuf); //调用StrCopyFrom 完成拷贝
}

int CToolsBuffer::memcmp(char* szData,int nDataLength) //二进制比较
{ //防御性设计
	if(0>=m_nDataLength) return -1;
	if(!szData) return -1;
	if(m_nDataLength!=nDataLength) return -1;
	int nRet=::memcmp(m_pData,szData,nDataLength); //调用系统函数完成
	return nRet;
}
int CToolsBuffer::strcmp(char* szString) //字符串比较
{ //防御性设计
	if(0>=m_nDataLength) return -1;
	if(!szString) return -1;
	int nRet=::strcmp(m_pData,szString); //调用系统函数完成
	return nRet;
}


#endif	// BUFFER_DYNAMIC



///////////////////////////
//PopBuffer 类

CToolsPopBuffer::CToolsPopBuffer(char* szBuffer,
	int nBufferSize,
	bool bInitFlag)
{
	m_pHead=null; //初始化各种管件变量
	m_pBuffer=null;
	m_nBufferSize=0;
	Set(szBuffer,nBufferSize); //调用后粘合的Set 函数，实现粘合
	if(bInitFlag) Clean(); //如果需要初始化，则清空整个队列
} 
CToolsPopBuffer::~CToolsPopBuffer(){}

bool CToolsPopBuffer::ICanWork(void)
{ //依次检测所有关键变量
	if(!m_pBuffer) return false;
	if(!m_nBufferSize) return false;
	if(!m_pHead) return false;
	return true;
}

void CToolsPopBuffer::Set(char* szBuffer,int nBufferSize)
{
	m_pBuffer=szBuffer; //挂接缓冲区
	m_nBufferSize=nBufferSize;
	m_pHead=(SToolsPopBufferHead*)m_pBuffer; //定义队列头指针
}

void CToolsPopBuffer::Clean(void)
{
	if(m_pHead) //注意，此处已经开始使用m_pHead
	{
		m_pHead->m_nTokenCount=0; //所有Token 总数置为0
		//总消耗的字节数，置为队列头的长度。
		//这表示，PopBuffer 最后输出的总字节数，是包含这个队列头长度的。
		//同时也表示，即使PopBuffer 内部一个Token 都没有，其字节数也不为0
		m_pHead->m_nAllBytesCount=SToolsPopBufferHeadSize;
	}
}

//格式化输出内部数据
void CToolsPopBuffer::PrintInside(void)
{
	if(!ICanWork()) //防御性设计
	{
		TOOLS_PRINTF("CToolsPopBuffer::PrintInside(): \
						 ERROR! m_pBuffer=null\n");
		return;
	}
	//定义元素区开始的指针
	char* pTokenBegin=TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(m_pBuffer);
	//定义元素的头指针
	SToolsPopBufferTokenHead* pTokenHead=(SToolsPopBufferTokenHead*)pTokenBegin;
	//利用pTokenHead，偏移计算本Token 的数据开始点
	//请注意，这里传入的pTokenHead，就不是字符串型，如果前文函数型宏定义中
	//没有做强制指针类型转换，此处已经出错。
	char* pTokenData=TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(pTokenBegin);
	int i=0;
	//预打印整个队列的信息，即元素个数，字节数。
	TOOLS_PRINTF("CToolsPopBuffer::PrintInside(): Token: %d Bytes: %d\n",
		m_pHead->m_nTokenCount,m_pHead->m_nAllBytesCount);
	for(i=0;i<m_pHead->m_nTokenCount;i++)
	{
		//注意，由于队列中存储的数据，可能是文本型，也可能是二进制型
		//笔者在此准备了两条打印语句，使用时，根据情况选择
		TOOLS_PRINTF("[%d] - %s\n", pTokenHead->m_nDataLength,pTokenData);//格式化输出文本
		//dbg_bin(pTokenData,pTokenHead->m_nDataLength); //格式化输出二进制
		//开始迭代计算，根据本Token 长度，计算下一Token 起始点
		pTokenBegin+=TOOLS_POP_BUFFER_TOKEN_LENGTH(pTokenHead->m_nDataLength);
		//修订相关Token 头等参变量
		pTokenHead=(SToolsPopBufferTokenHead*)pTokenBegin;
		pTokenData=TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(pTokenBegin);
	}
}

int CToolsPopBuffer::GetTokenCount(void)
{
	if(!ICanWork()) return 0; //防御性设计
	return m_pHead->m_nTokenCount; //返回元素个数
}

int CToolsPopBuffer::GetAllBytes(void)
{
	if(!ICanWork()) return 0; //防御性设计
	return m_pHead->m_nAllBytesCount; //返回所有占用的字节数
}

//检查剩余空间是否够存储给定的数据长度
bool CToolsPopBuffer::ICanSave(int nDataLength)
{
	int nLeaveBytes=0; //准备变量，求得剩余空间
	if(!ICanWork()) return false; //防御性设计
	//剩余空间=缓冲区总长度-AllBytes，我们知道，AllBytes 里面已经包含了队列头长度
	//因此，这种计算是正确的。
	nLeaveBytes=m_nBufferSize-m_pHead->m_nAllBytesCount;
	//判断语句，注意，进入的长度，需要利用函数型宏进行修饰。
	//由于每个Token 有一个小的头，这个头的长度，需要叠加进来判断，否则就不准确
	if(TOOLS_POP_BUFFER_TOKEN_LENGTH(nDataLength) > (ULONG)nLeaveBytes)
		return false;
	else
		return true;
}

//针对普通缓冲区的AddLast
int CToolsPopBuffer::AddLast(char* szData,int nDataLength)
{
	int nRet=0; //准备返回值
	//防御性设计
	if(!szData) goto CToolsPopBuffer_AddLast_End_Process;
	if(0>=nDataLength) goto CToolsPopBuffer_AddLast_End_Process;
	if(!ICanWork()) goto CToolsPopBuffer_AddLast_End_Process;
	//如果剩余空间不够添加，则跳转返回0
	if(!ICanSave(nDataLength)) goto CToolsPopBuffer_AddLast_End_Process;
	{ //请注意，这个大括号不是if 语句开始，上文if 语句如果成立，已经goto 跳转
		//此处主要是为了限定变量的作用域，gcc 中，不允许在goto 语句之后声明变量
		//此处的大括号，是为了重新开辟一个堆栈区，以便声明局部变量
		char* pTokenBegin= //利用AllBytes 求出队列最尾的偏移
			m_pBuffer+m_pHead->m_nAllBytesCount;
		SToolsPopBufferTokenHead* pTokenHead= //强制指针类型转换为Token 头指针
			(SToolsPopBufferTokenHead*)pTokenBegin;
		char* pTokenData= //求出Token 数据区的指针
			TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(pTokenBegin);
		//请注意具体的添加动作
		pTokenHead->m_nDataLength=nDataLength; //先给元素头中的长度赋值
		memcpy(pTokenData,szData,nDataLength); //memcpy 数据内容到缓冲区
		m_pHead->m_nTokenCount++; //元素个数+1
		//请注意，这里AllByutes 添加的是包括元素头的所有长度，而不仅仅是数据长度
		m_pHead->m_nAllBytesCount+= //AllByutes 加上增加的长度
			TOOLS_POP_BUFFER_TOKEN_LENGTH(nDataLength);
		nRet=nDataLength; //但返回值纯数据长度
	}
CToolsPopBuffer_AddLast_End_Process: //结束跳转点
	return nRet; //返回结果
} 
//针对Buffer 类的AddLast
int CToolsPopBuffer::AddLast(CToolsBuffer* pBuffer)
{
	if(!pBuffer) return 0; //防御性设计
	//调用上一函数，实现功能
	return AddLast(pBuffer->m_pData,pBuffer->m_nDataLength);
}

int CToolsPopBuffer::GetFirstTokenLength(void)
{
	if(!ICanWork()) return 0; //防御性设计
	char* pFirstTokenBegin= //利用宏计算第一个Token 起始点
		TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(m_pBuffer);
	SToolsPopBufferTokenHead* pFirstTokenHead= //获得Token 头指针
		(SToolsPopBufferTokenHead*)pFirstTokenBegin;
	return pFirstTokenHead->m_nDataLength; //返回头中包含的数据长度
}

//以普通缓冲区方式获得第一个Token 数据，上层程序保证缓冲区足够大，并传入供检查
int CToolsPopBuffer::GetFirst(char* szBuffer,int nBufferSize)
{
	int nRet=0; //准备返回参数
	//防御性设计
	if(!ICanWork())
		goto CToolsPopBuffer_GetFirst_End_Process;
	//判定队列是否为空
	if(!GetTokenCount())
		goto CToolsPopBuffer_GetFirst_End_Process;
	//判断给定的参数区是否合法
	if(GetFirstTokenLength()>nBufferSize)
		goto CToolsPopBuffer_GetFirst_End_Process;
	{ //注意，这个大括号不是if 语句的大括号，是限定变量作用域
		char* pFirstTokenBegin= //寻找第一个Token 起始点
			TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(m_pBuffer);
		SToolsPopBufferTokenHead* pFirstTokenHead= //获得Token 头指针
			(SToolsPopBufferTokenHead*)pFirstTokenBegin;
		char* pFirstTokenData= //获得Token 数据指针
			TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(pFirstTokenBegin);
		memcpy(szBuffer,pFirstTokenData, //拷贝数据到缓冲区
			pFirstTokenHead->m_nDataLength);
		nRet=pFirstTokenHead->m_nDataLength; //返回值设定
	}
CToolsPopBuffer_GetFirst_End_Process:
	return nRet;
}

//以Buffer 类方式获得第一个Token 数据，本函数破坏Buffer 原有内容
//由于Buffer 类本身是动态内存管理，因此，不存在缓冲区问题
int CToolsPopBuffer::GetFirst(CToolsBuffer* pBuffer)
{
	//防御性设计，
	if(!ICanWork()) return 0;
	if(!pBuffer->SetSize(GetFirstTokenLength())) return 0;
	if(!pBuffer->m_nDataLength) return 0;
	//调用上一函数，实现真实的GetFirst 功能。
	return GetFirst(pBuffer->m_pData,pBuffer->m_nDataLength);
}

//删除第一个元素，如果队列为空，删除会失败，返回false
bool CToolsPopBuffer::DeleteFirst(void)
{
	bool bRet=false; //准备返回值
	//防御性设计
	if(!ICanWork())
		goto CToolsPopBuffer_DeleteFirst_End_Porcess;
	//如果队列为空，则返回
	if(!GetTokenCount())
		goto CToolsPopBuffer_DeleteFirst_End_Porcess;
	{ //同上，这不是if 的大括号，是限定变量作用域的大括号
		char* pFirstTokenBegin= //求出第一个Token 起始点
			TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(m_pBuffer);
		SToolsPopBufferTokenHead* pFirstTokenHead= //第一个Token 头指针
			(SToolsPopBufferTokenHead*)pFirstTokenBegin;
		int nFirstTokenLength= //第一个Token 总长度
			TOOLS_POP_BUFFER_TOKEN_LENGTH(pFirstTokenHead->m_nDataLength);
		char* pSecondTokenBegin= //求出第二个Token 起始点
			pFirstTokenBegin+nFirstTokenLength;
		int nCopyBytesCount= //求出需要Move 的字节数
			m_pHead->m_nAllBytesCount- //队列总的Byte 数减去
			SToolsPopBufferHeadSize- //队列头长度，再减去
			nFirstTokenLength; //第一个Token 的长度
		memcpy(pFirstTokenBegin, //Move 动作
			pSecondTokenBegin, //利用第二个Token 后面的数据
			nCopyBytesCount); //把第一个Token 从物理上覆盖掉
		m_pHead->m_nAllBytesCount-= //修订AllBytes，
			nFirstTokenLength; //减去第一个Token 长度
		m_pHead->m_nTokenCount--; //Token 总数-1
		bRet=true; //删除成功
	}
CToolsPopBuffer_DeleteFirst_End_Porcess:
	return bRet;
}

//普通缓冲区方式，弹出第一个元素数据
int CToolsPopBuffer::GetAndDeleteFirst(char* szBuffer,int nBufferSize)
{
	if(!ICanWork()) return 0; //防御性设计
	//请注意，这里不校验获得是否会成功，依赖上层程序保证缓冲区够大。
	int nRet=GetFirst(szBuffer,nBufferSize); //先获得第一个元素数据
	DeleteFirst(); //再删除第一个元素
	return nRet;
}

//Buffer 类方式，弹出第一个元素数据
int CToolsPopBuffer::GetAndDeleteFirst(CToolsBuffer* pBuffer)
{
	if(!ICanWork()) return 0; //防御性设计
	int nRet=GetFirst(pBuffer); //获得第一个元素数据
	DeleteFirst(); //删除第一个元素
	return nRet;
}

//枚举遍历所有数据，提交回调函数处理，并且删除数据，返回经过处理的Token 个数
//为了避免过多的动态内存分配细节，或者缓冲区的组织，本函数没有使用GetFirst
int CToolsPopBuffer::MoveAllData(
	_TOOLS_ENUM_DATA_CALLBACK pCallBack, //回调函数指针
	PVOID pCallParam) //代传的void*参数指针
{
	int nMovedTokenCount=0; //统计变量返回值
	bool bCallbackRet=true; //这是记录回调函数返回值的变量
	if(!pCallBack) //防御性设计，如果回调函数为空，不做事
		goto CToolsPopBuffer_MoveAllData_End_Process;
	if(!ICanWork()) //如果条件不满足，不做事
		goto CToolsPopBuffer_MoveAllData_End_Process;
	while(m_pHead->m_nTokenCount) //以TokenCount 为while 循环的条件
	{
		char* pFirstTokenBegin= //求得第一个Token 开始点
			TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(m_pBuffer);
		SToolsPopBufferTokenHead* pFirstTokenHead= //求得第一个Token 的头指针
			(SToolsPopBufferTokenHead*)pFirstTokenBegin;
		char* pFirstTokenData= //求得第一个Token 的数据指针
			TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(pFirstTokenBegin);
		//请注意此处回调，将第一个Token 数据传给回调函数，且获得回调函数返回值
		bCallbackRet=pCallBack(pFirstTokenData,
			pFirstTokenHead->m_nDataLength,
			pCallParam);
		DeleteFirst(); //删除第一个Token
		nMovedTokenCount++; //返回值+1
		if(!bCallbackRet) break; //如果回调返回假，中止循环
	}
CToolsPopBuffer_MoveAllData_End_Process:
	return nMovedTokenCount; //返回处理的Token 个数
}










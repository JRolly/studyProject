#include "MemQueue.h"


//构造函数，初始化所有变量
CToolsMemoryQueue::CToolsMemoryQueue(
	CToolsLowDebug* pDebug,
	CToolsMemoryPoolWithLock* pMemPool,
	char* szAppName,
	int nMaxToken)
{
	m_nMaxToken=nMaxToken; //保留最大Token 上线
	m_pLast=null; //注意，此处加速因子m_pLast 被设置为null
	m_pDebug=pDebug; //保留debug 对象指针
	m_pMemPool=pMemPool; //保留内存池指针
	SafeStrcpy(m_szAppName,szAppName, //保留AppName
		TOOLS_APPLICATION_NAME_SIZE);
	m_pHead=null; //注意，m_pHead 被设置为null，表示无Token
	m_nTokenCount=0; //Token 计数器被设置为0
}
//析构函数，清除所有的Token，释放申请的内存
CToolsMemoryQueue::~CToolsMemoryQueue()
{
	if(m_pHead)
	{
		DeleteATokenAndHisNext(m_pHead);//此处递归释放
		m_pHead=null;
	}
}

bool CToolsMemoryQueue::ICanWork(void)
{
	if(!m_pDebug) return false; //检查debug 对象指针
	if(!m_pMemPool) return false; //检查内存池指针
	return true;
}

void CToolsMemoryQueue::CleanAll(void)
{
	if(!ICanWork()) return; //防御性设计
	while(DeleteFirst()){} //循环删除第一个对象，直到队列为空
	//注意，本类的DeleteFirst 返回删除结果
}

int CToolsMemoryQueue::GetFirstLength(void)
{
	int nRet=0;
	if(m_pHead) //如果ICanWork 为否，m_pHead 必然为null
	{
		nRet=m_pHead->m_nDataLength; //取出第一个Token 的长度
	}
	return nRet;
}

//私有函数，打印某一个指定的Token，并且递归其后所有的Token
void CToolsMemoryQueue::PrintAToken(SToolsQueueTokenHead* pToken)
{
	if(!pToken) return; //防御型设计，递归结束标志
	TOOLS_PRINTF("Queue Token: pToken:%p, \
					 Buffer=%p, Length=%d, m_pNext=%p\n",
					 pToken, //Token 指针
					 pToken->m_pBuffer, //数据缓冲区指针
					 pToken->m_nDataLength, //数据长度
					 pToken->m_pNext); //下一Token 指针
	if(pToken->m_pBuffer) //以二进制方式格式化输出业务数据
		dbg_bin(pToken->m_pBuffer,pToken->m_nDataLength);
	if(pToken->m_pNext) //递归
		PrintAToken(pToken->m_pNext);
}

//打印所有的Token 内容，公有函数入口
void CToolsMemoryQueue::PrintInside(void)
{
	if(!ICanWork()) return; //防御性设计
	//输出队列关键信息
	TOOLS_PRINTF("Queue: Token Count=%d, Head=0x%p, Last=0x%p\n",
		m_nTokenCount, //Token 总数
		m_pHead, //队列头Token 指针
		m_pLast); //队列尾Token 指针
	if(m_pHead) //从队列头开始递归
		PrintAToken(m_pHead);
}

//如果删除成功，返回真，否则返回假
bool CToolsMemoryQueue::DeleteATokenAndHisNext(
	SToolsQueueTokenHead* pToken) //纯C 调用，需给定Token 指针
{
	bool bRet=false; //准备返回值
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_DeleteATokenAndHisNext_End_Process;
	if(pToken->m_pNext) //注意，如果有m_pNext，递归删除
	{
		DeleteATokenAndHisNext(pToken->m_pNext);
		pToken->m_pNext=null;
	} 
	if(pToken->m_pBuffer) //开始删除本对象
	{
		m_pMemPool->Free(pToken->m_pBuffer);//向内存池释放数据缓冲区
		pToken->m_nDataLength=0; //所有变量赋初值
		pToken->m_pBuffer=null;
	} 
	m_pMemPool->Free((void*)pToken); //向内存池释放Token 头结构体缓冲区
	m_nTokenCount--; //Token 总计数器-1
	bRet=true;
CToolsMemoryQueue_DeleteATokenAndHisNext_End_Process:
	m_pLast=null; //删除动作后，由于链表尾部发生变化
	//加速因子失效，因此需要清空
	return bRet;
}

//创建一个Token 头内存区域，并初始化，返回Token 指针
SToolsQueueTokenHead* CToolsMemoryQueue::GetAToken(void)
{
	SToolsQueueTokenHead* pToken=null; //准备返回值
	char* pTokenBuffer=null; //准备临时指针
	char szNameBuffer[256]; //准备说明文字缓冲区
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_GetAToken_End_Process;
	//格式化说明文字，注意其中用到了AppName
	SafePrintf(szNameBuffer,256,"%s::Token_Head",m_szAppName);
	//开始申请Token 头内存块
	pTokenBuffer=(char*)m_pMemPool->Malloc( //请注意对说明文字的使用
		SToolsQueueTokenHeadSize,szNameBuffer);
	if(!pTokenBuffer)
	{ //申请失败，返回null
		TOOLS_DEBUG("%s::GetAToken(): ma lloc new token fail!\n",m_szAppName);
		goto CToolsMemoryQueue_GetAToken_End_Process;
	} 
	//强制指针类型转换，将申请到的二进制缓冲区指针转化成Token 头结构体指针
	pToken=(SToolsQueueTokenHead*)pTokenBuffer;
	pToken->m_nDataLength=0; //初始化过程，赋初值
	pToken->m_pNext=null;
	pToken->m_pBuffer=null;
	m_nTokenCount++; //Token 总数+1
CToolsMemoryQueue_GetAToken_End_Process:
	return pToken;
}

//将数据保存到一个Token，如果该Token 已经保存数据，
//则按照链表顺序向下寻找，直到找到一个空的Token，把数据放置其中。
//如果成功，返回数据长度，如果失败，返回0
int CToolsMemoryQueue::AddLast2ThisToken(
	SToolsQueueTokenHead* pToken, //需要处理的Token 头指针
	char* szData, //需要存储数据的指针
	int nDataLength) //需要存储的数据的长度
{
	int nRet=0; //准备返回值
	char szNameBuffer[256]; //准备说明文字缓冲区
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
	if(!pToken->m_pBuffer)
	{
		//如果本Token 未包含有效数据，则保存到自己。
		SafePrintf(szNameBuffer,256, //格式化内存块说明文字
			"%s::pToken->m_pBuffer",
			m_szAppName);
		pToken->m_pBuffer=(char*)m_pMemPool->Malloc( //向内存池申请内存块
			nDataLength,szNameBuffer);
		if(!pToken->m_pBuffer)
		{ //申请失败，报警
			TOOLS_DEBUG("%s::AddLast2ThisToken(): \
					   ma lloc pToken->m_pBuffer fail!\n",
					   m_szAppName);
			goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
		} 
		memcpy(pToken->m_pBuffer,szData,nDataLength); //拷贝业务数据到内存块
		pToken->m_nDataLength=nDataLength; //填充Token 头中的管理信息
		nRet=nDataLength; //给返回值赋值
		m_pLast=pToken; //保存加速因子(m_pLast 维护)
		goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
	}
	else
	{
		//保存在下家
		if(!pToken->m_pNext)
		{
			//如果指向下家的链指针为空，则利用GetAToken 创建一个头挂接
			pToken->m_pNext=GetAToken();
			if(!pToken->m_pNext)
			{ //创建失败报警
				TOOLS_DEBUG("%s::AddLast2ThisToken(): ma lloc \
						   pToken->m_pNext fail!\n",
						   m_szAppName);
				goto CToolsMemoryQueue_AddLast2ThisToken_End_Process;
			}
		} 
		if(pToken->m_pNext) //递归调用
			nRet=AddLast2ThisToken(pToken->m_pNext,szData,nDataLength);
	}
CToolsMemoryQueue_AddLast2ThisToken_End_Process:
	return nRet;
}

//返回添加的数据长度，失败返回0
int CToolsMemoryQueue::AddLast(
	char* szData, //添加的数据指针
	int nDataLength, //数据长度
	int nLimit) //最大单元限制，-1 表示不限制
{
	int nRet=0; //准备返回值，初值为0
	if(!ICanWork()) //防御性设计，条件不符合，直接返回0
		goto CToolsMemoryQueue_AddLast_End_Process;
	if(0>=nLimit) //应用限制值
	{ //这是无限制
		if(m_nMaxToken<=m_nTokenCount) //无限制时，以m_nMaxToken 作为边界限制
			goto CToolsMemoryQueue_AddLast_End_Process;
	} 
	else
	{
		//这是有限制
		if(nLimit<=m_nTokenCount) //如果有nLimit，则使用这个参数限制
			goto CToolsMemoryQueue_AddLast_End_Process;
	} 
	if(!m_pHead)
	{
		m_pHead=GetAToken(); //这是链头第一次初始化
		if(!m_pHead)
		{
			TOOLS_DEBUG("%s::AddLast(): ma lloc m_pHead fail!\n",
				m_szAppName);
			goto CToolsMemoryQueue_AddLast_End_Process;
		}
	}
	if(m_pLast) //加速因子开始起作用，如果有值，直接跳入
	{
		nRet=AddLast2ThisToken(m_pLast,szData,nDataLength);
	} 
	else if(m_pHead) //如果加速因子无值，按传统模式，遍历插入
	{
		nRet=AddLast2ThisToken(m_pHead,szData,nDataLength);
	}
CToolsMemoryQueue_AddLast_End_Process:
	return nRet;
}

//针对普通缓冲区进行提取，应用层保证缓冲区够大
//返回提取数据的真实长度（不一定是上层缓冲区的大小）
int CToolsMemoryQueue::GetFirst(char* szBuffer,int nBufferSize)
{
	int nRet=0; //准备返回值变量
	//此处开始防御性设计
	if(!ICanWork())
		goto CToolsMemoryQueue_GetFirst_End_Process;
	if(!m_pHead) //检查链表是否有数据
		goto CToolsMemoryQueue_GetFirst_End_Process;
	if(!m_pHead->m_pBuffer) //检查第一个Token 是否有数据
	{
		TOOLS_DEBUG("%s::GetFirst(): m_pHead->m_pBuffer=null\n",
			m_szAppName);
		goto CToolsMemoryQueue_GetFirst_End_Process;
	} 
	if(m_pHead->m_nDataLength>nBufferSize) //检查给定的缓冲区是否足够
	{
		TOOLS_DEBUG("%s::GetFirst(): m_pHead->m_nDataLength > nBufferSize\n",
			m_szAppName);
		goto CToolsMemoryQueue_GetFirst_End_Process;
	}
	memcpy(szBuffer,m_pHead->m_pBuffer,m_pHead->m_nDataLength); //拷贝数据
		nRet=m_pHead->m_nDataLength; //返回值赋值
CToolsMemoryQueue_GetFirst_End_Process:
	return nRet;
}
//这是针对Buffer 类对象的提取函数
int CToolsMemoryQueue::GetFirst(CToolsBuffer* pBuffer)
{
	if(!ICanWork()) return 0; //防御性设计
	if(!pBuffer) return 0;
	//调用上一函数完成功能
	return pBuffer->BinCopyFrom(m_pHead->m_pBuffer,m_pHead->m_nDataLength);
}

//删除第一个Token，有可能失败，因为队列可能为空，失败返回假，成功返回真
bool CToolsMemoryQueue::DeleteFirst(void)
{
	bool bRet=false; //准备返回值
	SToolsQueueTokenHead* pSecond=null; //准备指向第二Token 的临时指针
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_DeleteFirst_End_Process;
	if(!m_pHead)
		goto CToolsMemoryQueue_DeleteFirst_End_Process;
	//注意，先提取First 中保留的Socond 指针，做中间保护
	pSecond=m_pHead->m_pNext;
	//m_pHead 的m_pNext 赋为空值，这是割裂与队列其他元素的连接关系
	m_pHead->m_pNext=null;
	//然后调用DeleteATokenAndHisNext 完成删除，由于上面的割裂，因此不会影响其他Token
	bRet=DeleteATokenAndHisNext(m_pHead);
	if(bRet)
	{
		m_pHead=pSecond; //重新给m_pHead 挂接第二Token
		//完成对原有First 的挤出工作
		//此时，原有Second 变为First
		if(!m_pHead) //这里有一个特例，
			m_pLast=null; //如果本次删除把该队列删空，
		//需要清除加速因子，避免下次操作失败
	}
	else
	{ //如果删除失败（这种情况一般不太可能，属于保护动作，不会真实执行）
		//将队列恢复原状，起码不至于在本函数内部造成崩溃，或内存泄漏，但打印报警
		TOOLS_DEBUG("%s::DeleteFirst(): delete m_pHead fail!\n",
			m_szAppName);
		m_pHead->m_pNext=pSecond; //删除失败，还得恢复回去
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


//返回弹出的数据总长度，但请注意，不是PopBuffer 的AllBytes，仅仅是业务数据长度和
int CToolsMemoryQueue::PopFromFirst4ToolsPopBuffer(
	CToolsPopBuffer* pPopBuffer) //需传入PopBuffer 指针
{
	int nRet=0; //准备返回值变量
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	if(!m_pHead)
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	if(!m_pHead->m_pBuffer) //这也是防御性设计，检索First 是否有数据
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): \
				   m_pHead->m_pBuffer=null\n",
				   m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(!m_pHead->m_nDataLength) //防御性设计，检索First 数据尺寸是否合法
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): \
				   m_pHead->m_nDataLength=0\n",
				   m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(!pPopBuffer) //检查给定的PopBuffer 是否合法
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): pPopBuffer=null\n",
			m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	}
	//没有使用GetAndDeleteFirst 之类的函数，而是直接访问结构体内部变量
	//就是预防如果PopBuffer 满了，弹出来的数据不好处理，这样也减少无谓的动态内存分配
	nRet=pPopBuffer->AddLast(m_pHead->m_pBuffer,m_pHead->m_nDataLength);
	if(m_pHead->m_nDataLength!=nRet)
	{
		//这是buffer 装满了
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(!DeleteFirst()) //删除First
	{
		TOOLS_DEBUG("%s::PopFromFirst4ToolsPopBuffer(): DeleteFirst fail\n",
			m_szAppName);
		goto CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process;
	} 
	if(m_pHead) //注意此处的递归逻辑，继续向下弹
		nRet+=PopFromFirst4ToolsPopBuffer(pPopBuffer);
CToolsMemoryQueue_PopFromFirst4ToolsPopBuffer_End_Process:
	return nRet;
}

//向普通缓冲区，以PopBuffer 方式打包信令
int CToolsMemoryQueue::PopFromFirst(char* szBuffer,int nBufferSize)
{
	int nCopyBytes=0; //准备返回值
	//准备一个PopBuffer 对象，注意，粘合作用。
	CToolsPopBuffer PopBuffer(szBuffer,nBufferSize);
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_PopFromFirst_End_Process;
	if(m_pHead)
	{ //调用上一函数实现打包
		nCopyBytes=PopFromFirst4ToolsPopBuffer(&PopBuffer);
		if(nCopyBytes) //如果弹出了数据（数据长度!=0）
			//取PopBuffer 的AllBytes 作为返回值
			nCopyBytes=PopBuffer.GetAllBytes();//这就是实际需要发送的字节数
	}
CToolsMemoryQueue_PopFromFirst_End_Process:
	return nCopyBytes;
}

//将受到的一段PopBuffer 格式化的信令编组，推入MemQueue 的队列末尾
//返回推入的数据字节常数，失败返回0
int CToolsMemoryQueue::Push2Last(char* szData,int nDataLength)
{
	int nRet=0;
	CToolsPopBuffer PopBuffer(szData,nDataLength,false); //此处粘合
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_Push2Last_End_Process;
	//开始调用PopBuffer 的功能，实现遍历循环
	//请注意回调函数和this 指针参数
	PopBuffer.MoveAllData(PushDataCallback,this);
CToolsMemoryQueue_Push2Last_End_Process:
	return nRet;
}

//回调函数，返回bool 值，如果返回false，遍历循环将退出，信令可能会丢失。
bool CToolsMemoryQueue::PushDataCallback(
	char* szData, //拆解出来的信令地址
	int nDataLength, //信令数据长度
	void* pCallParam) //代传的参数指针，就是前面的this
{
	//笔者的习惯，一般类内回调函数，均以this 指针作为透传参数
	//在回调函数内部，一般称之为pThis，以区别于普通成员函数的this
	//回调函数一进入，第一件事就是强制指针类型转换，创建pThis，方便调用。
	CToolsMemoryQueue* pThis=
		(CToolsMemoryQueue*)pCallParam;
	//此处为调用实例，pThis 指针就是this，因此，调用的是本对象的AddLast
	int nRet=pThis->AddLast(szData,nDataLength);
	//成功，返回thre，遍历继续，直到数据遍历结束
	if(nDataLength==nRet) return true;
	else
	{ //失败，可能是队列满了，返回false，终止遍历，
		/*pThis->*/TOOLS_DEBUG("%s::PushDataCallback(): I am full!\n",
			pThis->m_szAppName);
		return false;
	}
}

//将指定Token 的数据写入文件
void CToolsMemoryQueue::WriteAToken2File(
	SToolsQueueTokenHead* pToken, //指定的Token 指针
	FILE* fp) //指定的文件指针
{
	if(!ICanWork()) return; //防御性设计
	if(!fp) return;
	if(!pToken) return;
	if(!pToken->m_pBuffer) return;
	if(!pToken->m_nDataLength) return;
	//写入磁盘，由于磁盘写入，通常发生在服务器即将退出期间，这已经是数据保护最大的努力
	//此时磁盘写入再出现bug，没有任何办法再保护数据，只能丢失信令
	//因此，此处不再做校验，如果磁盘写入失败，即丢失信令
	//先写入每个Token 的数据长度
	fwrite((void*)&(pToken->m_nDataLength),sizeof(int),1,fp);
	//再写入每个Token 的实际数据
	fwrite((void*)pToken->m_pBuffer,sizeof(char),pToken->m_nDataLength,fp);
	if(pToken->m_pNext) //递归到下一Token
		WriteAToken2File(pToken->m_pNext,fp);
}

//这是公有方法入口函数
void CToolsMemoryQueue::Write2File(char* szFileName)//需给出文件名
{
	FILE* fp=null;
	if(!ICanWork()) return; //防御性设计
	if(!m_pHead) return;
	if(!GetTokenCount()) return; //如果队列为空，直接返回
	fp=fopen(szFileName,"wb"); //打开文件
	if(fp)
	{
		//首先，将队列控制信息写入磁盘，以便读回时直接使用
		fwrite((void*)&m_nTokenCount,sizeof(int),1,fp);
		//开始调用上述递归函数，开始逐Token 写入
		WriteAToken2File(m_pHead,fp);
		fclose(fp); //关闭文件
	}
}

//从一个磁盘Dump 文件中读入数据，返回读入的Token 总数
int CToolsMemoryQueue::ReadFromFile(char* szFileName)
{
	FILE* fp=null;
	int n=0;
	int i=0;
	int nReadTokenCount=0;
	int nDataLength=0;
	char* pTempBuffer=null;
	char szNameBuffer[256];
	if(!ICanWork()) //防御性设计
		goto CToolsMemoryQueue_ReadFromFile_End_Process;
	SafePrintf(szNameBuffer,256, //构建内存申请说明文字
		"%s::ReadFromFile::pTempBuffer",m_szAppName);
	//申请临时缓冲区，由于临时缓冲区需要在循环中多次ReMalloc，因此，开始只申请1Byte 即可
	pTempBuffer=(char*)m_pMemPool->Malloc(1,szNameBuffer);
	fp=fopen(szFileName,"rb"); //打开文件
	if(!fp) //失败则跳转返回
		goto CToolsMemoryQueue_ReadFromFile_End_Process;
	//读入队列控制头，即TokenCount 信息
	n=fread((void*)&nReadTokenCount,sizeof(int),1,fp);
	if(1>n)
	{
		TOOLS_DEBUG("%s::ReadFromFile(): read token count fail!\n",m_szAppName);
		goto CToolsMemoryQueue_ReadFromFile_End_Process;
	}
	for(i=0;i<nReadTokenCount;i++) //开始逐一读出各个Token
	{
		//首先读出当前Token 的数据长度
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
		//调用ReMalloc，根据读入的nDataLength 重新分配缓冲区，以便读入数据
		pTempBuffer=(char*)m_pMemPool->ReMalloc(
		pTempBuffer, //原有的临时缓冲区地址
		nDataLength, //新的数据长度
		false); //由于这个缓冲区马上被覆盖
		//因此无需拷贝旧数据
		if(!pTempBuffer)
		{
			TOOLS_DEBUG("%s::ReadFromFile(): rema lloc pTempBuffer fail!\n",
				m_szAppName);
			goto CToolsMemoryQueue_ReadFromFile_End_Process;
		} 
		//准备缓冲区成功，开始读入该Token 数据
		n=fread((void*)pTempBuffer,sizeof(char),nDataLength,fp);
		if(nDataLength>n)
		{
			TOOLS_DEBUG("%s::ReadFromFile(): read data fail!\n",m_szAppName);
			goto CToolsMemoryQueue_ReadFromFile_End_Process;
		} 
		//读入成功，AddLast 添加到最后
		if(!AddLast(pTempBuffer,nDataLength)) break;
	}
CToolsMemoryQueue_ReadFromFile_End_Process: //出错跳转标签
	if(pTempBuffer) //清除临时缓冲区
	{
		m_pMemPool->Free(pTempBuffer);
		pTempBuffer=null;
	} 
	if(fp) //关闭文件
	{
		fclose(fp);
		fp=null;
	} 
	return nReadTokenCount; //返回读入的Token 总数
}



/////////////////////////////////////
//MemQueue 的线程安全封装类

//构造函数，请注意，参数和MemQueue 完全一样
CToolsMemoryQueueWithLock::CToolsMemoryQueueWithLock(
	CToolsLowDebug* pDebug,
	CToolsMemoryPoolWithLock* pMemPool,
	char* szAppName,
	int nMaxToken)
{
	//保存AppName
	SafeStrcpy(m_szAppName,szAppName,TOOLS_APPLICATION_NAME_SIZE);
	m_pMemPool=pMemPool; //保存内存池指针，析构函数要用
	m_pQueue=new CToolsMemoryQueue(pDebug, //实例化封装对象
		pMemPool,m_szAppName,nMaxToken);
	if(m_pQueue)
	{
		char szNameBuffer[256];
		//如果实例化成功，则试图在内存池注册它，以实现指针管理
		//注册前，先利用AppName 构造说明文字
		SafePrintf(szNameBuffer,256,"%s::m_pQueue",m_szAppName);
		m_pMemPool->Register(m_pQueue,szNameBuffer);
	}
}

//析构函数，摧毁封装对象
CToolsMemoryQueueWithLock::~CToolsMemoryQueueWithLock()
{
	m_Lock.EnableWrite(); //此处是带写函数，因此使用写锁
	{
		if(m_pQueue)
		{
			m_pMemPool->UnRegister(m_pQueue); //这部反注册很重要，否则内存池报警
			delete m_pQueue; //摧毁对象
			m_pQueue=null; //习惯，变量摧毁后立即赋初值
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












#include "MemoryTools.h"



CToolsMemoryStackToken::CToolsMemoryStackToken(int nBlockSize,
	CToolsLowDebug* pDebug)
{
	m_pDebug=pDebug; //����Debug ����ָ��
	m_ulBlockSize=(ULONG)nBlockSize; //���汾���������ڴ��ߴ�
	m_nBlockOutSide.Set(0); //ͳ�Ʊ�����ʼ��
	m_nBlockInSide.Set(0);
	m_Lock.EnableWrite(); //ע�ⵥд�������ʹ�ã�����д��
	{
		m_pFirstSon=null; //ָ�������ʼ��
		m_pNext=null; //ע�⣬�������������½��е�
	}
	m_Lock.DisableWrite();
} 
CToolsMemoryStackToken::~CToolsMemoryStackToken()
{
	if(m_nBlockOutSide.Get())
	{
		//ע��˴�������⵽�����ڴ�����ⱻӦ�ó���ʹ�ã�
		//������������Ҫ���������ڴ��ֹͣ����ʱ���������ѳ���Ա��
		TOOLS_DEBUG("Tools Memory Stack: lost %d * %d\n",
			m_ulBlockSize,m_nBlockOutSide.Get());
	} 
	m_Lock.EnableWrite();
	{
		//�˴������������£��ݻ����е���֦����֦�����ǵݹ�����
		if(m_pFirstSon) DestroySon(m_pFirstSon);
		m_pFirstSon=null;
		if(m_pNext) delete m_pNext;
		m_pNext=null;
	} 
	m_Lock.DisableWrite();
}

void* CToolsMemoryStackToken::Malloc(int nSize,
	CMRSWint& nAllBlockCount,
	CMRSWint& nMemoryUse)
{
	void* pRet=null; //׼�����ص�ָ��
	SToolsMemoryBlockHead* pNew=null; //�м����
	//��ע��������ʹ��
	//����һ��Ӧ�ó������ݿ�ĳ��ȣ�����һ���ڴ�����ʵ��С����n+8
	//#define TOOLS_MEM_BLOCK_SIZE(nDataLength) \
	// (nDataLength+SToolsMemoryBlockHeadSize)
	//���������С+8���ٺͱ���������С�Ƚϣ��Դ��޶��������ݴ�����ƫ��
	//���ﻹ��һ�����ɣ�m_ulBlockSize û��ʹ����������������Ϊm_ulBlockSize
	//�ӹ��캯���������е�ʹ�ö���ֻ���ģ�������Ҫ���������Լ�������
	if((TOOLS_MEM_BLOCK_SIZE(nSize))<m_ulBlockSize)
	{
		//���ʾ������Ĵ�С�������������������뽫�ӱ��ڵ���֦���
		m_Lock.EnableWrite(); //����
		{
			//�ж��Ƿ��п��е��ڴ�鱸��
			if(!m_pFirstSon)
			{
				//���û�У���Ҫ��ϵͳ������һ���ڴ��
				//ע�������ǿ��ָ������ת����������ڴ�飬�ڱ�����ֱ��
				//ת���ɹ���ṹ��ָ�룬�Ա����
				//ע������Ĵ�С����m_ulBlockSize�����
				//����������������ڴ�飬����һ����С�ġ�
				pNew=(SToolsMemoryBlockHead*)malloc(m_ulBlockSize);
				if(pNew) //��ȫ���
				{
					//ͳ�ƺ���+1����Ϊ����ڴ�����ϻ�����ȥ��
					//��ˣ��޶�m_nBlockOutSide+1��InSide ���ӡ�
					m_nBlockOutSide.Add();
					//���ǰ����ϲ�ͳ�����ڴ��ֽ�����ע�⣬���Ǵ�ַ���ã����ݻ��ϴ�
					nMemoryUse.Add(m_ulBlockSize);
					//��ʼ����������ڴ�飬����С��Ϣ
					//ע�⣬�����Free Ҫ�õ������Ϣ���Ҷ�Ӧ����֦�ڵ㡣
					pNew->m_ulBlockSize=m_ulBlockSize;
					//��������ָ��ֻ���ڹ���ʱʹ�ã������ȥ�ģ���ʱ���
					pNew->m_pNext=null;
					//������ؼ�����ע�⣬ʹ���˺���㣬p1=p0+8�����p1��
					//���ظ�Ӧ�ó���ʹ��
					pRet=TOOLS_MEM_BLOCK_DATA(pNew);
					//ͳ�Ʊ������ڴ������+1
					nAllBlockCount.Add();
				}
				//�������ʧ�ܣ���ֱ�ӷ���null ��Ӧ�ó���
			}
			else
			{
				//�����п����ڴ������
				//ֱ����ȡ�����һ�飬Ҳ����ջ�����¼�����ڴ��
				pNew=m_pFirstSon;
				//����ָ���޶���ע�⣬������m_pFirstSon �Ѿ�ָ����ԭ���ڶ����ڴ�
				m_pFirstSon=pNew->m_pNext;
				//ͬ�ϣ������ȥ���ڴ�飬m_pNext ���ã����
				pNew->m_pNext=null;
				//���p1=p0+8�����ظ�Ӧ�ó���ʹ��
				pRet=TOOLS_MEM_BLOCK_DATA(pNew);
				//ע��˴������ǰ��ڲ����ڴ���ٷ�������
				//��ˣ�OutSide+1��InSide-1
				m_nBlockOutSide.Add();
				m_nBlockInSide.Dec();
			}
		}
		m_Lock.DisableWrite(); //����
	}
	else
	{
		m_Lock.EnableWrite(); //��д��
		{
			//���Ǽ���ֵܽڵ��Ƿ��Ѿ����������û�У��򴴽�֮��
			//ע�⣬�˴���m_pNext ��д��ϵ����ˣ���д����
			if(!m_pNext)
			{
				m_pNext=new CToolsMemoryStackToken(m_ulBlockSize*2,m_pDebug);
			}
		} 
		m_Lock.DisableWrite(); //��д��
		//�˴�����дģʽת���ǳ���Ҫ������ר������
		m_Lock.AddRead(); //�Ӷ���
		{
			//�����󴫵ݸ��ֵܽڵ��Malloc ��������
			if(m_pNext)
				pRet=m_pNext->Malloc(nSize,nAllBlockCount,nMemoryUse);
			//����ֵܽڵ㴴��ʧ�ܣ���ʾϵͳ�ڴ����Ҳʧ�ܣ����ؿ�ָ���Ӧ�ó���
		} 
		m_Lock.DecRead(); //�����
	} 

	//����ɹ�����������ڴ�����
	if (pRet)
		memset((char*)pRet, '\0', nSize);

	return pRet;
}

//Free �������������CloseFlag ��־��ע�⣬�ⲿ�����ָ��Ϊp1����Ҫ����p0=p1-8
//��ĳ������£�Free ���ܻ�ʧ�ܣ���ˣ���Ҫ����һ��bool ֵ����ʾ�ͷŽ����
bool CToolsMemoryStackToken::Free(void* pPoint,bool bCloseFlag)
{
	bool bRet=false; //׼������ֵ����
	//ע��������pOld���Ѿ��Ǽ����p0=p1-8
	SToolsMemoryBlockHead* pOld=TOOLS_MEM_BLOCK_HEAD(pPoint);
	//���ȼ��ָ���ڴ���С�Ƿ��ɱ��������
	if(m_ulBlockSize==pOld->m_ulBlockSize)
	{
		//�˴����ж��ڴ������Ƿ��ޣ���������޶ֱ���ͷţ��������ô���
		//��ˣ����ڳ��޵��ڴ�飬�����ڵ�������Ǵ��ڵģ����������֦Ϊ�ա�
		if(TOOLS_MEMORY_STACK_MAX_SAVE_BLOCK_SIZE<=m_ulBlockSize)
		{
			free(pOld);
			m_nBlockOutSide.Dec(); //ע�⣬�����޶�OutSide ͳ�Ʊ�����
		} 
		else if(bCloseFlag)
		{ //��CloseFlag Ϊ�棬����������֦��ֱ���ͷ�
			free(pOld);
			m_nBlockOutSide.Dec();
		} 
		else
		{ //���������������㣬����������֦ջ��׼�������ڴ��
			m_Lock.EnableWrite(); //��д��
			{ //��ע��������͵�ѹջ�������¼����ڴ�飬���ڵ�һ����
				//ԭ�е��ڴ�飬�����ӵ����ڴ�����һ�����Ƚ��ȳ�
				pOld->m_pNext=m_pFirstSon;
				m_pFirstSon=pOld;
			} 
			m_Lock.DisableWrite(); //���д��
			m_nBlockOutSide.Dec(); //�޶�ͳ�Ʊ���
			m_nBlockInSide.Add();
		}
		//��ע�ⷵ��ֵ��λ�ã�ֻҪ�Ǳ��ڵ㴦�����᷵��true��
		bRet=true;
	}
	else
	{ //������һ��Ĭ���ƶ������ҹ�ע��
		//��һ���������еĶ�̬�ڴ����붼���ɱ��ڴ�ع����ǣ�
		//�ڴ��һ���Ǳ����ڴ�ط��䣬��ˣ����ڴ���ͷ�ʱ��
		//���Ӧ����֦�ڵ㣬���ڴ����Ԫ�ڵ㣬һ������
		//��ˣ�Free ���ٴ���m_pNext �Ĵ������⣬����ֱ�ӵ���
		m_Lock.AddRead(); //�Ӷ�����ԭ��ǰ���Ѿ�����
		{ //�˴��ݹ����
			if(m_pNext)
				bRet=m_pNext->Free(pPoint,bCloseFlag);
		} 
		m_Lock.DecRead(); //�����
	} return bRet;
}

//�ݻ����е��ӽڵ�
void CToolsMemoryStackToken::DestroySon(SToolsMemoryBlockHead* pSon)
{ //�������ǵ��͵Ķ�����˽�к������������̰߳�ȫ�ĺ������ã���ˣ��ڲ���������
	SToolsMemoryBlockHead* pObjNow=pSon; //�м����
	SToolsMemoryBlockHead* pOnjNext=null;
	while(1) //ѭ����ʽ
	{
		if(!pObjNow) break; //ѭ��������
		pOnjNext=pObjNow->m_pNext;
		free(pObjNow);
		m_nBlockInSide.Dec();
		pObjNow=pOnjNext;
	}
}

//�ڴ����Ԫ����Ϣ�������
void CToolsMemoryStackToken::PrintStack(void)
{
	//����һ�����͵ĵݹ麯����һ�δ�ӡ��֦�����е��ڴ����Ԫ������
	if(m_nBlockInSide.Get()+m_nBlockOutSide.Get())
	{ //��ֵ���ӡ����ֵ�����
		TOOLS_PRINTF(" [%ld] stack: all=%d, out=%d, in=%d\n",
			m_ulBlockSize, //������ʾ�ڴ��Ĵ�С
			m_nBlockInSide.Get()+m_nBlockOutSide.Get(),//���������ڴ�������
			m_nBlockOutSide.Get(), //�����ȥ���ڴ��
			m_nBlockInSide.Get()); //�ڲ����汸�õ��ڴ��
	}
	m_Lock.AddRead(); //�Ӷ���
	if(m_pNext)
	{
		m_pNext->PrintStack(); //ע�⣬����ݹ�
	}
	m_Lock.DecRead(); //�����
}



CToolsMemoryStack::CToolsMemoryStack(CToolsLowDebug* pDebug)
{
	m_CloseFlag.Set(false); //�رձ�־���
	m_pDebug=pDebug; //����debug ����ָ��
	m_pMaxPoint.Set(0); //ͳ�Ʊ�������ֵ
	m_nAllBlockCount.Set(0);
	m_nMemoryUse.Set(0);
	m_pHead=new CToolsMemoryStackToken( //����С�ڴ��ߴ�16Bytes��
		TOOLS_MEMORY_STACK_BLOCK_MIN, //������֦��һ���ڵ�
		m_pDebug);
	//ע�⣬�����������ڼ䣬��֦�ڵ�ֻ���������ݻ٣���ˣ�������Ϊ
	//��̬���������ڴ���Ƭ
} 
//��������
CToolsMemoryStack::~CToolsMemoryStack()
{
	//�˳�ʱ���㱨һ��ʹ�õ����ָ�룬�������Ա�۲�
	TOOLS_DEBUG("Memory Stack: Max Point= 0x%p\n",m_pMaxPoint.Get());
	//�����֦�����ǵݹ�ɾ������ÿ���ڵ���������
	if(m_pHead)
	{
		delete m_pHead;
		m_pHead=null;
	}
} 
//���з���������Close ��־
void CToolsMemoryStack::SetCloseFlag(bool bFlag)
{
	m_CloseFlag.Set(true);
}

void* CToolsMemoryStack::Malloc(int nSize)
{
	void* pRet=null;
	if(0>=nSize) //��������ƣ����볤��<=0 ���ڴ�ռ�������
	{
		TOOLS_DEBUG("CToolsMemoryStack::Malloc(): ERROR! nSize=%d\n",nSize);
		return pRet;
	} 
	if(m_pHead)
	{
		//ע�⣬�˴�����ݹ���䣬��һС���߼����ݹ鵽���ʵĹ���Ԫ����
		pRet=m_pHead->Malloc(nSize,m_nAllBlockCount,m_nMemoryUse);
		//ͳ�ƹ��ܣ�ͳ������ָ��
		if(m_pMaxPoint.Get()<(int)pRet)
			m_pMaxPoint.Set((int)pRet);
	} 
	return pRet;
} 
bool CToolsMemoryStack::Free(void* pPoint)
{
	bool bRet=false;
	if(m_pHead) //�ݹ������֦�ڵ��ϵ�Free�����Free ����
	{
		bRet=m_pHead->Free(pPoint,m_CloseFlag.Get());
	} 
	return bRet;
}

//ReMalloc ���ܣ��ı�һ��ָ��ָ����ڴ����ĳߴ硣
//�ٶ���ָ���Ǳ��ڴ�ط���ģ���ˣ����ݸ�����ָ��p1�������������p0=p1-8��
//���ɴ˻��ԭ�гߴ����ʵ��С��
void* CToolsMemoryStack::ReMalloc(void* pPoint, //ԭ��ָ�룬p1
	int nNewSize, //�³ߴ�
	bool bCopyOldDataFlag) //���������ݱ�־
{
	void* pRet=null;
	SToolsMemoryBlockHead* pOldToken=null; //�ɵ�p0
	int nOldLen=0; //�ɵĳ���
	if(0>=nNewSize) //��������ƣ���ֹ����Ƿ��ĳ��ȣ�<=0��
	{ //��ע���ӡ��ʽ���Ժ�������ʼ���������Ա�۲�Debug ��Ϣʱ��λ
		TOOLS_DEBUG("CToolsMemoryStack::ReMalloc(): ERROR! nNewSize=%d\n",
			nNewSize);
		goto CToolsMemoryStack_ReMalloc_Free_Old;
	} 
	//��ע��������ú����p0=p1-8
	pOldToken=TOOLS_MEM_BLOCK_HEAD(pPoint);
	//���ԭ�ڴ��Ĵ�С
	nOldLen=pOldToken->m_ulBlockSize;
	//�Ƚ��µĳ��Ⱥ��ڴ���ܳ��ȵĴ�С��
	//�ر�ע�⣬NewSize �������+8��������ڴ���С�������޶����
	if(TOOLS_MEM_BLOCK_SIZE(nNewSize)<=(ULONG)nOldLen)
	{
		//����֪�����ڴ�ջ������ڴ�鶼���Ѿ�ȡģ���ڴ�飬
		//�䳤��ͨ������16Bytes �������������ұ�Ӧ�ó���������ڴ�Ҫ��
		//��ˣ��ܿ���Ӧ�ó�����������ڴ��С����û�г���ԭ�ڴ�鱾��Ĵ�С
		//��ʱ���Ϳ���ֱ�ӽ�ԭ�ڴ�鷵�ؼ���ʹ�ã�������˵����ڴ������bug
		//���磬Ӧ�ó����һ������һ��260Bytes ���ڴ�飬�����ڴ�ȡģԭ��
		//�ڴ�ػ����һ��512Bytes ���ڴ�����ʹ�ã���Чʹ�ÿռ�512-8=504Bytes
		//�����ڶ��Σ�Ӧ�ó���ϣ��ʹ��һ��300Bytes ���ڴ���������С��504Bytes
		//��ʱ��ReMalloc �᷵�ؾ�ָ�룬�������ʹ�ã��������������룬�����Ч�ʡ�
		//���⣬������߼�����Ҳ���Ե�֪������������³ߴ籾���ͱ�ԭ�ռ�С
		//����ڶ��ε����ĳߴ粻��300Bytes������100Bytes��
		//Ҳ����Ϊ���ԭ�򣬼���ʹ��ԭ�ڴ棬������η���
		//����һ�����͵Ŀռ任ʱ���Ż�����һ���ڴ���˷ѣ�������η��䣬����Ч��
		//��������ԭ�ڴ淵�أ���Ȼ����ԭ�����ݣ����������追������
		pRet=pPoint;
		//��ע����������˵�һ��ת�㣬ֱ��������������
		//�������ָ�벻�ᱻFree�����Ƕ���ʹ�á�
		goto CToolsMemoryStack_ReMalloc_End_Process;
	} 
	//��ȷ���µĳߴ�Ƚϴ�ԭ���ڴ��޷����ܣ����������ڴ����Ԫ����������һ��
	pRet=m_pHead->Malloc(nNewSize,m_nAllBlockCount,m_nMemoryUse);
	//�����ڴ�����ɹ������ݿ�����ʾ��������
	if((pRet)&&(pPoint))
		if(bCopyOldDataFlag)
			memcpy(pRet,pPoint,nOldLen);
CToolsMemoryStack_ReMalloc_Free_Old:
	//��һ��ת�㣬����ʱ������ȷ����ʱ����Free ��ָ��
	m_pHead->Free(pPoint,m_CloseFlag.Get());
CToolsMemoryStack_ReMalloc_End_Process:
	//�����˳���ת�㣬������ָ��
	return pRet;
}

//��ӡ�ؼ�������ֵ
void CToolsMemoryStack::PrintInfo(void)
{
	TOOLS_PRINTF("block=%d, use=%d kbytes, biggest=%p\n",
		m_nAllBlockCount.Get(), //�����ڴ�������
		m_nMemoryUse.Get()/1024, //���ڴ�ʹ�ô�С��KBytes��
		m_pMaxPoint.Get()); //���ָ��
} 
//�ݹ�����ڴ����Ԫ�Ķ�Ӧ��������ӡ�������������
void CToolsMemoryStack::PrintStack(void)
{
	if(m_pHead)
		m_pHead->PrintStack();
}



//���캯��
CMemoryRegister::CMemoryRegister(CToolsLowDebug* pDebug)
{
	m_pDebug=pDebug;
	//��ʼ������
	m_pMaxPoint=null;
	m_nUseMax=0;
	m_nPointCount=0;
	//��ע��������ǵĽṹ���У���û�е�����Ʊ�ʾʹ�����ı���
	//��ˣ�һ�����Ա����ָ���Ƿ�Ϊnull ����ʾ�ṹ���Ƿ�ʹ��
	//���Ҫ�󣬳�ʼ��ʱ���Ƚ����е��ڴ��ָ�����Ϊnull��������������ж�
	int i=0;
	for(i=0;i<TOOLS_MEMORY_REGISTER_MAX;i++)
	{
		m_RegisterArray[i].m_pPoint=null;
		TOOLS_CLEAN_CHAR_BUFFER(m_RegisterArray[i].m_szInfo);
	}
}

CMemoryRegister::~CMemoryRegister()
{
	int i=0;
	m_Lock.Lock(); //����
	{
		//��ӡͳ�Ƶ����ָ�룬���ѳ���Ա
		TOOLS_DEBUG("CMemoryRegister: Max Register Point= 0x%p\n",m_pMaxPoint);
		//��������ʹ�õĽṹ�壬�����ָ���0����ʾû���ͷŵģ���ӡ������Ϣ��
		//��ע�⣬Ϊ���Ż�Ч�ʣ�����ѭ�����յ���m_nUseMax�������û��ʹ�õĲ���
		for(i=0;i<m_nUseMax;i++)
		{
			if(m_RegisterArray[i].m_pPoint)
			{
				//ԭ���ϣ�Ӧ�ð���Ӧ�ó����ͷţ������ǵ������ģ���ǻ���֧��ģ�顣
				//����������ִ��ʱ�����̼����رգ���ˣ��������������ͷ�
				TOOLS_DEBUG("***** Memory Lost: [%p] - %s\n",
					m_RegisterArray[i].m_pPoint,
					m_RegisterArray[i].m_szInfo);
			}
		}
	} 
	m_Lock.Unlock(); //����
}

void CMemoryRegister::RegisterCopy(
	SToolsMemoryRegister* pDest, //Ŀ��ṹ��ָ��
	void* pPoint, //��������ע��ָ��
	char* szInfo) //��������˵������
{
	pDest->m_pPoint=pPoint;
	if(szInfo) //����szInfo ������null�������Ҫ���ж�
	{ 
		//��ע�������SafeStrcpy ��ʹ�ã�������Զ�ǰ�ȫ�ģ�������ٺܶ��жϣ��Եúܼ��
		SafeStrcpy(pDest->m_szInfo,szInfo,TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE);
	} 
	else
		TOOLS_CLEAN_CHAR_BUFFER(szInfo);//���Ϊ�գ��򻺳�����Ϊ���ַ���
}

//ע�᷽��
void CMemoryRegister::Add(void* pPoint,char* szInfo)
{
	int i=0;
	m_Lock.Lock(); //����
	{
		//���ͳ�ƹ��ܣ������ע���ָ������ָ��󣬸������ָ��
		if(pPoint>m_pMaxPoint) m_pMaxPoint=pPoint;
		//ѭ�������Ѿ�ʹ�õ���������Ѱ����Del ���µĿ������ظ�ʹ��
		//ע�⣬ѭ�����յ���m_nUseMax���������������Ԫ
		for(i=0;i<m_nUseMax;i++)
		{
			//��ע�⣬����ṹ�屣���ָ��Ϊ�գ��ж�δʹ��
			if(!m_RegisterArray[i].m_pPoint)
			{
				//ͳ������ָ������
				m_nPointCount++;
				//���ÿ������ܺ�����ִ����ʵ�Ŀ������������洫�����Ϣ����ע��
				RegisterCopy(&(m_RegisterArray[i]),pPoint,szInfo);
				//������ɣ�ֱ��������󣬷���
				goto CMemoryRegister_Add_End_Process;
			}
		} 
		//���ǵڶ��߼����䣬��ʹ�������޿�������Ҫ��������β
		//���ȣ�����Ƿ�����Խ�磬���Խ�磬����
		if(TOOLS_MEMORY_REGISTER_MAX<=m_nUseMax)
		{
			//ʹ��Debug ģ�鱨����ԭ���ϣ�����Ա�����Debug ��Ϣ�п�����һ��
			//��ʾ�ó��򲢷���ָ�����������������ƣ����Կ���
			//����TOOLS_MEMORY_REGISTER_MAX ��ֵ��
			TOOLS_DEBUG("***ERROR*** CMemoryRegister is full!\n");
			goto CMemoryRegister_Add_End_Process;
		} 
		//���ǽ�ע�����ݿ�����������β���߼�
		RegisterCopy(&(m_RegisterArray[m_nUseMax]),pPoint,szInfo);
		m_nPointCount++;
		m_nUseMax++;
	}
CMemoryRegister_Add_End_Process:
	m_Lock.Unlock(); //����
}

//��ע�ắ��
void CMemoryRegister::Del(void* pPoint)
{
	int i=0;
	m_Lock.Lock(); //����
	{
		//Ѱ�������ڴ�����
		for(i=0;i<m_nUseMax;i++)
		{
			//���ڲ�������ڴ�ָ���Ƿ���ȣ��ж��Ƿ��Ƕ�Ӧ�ṹ��
				if(pPoint==m_RegisterArray[i].m_pPoint)
				{
					//ͳ��ֵ-1
					m_nPointCount--;
					//����߼������ṹ��Ҳ�Ϳ��г������ȴ��´�Add ����
					m_RegisterArray[i].m_pPoint=null;
					TOOLS_CLEAN_CHAR_BUFFER(m_RegisterArray[i].m_szInfo);
					//����ѭ��������
					goto CMemoryRegister_Del_End_Process;
				}
		}
	}
CMemoryRegister_Del_End_Process:
	m_Lock.Unlock(); //����
}

//�޸�ע��ָ���ֵ
void CMemoryRegister::Modeify(void* pOld,void* pNew)
{
	int i=0;
	m_Lock.Lock();
	{
		//����Ҫ�л�ָ�룬�����Ҫ��һ��ͳ��
		if(pOld>m_pMaxPoint) m_pMaxPoint=pOld;
		for(i=0;i<m_nUseMax;i++)
		{
			//ע�⣬���еļ������ڴ��ָ����Ϊ���ݣ��൱�ڹ�ϣ�ϵ�key
			if(pOld==m_RegisterArray[i].m_pPoint)
			{
				//�����޶�ָ�룬���޶�˵������
				m_RegisterArray[i].m_pPoint=pNew;
				goto CMemoryRegister_Del_End_Process;
			}
		}
	} 
	//����һ����ʽ�ı��������һ��ָ��û���ҵ�����Ӧ�ò����������޸�
	//���ʾӦ�ó�����bug����ˣ�debug ���ѳ���Ա�޸�bug
	TOOLS_DEBUG("***ERROR*** CMemoryRegister::Modeify(): I can\'t found point!\n");
CMemoryRegister_Del_End_Process:
	m_Lock.Unlock();
}

//��Ϣ��ӡ����
void CMemoryRegister::PrintInfo(void)
{
	m_Lock.Lock();
	{
		TOOLS_PRINTF("memory pool: %d / %d, biggest=%p\n",
			m_nPointCount, //����ָ������
			m_nUseMax+1, //ע������ʹ�÷�Χ
			m_pMaxPoint); //ͳ�Ƶ����ָ��
	} 
	m_Lock.Unlock();
}


//���캯��
CToolsMemoryPoolWithLock::CToolsMemoryPoolWithLock(
	CToolsLowDebug* pDebug,
	bool bOpenRegisterFlag)
{
	m_pDebug=pDebug; //����debug ����ָ��
	m_pMemPool=new CToolsMemoryStack(m_pDebug); //ʵ�����ڴ�ջ����
	m_pRegister=null; //��ʼ������ָ�����
	m_pSocketRegister=null;
	//m_pLockRegister=null;
	if(bOpenRegisterFlag)
	{ //���ݱ�־λ�������Ƿ�ʵ��������ע�����
		m_pRegister=new CMemoryRegister(m_pDebug);
		m_pSocketRegister=new CSocketRegister(m_pDebug);
	} 
	//��ӡ�ڴ����ȷ������־
	TOOLS_DEBUG("Tools. Memory Pool Open, register flag=%d\n",bOpenRegisterFlag);
}

//��������
CToolsMemoryPoolWithLock::~CToolsMemoryPoolWithLock()
{
	//���δݻٸ����Ӷ���
	if(m_pRegister) //�����ע��ɾ������ı�׼д��
	{
		delete m_pRegister;
		m_pRegister=null;
	}
	if(m_pSocketRegister)
	{
		delete m_pSocketRegister;
		m_pSocketRegister=null;
	}
	if(m_pMemPool)
	{
		delete m_pMemPool;
		m_pMemPool=null;
	} 
	//��ӡ�ڴ����ȷ������־
	TOOLS_DEBUG("Tools. Memory Pool Close.\n");
}

//�����˳���־�������ڴ�ջ���ͷŹ���
void CToolsMemoryPoolWithLock::SetCloseFlag(bool bFlag)
{
	if(m_pMemPool) m_pMemPool->SetCloseFlag(bFlag);
}

//Malloc ����
void* CToolsMemoryPoolWithLock::Malloc(int nSize,char* szInfo)
{
	void* pRet=null;
	if(m_pMemPool)
	{
		pRet=m_pMemPool->Malloc(nSize); //�����ڴ�ջʵ���ڴ����
		if(pRet) Register(pRet,szInfo); //���ָ����Ч���Զ�ע��
	}
	return pRet;
}

//Free ����
void CToolsMemoryPoolWithLock::Free(PVOID pBlock)
{
	if(m_pMemPool)
		m_pMemPool->Free(pBlock); //�����ڴ�ջʵ��Free
	UnRegister(pBlock); //��ע��ָ��
}

//ReMalloc ����
void* CToolsMemoryPoolWithLock::ReMalloc(
	void* pPoint,
	int nNewSize,
	bool bCopyOldDataFlag)
{
	void* pRet=null;
	if(m_pMemPool)
	{ //�����ڴ�ջ�ض����ڴ������С
		pRet=m_pMemPool->ReMalloc(pPoint,nNewSize,bCopyOldDataFlag);
		if(m_pRegister)
		{
			if(pRet) //����ط���ɹ�����ע�������Modeify �µ�ָ��
				m_pRegister->Modeify(pPoint,pRet);
			else //���ʧ�ܣ�������ָ���Ѿ��ݻ٣������Ҫ��ע������з�ע���ָ��
				m_pRegister->Del(pPoint);
		}
	}
	return pRet;
}

//ָ��ע�᷽��
void CToolsMemoryPoolWithLock::Register(void* pPoint,char* szInfo)
{
	if(m_pRegister)
	{
		m_pRegister->Add(pPoint,szInfo);
	}
} 
//ָ�뷴ע�᷽��
void CToolsMemoryPoolWithLock::UnRegister(void* pPoint)
{
	if(m_pRegister)
	{
		m_pRegister->Del(pPoint);
	}
}
//Ӧ�ó���ע��һ��socket ��ʼ����ע�⣬һ��socket�����ܱ�ע���Σ����޸���˵������
//�������ǿ��Զ������ġ�
void CToolsMemoryPoolWithLock::RegisterSocket(Linux_Win_SOCKET s,char* szInfo)
{
	if(m_pSocketRegister)
	{
		m_pSocketRegister->Add(s,szInfo);
	}
}
//���еĹر�Socket ��������ע��+�رա�
void CToolsMemoryPoolWithLock::CloseSocket(Linux_Win_SOCKET& s)
{
	if(SocketIsOK(s))
	{
		if(m_pSocketRegister)
		{
			if(!m_pSocketRegister->Del(s))
			{
				//����һ������Ҫ�ı��������һ��socket������飬û�����ڲ�ע��
				//����Ӧ�ó���ȴcall ����������ͱ�ʾ�����ڴ���û��ע���socket ���
				//˵��socket �Ĺ�������������©������Ա�б�Ҫ������
				//����һ�ֿ��ܣ����socket ����������رգ���һ�ιر�ʱ��
				//����Ϣ�Ѿ���ע�ᣬ�ڶ��ξʹ����Ҳ���������
				//��˵������Ա��socket �Ĺر���������Ϊ����Ȼ������ʲô���⣬
				//����������޸ġ�
				TOOLS_DEBUG("CToolsMemoryPoolWithLock::CloseSocket(): \
						   Socket %d is not registered! but I have close it yet!\n",
						   s);
			}
		} 
		//��ʵ�عر�socket
		_Linux_Win_CloseSocket(s);
		s=Linux_Win_InvalidSocket; //�ر����������ֵ
	}
}

//�����ڴ�ջ���ܣ���ӡ��ϸ������Ϣ
void CToolsMemoryPoolWithLock::PrintTree(void)
{
	if(m_pMemPool) m_pMemPool->PrintStack();
} 
//��ӡ�����Ӷ�����Ϣ
void CToolsMemoryPoolWithLock::PrintInfo(void)
{
	if(m_pSocketRegister) //��ӡSocket ע�������Ϣ
		m_pSocketRegister->PrintInfo();
	if(m_pRegister) //��ӡָ��ע�������Ϣ
		m_pRegister->PrintInfo();
	if(m_pMemPool) //��ӡ�ڴ�ջ������Ϣ
		m_pMemPool->PrintInfo();
}
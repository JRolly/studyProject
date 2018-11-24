////////////////////////////////////////////////////////////
//							�ڴ��
////////////////////////////////////////////////////////////

#ifndef __MEMORY_TOOLS_H__
#define __MEMORY_TOOLS_H__



#include "IncludeDef.h"
#include "DebugTools.h"
#include "LockTools.h"
#include "SocketTools.h"

//��������ָ�������PC ƽ̨һ�㽨��10000��
//��Ƕ��ʽƽ̨��Ҫ���ݾ������������һ�㲻���鳬��1024
#ifndef TOOLS_MEMORY_REGISTER_MAX
#define TOOLS_MEMORY_REGISTER_MAX 10000
#endif

//����һ��Ӧ�ó������ݿ�ĳ��ȣ�����һ���ڴ�����ʵ��С����n+8
#define TOOLS_MEM_BLOCK_SIZE(nDataLength) \
	(nDataLength+SToolsMemoryBlockHeadSize)
//������ϵͳ������ڴ�飬������Ӧ�ó��������ڴ����ʵ��С����n-8
#define TOOLS_MEM_BLOCK_DATA_SIZE(nBlockSize) \
	(nBlockSize-SToolsMemoryBlockHeadSize)
//����Ӧ�ó����ͷŵ�ָ�룬������ʵ���ڴ��ָ�룬��p0=p1-8
#define TOOLS_MEM_BLOCK_HEAD(pData) \
	((SToolsMemoryBlockHead*)(((char*)pData)-SToolsMemoryBlockHeadSize))
//����һ���ڴ�����ʵָ�룬�������ڴ���ָ�룬��p1=p0+8
#define TOOLS_MEM_BLOCK_DATA(pHead) \
	(((char*)pHead)+SToolsMemoryBlockHeadSize)
//��С�ڴ�鳤�ȣ�16 Bytes���������ǹ���ռ��8 Bytes�������С���Ȳ�����С�ˣ�
//���������壬��ʹ������������С���ڴ�飬�ܷ����Ӧ�ó���ʹ�õģ�����8 Bytes��
#define TOOLS_MEMORY_STACK_BLOCK_MIN 16
//���ǹ��������ڴ�鳤�ȣ�1M����ǰ�ı�����ʾ�����������ƣ��ڴ��ֹͣ����
//��Ϊֱ����ϵͳ������ͷš�
#define TOOLS_MEMORY_STACK_MAX_SAVE_BLOCK_SIZE (1*1024*1024)



typedef struct _TOOLS_MEM_BLOCK_HEAD_
{
	ULONG m_ulBlockSize; //�ڴ��ĳߴ�
	struct _TOOLS_MEM_BLOCK_HEAD_* m_pNext; //ָ����һ����Ԫ�ص�ָ��
}SToolsMemoryBlockHead;
//���ṹ��ĳ��ȣ��������㣬�㶨Ϊ8Bytes
const ULONG SToolsMemoryBlockHeadSize=sizeof(SToolsMemoryBlockHead);

//�ڴ�ջ������Ĺ���Ԫ������ϰ����Token ������λ����Ԫ��Ԫ�صȽṹ��������ϰ�߶��ѡ�
//����ʹ����һ���ĵݹ��߼�
class CToolsMemoryStackToken
{ 
public:
	//���캯��������������ע�⣬�˴�Ҫ�����뱾�ڴ�����Ļ����ڴ��С����64 Bytes
	//�Լ�Debug �����ָ�룬��ģ����Ҫ����Debug �����м�������
	CToolsMemoryStackToken(int nBlockSize,CToolsLowDebug* pDebug);
	~CToolsMemoryStackToken();
public:
	//���������뺯��Malloc�����سɹ�������ڴ��ָ�룬ע�⣬��p1������p0
	//ע�����е�ͳ����ƣ�����Ϊ��Debug �͹۲췽��
	//���⣬��ע�⣬ͳ�Ʊ����Ǵ�ַ��������ˣ������ں����ڲ��޸ģ��ش���Ϣ
	// nAllBlockCount- nMemoryUse=�ڲ��Ŀ����ڴ������
	void* Malloc(int nSize, //Ӧ�ó���������ڴ�ߴ�
		CMRSWint& nAllBlockCount, //ͳ�Ʊ��������ع�������ڴ������
		CMRSWint& nMemoryUse); //ͳ�Ʊ��������ر�Ӧ�ó���ʹ�õ��ڴ������
	//�ͷź������˴���bCloseFlag ��һ�������Ż������ڳ����˳�ʱ
	//�ͷŵ��ڴ治���ٷ����ڴ�ջ��ֱ�ӱ�free �����Լӿ�����˳��ٶȡ�
	//ע�⣬�˴�Ӧ�ó��򴫽�������p1���ڲ���Ҫ��������p0 ʵ�ֲ�����
	bool Free(void* pPoint,bool bCloseFlag);
	//���Ǵ�������ܹ۲캯������Ҳ�Ǳ��߿����ײ�ģ���һ��ϰ��
	//�ײ�ģ�飬���ں�����UI �����Ļ��ᣬ��ˣ�����ڲ���ʲô���⣬����Ա���ѹ۲쵽
	//�ɴ˿��ܵ���bug����ˣ�һ��Եײ�ģ�飬����ϰ������һ����ӡ����
	//��ӡһЩ������Ϣ����������Ա�۲����ܻ�bug��
	void PrintStack(void);
private:
	//ϵͳ�˳�ʱ���ݹ����������ڴ��ĺ�����
	//����һ��ϰ����Brother���ֵܣ���Next����һ������������֦��
	//��Son�����ӣ���������֦
	void DestroySon(SToolsMemoryBlockHead* pSon);
private:
	//��һ�����ӵ�ָ�룬�������ͷ��
	SToolsMemoryBlockHead* m_pFirstSon;
	//����ָ���ֵܽڵ㣬����֦��һ�ڵ��ָ��
	CToolsMemoryStackToken* m_pNext;
	//����Ҫ����ƣ��̰߳�ȫ����ע�⣬Ϊ������Ч�ʣ�����ʹ���˵�д�����
	//���ݱ��ඨ�壬����������������ָ�����
	CMultiReadSingleWriteLock m_Lock;
	//�ڲ�����һ�±����������ڴ��ߴ磬���ǹ��캯�����������
	//���ȶ�ʹ��
	ULONG m_ulBlockSize;
	//����ͳ�Ʊ�������ע�⣬��Щ���ǵ�д�������ȫ�������������ֳɰ�ȫ�ġ�
	CMRSWint m_nBlockOutSide; //�����ȥ���ڴ������
	CMRSWint m_nBlockInSide; //�ڲ������Ŀ����ڴ������
	CToolsLowDebug* m_pDebug; //debug ����ָ��
};

//�ڴ�ջ
class CToolsMemoryStack
{ 
public:
	CToolsMemoryStack(CToolsLowDebug* pDebug); //���캯������Ҫ����Debug ����
	~CToolsMemoryStack();
public:
	//�ض���ָ��ָ����ڴ浥Ԫ��ַ�ռ��С��������ָ�룬���µĿռ�ߴ�
	//����ɹ���������Ч����ָ�룬ָ���ض����С֮����¿ռ䣬ʧ�ܷ���null
	//ע�⣬���������԰Ѿɿռ���������ݱ��ݵ��¿ռ䣬���ⲻһ����ȡ�����¿ռ��С
	void* ReMalloc(void* pPoint, //��ָ��
		int nNewSize, //�µĳߴ�����
		bool bCopyOldDataFlag=true); //�Ƿ񱸷ݾ����ݵı�־��Ĭ�ϡ��桱��
	//Malloc ��Free �����������ڴ�����Ԫ�������
	void* Malloc(int nSize);
	bool Free(void* pPoint);
	//�ڲ���Ϣ������������Ļὲ������
	void PrintStack(void);
	void PrintInfo(void);
	//��Ϊһ���Ż������app ��������رձ�־��
	//���е�free ������ֱ�ӵ���ϵͳ��free ��ɣ����ٱ�����stack �С�
	//�ӿ��˳��ٶȡ�
	void SetCloseFlag(bool bFlag=true);
	CToolsLowDebug* m_pDebug; //debug ���󣬴˴�Ϊ���Ż�����
private:
	CToolsMemoryStackToken* m_pHead; //ע�⣬������֦��ʼ�ĵ�һ���ڵ�
	CMRSWint m_pMaxPoint; //ͳ�Ƶ�ǰ�õ�������ڴ�ָ��
	CMRSWint m_nAllBlockCount; //ͳ���������õ��ڴ��
	CMRSWint m_nMemoryUse; //ͳ���ڴ�ʹ�õ����ֽ���
	CMRSWbool m_CloseFlag; //�رձ�ʾ
};


//�ڴ�ע����������ݽṹ
typedef struct _TOOLS_MEMORY_REGISTER_
{
	void* m_pPoint; //������ָ��
	char m_szInfo[TOOLS_MEMORY_BLOCK_INFO_MAX_SIZE]; //˵������
}SToolsMemoryRegister; //����ı�������
//ϰ����д���������˽ṹ�������������ߴ糣��
const ULONG SToolsMemoryRegisterSize=sizeof(SToolsMemoryRegister);

//�ڴ�ע����
class CMemoryRegister
{
public:
	CMemoryRegister(CToolsLowDebug* pDebug); //���캯������debug ����ָ��
	~CMemoryRegister();
public:
	//���һ��ָ�뼰��˵������
	void Add(void* pPoint,char* szInfo);
	//ɾ��һ��ָ�루���ڴ�鱻�ͷţ�ʧЧ��
	void Del(void* pPoint);
	//remalloc ��ʱ�����ָ��
	void Modeify(void* pOld,void* pNew);
	//��ӡ��Ϣ������Debug �͹۲�������
	void PrintInfo(void);
private:
	//����һ���ڲ����ߺ�������һ��ָ���˵�����֣����������涨��Ľṹ����
	void RegisterCopy(SToolsMemoryRegister* pDest,
	void* pPoint,char* szInfo);
private:
	CToolsLowDebug* m_pDebug; //Debug ����
	//��ע�⣬����ע���಻����ע�ᣬ���Ƿ�ע�ᶯ����������д����
	//��ʱ��ʹ�õ�д��������岻�����ʹ����ͨ�������
	CMutexLock m_Lock; //�̰߳�ȫ��
	//��ע���������ʹ���˾�̬���飬��Ҫԭ���ǿ��ǵ��ڴ�ע����
	//���ڴ�ص�һ�����ܣ��������ж�̬�ڴ����룬��������µĲ��ȶ����ء�
	//������ע�⣬�������ռ��ջ�ռ䣬����Ƕ��ʽ�豸������û����ô��Ҫ��ע��ҪԽ�硣
	SToolsMemoryRegister m_RegisterArray[TOOLS_MEMORY_REGISTER_MAX];
	//��������ʹ�ñ�־����ʾ��ǰ�������ʹ�ö��ٵ�Ԫ��
	//ע�⣬�ⲻ�ǲ���ָ���������ŷ�ע��Ľ��У������п����п���
	int m_nUseMax;
	//����һ��ͳ�ƣ�ͳ����ʷ����ע������ָ�룬ͳ������ʵ�á�
	void* m_pMaxPoint;
	//����ͳ�Ƶĵ�ǰ����ָ������
	int m_nPointCount;
};



//�ڴ����
class CToolsMemoryPoolWithLock
{ 
public:
	//���캯��
	//���ǵ�ĳЩ����Ĵ���ģ�飬�Ѿ��������ԣ�ȷ��û��bug�����Կ���������
	//�ر�ע�Ṧ�ܣ�������������ÿ���ڴ�������ͷ�ʱ��ע��ͷ�ע����߼�����������Ч��
	CToolsMemoryPoolWithLock(CToolsLowDebug* pDebug, //�����Debug ����ָ��
		bool bOpenRegisterFlag=true); //������ע�Ṧ�ܵı�־
	~CToolsMemoryPoolWithLock();
//////////////////////////////////////////////////////////
//ָ�����
public:
	//ע��ָ�룬ʵ�ֹ���ע����Ҫ˵������
	void Register(void* pPoint,char* szInfo);
	void UnRegister(void* pPoint);
private:
	CMemoryRegister* m_pRegister; //ָ��ע��������

	//////////////////////////////////////////////////////////
	//Socket ����
public:
	//ע��Socket��ʵ�ֹ���ע����Ҫ˵������
	void RegisterSocket(Linux_Win_SOCKET s,char* szInfo=null);
	//��Ӧ�ó���ִ��Close Socket������Socket ��Close �ɴ˴����
	void CloseSocket(Linux_Win_SOCKET& s); //�ر�Socket
private:
	CSocketRegister* m_pSocketRegister; //Socket ע��������
	///////////
public:
	//��Ϊһ���Ż������app ��������رձ�־��
	//���е�free ��ֱ��free�����ٱ�����stack �С�
	//�ӿ��˳��ٶȡ�
	void SetCloseFlag(bool bFlag=true);
	//���·���һ��ָ��Ŀռ䣬Ĭ�Ͽ���ԭʼ���ݵ��¿ռ䡣
	//���ǵ���ҿ��ܻ�ʹ��p=pMemPool->ReMalloc(p,1024);������ʽ��Ϊ�˷�ֹ�ڴ�й¶
	//���pPoint û�б��ҵ�,������ָ�����ʧ�ܣ���ָ��ᱻfree
	void* ReMalloc(void* pPoint,int nNewSize,bool bCopyOldDataFlag=true);
	//����һ���飬ע�⣬��Ҫһ��˵�����֣�˵��ָ����;������ע�����
	void* Malloc(int nSize,char* szInfo=null);
	//�ͷ�һ����
	void Free(PVOID pBlock);
	//��ʾ�����ڴ���������
	void PrintTree(void);
	//�ؼ���Ϣ��ʾ
	void PrintInfo(void);
	CToolsMemoryStack* m_pMemPool; //�ڴ�ջ����
	CToolsLowDebug* m_pDebug;
};




#endif	// __MEMORY_TOOLS_H__
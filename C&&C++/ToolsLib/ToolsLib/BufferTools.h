////////////////////////////////////////////////////////////
//							Buffer����
////////////////////////////////////////////////////////////




#ifndef __BUFFER_TOOLS_H__
#define __BUFFER_TOOLS_H__

#include "IncludeDef.h"
#include "MemoryTools.h"
#include "DebugTools.h"


//#define BUFFER_DYNAMIC		//buffer���أ�ʹ�þ�̬buffer���Ƕ�̬buffer

/////////////////////////////
///��̬Buffer
#ifdef BUFFER_DYNAMIC

#define TOOLS_BUFFER_STRING_MAX	1024

//Buffer ��
class TOOLSLIB_API CToolsBuffer
{ 
public:
	//���캯����ע�⴫��pMemPool �ڴ�ض���ָ�롣
	CToolsBuffer(CToolsMemoryPoolWithLock* pMemPool);
	~CToolsBuffer();
public: //��ע�⣬���͵Ĺ����������������ڲ�������ȫ�����У�����Ӧ�ò����
	CToolsMemoryPoolWithLock* m_pMemPool; //�ڴ��ָ��
	char* m_pData; //��̬�ڴ滺����ָ��
	int m_nDataLength; //�ڴ滺�������ȣ������ݳ��ȣ�
public:
	////////////////////////////////////
	//�ߴ����ú���
	bool SetSize(int nSize); //�����µĴ�С
	bool InsertSpace2Head(int nAddBytes); //��ǰ�����հ�
	bool AddSpace2Tail(int nAddBytes); //�ں������հ�
	void CutHead(int nBytes); //��ǰ����е�һ������
	void CutTail(int nBytes); //�Ӻ�����е�һ������

	////////////////////////////////////
	//��ֵת������
	bool SetInt(int n); //��һ�������Զ����Ʒ�ʽ���������������������ֽ�����
	int GetInt(void); //��������ʽ��û���������ֵ
	bool SetShort(short n); //��һ���������Զ����Ʒ�ʽ���������������������ֽ�����
	short GetShort(void); //�Զ����ͷ�ʽ��û���������ֵ
	bool SetChar(char n); //��һ���ֽ��Զ����Ʒ�ʽ������������
	char GetChar(void); //���ֽڷ�ʽ��û���������ֵ

	////////////////////////////////////
	//����������׷�Ӻ���
	//׷�����ݵ���󣬷����µ����ݳ���
	int AddData(char* szData,int nDataLength);
	//�������ݵ���ǰ�棬�����µ����ݳ���
	int InsertData2Head(char* szData,int nDataLength);

	////////////////////////////////////
	//���������ݿ�������
	//������һ��Ŀ�껺�������ܴ���Ļ�������������
	int BinCopyTo(char* szBuffer,int nBufferSize);
	//��һ����Դ�������������ݵ���������
	int BinCopyFrom(char* szData,int nDataLength);
	//������һ��Buffer ���󿽱����ݵ�������
	int BinCopyFrom(CToolsBuffer* pBuffer);

	////////////////////////////////////
	//�ı����ݿ�����������
	int StrCopyFrom(char* szString);
	int Printf(char* szFormat,...);

	////////////////////////////////////
	//���ݱȽϺ���
	int memcmp(char* szData,int nDataLength);
	int strcmp(char* szString);
};


#else
//////////////////////////////
//��̬Buffer

#define TOOLS_SAFE_BUFFER_MAX_SIZE	(100*1024)
	

class CToolsBaseLibrary;

class TOOLSLIB_API CToolsBuffer
{ 
public:
	//���ڶ���̬Buffer ��api ��ȫһ������ˣ����к������ͱ��뱣��һ�¡�
	CToolsBuffer(CToolsBaseLibrary* pToolsBaseLib);
	CToolsBuffer(CToolsMemoryPoolWithLock* pMemPool);
	~CToolsBuffer(){} //����û�ж�̬�ڴ���ͷ������������������κ���
public:
	////////////////////////////////////
	//���������ݿ�������
	int BinCopyTo(char* szBuffer,int nBufferSize);
	int BinCopyFrom(char* szData,int nDataLength);
	int BinCopyFrom(CToolsBuffer* pBuffer);

	////////////////////////////////////
	//�ı����ݿ�����������
	int StrCopyFrom(char* szString);
	int Printf(char* szFormat,...);

	////////////////////////////////////
	//�ߴ����ú���
	//�����µĴ�С
	bool SetSize(int nSize);
	//��ǰ�����հ�
	bool InsertSpace2Head(int nAddBytes);
	//�ں������հ�
	bool AddSpace2Tail(int nAddBytes);
	//��ǰ����е�һ������
	void CutHead(int nBytes);
	//�Ӻ�����е�һ������
	void CutTail(int nBytes);

	////////////////////////////////////
	//��ֵת������
	bool SetInt(int n);
	int GetInt(void);
	bool SetShort(short n);
	short GetShort(void);
	bool SetChar(char n);
	char GetChar(void);	

	////////////////////////////////////
	//����������׷�Ӻ���
	//׷�����ݵ���󣬷����µ����ݳ���
	int AddData(char* szData,int nDataLength);
	//�������ݵ���ǰ�棬�����µ����ݳ���
	int InsertData2Head(char* szData,int nDataLength);

	////////////////////////////////////
	//���ݱȽϺ���
	int memcmp(char* szData,int nDataLength);
	int strcmp(char* szString);

	////////////////////////////////////
	//������
	bool IHaveData(void);
public:
	char m_pData[TOOLS_SAFE_BUFFER_MAX_SIZE]; //��ע�����m_pData ��Ϊ��̬����
	int m_nDataLength;
	CToolsMemoryPoolWithLock* m_pMemPool; //����MemPool����Ϊ��Debug ����
};	

#endif	// BUFFER_DYNAMIC


///////////////////////
//PopBuffer ��

//ÿ��Token ��ͷ�ṹ��
typedef struct _TOOLS_POP_BUFFER_TOKEN_HEAD_
{
	int m_nDataLength; //��ʾ��Token �����ݳ���
}SToolsPopBufferTokenHead; //����Ľṹ���������
//�ṹ�峤�ȳ���
const ULONG SToolsPopBufferTokenHeadSize=sizeof(SToolsPopBufferTokenHead);

//PopBuffer ���й�������ṹ��
typedef struct _TOOLS_POP_BUFFER_HEAD_
{
	int m_nTokenCount; //�ڲ�������Ԫ�ظ���
	int m_nAllBytesCount; //ʹ�õ����ֽ���
}SToolsPopBufferHead; //����Ľṹ���������
//ϰ����д���������˽ṹ�壬���������䳤�ȳ���
const ULONG SToolsPopBufferHeadSize=sizeof(SToolsPopBufferHead);

//����PopBuffer ������������������ַ���ԣ��������ͷ�ṹ�屻��Ƴ�λ�ڻ������ʼ�ĵط�
//��ˣ����е�һ��Ԫ����ʵ�Ŀ�ʼ�㣬�ǻ�������ʼ�����ƫ��SToolsPopBufferHeadSize ����
//����궨�������Ԫ����������ʼָ�루�ַ���ָ�룩
#define TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(p) \
	(((char*)p)+SToolsPopBufferTokenHeadSize)

//���һ��׼��������е����ݳ���Ϊn�����Token ���ܳ��ȿ����øú����
#define TOOLS_POP_BUFFER_TOKEN_LENGTH(n) (n+SToolsPopBufferTokenHeadSize)
//�����֪һ��Token ����ʼָ��Ϊp�����Token ����������ʼ�������øú����
#define TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(p) \
	(((char*)p)+SToolsPopBufferHeadSize)

//����ö�ٻص�����,�����棬����ö�٣�ֱ������������ֱ�ӽ���ѭ��
typedef bool (*_TOOLS_ENUM_DATA_CALLBACK)(char* szData, //����ָ��
	int nDataLength, //���ݳ���
	void* pCallParam); //�����Ĳ���ָ��
//Demo������ʹ���߿���ֱ�ӿ���ʹ��
//static bool EnumDataCallback(char* szData,int nDataLength,void* pCallParam);


//������PopBuffer �࣬����ͬʱ���ճ����Ͷ�������������
class TOOLSLIB_API CToolsPopBuffer
{ 
public:
	//ע�⣬����ճ��������й��캯�����ڲ����������ⲿ���룬
	CToolsPopBuffer(char* szBuffer, //������ָ��
		int nBufferSize, //�������ߴ�
		bool bInitFlag=true); //�Ƿ��ʼ����־
	~CToolsPopBuffer();
public:
	//ʵ�֡���ճ�ϡ��ľ��庯������ʵ��ճ�ϵķ���
	void Set(char* szBuffer,int nBufferSize);
	//������������������������ݹ��㣬���������ͷ�
	void Clean(void);
	//�ڲ���Ϣ��ӡ������Debug �ã��൱��ǰ�ĵ�PrintfInfo
	void PrintInside(void);
	//�ܷ���ȷ�����ı�־����
	bool ICanWork(void);
public:
	//�������Ĺ��ܣ�׷�ӵ�ĩβ���˴�������ͨ��������Buffer ��
	int AddLast(char* szData,int nDataLength);
	int AddLast(CToolsBuffer* pBuffer);
public:
	//��õ�ǰ�ڲ�Ԫ�ظ���
	int GetTokenCount(void);
	//��õ�ǰʹ�õ������ֽ��������������ֽڣ�
	int GetAllBytes(void);
	//���ݼ������ͽ����е����ݳ��ȣ��ж��ڲ�ʣ��ռ��Ƿ���
	bool ICanSave(int nDataLength);
public:
	//��õ�һ��Ԫ�صĳ���
	int GetFirstTokenLength(void);
	//��ȡ��һ��Ԫ�أ�������ͨbuffer �汾����ҪӦ�ò㱣֤�����������㹻
	//��GetFirstTokenLength ���Բ�ѯ��һ��Ԫ�صĳ���
	int GetFirst(char* szBuffer,int nBufferSize);
	//��õ�һ��Ԫ�أ�����Buffer ��汾
	int GetFirst(CToolsBuffer* pBuffer);
	//ɾ����һ��Ԫ��
	bool DeleteFirst(void);
	//��ȡ��ɾ����һԪ�أ����ǴӶ����е�����һ��Ԫ��
	int GetAndDeleteFirst(char* szBuffer,int nBufferSize);
	int GetAndDeleteFirst(CToolsBuffer* pBuffer);
public:
	//ö�ٱ����������ݣ��ύ�ص�������������ɾ�����ݣ����ؾ��������Token ����
	int MoveAllData(_TOOLS_ENUM_DATA_CALLBACK pCallBack,PVOID pCallParam);
public:
	char* m_pBuffer; //��ؼ����ڲ�������ָ��
	int m_nBufferSize; //�ڲ�����������
private:
	//���Ƕ���ͷ��ָ�룬ע�⣬���ָ�벢���Ƕ�̬������ڴ�飬����ָ�򻺳���m_pBuffer ͷ
	SToolsPopBufferHead* m_pHead;
};





#endif	// __BUFFER_TOOLS_H__
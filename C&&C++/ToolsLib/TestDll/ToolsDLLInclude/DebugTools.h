
////////////////////////////////////////////////////////////
//							Debug����
////////////////////////////////////////////////////////////


#ifndef __DEBUG_TOOLS_H__
#define __DEBUG_TOOLS_H__

#include "IncludeDef.h"
#include "LockTools.h"


#define DEBUG_BUFFER_LENGTH 1024 //debug ��������С
#define TOOLS_DEBUG_FILENAME_LENGTH 256 //�ļ�����
#define FILENAME_STRING_LENGTH 256 //�ļ�������ͳһΪ256 �ֽ�
#define APP_INFO_OIT_STRING_MAX 1024


#define TOOLS_CLEAN_CHAR_BUFFER(p) (*((char*)p)='\0')

#define TimeSetNow(t) time(&t) //���ø�����t Ϊ��ǰʱ��



#ifdef WIN32
#define Linux_Win_vsnprintf _vsnprintf
#else // not WIN32
#define Linux_Win_vsnprintf vsnprintf
#endif



#define CON_DEBUG 1
#ifdef CON_DEBUG
#define CON_PRINTF printf
#else
#define CON_PRINTF /\
	/printf
#endif

//TOOLS_DEBUG�Ƿ���Ҫ������ļ�
#ifdef CON_DEBUG
#define TOOLS_DEBUG printf
#else
#define TOOLS_DEBUG /\
	/printf
#endif
//TOOLS_PRINTF�Ƿ���Ҫ������ļ�
#ifdef CON_DEBUG
#define TOOLS_PRINTF printf
#else
#define TOOLS_PRINTF /\
	/printf
#endif

#if 0	//VCʹ��
#define CON_DEBUG 1
#ifdef CON_DEBUG
#define CON_PRINTF TRACE
#else
#define CON_PRINTF /\
	/TRACE
#endif
#endif





//��ȫ���ַ�����������
//������˳���ţ�Ŀ�ĵ�ַ��Դ��ַ������������ֽ���
TOOLSLIB_API void SafeStrcpy(char *pDest, char *pSource,int nCount);

//��ȫ�ı���������
//szBuf: �û�ָ�������������
//nMaxLength���û�ָ��������������ߴ�
//szFormat����ʽ������ַ�������Σ������Ƕ����
//����������ַ�������strlen �ĳ��ȣ����������ġ�\0����
TOOLSLIB_API int SafePrintf(char* szBuf,int nMaxLength,char *szFormat, ...);


//��ָ���Ļ��������һ��ʱ����ַ���
//szBuf: �û�ָ�������������
//nMaxLength���û�ָ��������������ߴ�
//����������ַ�������strlen �ĳ��ȣ����������ġ�\0����
TOOLSLIB_API int GetATimeStamp(char* szBuf,int nMaxLength);


//��ָ���Ļ��������һ��ʱ����ַ���
// szFileName: �û�ָ��������ļ�
// szMode���������ļ��򿪷�ʽ�����ַ�����һ�㽨�顱a+��
//����������ַ�������strlen �ĳ��ȣ����������ġ�\0����
TOOLSLIB_API int dbg2file(char* szFileName,char* szMode, char *szFormat, ...);


//�����ʽ
//0000 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 xxxxxxxxxxxxxxxx
//��ASCII ��ʽ��ʾ��������
TOOLSLIB_API int dbg_bin_ascii(char* pPrintBuffer,char* pBuffer,int nLength);


//��ʮ�����Ʒ�ʽ��ʾָ�����������ݡ�
TOOLSLIB_API int dbg_bin_hex(char* pPrintBuffer,char* pBuffer,int nLength);


//****************��������ں���
//��16 �ֽ�Ϊһ�У���ʽ������������������ݡ�
TOOLSLIB_API void dbg_bin(char* pBuffer,int nLength);


#ifdef WIN32 //����Windows ����Ч
TOOLSLIB_API int SafeScanf(char* szBuffer, //�������뻺����ָ��
		int nLength); //�������뻺��������
#else // not WIN32
#endif


//��������

//��÷�0�����
TOOLSLIB_API inline int _GetNot0(void)
{
	int nRet=rand();
	if(!nRet) nRet++; //�����õ����������Ϊ0������1
	return nRet;
}

//���0
TOOLSLIB_API inline int _Get0(void)
{
	int nRet=rand();
	return nRet^nRet; //�����ʽ���0
}

//��ø��������ڵ������
TOOLSLIB_API inline int GetRandomBetween(int nBegin,int nEnd)
{
	int n=_GetNot0(); //���һ�������
	int nBetween=0;
	if(0>nBegin) nBegin=-nBegin; //��������Ʒ�ֹBegin Ϊ��ֵ
	if(0>nEnd) nEnd=-nEnd; //��������Ʒ�ֹEnd Ϊ��ֵ
	if(nBegin>nEnd) //����Begin ��End ��˳�򣬱�֤End>Begin
	{
		nBetween=nEnd;
		nEnd=nBegin;
		nBegin=nBetween;
	} 
	else if(nBegin==nEnd) 
		//���������Beggin ��End ��ȣ�����ΧΪ0
		nEnd=nBegin+10; //ǿ�ж��巶Χ����Ϊ10
	nBetween=nEnd-nBegin; //�������
	n=n%nBetween; //ͨ�����������޷�
	n+=nBegin; //��Begin �ۼӣ�ȷ���������Begin ��End ֮��
	return n;
}


//�ж��Ƿ�ʱ�䵽��
// tLast�����һ�θ���ʱ��
//�趨�����ʱ��
TOOLSLIB_API inline bool TimeIsUp(time_t tLast,long lMax)
{
	time_t tNow;
	TimeSetNow(tNow);
	long lDeltaT=(long)tNow-(long)tLast;
	if(lMax<=lDeltaT) return true;
	else return false;
}



//Windows ��Linux ���и������·���ļ������Linux �·���Unix ��׼���ǡ�/������Windows
//��Ϊ��\�������СС�ĺ궨�壬������ַ�����
#ifdef WIN32
#define PATH_CHAR "\\"
#else // not WIN32
#define PATH_CHAR "/"
#endif

//ע������ı��⣬������������Ϊ·�����ļ�����������ȫ������������չ��
#define FULL_NAME(path,name,fullname,ext_name) \
{ \
    if(strlen(path)) \
    { \
	    if(strlen(ext_name))  \
	        SafePrintf(fullname, \
	          FILENAME_STRING_LENGTH, \
	          "%s%s%s.%s", \
	          path, \
	          PATH_CHAR, \
              name, \
              ext_name); \
        else \
        {\
	        SafePrintf(fullname, \
	          FILENAME_STRING_LENGTH, \
	          "%s%s%s", \
	          path, \
	          PATH_CHAR,\
	          name); \
        }\
    } \
	else \
    { \
	    if(strlen(ext_name))  \
	        SafePrintf(fullname, \
	          FILENAME_STRING_LENGTH, \
	          "%s.%s", \
	          name, \
	          ext_name); \
		else \
		  SafePrintf(fullname, \
			FILENAME_STRING_LENGTH, \
			"%s", \
			name); \
    } \
}





//ͳ�ƽṹ
typedef struct _COUNT_SUB_
{
	unsigned long m_lXBegin;
	unsigned long m_lXEnd;
}SCountSub;

//��æ�X
TOOLSLIB_API unsigned long SCountSubGetX(SCountSub& CountSub);
//���ó�ʼֵ
TOOLSLIB_API void SCountSubSetBegin(SCountSub& CountSub,unsigned long n);
//���ý���ֵ
TOOLSLIB_API unsigned long SCountSubSetEnd(SCountSub& CountSub,unsigned long n);

//ͳ����Ϣ
class TOOLSLIB_API CCountSub
{
public:
	CCountSub(){m_CountSub.m_lXBegin=0;m_CountSub.m_lXEnd=0;}
	~CCountSub(){}
public:
	//���ó�ʼֵ
	unsigned long SetBegin(unsigned long n){return m_CountSub.m_lXBegin=n;}
	//���ý���ֵ
	unsigned long SetEnd(unsigned long n){return m_CountSub.m_lXEnd=n;}
	//��ó�ʼֵ
	unsigned long GetBegin(void){return m_CountSub.m_lXBegin;}
	//��ý���ֵ
	unsigned long GetEnd(void){return m_CountSub.m_lXEnd;}
	//��á�
	unsigned long GetX(void){return m_CountSub.m_lXEnd-m_CountSub.m_lXBegin;}
	//�ѽ���ֵ������ʼֵ���൱�ڡ�����
	void E2B(void){m_CountSub.m_lXBegin=m_CountSub.m_lXEnd;}
	//�ѽ���ֵ������ʼֵ��Ȼ�������ֵ����ֵ������ĳЩѭ��ͳ�Ƶĳ��Ϸǳ�����
	void Push(unsigned long ulNew){E2B();m_CountSub.m_lXEnd=ulNew;}
	//��ǰ�Ĺ��õ����������ṹ��
	SCountSub m_CountSub;
};





//����ͳ��ƽ��ֵģ��
typedef struct _COUNT_
{
	SCountSub m_Sub; //��X ����
	unsigned long m_Sum; //ͳ��ƽ��ֵ
}SCount;

//��ʼ��
TOOLSLIB_API void SCountReset(SCount& Count,unsigned long n);
//����ͳ��ƽ��ֵ
TOOLSLIB_API unsigned long SCountSum(SCount& Count);
//����Sum ֵ
TOOLSLIB_API unsigned long SCountGetSum(SCount& Count);
//���ص�ǰ�Ħ�X
TOOLSLIB_API unsigned long SCountGetX(SCount& Count);
//���ÿ�ʼ
TOOLSLIB_API void SCountSetBegin(SCount& Count,unsigned long n);
//���ý���ֵ,��������,���Զ��ˢ��
TOOLSLIB_API unsigned long SCountSetEnd(SCount& Count,unsigned long n);

//ƽ��ֵ����
class TOOLSLIB_API CDeltaTime
{ 
public:
	CDeltaTime(){TouchBegin();}
	~CDeltaTime(){}
public:
	//Reset ���ܣ���ʼ��ͳ��ʱ�ӣ���Begin=End
	void Reset(void)
	{m_CountSub.SetEnd(m_CountSub.SetBegin(
	(unsigned long)time(null)));}
	//������ʼʱ�����
	void TouchBegin(void){m_CountSub.SetBegin((unsigned long)time(null));}
	//��������ʱ�似��
	void TouchEnd(void){m_CountSub.SetEnd((unsigned long)time(null));}
	//�������ĵ�Push ���ܣ�ʵ��ѭ��ͳ�ơ���Now->End->Begin
	void Touch(void){m_CountSub.Push((unsigned long)time(null));}
	//��á�
	unsigned long GetDeltaT(void){return m_CountSub.GetX();}
	//ƽ��ֵ������ÿ���ӵĲ��������û����ۼ���ͳ���ܵĲ����������ݽ�����
	//�������Զ������ڲ��ġ�����ƽ��ֵ�����������ṩdouble �ľ��ȣ�����ܳ�0 ����
	double GetOperationsPreSecond(unsigned long ulOperationCount)
	{
		double dRet=0.0;
		double dCount=(double)ulOperationCount;
		unsigned long ulDeltaSecond=GetDeltaT();
		double dSeconds=(double)ulDeltaSecond;
		if(0==ulDeltaSecond) return dRet;
		return dCount/dSeconds;
	} 
	//��ǰ��ģ�������Ļ���ͳ��ģ��
	CCountSub m_CountSub;
};


//������ʱ��ƽ��ֵͳ��ģ�飬���к�������ͬ�ϣ���������ṩ������
class TOOLSLIB_API CDeltaTimeVSLock
{ 
public:
	CDeltaTimeVSLock(){}
	~CDeltaTimeVSLock(){}
public:
	void Reset(void)
	{//Reset Ϊд���������ܲ���
		m_Lock.EnableWrite();
		m_nDeltaT.Reset();
		m_Lock.DisableWrite();
	} 
	void TouchBegin(void)
	{//TouchBegin Ϊд���������ܲ���
		m_Lock.EnableWrite();
		m_nDeltaT.TouchBegin();
		m_Lock.DisableWrite();
	} 
	void TouchEnd(void)
	{//TouchEnd Ϊд���������ܲ���
		m_Lock.EnableWrite();
		m_nDeltaT.TouchEnd();
		m_Lock.DisableWrite();
	}
	unsigned long GetDeltaT(void)
	{//GetDeltaT Ϊ�����������Բ�����
		unsigned long nRet=0;
		m_Lock.AddRead();
		nRet=m_nDeltaT.GetDeltaT();
		m_Lock.DecRead();
		return nRet;
	}
	double GetOperationsPreSecond(unsigned long ulOperationCount)
	{//GetOterationPerSecond Ϊ�����������Բ�����
		double dRet=0.0;
		m_Lock.AddRead();
		dRet=m_nDeltaT.GetOperationsPreSecond(ulOperationCount);
		m_Lock.DecRead();
		return dRet;
	}
private:
	CDeltaTime m_nDeltaT; //����ͳ������
	CMultiReadSingleWriteLock m_Lock; //��д���������
};




//���нӿ���C ģʽһһ��Ӧ
class TOOLSLIB_API CCount
{
public:
	CCount(){SCountReset(0);}
	~CCount(){}
public:
	void SCountReset(unsigned long n){::SCountReset(m_Count,n);}
	unsigned long SCountSum(void){return ::SCountSum(m_Count);}
	unsigned long SCountSetSum(unsigned long n){m_Count.m_Sum=n;return n;}
	unsigned long SCountGetSum(void){return ::SCountGetSum(m_Count);}
	unsigned long SCountGetX(void){return ::SCountGetX(m_Count);}
	void SCountSetBegin(unsigned long n){::SCountSetBegin(m_Count,n);}
	unsigned long SCountSetEnd(unsigned long n)	{return ::SCountSetEnd(m_Count,n);}
	SCount m_Count;
};






/////////////////////////////////////
//         �ײ�debug��              
/////////////////////////////////////

//�ص���������
typedef void (*_APP_INFO_OUT_CALLBACK)(char* szInfo,void* pCallParam);

class TOOLSLIB_API CToolsLowDebug
{
public:
	//��̬���ߺ�����ɾ��һ���ļ�
	static void DeleteAFile(char* szFileName);
	//���˵�__FILE__ǰ���·����������info ̫��
	//�Ӻ���ǰ���ˣ�ֱ���ҵ�һ��'\\'��'/'Ϊֹ��
	//���ظ��ַ���һ���ַ���������ʵ�ļ�����ʼλ��
	//����Ҳ������򷵻����ַ�
	static char* GetTrueFileName(char* szBuffer);
public:
	//��ҵ����������ַ������ļ������̨�������ƣ�����ʹ�á������ֽ��������ơ�\0��
	int Debug2File(char *szFormat, ...);
	//���������һ���ڴ�������ʽ�ο�ǰ�ĵ�dbg4bin
	void Debug2File4Bin(char* pBuffer,int nLength);
public:
	//���캯������������
	CToolsLowDebug(const char* szPathName, //·����
		const char* szAppName, //�ļ���
		bool bPrint2TTYFlag=false, //�Ƿ��ӡ������̨��Ļ
		_APP_INFO_OUT_CALLBACK pInfoOutCallback=null, //���������ص�
		void* pInfoOutCallbackParam=null); //�ص���������
	~CToolsLowDebug();
public:
	//����һ���������Ĺ��ܣ��ܶ�ʱ��Ӧ�ó������Լ�������豸��
	//����Windows ��һ�����ڣ������ṩһ���ص�����������Ӧ�ò�
	//����Ҫ��ʱ��ץȡ�����Ϣ�������Լ����������
	//����public������Ϊ����ĳЩ�ڲ�ģ����Ҫ��һ�����ָ�룬ͬʱ���
	_APP_INFO_OUT_CALLBACK m_pInfoOutCallback;
	//���еĻص���������ߣ������������ߴ�һ��ָ��
	void* m_pInfoOutCallbackParam;
private:
	bool m_bPrint2TTYFlag; //�ڲ������Ŀ���̨�����־
	char m_szFileName[TOOLS_DEBUG_FILENAME_LENGTH]; //ƴ�Ӻõ�·����+�ļ���
	CMutexLock m_Lock; //�̰߳�ȫ��
};




#endif	// __DEBUG_TOOLS_H__
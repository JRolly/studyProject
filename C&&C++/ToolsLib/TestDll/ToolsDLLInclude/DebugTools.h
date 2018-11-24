
////////////////////////////////////////////////////////////
//							Debug工具
////////////////////////////////////////////////////////////


#ifndef __DEBUG_TOOLS_H__
#define __DEBUG_TOOLS_H__

#include "IncludeDef.h"
#include "LockTools.h"


#define DEBUG_BUFFER_LENGTH 1024 //debug 缓冲区大小
#define TOOLS_DEBUG_FILENAME_LENGTH 256 //文件名长
#define FILENAME_STRING_LENGTH 256 //文件名长度统一为256 字节
#define APP_INFO_OIT_STRING_MAX 1024


#define TOOLS_CLEAN_CHAR_BUFFER(p) (*((char*)p)='\0')

#define TimeSetNow(t) time(&t) //设置给定的t 为当前时间



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

//TOOLS_DEBUG是否需要输出到文件
#ifdef CON_DEBUG
#define TOOLS_DEBUG printf
#else
#define TOOLS_DEBUG /\
	/printf
#endif
//TOOLS_PRINTF是否需要输出到文件
#ifdef CON_DEBUG
#define TOOLS_PRINTF printf
#else
#define TOOLS_PRINTF /\
	/printf
#endif

#if 0	//VC使用
#define CON_DEBUG 1
#ifdef CON_DEBUG
#define CON_PRINTF TRACE
#else
#define CON_PRINTF /\
	/TRACE
#endif
#endif





//安全的字符串拷贝函数
//参数按顺序排：目的地址，源地址，拷贝的最大字节数
TOOLSLIB_API void SafeStrcpy(char *pDest, char *pSource,int nCount);

//安全的变参输出函数
//szBuf: 用户指定的输出缓冲区
//nMaxLength：用户指定的输出缓冲区尺寸
//szFormat：格式化输出字符串（变参，可以是多个）
//返回输出的字符总数（strlen 的长度，不包括最后的’\0’）
TOOLSLIB_API int SafePrintf(char* szBuf,int nMaxLength,char *szFormat, ...);


//向指定的缓冲区输出一个时间戳字符串
//szBuf: 用户指定的输出缓冲区
//nMaxLength：用户指定的输出缓冲区尺寸
//返回输出的字符总数（strlen 的长度，不包括最后的’\0’）
TOOLSLIB_API int GetATimeStamp(char* szBuf,int nMaxLength);


//向指定的缓冲区输出一个时间戳字符串
// szFileName: 用户指定的输出文件
// szMode：常见的文件打开方式描述字符串，一般建议”a+”
//返回输出的字符总数（strlen 的长度，不包括最后的’\0’）
TOOLSLIB_API int dbg2file(char* szFileName,char* szMode, char *szFormat, ...);


//输出格式
//0000 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 xxxxxxxxxxxxxxxx
//以ASCII 方式显示数据内容
TOOLSLIB_API int dbg_bin_ascii(char* pPrintBuffer,char* pBuffer,int nLength);


//以十六进制方式显示指定数据区内容。
TOOLSLIB_API int dbg_bin_hex(char* pPrintBuffer,char* pBuffer,int nLength);


//****************这是主入口函数
//以16 字节为一行，格式化输出二进制数据内容。
TOOLSLIB_API void dbg_bin(char* pBuffer,int nLength);


#ifdef WIN32 //仅在Windows 下有效
TOOLSLIB_API int SafeScanf(char* szBuffer, //给定输入缓冲区指针
		int nLength); //给定输入缓冲区长度
#else // not WIN32
#endif


//辅助函数

//获得非0随机数
TOOLSLIB_API inline int _GetNot0(void)
{
	int nRet=rand();
	if(!nRet) nRet++; //如果获得的随机数本身为0，返回1
	return nRet;
}

//获得0
TOOLSLIB_API inline int _Get0(void)
{
	int nRet=rand();
	return nRet^nRet; //以异或方式求的0
}

//获得给定区间内的随机数
TOOLSLIB_API inline int GetRandomBetween(int nBegin,int nEnd)
{
	int n=_GetNot0(); //获得一个随机数
	int nBetween=0;
	if(0>nBegin) nBegin=-nBegin; //防御性设计防止Begin 为负值
	if(0>nEnd) nEnd=-nEnd; //防御性设计防止End 为负值
	if(nBegin>nEnd) //调整Begin 和End 的顺序，保证End>Begin
	{
		nBetween=nEnd;
		nEnd=nBegin;
		nBegin=nBetween;
	} 
	else if(nBegin==nEnd) 
		//如果给定的Beggin 和End 相等，即范围为0
		nEnd=nBegin+10; //强行定义范围区间为10
	nBetween=nEnd-nBegin; //求的区间
	n=n%nBetween; //通过求余运算限幅
	n+=nBegin; //与Begin 累加，确保结果落于Begin 和End 之间
	return n;
}


//判断是否时间到了
// tLast：最后一次更新时间
//设定的最大时间
TOOLSLIB_API inline bool TimeIsUp(time_t tLast,long lMax)
{
	time_t tNow;
	TimeSetNow(tNow);
	long lDeltaT=(long)tNow-(long)tLast;
	if(lMax<=lDeltaT) return true;
	else return false;
}



//Windows 和Linux 下有个差别，其路径的间隔符，Linux 下符合Unix 标准，是”/”，而Windows
//下为”\”，这个小小的宏定义，解决这种纷争。
#ifdef WIN32
#define PATH_CHAR "\\"
#else // not WIN32
#define PATH_CHAR "/"
#endif

//注意参数的表意，从左至右依次为路径、文件名，构建的全名缓冲区，扩展名
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





//统计结构
typedef struct _COUNT_SUB_
{
	unsigned long m_lXBegin;
	unsigned long m_lXEnd;
}SCountSub;

//获得ΔX
TOOLSLIB_API unsigned long SCountSubGetX(SCountSub& CountSub);
//设置初始值
TOOLSLIB_API void SCountSubSetBegin(SCountSub& CountSub,unsigned long n);
//设置结束值
TOOLSLIB_API unsigned long SCountSubSetEnd(SCountSub& CountSub,unsigned long n);

//统计信息
class TOOLSLIB_API CCountSub
{
public:
	CCountSub(){m_CountSub.m_lXBegin=0;m_CountSub.m_lXEnd=0;}
	~CCountSub(){}
public:
	//设置初始值
	unsigned long SetBegin(unsigned long n){return m_CountSub.m_lXBegin=n;}
	//设置结束值
	unsigned long SetEnd(unsigned long n){return m_CountSub.m_lXEnd=n;}
	//获得初始值
	unsigned long GetBegin(void){return m_CountSub.m_lXBegin;}
	//获得结束值
	unsigned long GetEnd(void){return m_CountSub.m_lXEnd;}
	//获得△
	unsigned long GetX(void){return m_CountSub.m_lXEnd-m_CountSub.m_lXBegin;}
	//把结束值赋给初始值，相当于△归零
	void E2B(void){m_CountSub.m_lXBegin=m_CountSub.m_lXEnd;}
	//把结束值赋给初始值，然后给结束值赋新值，这在某些循环统计的场合非常有用
	void Push(unsigned long ulNew){E2B();m_CountSub.m_lXEnd=ulNew;}
	//与前文共用的数据描述结构体
	SCountSub m_CountSub;
};





//基本统计平均值模块
typedef struct _COUNT_
{
	SCountSub m_Sub; //ΔX 计算
	unsigned long m_Sum; //统计平均值
}SCount;

//初始化
TOOLSLIB_API void SCountReset(SCount& Count,unsigned long n);
//计算统计平均值
TOOLSLIB_API unsigned long SCountSum(SCount& Count);
//返回Sum 值
TOOLSLIB_API unsigned long SCountGetSum(SCount& Count);
//返回当前的ΔX
TOOLSLIB_API unsigned long SCountGetX(SCount& Count);
//设置开始
TOOLSLIB_API void SCountSetBegin(SCount& Count,unsigned long n);
//设置结束值,单纯更新,可以多次刷新
TOOLSLIB_API unsigned long SCountSetEnd(SCount& Count,unsigned long n);

//平均值计算
class TOOLSLIB_API CDeltaTime
{ 
public:
	CDeltaTime(){TouchBegin();}
	~CDeltaTime(){}
public:
	//Reset 功能，初始化统计时钟，且Begin=End
	void Reset(void)
	{m_CountSub.SetEnd(m_CountSub.SetBegin(
	(unsigned long)time(null)));}
	//触发开始时间计数
	void TouchBegin(void){m_CountSub.SetBegin((unsigned long)time(null));}
	//触发结束时间技术
	void TouchEnd(void){m_CountSub.SetEnd((unsigned long)time(null));}
	//利用上文的Push 功能，实现循环统计。即Now->End->Begin
	void Touch(void){m_CountSub.Push((unsigned long)time(null));}
	//获得△
	unsigned long GetDeltaT(void){return m_CountSub.GetX();}
	//平均值计算获得每秒钟的操作数，用户以累加器统计总的操作数，传递进来，
	//本函数自动根据内部的△计算平均值，除法计算提供double 的精度，并规避除0 错误
	double GetOperationsPreSecond(unsigned long ulOperationCount)
	{
		double dRet=0.0;
		double dCount=(double)ulOperationCount;
		unsigned long ulDeltaSecond=GetDeltaT();
		double dSeconds=(double)ulDeltaSecond;
		if(0==ulDeltaSecond) return dRet;
		return dCount/dSeconds;
	} 
	//以前文模块描述的基本统计模块
	CCountSub m_CountSub;
};


//带锁的时间平均值统计模块，所有函数功能同上，本层仅仅提供锁保护
class TOOLSLIB_API CDeltaTimeVSLock
{ 
public:
	CDeltaTimeVSLock(){}
	~CDeltaTimeVSLock(){}
public:
	void Reset(void)
	{//Reset 为写动作，不能并发
		m_Lock.EnableWrite();
		m_nDeltaT.Reset();
		m_Lock.DisableWrite();
	} 
	void TouchBegin(void)
	{//TouchBegin 为写动作，不能并发
		m_Lock.EnableWrite();
		m_nDeltaT.TouchBegin();
		m_Lock.DisableWrite();
	} 
	void TouchEnd(void)
	{//TouchEnd 为写动作，不能并发
		m_Lock.EnableWrite();
		m_nDeltaT.TouchEnd();
		m_Lock.DisableWrite();
	}
	unsigned long GetDeltaT(void)
	{//GetDeltaT 为读动作，可以并发读
		unsigned long nRet=0;
		m_Lock.AddRead();
		nRet=m_nDeltaT.GetDeltaT();
		m_Lock.DecRead();
		return nRet;
	}
	double GetOperationsPreSecond(unsigned long ulOperationCount)
	{//GetOterationPerSecond 为读动作，可以并发读
		double dRet=0.0;
		m_Lock.AddRead();
		dRet=m_nDeltaT.GetOperationsPreSecond(ulOperationCount);
		m_Lock.DecRead();
		return dRet;
	}
private:
	CDeltaTime m_nDeltaT; //基本统计因子
	CMultiReadSingleWriteLock m_Lock; //单写多读锁对象
};




//所有接口与C 模式一一对应
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
//         底层debug类              
/////////////////////////////////////

//回调函数构型
typedef void (*_APP_INFO_OUT_CALLBACK)(char* szInfo,void* pCallParam);

class TOOLSLIB_API CToolsLowDebug
{
public:
	//静态工具函数，删除一个文件
	static void DeleteAFile(char* szFileName);
	//过滤掉__FILE__前面的路径名，避免info 太长
	//从后向前过滤，直到找到一个'\\'或'/'为止，
	//返回该字符下一个字符，就是真实文件名起始位置
	//如果找不到，则返回首字符
	static char* GetTrueFileName(char* szBuffer);
public:
	//主业务函数，输出字符串到文件或控制台，变参设计，方便使用。返回字节数，不计”\0”
	int Debug2File(char *szFormat, ...);
	//二进制输出一段内存区，格式参考前文的dbg4bin
	void Debug2File4Bin(char* pBuffer,int nLength);
public:
	//构造函数和析构函数
	CToolsLowDebug(const char* szPathName, //路径名
		const char* szAppName, //文件名
		bool bPrint2TTYFlag=false, //是否打印到控制台屏幕
		_APP_INFO_OUT_CALLBACK pInfoOutCallback=null, //额外的输出回调
		void* pInfoOutCallbackParam=null); //回调函数参数
	~CToolsLowDebug();
public:
	//这是一个额外加入的功能，很多时候，应用程序有自己的输出设备，
	//比如Windows 的一个窗口，这里提供一个回调函数，方便应用层
	//在需要的时候，抓取输出信息，打入自己的输出队列
	//至于public，是因为可能某些内部模块需要看一下这个指针，同时输出
	_APP_INFO_OUT_CALLBACK m_pInfoOutCallback;
	//所有的回调函数设计者，有义务帮调用者传一根指针
	void* m_pInfoOutCallbackParam;
private:
	bool m_bPrint2TTYFlag; //内部保留的控制台输出标志
	char m_szFileName[TOOLS_DEBUG_FILENAME_LENGTH]; //拼接好的路径名+文件名
	CMutexLock m_Lock; //线程安全锁
};




#endif	// __DEBUG_TOOLS_H__
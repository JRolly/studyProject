////////////////////////////////////////////////////////////
//							Buffer工具
////////////////////////////////////////////////////////////




#ifndef __BUFFER_TOOLS_H__
#define __BUFFER_TOOLS_H__

#include "IncludeDef.h"
#include "MemoryTools.h"
#include "DebugTools.h"


//#define BUFFER_DYNAMIC		//buffer开关，使用静态buffer还是动态buffer

/////////////////////////////
///动态Buffer
#ifdef BUFFER_DYNAMIC

#define TOOLS_BUFFER_STRING_MAX	1024

//Buffer 类
class TOOLSLIB_API CToolsBuffer
{ 
public:
	//构造函数，注意传入pMemPool 内存池对象指针。
	CToolsBuffer(CToolsMemoryPoolWithLock* pMemPool);
	~CToolsBuffer();
public: //请注意，典型的工具类特征，所有内部变量，全部公有，方便应用层调用
	CToolsMemoryPoolWithLock* m_pMemPool; //内存池指针
	char* m_pData; //动态内存缓冲区指针
	int m_nDataLength; //内存缓冲区长度（代数据长度）
public:
	////////////////////////////////////
	//尺寸设置函数
	bool SetSize(int nSize); //设置新的大小
	bool InsertSpace2Head(int nAddBytes); //在前面插入空白
	bool AddSpace2Tail(int nAddBytes); //在后面插入空白
	void CutHead(int nBytes); //从前面剪切掉一段数据
	void CutTail(int nBytes); //从后面剪切掉一段数据

	////////////////////////////////////
	//数值转换函数
	bool SetInt(int n); //将一个整数以二进制方式拷贝到缓冲区，带网络字节排序
	int GetInt(void); //以整数方式获得缓冲区的数值
	bool SetShort(short n); //将一个短整数以二进制方式拷贝到缓冲区，带网络字节排序
	short GetShort(void); //以短整型方式获得缓冲区的数值
	bool SetChar(char n); //将一个字节以二进制方式拷贝到缓冲区
	char GetChar(void); //以字节方式获得缓冲区的数值

	////////////////////////////////////
	//二进制数据追加函数
	//追加数据到最后，返回新的数据长度
	int AddData(char* szData,int nDataLength);
	//插入数据到最前面，返回新的数据长度
	int InsertData2Head(char* szData,int nDataLength);

	////////////////////////////////////
	//二进制数据拷贝函数
	//拷贝到一块目标缓冲区，受传入的缓冲区长度限制
	int BinCopyTo(char* szBuffer,int nBufferSize);
	//从一块来源缓冲区拷贝数据到本对象中
	int BinCopyFrom(char* szData,int nDataLength);
	//从另外一个Buffer 对象拷贝数据到本对象
	int BinCopyFrom(CToolsBuffer* pBuffer);

	////////////////////////////////////
	//文本数据拷贝构建函数
	int StrCopyFrom(char* szString);
	int Printf(char* szFormat,...);

	////////////////////////////////////
	//数据比较函数
	int memcmp(char* szData,int nDataLength);
	int strcmp(char* szString);
};


#else
//////////////////////////////
//静态Buffer

#define TOOLS_SAFE_BUFFER_MAX_SIZE	(100*1024)
	

class CToolsBaseLibrary;

class TOOLSLIB_API CToolsBuffer
{ 
public:
	//由于动静态Buffer 类api 完全一样，因此，公有函数构型必须保持一致。
	CToolsBuffer(CToolsBaseLibrary* pToolsBaseLib);
	CToolsBuffer(CToolsMemoryPoolWithLock* pMemPool);
	~CToolsBuffer(){} //由于没有动态内存的释放任务，析构函数不做任何事
public:
	////////////////////////////////////
	//二进制数据拷贝函数
	int BinCopyTo(char* szBuffer,int nBufferSize);
	int BinCopyFrom(char* szData,int nDataLength);
	int BinCopyFrom(CToolsBuffer* pBuffer);

	////////////////////////////////////
	//文本数据拷贝构建函数
	int StrCopyFrom(char* szString);
	int Printf(char* szFormat,...);

	////////////////////////////////////
	//尺寸设置函数
	//设置新的大小
	bool SetSize(int nSize);
	//在前面插入空白
	bool InsertSpace2Head(int nAddBytes);
	//在后面插入空白
	bool AddSpace2Tail(int nAddBytes);
	//从前面剪切掉一段数据
	void CutHead(int nBytes);
	//从后面剪切掉一段数据
	void CutTail(int nBytes);

	////////////////////////////////////
	//数值转换函数
	bool SetInt(int n);
	int GetInt(void);
	bool SetShort(short n);
	short GetShort(void);
	bool SetChar(char n);
	char GetChar(void);	

	////////////////////////////////////
	//二进制数据追加函数
	//追加数据到最后，返回新的数据长度
	int AddData(char* szData,int nDataLength);
	//插入数据到最前面，返回新的数据长度
	int InsertData2Head(char* szData,int nDataLength);

	////////////////////////////////////
	//数据比较函数
	int memcmp(char* szData,int nDataLength);
	int strcmp(char* szString);

	////////////////////////////////////
	//服务函数
	bool IHaveData(void);
public:
	char m_pData[TOOLS_SAFE_BUFFER_MAX_SIZE]; //请注意这里，m_pData 变为静态数组
	int m_nDataLength;
	CToolsMemoryPoolWithLock* m_pMemPool; //保留MemPool，是为了Debug 方便
};	

#endif	// BUFFER_DYNAMIC


///////////////////////
//PopBuffer 类

//每个Token 的头结构体
typedef struct _TOOLS_POP_BUFFER_TOKEN_HEAD_
{
	int m_nDataLength; //标示该Token 的数据长度
}SToolsPopBufferTokenHead; //定义的结构体变量类型
//结构体长度常量
const ULONG SToolsPopBufferTokenHeadSize=sizeof(SToolsPopBufferTokenHead);

//PopBuffer 队列管理变量结构体
typedef struct _TOOLS_POP_BUFFER_HEAD_
{
	int m_nTokenCount; //内部包含的元素个数
	int m_nAllBytesCount; //使用的总字节数
}SToolsPopBufferHead; //定义的结构体变量类型
//习惯性写法，定义了结构体，立即定义其长度常量
const ULONG SToolsPopBufferHeadSize=sizeof(SToolsPopBufferHead);

//由于PopBuffer 缓冲区的线性连续编址特性，这个队列头结构体被设计成位于缓冲区最开始的地方
//因此，队列第一个元素真实的开始点，是缓冲区开始处向后偏移SToolsPopBufferHeadSize 长度
//这个宏定义出队列元素数据区开始指针（字符型指针）
#define TOOLS_POP_BUFFER_TOKEN_DATA_BEGIN(p) \
	(((char*)p)+SToolsPopBufferTokenHeadSize)

//如果一笔准备推入队列的数据长度为n，则该Token 的总长度可以用该宏计算
#define TOOLS_POP_BUFFER_TOKEN_LENGTH(n) (n+SToolsPopBufferTokenHeadSize)
//如果已知一个Token 的起始指针为p，则该Token 的数据区开始处可以用该宏计算
#define TOOLS_POP_BUFFER_FIRST_TOKEN_BEGIN(p) \
	(((char*)p)+SToolsPopBufferHeadSize)

//数据枚举回调函数,返回真，继续枚举，直到结束，否则直接结束循环
typedef bool (*_TOOLS_ENUM_DATA_CALLBACK)(char* szData, //数据指针
	int nDataLength, //数据长度
	void* pCallParam); //代传的参数指针
//Demo，后续使用者可以直接拷贝使用
//static bool EnumDataCallback(char* szData,int nDataLength,void* pCallParam);


//基本的PopBuffer 类，本类同时兼顾粘合类和独立类两种特性
class TOOLSLIB_API CToolsPopBuffer
{ 
public:
	//注意，这是粘合类的特有构造函数，内部缓冲区是外部传入，
	CToolsPopBuffer(char* szBuffer, //缓冲区指针
		int nBufferSize, //缓冲区尺寸
		bool bInitFlag=true); //是否初始化标志
	~CToolsPopBuffer();
public:
	//实现“后粘合”的具体函数，即实现粘合的方法
	void Set(char* szBuffer,int nBufferSize);
	//清空整个数据区，仅仅是数据归零，缓冲区不释放
	void Clean(void);
	//内部信息打印函数，Debug 用，相当于前文的PrintfInfo
	void PrintInside(void);
	//能否正确工作的标志函数
	bool ICanWork(void);
public:
	//队列最经典的功能，追加到末尾，此处兼容普通缓冲区和Buffer 类
	int AddLast(char* szData,int nDataLength);
	int AddLast(CToolsBuffer* pBuffer);
public:
	//获得当前内部元素个数
	int GetTokenCount(void);
	//获得当前使用的所有字节数（包含管理字节）
	int GetAllBytes(void);
	//根据即将推送进队列的数据长度，判断内部剩余空间是否够用
	bool ICanSave(int nDataLength);
public:
	//获得第一个元素的长度
	int GetFirstTokenLength(void);
	//获取第一个元素，这是普通buffer 版本，需要应用层保证缓冲区长度足够
	//用GetFirstTokenLength 可以查询第一个元素的长度
	int GetFirst(char* szBuffer,int nBufferSize);
	//获得第一个元素，这是Buffer 类版本
	int GetFirst(CToolsBuffer* pBuffer);
	//删除第一个元素
	bool DeleteFirst(void);
	//提取并删除第一元素，就是从队列中弹出第一个元素
	int GetAndDeleteFirst(char* szBuffer,int nBufferSize);
	int GetAndDeleteFirst(CToolsBuffer* pBuffer);
public:
	//枚举遍历所有数据，提交回调函数处理，并且删除数据，返回经过处理的Token 个数
	int MoveAllData(_TOOLS_ENUM_DATA_CALLBACK pCallBack,PVOID pCallParam);
public:
	char* m_pBuffer; //最关键的内部缓冲区指针
	int m_nBufferSize; //内部缓冲区长度
private:
	//这是队列头的指针，注意，这个指针并不是动态申请的内存块，而是指向缓冲区m_pBuffer 头
	SToolsPopBufferHead* m_pHead;
};





#endif	// __BUFFER_TOOLS_H__
////////////////////////////////////////////////////////////
//							锁工具
////////////////////////////////////////////////////////////




#ifndef __LOCK_TOOLS_H__
#define __LOCK_TOOLS_H__

#include "IncludeDef.h"
//#include "DebugTools.h"


#ifdef WIN32 //Windows 下定义
	//定义锁变量类型
	#define MUTEX CRITICAL_SECTION
	//定义初始化锁的功能
	#define MUTEXINIT(m) InitializeCriticalSection(m)
	//定义加锁
	#define MUTEXLOCK(m) EnterCriticalSection(m)
	//定义解锁
	#define MUTEXUNLOCK(m) LeaveCriticalSection(m)
	//定义摧毁锁变量操作
	#define MUTEXDESTROY(m) DeleteCriticalSection(m)
#else //Linux 下定义
	//定义锁变量类型
	#define MUTEX pthread_mutex_t
	//定义初始化锁的功能
	#define MUTEXINIT(m) pthread_mutex_init(m, NULL)
	//定义加锁
	#define MUTEXLOCK(m) pthread_mutex_lock(m)
	//定义解锁
	#define MUTEXUNLOCK(m) pthread_mutex_unlock(m)
	//定义摧毁锁变量操作
	#define MUTEXDESTROY(m) pthread_mutex_destroy(m)
#endif

#ifdef WIN32
//
#else
//Linux 下普通的睡眠函数对比
	#define Sleep(ms) usleep(ms*1000)
#endif

class CMutexLock
{ 
public:
	CMutexLock(void){MUTEXINIT(&m_Lock);} //构造函数，初始化锁
	~CMutexLock(void){MUTEXDESTROY(&m_Lock);} //析构函数，摧毁锁
public:
	void Lock(){MUTEXLOCK(&m_Lock);} //加锁操作
	void Unlock(){MUTEXUNLOCK(&m_Lock);} //解锁操作
private:
	MUTEX m_Lock; //锁变量（私有）
};



typedef struct _MINT_ //这是整型的多线程安全单元
{
	int m_nValue; //这是整型值
	MUTEX m_MyLock; //这是实现保护的C 语言锁变量
}MINT,MBOOL; //int 型和bool 型同时实现

//初始化一个线程安全变量,同时可以设置值,返回设置值
extern int MvarInit(MINT& (mValue),int nValue=0);
//摧毁一个线程安全变量
extern void MvarDestroy(MINT& (mValue));
//设置一个线程安全变量的值,返回设置的值
extern int MvarSet(MINT& (mValue),int nValue);
//得到一个线程安全变量的值
extern int MvarGet(MINT& (mValue));
//线程安全变量做加法运算,默认+1
extern int MvarADD(MINT& (mValue),int nValue=1);
//线程安全变量做减法运算,默认-1
extern int MvarDEC(MINT& (mValue),int nValue=1);

//这里全部使用内联函数实现
//请注意，类中所有公有方法均是调用C 的方法实现。
class CMint //int 型多线程安全变量类
{
public:
	CMint(int nVlaue=0){MvarInit(m_nValue,nVlaue);}
	~CMint(void){MvarDestroy(m_nValue);}
public:
	int Get(void){return MvarGet(m_nValue);}
	int Set(int nValue){return MvarSet(m_nValue,nValue);}
	int Add(int nValue=1){return MvarADD(m_nValue,nValue);}
	int Dec(int nValue=1){return MvarDEC(m_nValue,nValue);}
private:
	MINT m_nValue;
};

class CMbool //bool 型多线程安全的变量类
{
public:
	CMbool(bool nVlaue=false){MvarInit(m_nValue,nVlaue);}
	~CMbool(void){MvarDestroy(m_nValue);}
public: //只提供Get 和Set 方法
	int Get(void){return MvarGet(m_nValue);}
	int Set(bool nValue){return MvarSet(m_nValue,nValue);}
private:
	MBOOL m_nValue;
};


#if 0
//模板定义
#include <Afxmt.h> //包含Windows 多线程库的头文件
template <class MVAR_TYPE>
class MVAR
{ 
private:
	//为了适应所有的变量类型，此处使用动态内存块保存变量区域，
	//因此，内部仅仅保留一个指向变量区域的指针，通过强制指针类型转换实现访问
	char* m_pBegin;
	CCriticalSection m_csLockHandle; //使用Windows 临界区类实现锁
public:
	//构造函数使用标准C++的new 方式申请内存
	MVAR(){m_pBegin=new char[sizeof(MVAR_TYPE)];}
	//析构函数使用标准C++的delete[]方式释放内存
	~MVAR(){delete[] m_pBegin;}
	//获得变量的长度，也就是获得该变量类型的字节宽度（sizeof）
	int GetLength(){return sizeof(MVAR_TYPE);}
	//设置变量的值
	MVAR_TYPE Set(MVAR_TYPE& value)
	{
		m_csLockHandle.Lock(); //所有访问均使用临界区锁保护
		//请注意，所有的拷贝动作，均使用memcpy，避免变量类型带来的干扰
		memcpy(m_pBegin,(char*)&value,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return value;
	} 
	//获取变量的值
	MVAR_TYPE Get()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载=，直接赋值符号
	MVAR_TYPE operator=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		myValue=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载按位否定运算符~
	MVAR_TYPE operator~()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue=~myValue;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载++运算符（整型）
	MVAR_TYPE operator++(int)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue++;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载++运算符，++运算符需要重载两次
	MVAR_TYPE operator++()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue++;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载--运算符（整型）
	MVAR_TYPE operator--(int)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue--;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载--运算符，--运算符也需要重载两次
	MVAR_TYPE operator--()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue--;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载+运算符，加法计算
	MVAR_TYPE operator+(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue+=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载-运算符，减法计算
	MVAR_TYPE operator-(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue-=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载*运算符，乘法运算
	MVAR_TYPE operator*(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue*=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载/运算符，除法计算
	MVAR_TYPE operator/(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue/=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载&运算法and 运算
	MVAR_TYPE operator&(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue&=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载|运算法，or 运算
	MVAR_TYPE operator|(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue|=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载^运算符，异或运算
	MVAR_TYPE operator^(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue^=value;
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载+=运算符
	MVAR_TYPE operator+=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue+=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载-=运算符
	MVAR_TYPE operator-=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue-=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载*=运算符
	MVAR_TYPE operator*=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue*=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载/=运算符
	MVAR_TYPE operator/=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue/=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载&=运算符
	MVAR_TYPE operator&=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue&=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载|=运算符
	MVAR_TYPE operator|=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue|=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	} 
	//重载^=运算符 
	MVAR_TYPE operator^=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue^=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载>运算符，比较运算
	BOOL operator>(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue>value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	//重载<运算符，比较运算
	BOOL operator<(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue<value);
		m_csLockHandle.Unlock();
		return bRet;
	} 
	//重载>=运算符，比较运算
	BOOL operator>=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue>=value);
		m_csLockHandle.Unlock();
		return bRet;
	} 
	//重载<=运算符，比较运算
	BOOL operator<=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue<=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	//重载==运算符，比较运算
	BOOL operator==(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue==value);
		m_csLockHandle.Unlock();
		return bRet;
	} 
	//重载!=运算符，比较运算
	BOOL operator!=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		bRet=(myValue!=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
};

#endif

//单写多度锁
typedef struct _TOOLS_MULTI_READ_SINGLE_WRITE_LOCK_
{ //注意变量命名，遵循匈牙利命名法在类中的命名规则
	int m_nReadCount; //读计数器
	bool m_bWriteFlag; //写标志
	MUTEX m_Lock; //作为单写多读锁本身，也应该是多线程安全的，
	//因此，需要增加一个锁变量
}SToolsMultiReadSingleWriteLock; //这是新的变量类型，可以定义变量
const ULONG SToolsMultiReadSingleWriteLockSize=
	sizeof(SToolsMultiReadSingleWriteLock);

//MRSW 是Multi Read and Signal Write（多读和单写）的缩写
//MRSWLock 前缀表示单写多读锁
//中间一个“_”分割符，后面是函数的功能描述Greate，创建，Destroy，摧毁，等等
void MRSWLock_Create(SToolsMultiReadSingleWriteLock* pLock);
void MRSWLock_Destroy(SToolsMultiReadSingleWriteLock* pLock);
//获取写状态
bool MRSWLock_GetWrite(SToolsMultiReadSingleWriteLock* pLock);
//获取读计数器
int MRSWLock_GetRead(SToolsMultiReadSingleWriteLock* pLock);
//进入写操作函数
void MRSWLock_EnableWrite(SToolsMultiReadSingleWriteLock* pLock);
//“退出写”操作
void MRSWLock_DisableWrite(SToolsMultiReadSingleWriteLock* pLock);
//进入读函数，返回当前的读计数器值
int MRSWLock_AddRead(SToolsMultiReadSingleWriteLock* pLock);
//返回读计数器变化后的结果
int MRSWLock_DecRead(SToolsMultiReadSingleWriteLock* pLock);
//读转写
void MRSWLock_Read2Write(SToolsMultiReadSingleWriteLock* pLock);

//高精度睡眠函数，采用内联模式加速调用
inline void ToolsMinSleep(void);

class CMultiReadSingleWriteLock
{
public:
	//构造函数和析构函数，自动调用结构体的初始化和摧毁
	CMultiReadSingleWriteLock(){MRSWLock_Create(&m_Lock);}
	~CMultiReadSingleWriteLock(){MRSWLock_Destroy(&m_Lock);}
public:
	//相应的公有方法，完全是调用C 语言的函数
	void EnableWrite(void){MRSWLock_EnableWrite(&m_Lock);}
	void DisableWrite(void){MRSWLock_DisableWrite(&m_Lock);}
	void Read2Write(void){MRSWLock_Read2Write(&m_Lock);}
	void DecRead(void){MRSWLock_DecRead(&m_Lock);}
	void AddRead(void){MRSWLock_AddRead(&m_Lock);}
	bool GetWrite(void){return MRSWLock_GetWrite(&m_Lock);}
	int GetRead(void){return MRSWLock_GetRead(&m_Lock);}
private:
	//私有结构体
	SToolsMultiReadSingleWriteLock m_Lock;
};


//单写多读锁安全变量
class CMRSWint
{ 
public:
	CMRSWint();
	~CMRSWint(){} //析构函数不做任何事
public:
	int Get(void);
	int Set(int nValue);
	int Add(int nValue=1);
	int Dec(int nValue=1);
	int GetAndClean2Zero(void);
	int DecUnless0(int nValue=1); //如果不是，-1
private:
	int m_nValue;
	CMultiReadSingleWriteLock m_Lock;
};

class CMRSWbool
{ 
public:
	CMRSWbool(){}
	~CMRSWbool(){}
public:
	//得到变量的值，或者设置变量的值，均调用整型对象完成
	bool Get(void){return (bool)m_nValue.Get();}
	bool Set(bool bFlag){return m_nValue.Set((int)bFlag);}
private:
	CMRSWint m_nValue; //内部聚合一个上文定义的整型单写多读锁安全变量
};



//不可重入锁
class CNonReentrant
{
public:
	CNonReentrant();
	~CNonReentrant(){} //析构函数不做任何事
public:
	//设置为真的时候
	// 如果没有设置进入标志，设置，并返回真
	// 如果已经设置进入标志，不设置，并返回假
	//设置为假的时候，
	// 总是成功并返回真
	bool Set(bool bRunFlag);
private:
	CMutexLock m_Lock; //锁
	bool m_bAlreadRunFlag; //内部的变量值
};



//线程控制锁
class CThreadManager
{ 
private:
	//大家可能注意到，线程控制锁，大多数情况下用于查询，
	//只有在线程起停时，才会改写内部的值，
	//因此，此处用的全部是单写多读变量
	CMRSWbool m_bThreadContinue; //线程持续的标志
	CMRSWint m_nThreadCount; //线程计数器
	//很多时候，我们做测试代码，可能需要多个线程并发
	//在Debug 打印输出时，可能会需要一个独立的线程ID，
	//线程ID 需要做唯一性分配，因此，将这个分配器做在线程安全锁中，能被所有线程看到
	//与业务无关，仅用于区别打印信息来自于哪个线程，
	//这里提供一个线程ID 提供器，程序员可以根据需要，在线程中使用，
	//这算是一个内嵌的debug 友好功能。
	CMRSWint m_nThreadID;
public:
	CThreadManager(){} //由于多线程安全变量对象内置初始化，此处无需初始化
	~CThreadManager(){CloseAll();} //退出时自动关闭所有线程
	//启动逻辑，其实也是初始化逻辑
	//在使用线程控制锁前，请一定要先调用本接口函数
	void Open(void)
	{
		CloseAll(); //为防止多重启动，先执行一次Close
		//初始化线程控制变量
		m_bThreadContinue.Set(true);
		m_nThreadCount.Set(0);
	} 
	//关闭所有线程逻辑
	void CloseAll(void)
	{ //这个逻辑已经出现几次，此处不再赘述
		m_bThreadContinue.Set(false);
		while(m_nThreadCount.Get()){ToolsMinSleep();}
	} 
	//启动一个线程前，线程计数器+1的动作
	int AddAThread(void){return m_nThreadCount.Add();}
	//线程退出前，线程计数器-1 动作
	void DecAThread(void){m_nThreadCount.Dec();}
	//查询线程维持变量的值
	bool ThreadContinue(void){return m_bThreadContinue.Get();}
	//获得线程计数器的值
	int GetThreadCount(void){return m_nThreadCount.Get();}
	//分配一个线程ID，供Debug 使用
	int GetID(void) {return m_nThreadID.Add()-1;}
};



#endif	// __LOCK_TOOLS_H__
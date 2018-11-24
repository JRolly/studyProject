#include "LockTools.h"



int MvarInit(MINT& mValue,int nValue)
{
	MUTEXINIT(&mValue.m_MyLock); //��ʼ��������Ҫ���ǳ�ʼ��������
	mValue.m_nValue=nValue; //ͬʱ����ֵ
	return nValue;
} 

void MvarDestroy(MINT& mValue)
{
	MUTEXLOCK(&mValue.m_MyLock);
	MUTEXUNLOCK(&mValue.m_MyLock);
	//���ǵ��������������һ�ο���������ļ����ͽ�����Ϊ
	//ʹ�ݻٺ������Եȴ������߳���û����ɵķ��ʣ�����޶ȱ�֤��ȫ
	MUTEXDESTROY(&mValue.m_MyLock);//�ݻ�������
} 

int MvarSet(MINT& mValue,int nValue)
{
	MUTEXLOCK(&mValue.m_MyLock);
	mValue.m_nValue=nValue; //�������ڵĸ�ֵ
	MUTEXUNLOCK(&mValue.m_MyLock);
	return nValue;
} 

int MvarGet(MINT& mValue)
{
	int nValue;
	MUTEXLOCK(&mValue.m_MyLock);
	nValue=mValue.m_nValue; //�������ڵ�ȡֵ
	MUTEXUNLOCK(&mValue.m_MyLock);
	return nValue;
} 

int MvarADD(MINT& mValue,int nValue)
{
	int nRet;
	MUTEXLOCK(&mValue.m_MyLock);
	mValue.m_nValue+=nValue; //�������ڵ��ۼӶ���
	nRet=mValue.m_nValue;
	MUTEXUNLOCK(&mValue.m_MyLock);
	return nRet;
} 

int MvarDEC(MINT& mValue,int nValue)
{
	int nRet;
	MUTEXLOCK(&mValue.m_MyLock);
	mValue.m_nValue-=nValue; //�������ڵļ�������
	nRet=mValue.m_nValue;
	MUTEXUNLOCK(&mValue.m_MyLock);
	return nRet;
}



//��д�����
void MRSWLock_Create(SToolsMultiReadSingleWriteLock* pLock)
{
	MUTEXINIT(&(pLock->m_Lock)); //��ʼ���ڲ���
	pLock->m_nReadCount=0; //��ʼ����������
	pLock->m_bWriteFlag=false; //��ʼ��д��־
} 
void MRSWLock_Destroy(SToolsMultiReadSingleWriteLock* pLock)
{
	MUTEXLOCK(&pLock->m_Lock); //���ǵ�ǰ�ĵļ�����
	MUTEXUNLOCK(&pLock->m_Lock); //����һ�οռ���������������ܷ���
	MUTEXDESTROY(&(pLock->m_Lock)); //�ݻ��ڲ���
}
//��ȡд״̬
bool MRSWLock_GetWrite(SToolsMultiReadSingleWriteLock* pLock)
{
	bool bRet=false;
	MUTEXLOCK(&(pLock->m_Lock));
	{
		bRet=pLock->m_bWriteFlag;
	}
	MUTEXUNLOCK(&(pLock->m_Lock));
	return bRet;
} 
//��ȡ��������
int MRSWLock_GetRead(SToolsMultiReadSingleWriteLock* pLock)
{
	int nRet=0;
	MUTEXLOCK(&(pLock->m_Lock));
	{
		nRet=pLock->m_nReadCount;
	} 
	MUTEXUNLOCK(&(pLock->m_Lock));
	return nRet;
}
//����д��������
void MRSWLock_EnableWrite(SToolsMultiReadSingleWriteLock* pLock)
{
	while(1) //��ѭ���ȴ�
	{
		//��һ��ѭ������⡰д����־�Ƿ�Ϊ���١����������ᡰд��Ȩ
		//���ҷ��ģ���ʹ�������߳�����д�������ܻ����
		//��ˣ������ѭ��������Զ���ȣ�һ��ܿ�ͻ���Ϊ�������������
		MUTEXLOCK(&(pLock->m_Lock)); //�ڲ�����������������
		{
			//�ڴ����ڣ��������ʱ���д��������̣߳�����Ϊ�ڲ��������ñ���ס
			//�ж��Ƿ�������ᡰд��Ȩ��
			if(!pLock->m_bWriteFlag)
			{
				//���д��־Ϊ���١������������ᡰд��Ȩ��
				//ע�⣬��ʱһ����Ҫ���ڲ�����Ӧ��������д��־��Ϊ���桱
				pLock->m_bWriteFlag=true;
				//������д��Ȩ�󣬱����߼���ϣ�����ڲ����󣬿����˳�
				//�ؼ�����ע�⣬�����һ��������Ϊ��ȫ����ʹ��
				MUTEXUNLOCK(&(pLock->m_Lock));
				//ע���˳���ʽ��ʹ��goto ��ȷ��λ
				goto MRSWLock_EnableWrite_Wait_Read_Clean;
			} //����if �����
			//�˴�����д����־Ϊ�棬��ʾ�����߳��Ѿ�������д��Ȩ��
			//���̱߳������ҵȴ���
		} //�����������
		//�ȴ�˯��ʱ��Ӧ�ü�ʱ�ͷ��ڲ��������������̱߳���������
		MUTEXUNLOCK(&(pLock->m_Lock));
		//����һ�������Sleep������ὲ��
		ToolsMinSleep();
	} 
	//���ǵ�һ�׶���ɱ�־���������е��ˣ���ʾ��д��Ȩ�Ѿ���������������
MRSWLock_EnableWrite_Wait_Read_Clean:
	//���棬��ʼ�ȴ������ġ������������
	while(MRSWLock_GetRead(pLock)) //����ع�ע�������
		//�������ù��е�ȡ��״̬��������ȡ��Ϣ
		//ǰ���Ѿ�˵������������ڲ����ǡ���Դ����ģ�ͣ�
		//�������ڽ������ڲ������������̰߳�ȫ�ģ�
		//�˳��������ڲ����Զ�����
		//��ˣ���ѭ��Sleep �ڼ䣬������û�й�ס�ڲ�����
		//�����̷߳��ʵ��������з��������������޸Ķ���������ֵ��
		//�������߼��쳣��Ҫ!
	{
		//�ڶ���ѭ�����ȴ����еġ����������˳�
		//����ģ�һ����д����־����Ϊ���桱���µġ����������ᱻ���ң��������
		//���ϵĶ�����������Ṥ�����
		//��ˣ������ѭ�������ܵȵ��˳���ʱ�򣬲�������ѭ��
		ToolsMinSleep();
	}
}
//���˳�д������
void MRSWLock_DisableWrite(SToolsMultiReadSingleWriteLock* pLock)
{
	MUTEXLOCK(&(pLock->m_Lock));
	{
		pLock->m_bWriteFlag=false;
	} 
	MUTEXUNLOCK(&(pLock->m_Lock));
}
//��������������ص�ǰ�Ķ�������ֵ
int MRSWLock_AddRead(SToolsMultiReadSingleWriteLock* pLock)
{
	while(1)
	{
		//��������ѭ���ȴ�����������ʹ�������߳��ڽ���д������
		//�����ܻ���ɣ���ˣ����л�������д��־Ϊ���١�����������ѭ��
		MUTEXLOCK(&(pLock->m_Lock)); //���ڲ�������������
		{
			if(!pLock->m_bWriteFlag) //���д��־�Ƿ�Ϊ���١�
			{
				//���Ϊ���١�����ʾ���Կ�ʼ��
				//��ʱ��һ��Ҫ���ۼӣ����ͷ��ڲ������������ڿ�϶��
				//���±���̴߳�������
				pLock->m_nReadCount++;
				MUTEXUNLOCK(&(pLock->m_Lock));
				//���ض���������ֵ��
				//ע�⣺���ֵ���ܲ�һ���Ǹո��ۼӵ�ֵ
				//�����ڲ����Ѿ��������Ķ��߳���ȫ�����н���
				//�����ֵ���Ӻü���
				return MRSWLock_GetRead(pLock);//���Ǳ�����Ψһ������
			}
		} 
		//���д��־Ϊ���桱��ֻ��ѭ���ȴ�
		MUTEXUNLOCK(&(pLock->m_Lock));
		//ʹ������˯�ߣ������н���
		ToolsMinSleep();
	}
}
//���ض��������仯��Ľ��
int MRSWLock_DecRead(SToolsMultiReadSingleWriteLock* pLock)
{
	int nRet=0;
	MUTEXLOCK(&(pLock->m_Lock));
	{
		//����һ��ϰ���Ա������ݼ�����ʱ�������Сֵ��0�����ǼӸ��ж�
		if(0<(pLock->m_nReadCount))
			pLock->m_nReadCount--;
		//ע�⣬������ֱ�ӻ�ö���������ֵ�����������Ƚ����Ҫ׼ȷһ��
		nRet=pLock->m_nReadCount;
	} 
	MUTEXUNLOCK(&(pLock->m_Lock));
	return nRet;
}
//��תд
void MRSWLock_Read2Write(SToolsMultiReadSingleWriteLock* pLock)
{
	while(1) //��ѭ�����ͽ���д�е���ѭ��һ������
	{
		MUTEXLOCK(&(pLock->m_Lock));
		{
			if(!pLock->m_bWriteFlag)
			{
				//ע�����һ����⵽��������дȨ��
				//�Ȱ�д��־��Ϊ���桱
				pLock->m_bWriteFlag=true;
				//�мǣ������Ƕ�תд����ǰ�������ʱ���Ѿ��Ѽ�����+1
				//����һ��Ҫ-1������ᵼ�¼�������Զ��Ϊ0��ϵͳ����
				if(0<(pLock->m_nReadCount))
					pLock->m_nReadCount--;
				//��ǰ������״̬������ɣ�����ڲ�����������һ��
				MUTEXUNLOCK(&(pLock->m_Lock));
				goto MRSWLock_Read2Write_Wait_Read_Clean;
			}
		}
		//����ڲ����ȴ���ǰ���Ѿ�˵��
		MUTEXUNLOCK(&(pLock->m_Lock));
		ToolsMinSleep();
	} 
	//�˴���ʼ�ȴ����еĶ��˳���ͬ������д�����߼�
MRSWLock_Read2Write_Wait_Read_Clean:
	while(MRSWLock_GetRead(pLock))
	{
		ToolsMinSleep();
	}
}

//�߾���˯�ߺ�������������ģʽ���ٵ���
inline void ToolsMinSleep(void)
{
#ifdef WIN32
	Sleep(1); //Windows �²����ı䣬����Ӧ�ü�Sleep ����
#else // not WIN32
	//Linux �£�ʹ��nanosleep ʵ�ָ߾���˯��
	struct timespec slptm;
	slptm.tv_sec = 0;
	slptm.tv_nsec = 1000; //1000 ns = 1 us
	if(nanosleep(&slptm, NULL) == -1) usleep(1);
#endif //WIN32
} 


//��д�������ȫ����

CMRSWint::CMRSWint() //���캯����ʼ������
{
	m_Lock.EnableWrite();
	m_nValue=0;
	m_Lock.DisableWrite();
} 
int CMRSWint::Get(void) //�õ�������ֵ
{
	int nRet=0;
	m_Lock.AddRead(); //���ע������Ƕ���ʽ��������������Բ���
	{
		nRet=m_nValue;
	} m_Lock.DecRead();
	return nRet;
} 
int CMRSWint::Set(int nValue) //���ñ�����ֵ
{
	int nRet=0;
	m_Lock.EnableWrite(); //ע�⣬������д��ʽ����ʾ�Ǵ��е�
	{
		m_nValue=nValue;
		nRet=m_nValue;
	} m_Lock.DisableWrite();
	return nRet;
} 
int CMRSWint::Add(int nValue) //�ӷ�����
{
	int nRet=0;
	m_Lock.EnableWrite(); //д��ʽ������
	{
		m_nValue+=nValue;
		nRet=m_nValue;
	} m_Lock.DisableWrite();
	return nRet;
} 
int CMRSWint::Dec(int nValue) //��������
{
	int nRet=0;
	m_Lock.EnableWrite(); //д��ʽ������
	{
		m_nValue-=nValue;
		nRet=m_nValue;
	} m_Lock.DisableWrite();
	return nRet;
}



//����������
CNonReentrant::CNonReentrant()
{ //��ʼ���ڲ�����
	m_bAlreadRunFlag=false;
} 
//���ĵ�Set ����
bool CNonReentrant::Set(bool bRunFlag)
{
	//��ע�⣬���ؽ�������ö����ĳɹ���񣬺��ڲ���bool ������û���κι�ϵ
	bool bRet=false;
	if(bRunFlag) //��Ҫ����Ϊ����߼����Ƚϸ���
	{
		m_Lock.Lock(); //��������
		{
			if(!m_bAlreadRunFlag)
			{ //���ԭֵΪ���١�����ʾ��������
				m_bAlreadRunFlag=true; //�����ڲ�bool ����
				bRet=true; //�����棬��ʾ���óɹ�
			} 
			//���򣬲����κ��£����ڲ�bool �����������ã��ҷ��ؼ�
		}
		m_Lock.Unlock(); //�˳�����
	} 
	else
	{ //��������Ϊ���١������
		m_Lock.Lock(); //��������
		{
			m_bAlreadRunFlag=false; //�����������ڲ�bool ����Ϊ���١�
			bRet=true; //������Ҳ�����óɹ�����˷�����
		} 
		m_Lock.Unlock(); //�˳�����		
	} 
	return bRet;
}










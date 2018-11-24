#include "stdafx.h"
#include "FunctionLib.h"


CString itoa(INT64 nVal)
{
	CString szRet;
	char szBuffer[100] = {0};
	szRet = _itoa(nVal, szBuffer, 10);
	return szRet;
}

CString uitoa(UINT64 uiVal)
{
	CString szRet;
	char szBuffer[100] = {0};
	szRet = _ui64toa(uiVal, szBuffer, 10);
	return szRet;
}

CString hextoa(UINT64 uiVal)
{
	CString szRet, szTemp;
	BYTE nTemp = 0;
	
	while (uiVal)
	{
		nTemp = uiVal;
		szTemp.Format("%02X", nTemp);
		szRet.Insert(0, szTemp);
		uiVal >>= 8;
	}

	return szRet;
}

UINT64 atohex(char* pHex, UINT32 uiLen)
{
	UINT64 uiRet = 0;
	if (!pHex) return 0;
	if (uiLen <= 0) return 0;
	if ('0' == *pHex && ('x' == *(pHex+1) || 'X' == *(pHex+1)))
		pHex += 2;

	for (int i=uiLen-1; i>=0; --i)
	{
		if (*pHex >= '0' && *pHex <= '9')
			uiRet += (*pHex - '0') * (int)pow(16.0, i);
		else if (toupper(*pHex) >= 'A' && toupper(*pHex) <= 'F')
			uiRet += (toupper(*pHex) - 'A' + 10) * (int)pow(16.0, i);
		else
			return 0;
		++pHex;
	}

	return uiRet;
}


CString GetCurDir()
{
	CString szRet = "";
	char szBuffer[MAX_PATH] = {0};
	if (getcwd(szBuffer, MAX_PATH))
		szRet = szBuffer;
	return szRet;
}

UINT64 gcd(UINT64 uiA, UINT64 uiB)
{
	UINT64 uiRet = 0;
	if (0 == uiB) return uiA;
	if (0 == uiA) return uiB;

	if (uiA > uiB)
		gcd(uiB, uiA%uiB);		
	else 
		gcd(uiA, uiB%uiA);
}

UINT64* Sieve(UINT64* pList, UINT64 uiLen)
{
	if (!pList) return NULL;
	if (0 == uiLen) return NULL;

	UINT64* pArr = new UINT64[uiLen];
	UINT64 uiIdx = 0;
	memset(pArr, 0, sizeof(pArr));

	//初始化pArr
	for (UINT64 i=0; i<uiLen; ++i)
		pArr[i] = i;

	//开始筛选
	for (UINT64 i=2; i<(UINT64)sqrt((double)uiLen); ++i)
	{
		UINT64 j = 0;
		if (0 != pArr[i])	//判断是否已经消除
		{
			j = i*i;
			while (j <= uiLen)	//消除
			{
				pArr[j] = 0;	
				j += i;
			}
		}
	}

	//拷贝剩余元素
	for (UINT64 i=0; i<uiLen; ++i) 
	{
		if (0 != pArr[i])
			pList[uiIdx++] = pArr[i];
	}

	return pList;
}



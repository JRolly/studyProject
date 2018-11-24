#include "stdafx.h"

#ifndef	__FUNCTIONLIB__H
#define __FUNCTIONLIB__H

#include <math.h>
#include <cstring>
#include <atlstr.h>
#include <direct.h>

#define sw16(X)                 ((((UINT16)(X) & 0xff00) >> 8) |(((UINT16)(X) & 0x00ff) << 8))

#define sw32(X)                 ((((UINT32)(X) & 0xff000000) >> 24) | \
								(((UINT32)(X) & 0x00ff0000) >> 8) | \
								(((UINT32)(X) & 0x0000ff00) << 8) | \
								(((UINT32)(X) & 0x000000ff) << 24))

#define sw64(X)					(\
								(((UINT64)(X) & 0xff00000000000000) >>56) |\
								(((UINT64)(X) & 0x00ff000000000000) >>40)  |\
								(((UINT64)(X) & 0x0000ff0000000000) >>24)  |\
								(((UINT64)(X) & 0x000000ff00000000) >>8)  |\
								(((UINT64)(X) & 0x00000000ff000000) <<8)  |\
								(((UINT64)(X) & 0x0000000000ff0000) <<24) |\
								(((UINT64)(X) & 0x000000000000ff00) <<40) |\
								(((UINT64)(X) & 0x00000000000000ff) <<56)) \
								)



//数值转字符串
CString itoa(INT64 nVal);	//有符号
CString uitoa(UINT64 uiVal); //无符号
CString hextoa(UINT64 uiVal); //十六进制

//字符串转数值
UINT64 atohex(char* pHex, UINT32 uiLen); //十六进制, 如果输入不为0，但返回0则表示错误

//获取当前工作路径，失败返回空字符
CString GetCurDir();

//最大公约数，欧几里德算法(Euclid)
UINT64 gcd(UINT64 uiA, UINT64 uiB);

//埃拉托色尼筛选法，筛选质数，从2开始返回
UINT64* Sieve(UINT64* pList, UINT64 uiLen);


//最小值
template<typename TYPE> TYPE MIN(TYPE a, TYPE b){return (a < b) ? a : b;}
//最大值
template<typename TYPE> TYPE MAX(TYPE a, TYPE b){return (a > b) ? a : b;}
//最值
template<typename TYPE> void GetMinMaxVal(const TYPE *arr, DWORD l, DWORD r,
	TYPE &maxValue, TYPE &minValue)
{
	if(l == r) // l与r之间只有一个元素  
	{  
		maxValue = arr[l] ;  
		minValue = arr[l] ;  
		return ;  
	}  

	if(l + 1 == r) // l与r之间只有两个元素  
	{  
		if(arr[l] >= arr[r])  
		{  
			maxValue = arr[l] ;  
			minValue = arr[r] ;  
		}  
		else  
		{  
			maxValue = arr[r] ;  
			minValue = arr[l] ;  
		}  
		return ;  
	}  

	TYPE m = (l + r) / 2 ; // 求中点  

	TYPE lmax ; // 左半部份最大值  
	TYPE lmin ; // 左半部份最小值  
	GetMinMaxVal(arr, l, m, lmax, lmin) ; // 递归计算左半部份  

	TYPE rmax ; // 右半部份最大值  
	TYPE rmin ; // 右半部份最小值  
	GetMinMaxVal(arr, m + 1, r, rmax, rmin) ; // 递归计算右半部份  

	maxValue = MAX(lmax, rmax) ; // 总的最大值  
	minValue = MIN(lmin, rmin) ; // 总的最小值
}


//顺序查找，失败返回-1
template<typename TYPE> int sq_search(TYPE key[], int n, TYPE k)
{
	for (int i=0; i<n; ++i)
		if (key[i] = k)
			return i;
	return -1;
}

//二分查找，输入必须为升序，失败返回-1
template<typename TYPE> int bin_search(TYPE key[], int n, TYPE k)
{
	int mid, low=0, high=n-1;
	while(low < high)
	{
		mid = (low+high)/2;
		if (key[mid] == k)
			return mid;
		if (k > key[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}
}

//插入排序
template<typename TYPE> void InsertSort(TYPE k[], int n) 
{
	int j;
	TYPE temp;
	for (int i=1; i<n; ++i)
	{
		temp = k[i];
		j = i - 1;
		while (j>=0 && temp<k[j])
			k[j+1] = k[j--];
		k[j+1] = temp;
	}
}

//选择排序
template<typename TYPE> void SelectSort(TYPE k[], int n)
{
	int min;
	TYPE temp;
	for (int i=0; i<n; ++i)
	{
		min = i;
		for (int j=i+1; j<n; ++j)
			if (k[j] < k[min])
				min = j;
		if (min != i)
		{
			temp = k[min];
			k[min] = k[i];
			k[i] = temp;
		}
	}
}

//冒泡排序
template<typename TYPE> void BubbleSort(TYPE k[], int n)
{
	TYPE temp;	
	int flag = 1;
	for (int i=1; i<n && 1==flag; ++i)
	{		
		flag = 0;
		for (int j=0; j<n-i; ++j)
		{
			if (k[j] > k[j+1])
			{
				temp = k[j];
				k[j] = k[j+1];
				k[j+1] = temp;
				flag = 1;
			}
		}
	}
}

//希尔排序
template<typename TYPE> void ShellSort(TYPE k[], int n)
{
	TYPE temp;
	int gap = n, flag = 1;
	while (gap>1)
	{
		gap /= 2;
		do 
		{
			flag = 0;
			for (int i=0; i<n-gap; ++i)
			{
				if (k[i] > k[i+gap])
				{
					temp = k[i];
					k[i] = k[i+gap];
					k[i+gap] = temp;
					flag = 1;
				}
			}
		} while (flag!=0);
	}
}

//快速排序
template<typename TYPE> void QuickSort(TYPE k[], int nLeft, int nRight)
{
	if (nLeft < nRight)
	{
		TYPE temp = k[nLeft];
		int low = nLeft, hight = nRight;
		while (low<hight)
		{
			while (low<hight && temp<k[hight])	--hight;
			k[low] = k[hight];
			while (low<hight && temp>k[low]) ++low;
			k[hight] = k[low];
		}
		k[low] = temp;

		QuickSort(k, nLeft, low-1);
		QuickSort(k, low+1, nRight);
	}
}














#endif	//#define __FUNCTIONLIB__H
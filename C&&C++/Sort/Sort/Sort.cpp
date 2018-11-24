/*
*	sort,排序
*/
#include <stdio.h>
#include <stdlib.h>

int arr[] = {2,1,8,7,11,4,6,9};
int arr_size = sizeof(arr)/sizeof(arr[0]);


void BubbleSort(int *pDataArray, int iDataNum)
{
	for (int i = 0,change = 1; i < iDataNum && change; i++)
	{
		change = 0;
		for (int j = 0; j < i; j++)
		{
			if (pDataArray[j] > pDataArray[j+1])
			{
				pDataArray[j] += pDataArray[j+1];
				pDataArray[j+1] = pDataArray[j] - pDataArray[j+1];
				pDataArray[j] -= pDataArray[j+1];
				change = 1;
			}
		}
	}
}


/********************************************************
*函数名称：InsertSort
*参数说明：pDataArray 无序数组；
*		   iDataNum为无序数据个数
*说明：    插入排序
*********************************************************/
void InsertSort(int* pDataArray, int iDataNum)
{
	for (int i = 1; i < iDataNum; i++)    //从第2个数据开始插入
	{
		int j = i - 1;
		int temp = pDataArray[i];    //记录要插入的数据
		while (j >= 0 && pDataArray[j] > temp)    //从后向前，找到比其小的数的位置
		{
			pDataArray[j+1] = pDataArray[j];    //向后挪动
			j--;
		}

		if (j != i - 1)    //存在比其小的数
			pDataArray[j+1] = temp;
	}
}

//快速排序
void QuickSort(int *pDataArray, int low, int high)
{
	if (low < high)
	{
		int i = low, j = high;
		int pivo = pDataArray[low];		//轴标识，把小于pivo的数都放到它左边，大于pivo的数都放到它右边
		while (i < j)
		{
			while (i < j && pDataArray[j] >= pivo)	//从右向左扫描，第一个小于pivo的数
				j--;
			if (i < j)
				pDataArray[i++] = pDataArray[j];
			while (i < j && pDataArray[i] < pivo)	//从左向右扫描，第一个大于pivo的数
				i++;
			if (i < j)
				pDataArray[j--] = pDataArray[i];
		}
		pDataArray[i] = pivo;	//i=j,第一趟完成
		QuickSort(pDataArray,low,i-1);	//递归，分别对轴标识左边和右边的数分治
		QuickSort(pDataArray,i+1,high);
	}
}

//简单选择排序
void SelectSort(int *pDataArray, int iDataNum)
{
	for (int i = 0; i < iDataNum - 1; i++)
	{
		int index = i;
		for (int j = i+1; j < iDataNum; j++)
		{
			if (pDataArray[j] < pDataArray[index])
				index = j;
		}
		if (i != index)
		{
			pDataArray[i] += pDataArray[index];
			pDataArray[index] = pDataArray[i] - pDataArray[index];
			pDataArray[i] -= pDataArray[index];
		}
	}
}


void PrintArr(void)
{
	int i = 0;
	for (; i<arr_size; i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");
}

void main()
{
	printf("Befor Sort: \n");
	PrintArr();
	//InsertSort(arr,arr_size);
	//QuickSort(arr,0,arr_size-1);
	//SelectSort(arr,arr_size);
	BubbleSort(arr,arr_size);
	printf("After Sort: \n");
	PrintArr();
}
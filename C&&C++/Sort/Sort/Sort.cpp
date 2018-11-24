/*
*	sort,����
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
*�������ƣ�InsertSort
*����˵����pDataArray �������飻
*		   iDataNumΪ�������ݸ���
*˵����    ��������
*********************************************************/
void InsertSort(int* pDataArray, int iDataNum)
{
	for (int i = 1; i < iDataNum; i++)    //�ӵ�2�����ݿ�ʼ����
	{
		int j = i - 1;
		int temp = pDataArray[i];    //��¼Ҫ���������
		while (j >= 0 && pDataArray[j] > temp)    //�Ӻ���ǰ���ҵ�����С������λ��
		{
			pDataArray[j+1] = pDataArray[j];    //���Ų��
			j--;
		}

		if (j != i - 1)    //���ڱ���С����
			pDataArray[j+1] = temp;
	}
}

//��������
void QuickSort(int *pDataArray, int low, int high)
{
	if (low < high)
	{
		int i = low, j = high;
		int pivo = pDataArray[low];		//���ʶ����С��pivo�������ŵ�����ߣ�����pivo�������ŵ����ұ�
		while (i < j)
		{
			while (i < j && pDataArray[j] >= pivo)	//��������ɨ�裬��һ��С��pivo����
				j--;
			if (i < j)
				pDataArray[i++] = pDataArray[j];
			while (i < j && pDataArray[i] < pivo)	//��������ɨ�裬��һ������pivo����
				i++;
			if (i < j)
				pDataArray[j--] = pDataArray[i];
		}
		pDataArray[i] = pivo;	//i=j,��һ�����
		QuickSort(pDataArray,low,i-1);	//�ݹ飬�ֱ�����ʶ��ߺ��ұߵ�������
		QuickSort(pDataArray,i+1,high);
	}
}

//��ѡ������
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
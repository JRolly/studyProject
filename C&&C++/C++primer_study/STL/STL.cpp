#include <iostream>

using namespace std;

template <typename T>
int compare(const T &v1, const T &v2)
{
	if (v1 < v2)
		return -1;
	if (v2 < v1)
		return 1;
	return 0;
}

template <typename T>
T absVal(T val)
{
	return val > 0 ? val : -val;
}

//������ģ���β�
//�����������һ���βΣ� ���β������������
//��ʼ������
template <typename T, size_t N> 
void arr_init(T (&parm)[N])	//int arr[10]
{
	for (size_t i = 0; i < N; ++i)
		parm[i] = 0;
}

//�������鳤��
template <typename T, size_t N>
size_t arr_len(T (&arr)[N])
{
	return N;
}

//�������
template <typename T, size_t N>
void printArr(T (&arr)[N])
{
	for (size_t i = 0; i < N; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}



//void main()
//{
//	int arr[10];
//	arr_init(arr);
//	arr[3] = 3;
//	printArr(arr);
//
//
//
//	system("PAUSE");
//}



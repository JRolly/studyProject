/*
*  linear_list,���Ա�
*/
#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__


//���Ա�Ķ�̬����˳��洢�ṹ
#define LIST_INIT_SIZE	100	//���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT	10	//���Ա�洢�ռ�ķ�������

//Status code
#define TRUE			1
#define FALSE			-1
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1
#define OVERFLOW		-2

typedef int Status;		//���������ͣ�ֵΪ�����ṹ״̬����
typedef int ElemType;	//������ʾ��������

//Struct
typedef struct {
	ElemType *elem;		//�洢�ռ��ַ
	int length;			//��ǰ����
	int listsize;		//��ǰ����Ĵ洢������sizeof(ElemType)��
}Sqlist;


#endif //end #ifndef __LINEAR_LIST_H__

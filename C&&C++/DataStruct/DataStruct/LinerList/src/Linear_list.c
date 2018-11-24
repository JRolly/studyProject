#include <stdio.h>
#include <stdlib.h>
#include "Linear_list.h"

//Functions

//����һ���յ����Ա�
Status InitList(Sqlist *L)
{
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
	{
		exit(OVERFLOW);		//�洢�ռ����ʧ��
	}
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;

	return OK;
}

//�������Ա�
Status DestoryList(Sqlist *L)
{
	free((*L).elem);
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;

	return OK;
}

 void visit(ElemType *c) /* ListTraverse()���õĺ���(����Ҫһ��) */
 {
   printf("%d ",*c);
 }

//�����Ա�����Ϊ�ձ�
Status ClearList(Sqlist *L)
{
	(*L).length = 0;

	return OK;
}

//�ж����Ա��Ƿ�Ϊ�գ��ǣ�����TRUE���񣬷���FALSE
Status ListEmpty(Sqlist L)
{
	if (L.length = 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�������Ա���Ԫ�صĸ���
int ListLength(Sqlist L)
{
	return L.length;
}

//��e�������Ա��е�i��Ԫ�ص�ֵ
Status GetElem(Sqlist L, int i, ElemType *e)
{
	if (i < 1 || i > L.length)
	{
		exit(ERROR);
	}
	*e = *(L.elem + i-1); 

	return OK;
}

//����L�е�һ����e�����ϵcompar()������Ԫ�ص�λ��������������������Ԫ�أ�����0
int LocateElem(Sqlist L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	int i = 1;
	ElemType *p = L.elem;

	while (i <= L.length && compare(*p++,e))
	{
		++i;
	}

	if (i <= L.length)
	{
		return i;
	}
	else
	{
		return 0;
	}
}

//��cur_e ��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
Status PriorElem(Sqlist L, ElemType cur_e, ElemType *pre_e)
{
	int i = 2;
	ElemType *p = L.elem + 1;

	while (i <= L.length && *p != cur_e)
	{
		i++;
		p++;
	}

	if (i > L.length)
	{
		return INFEASIBLE;
	}
	else
	{
		*pre_e = *(--p);
		return OK;
	}
}

//��cur_e ��L������Ԫ�أ��Ҳ������һ������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶���
Status NextElem(Sqlist L, ElemType cur_e, ElemType *next_e)
{
	int i = 1;
	ElemType *p = L.elem;

	while (i < L.length && *p != cur_e)
	{
		i++;
		p++;
	}

	if (i > L.length)
	{
		return INFEASIBLE;
	}
	else
	{
		*next_e = *(++p);
		return OK;
	}
}

//��L�е�i��λ��֮ǰ�����µ�����Ԫ�ض�e��L�ĳ��ȼ�1
Status ListInsert(Sqlist *L, int i, ElemType e)
{
	ElemType *newBase, *q, *p;

	if (i < 1 || i > (*L).length+1)
	{
		return ERROR;
	}

	if ((*L).length >= (*L).listsize)
	{	//��ǰ�洢�ռ����������ӷ���ռ�
		newBase = (ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
		if (!newBase)
		{
			exit(OVERFLOW);		//�洢�ռ����ʧ��
		}
		(*L).elem = newBase;	//�»�ַ
		(*L).listsize += LISTINCREMENT;	//���Ӵ洢����
	}

	q = (*L).elem + i-1;	//qΪ����λ��
	for (p = (*L).elem+(*L).length-1; p >= q; --p)
	{	//����λ�ü�֮���Ԫ������
		*(p+1) = *p;
	}

	*q = e; //����e
	++(*L).length;	//����1

	return OK;
}

//ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
Status ListDelete(Sqlist *L, int i, ElemType *e)
{
	ElemType *p;
	
	if (i <1 || i > (*L).length)
	{
		return ERROR;
	}

	*e = *((*L).elem + i-1);

	for (p = (*L).elem+i; p <= (*L).elem+(*L).length-1; p++)
	{
		*(p-1) = *p;
	}

	(*L).length--;

	return OK;
}

Status ListTraverse(Sqlist L, void(*visit)(ElemType*))
 { /* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
   /*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
   ElemType *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     visit(p++);
   printf("\n");
   return OK;
 }

//��֪˳�����Ա�La �� Lb ��Ԫ�ذ��ǵݼ����У�
//�鲢La��Lb���µ�˳�����Ա�Lc,Lc��Ԫ��Ҳ���ǵݼ�����
void MergerList(Sqlist La, Sqlist Lb, Sqlist *Lc)
{
	ElemType *pa, *pa_last, *pb, *pb_last, *pc;
	pa = La.elem;
	pb = Lb.elem;
	(*Lc).listsize = (*Lc).length = La.length+Lb.length;
	pc = (*Lc).elem = (ElemType*)malloc((*Lc).listsize*sizeof(ElemType));
	if (!(*Lc).elem)
	{
		exit(OVERFLOW);
	}

	pa_last = La.elem + La.length-1;
	pb_last = Lb.elem + Lb.length-1;

	while (pa<=pa_last && pb<=pb_last)
	{
		if (*pa <= *pb)
		{
			*pc++ = *pa++;
		}
		else
		{
			*pc++ = *pb++;
		}
	}
	while (pa <= pa_last)
	{
		*pc++ = *pa++;
	}
	while (pb <= pb_last)
	{
		*pc++ = *pb++;
	}

}

void print(ElemType *c)
 {
   printf("%d ",*c);
 }
 
void main()
{
	Sqlist La, Lb, Lc;
	int i;
	InitList(&La);
	for (i = 1; i <=5; i++)
	{
		ListInsert(&La, i, i);
	}
	printf("La= ");
	ListTraverse(La,print);
	InitList(&Lb);
	for (i = 0; i <= 5; i++)
		ListInsert(&Lb, i, i);
	printf("Lb= ");
	ListTraverse(Lb,print);

	MergerList(La,Lb,&Lc);
	printf("Lc= ");
	ListTraverse(Lc,print);
}

////main
//void main(void)
//{
//	Sqlist L;
//	ElemType e;
//	Status stat;
//	int i,j;
//
//	stat = InitList(&L);
//	printf("��ʼ��L��L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
//	for (i = 1; i <=5; i++)
//	{
//		stat = ListInsert(&L,1,i);
//	}
//	printf("\n");
//
//	printf("����Ԫ�غ�L��L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
//
//	stat = ListEmpty(L);
//	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);
//
//	stat = ClearList(&L);
//	printf("���L��L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
//
//	stat = ListEmpty(L);
//	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);
//
//	for (i = 1; i <= 10; i++)
//	{
//		ListInsert(&L,i,i);
//	}
//	printf("��L�ı�β���β���1��10��*L.elem=");
//	for (i = 1; i <= 10; i++)
//	{
//		printf("%d ",*(L.elem+i-1));
//	}
//	printf("\n");
//
//	GetElem(L,5,&e);
//    printf("��5��Ԫ�ص�ֵΪ��%d\n",e);
//
//	PriorElem(L, 5,&e);
//	printf("5��ǰ���ǣ�%d\n",e);
//
//	NextElem(L,5,&e);
//	printf("5�ĺ���ǣ�%d\n",e);
//
//	ListDelete(&L,5,&e);
//	printf("ɾ����5��Ԫ��:%d,ɾ����ı��ǣ�\n",e);
//	for (i = 1; i <= L.length; i++)
//	{
//		printf("%d ",*(L.elem+i-1));
//	}
//	printf("\n");
//
//	DestoryList(&L);
//}


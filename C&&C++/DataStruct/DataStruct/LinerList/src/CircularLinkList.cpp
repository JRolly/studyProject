/*
*	��ѭ������,����βָ��
*/
#include <stdio.h>
#include <stdlib.h>
#include "CircularLinkList.h"

Status InitList_CL(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode)); //����ͷ��㣬��ʹLָ��ͷ���
	if (!*L)
		exit(OVERFLOW);
	(*L)->next = *L;

	return OK;
}

//����
Status DestroyList_CL(LinkList *L)
{
	LinkList q, p = (*L)->next;
	while (p != *L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(*L);
	*L = NULL;
	return OK;
}

//����Ϊ�ձ�
Status ClearList_CL(LinkList *L)
{
	LinkList p, q;
	*L = (*L)->next;
	p = (*L)->next;
	while (p != *L)
	{
		q = p->next;
		free(p);
		q = p;
	}
	(*L)->next = *L;
	return OK;
}

//�Ƿ�Ϊ�ձ�
Status ListEmpty_CL(LinkList L)
{
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

//��
int ListLength_CL(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p != L)
	{
		i++;
		p = p->next;
	}
	return i;
}

//��ȡ��i��Ԫ�أ�����*e��
Status GetElem_CL(LinkList L, int i, ElemType *e)
{
	int j = 1;
	LinkList p = L->next->next;
	if (i<=0 || i>ListLength_CL(L))
		return ERROR;
	while (j < i)
	{
		j++;
		p = p->next;
	}
	*e = p->data;
	return OK;
}

//������e����compare��ϵ��Ԫ�ص�λ��
int LocateElem_CL(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	int i = 0;
	LinkList p = L->next->next;
	while (p != L->next)
	{
		i++;
		if (compare(p->data,e))
			return i;
		p = p->next;
	}
	return 0;
}

//����cur_e��ǰ��
Status PriorElem_CL(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList q, p = L->next->next;
	q = p->next;
	while (q != L->next)
	{
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return TRUE;
		}
		p = q;
		q = q->next;
	}
	return FALSE;
}

//����cur_e�ĺ��
Status NextElem_CL(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next->next;
	while (p != L)
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return TRUE;
		}
		else
			p = p->next;
	}
	return FALSE;
}

//�ڵ�i��λ�ò���Ԫ��e
Status ListInsert_CL(LinkList *L, int i, ElemType e)
{
	LinkList p = (*L)->next, node;
	int j = 0;
	if (i <=0 || i>ListLength_CL(*L)+1)
		return ERROR;
	while (j < i-1)
	{
		j++;
		p = p->next;
	}
	node = (LinkList)malloc(sizeof(struct LNode));
	node->data = e;
	node->next = p->next;
	p->next = node;
	if (p == *L)	//�ı�β���
		*L = node;
	return OK;
}

//ɾ����i��λ���ϵ�Ԫ��,�����ص�e
Status ListDelete_CL(LinkList *L, int i, ElemType *e)
{
	LinkList p = (*L)->next, q;
	int j = 0;
	if (i<=0 || j>ListLength_CL(*L))
		return ERROR;
	while (j < i-1)
	{
		p = p->next;
		j++;
	}
	q = p->next;	//��ɾ�����
	p->next = q->next;
	*e = q->data;
	if (*L == q)
		*L = p;
	free(q);
	return OK;

}

//����
Status ListTraverse_CL(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L->next->next;
	while (p != L->next)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}



Status compare(ElemType c1,ElemType c2)
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList L;
   ElemType e;
   int j;
   Status i;
   i=InitList_CL(&L); /* ��ʼ����ѭ������L */
   printf("��ʼ����ѭ������L i=%d (1:��ʼ���ɹ�)\n",i);
   i=ListEmpty_CL(L);
   printf("L�Ƿ�� i=%d(1:�� 0:��)\n",i);
   ListInsert_CL(&L,1,3); /* ��L�����β���3,5 */
   ListInsert_CL(&L,2,5);
   i=GetElem_CL(L,1,&e);
   j=ListLength_CL(L);
   printf("L������Ԫ�ظ���=%d,��1��Ԫ�ص�ֵΪ%d��\n",j,e);
   printf("L�е�����Ԫ������Ϊ��");
   ListTraverse_CL(L,visit);
   PriorElem_CL(L,5,&e); /* ��Ԫ��5��ǰ�� */
   printf("5ǰ���Ԫ�ص�ֵΪ%d��\n",e);
   NextElem_CL(L,3,&e); /* ��Ԫ��3�ĺ�� */
   printf("3�����Ԫ�ص�ֵΪ%d��\n",e);
   printf("L�Ƿ�� %d(1:�� 0:��)\n",ListEmpty_CL(L));
   j=LocateElem_CL(L,3,compare);
   if(j)
     printf("L�ĵ�%d��Ԫ��Ϊ3��\n",j);
   else
     printf("������ֵΪ3��Ԫ��\n");
   i=ListDelete_CL(&L,2,&e);
   printf("ɾ��L�ĵ�2��Ԫ�أ�\n");
   if(i)
   {
     printf("ɾ����Ԫ��ֵΪ%d,����L�е�����Ԫ������Ϊ��",e);
     ListTraverse_CL(L,visit);
   }
   else
   printf("ɾ�����ɹ���\n");
   i = ClearList_CL(&L);
   printf("���L��%d(1: �ɹ�)\n",i);
   i = ListEmpty_CL(L);
   printf("���L��L�Ƿ�գ�%d(1:�� 0:��)\n",i);
   i = DestroyList_CL(&L);
   printf("����L��%d(1: �ɹ�)\n",i);
 }

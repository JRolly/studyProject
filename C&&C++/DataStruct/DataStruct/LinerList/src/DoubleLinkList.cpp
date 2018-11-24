/*
*	˫��ѭ������
*/
#include <stdio.h>
#include <stdlib.h>
#include "Define.h"
#include "DoubleLinkList.h"


//�����յ�˫��ѭ������
Status InitList(DuLinkList *L)
{
	*L = (DuLinkList)malloc(sizeof(struct DuLNode));
	if (!*L)
		return OVERFLOW;
	(*L)->next = (*L)->prior = *L;
	return OK;
}

//����˫��ѭ������
Status DestroyList(DuLinkList *L)
{
	DuLinkList q, p = (*L)->next;
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

//����˫��ѭ������Ϊ�ձ�
Status ClearList(DuLinkList L)
{
	DuLinkList q, p = L->next;
	while (p != L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = L->prior = L;
	return OK;
}

//����Ƿ�Ϊ�ձ�
Status ListEmpty(DuLinkList L)
{
	if (L->next==L && L->prior==L)
		return TRUE;
	else
		return FALSE;
}

//��ȡ����
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next;
	int i = 0;
	while (p != L)
	{
		p = p->next;
		i++;
	}
	return i;
}

//��ȡ��i��λ���ϵ�Ԫ��
Status GetElem(DuLinkList L, int i, ElemType *e)
{
	int j = 1;
	DuLinkList p = L->next;
	while (p!=L && j<i)
	{
		p = p->next;
		j++;
	}
	if (p==L || j>i)
		return ERROR;
	*e = p->data;
	return OK;
}

//��������compare��ϵ��Ԫ�ص�λ��
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	DuLinkList p = L->next;
	int i = 0;
	while (p != L)
	{
		i++;
		if (TRUE == compare(p->data,e))
			return i;
		p = p->next;
	}
	return 0;
}

//����cur_e��ǰ��
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e)
{
	DuLinkList p = L->next->next;
	while (p != L)
	{
		if (p->data == cur_e)
		{
			*pre_e = p->prior->data;
			return TRUE;
		}
		p = p->next;
	}
	return FALSE;
}

//����cur_e�ĺ��
Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e)
{
	DuLinkList p = L->next;
	while (p!=L)
	{
		if (p->prior->data == cur_e)
		{
			*next_e = p->data;
			return TRUE;
		}
		p = p->next;
	}
	return FALSE;
}

//���ص�i��Ԫ�ص�λ��ָ��
DuLinkList GetElemP(DuLinkList L, int i)
{
	int j = 1;
	DuLinkList p = L;
	for (; j<=i; j++)
	{
		p = p->next;
	}
	return p;
}

//�ڵ�i��λ��֮ǰ����Ԫ��
Status ListInsert(DuLinkList L, int i, ElemType e)
{
	DuLinkList p,node;
	if (i<i || i>ListLength(L)+1)
		return ERROR;
	p = GetElemP(L,i);
	if (!p)
		return ERROR;
	node = (DuLinkList)malloc(sizeof(struct DuLNode));
	if (!node)
		return OVERFLOW;
	node->data = e;
	node->prior = p->prior;
	p->prior->next = node;
	node->next = p;
	p->prior = node;
	return OK;
}

//ɾ����i��Ԫ��
Status ListDelete(DuLinkList L, int i, ElemType *e)
{
	DuLinkList p;
	if (i<1 || i>ListLength(L))
		return ERROR;
	p = GetElemP(L,i);
	if (!p)
		return ERROR;
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

//˳�����
void ListTraverse(DuLinkList L, void(*visit)(ElemType))
{
	DuLinkList p = L->next;
	while (p != L)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}

//�������
void ListTraverseBack(DuLinkList L, void(*visit)(ElemType))
{
	DuLinkList p = L->prior;
	while(p != L)
	{
		visit(p->data);
		p = p->prior;
	}
	printf("\n");
}


//main
Status compare(ElemType c1,ElemType c2) /* ����Ԫ���ж�����(�ж����) */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void vd(ElemType c) /* ListTraverse()���õĺ���(����һ��) */
 {
   printf("%d ",c);
 }

 void main()
 {
   DuLinkList L;
   int i,n;
   Status j;
   ElemType e;
   InitList(&L);
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* �ڵ�i�����֮ǰ����i */
   printf("�����������");
   ListTraverse(L,vd); /* ������� */
   printf("�����������");
   ListTraverseBack(L,vd); /* ������� */
   n=2;
   ListDelete(L,n,&e); /* ɾ�����ͷŵ�n����� */
   printf("ɾ����%d����㣬ֵΪ%d��������Ϊ��",n,e);
   ListTraverse(L,vd); /* ������� */
   printf("�����Ԫ�ظ���Ϊ%d\n",ListLength(L));
   printf("�����Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
   ClearList(L); /* ������� */
   printf("��պ������Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* ���²���5����� */
   ListTraverse(L,vd); /* ������� */
   n=3;
   j=GetElem(L,n,&e); /* ������ĵ�n��Ԫ�ظ�ֵ��e */
   if(j)
     printf("����ĵ�%d��Ԫ��ֵΪ%d\n",n,e);
   else
     printf("�����ڵ�%d��Ԫ��\n",n);
   n=4;
   i=LocateElem(L,n,compare);
   if(i)
     printf("����%d��Ԫ���ǵ�%d��\n",n,i);
   else
     printf("û�е���%d��Ԫ��\n",n);
   n = 1;
   j=PriorElem(L,n,&e);
   if(TRUE == j)
     printf("%d��ǰ����%d\n",n,e);
   else
     printf("������%d��ǰ��\n",n);
   n = 5;
   j=NextElem(L,n,&e);
   if(TRUE == j)
     printf("%d�ĺ����%d\n",n,e);
   else
     printf("������%d�ĺ��\n",n);
   DestroyList(&L);
 }

/*
* link list,�����������
*/

#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

//Functions

//����һ���յ���������L
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode));	//����ͷ��㣬��ʹLָ���ͷ���
	if (!*L)
	{
		exit(OVERFLOW);
	}
	
	(*L)->next = NULL;

	return OK;
}

//������������
Status DestroyList(LinkList *L)
{
	LinkList q;
	while (*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}

	return OK;
}

//��������������Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
Status ClearList(LinkList L)
{
	LinkList p,q;
	p = L->next;	//ָ���һ�����
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;	//ͷ���ָ����Ϊ��
	
	return OK;
}

//��LΪ�գ�����TRUE�����򷵻�FALSE
Status ListEmpty(LinkList L)
{
	if (L->next)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//����L��Ԫ�صĸ���
int ListLength(LinkList L)
{
	int i = 0;
	while (L->next)
	{
		i++;
		L->next = L->next->next;
	}

	return i;
}

//����i��Ԫ�ش��ڣ���ֵ��e��������OK�����򷵻�ERROR
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j = 1;
	while (L->next && j<i)
	{
		L->next = L->next->next;
		j++;
	}

	if (!L->next || j>i)
	{	//��i��Ԫ�ز�����
		return ERROR;
	}

	*e = L->next->data;	//ȡ��i��Ԫ��
	
	return OK;
}

//����L�е�1����e����compare()��ϵ������Ԫ�ص�λ�ã��������ڣ��򷵻�0
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	int i = 0;

	while (L->next)
	{
		i++;
		if (compare(L->next->data,e))
		{
			return i;
		}
		L->next = L->next->next;
	}

	return 0;
}

//��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��,����OK;�������ʧ��,pre_e�޶���,����INFEASIBLE 
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList p,q;
	p = L->next;
	while (p->next)
	{
		q = p->next;	//qΪp�ĺ��
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;		//p�����
	}

	return INFEASIBLE;
}

//��cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ��, ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p;
	p = L->next;
	while (p->next)
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return OK;
		}
		p = p->next;
	}

	return INFEASIBLE;
}

//��ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
Status ListInsert(LinkList L, int i, ElemType e)
{
	LinkList p = L;
	LinkList node;
	int j = 0;
	while (p && j < i-1)	//Ѱ�ҵ�i-1�����
	{
		p = p->next;
		j++;
	}
	if (!p || j > i-1)		//iС��1����ڱ�
	{
		return ERROR;
	}

	node = (LinkList)malloc(sizeof(struct LNode));	//�����½��
	node->data = e;		//������Ԫ��
	node->next = p->next;
	p->next = node;

	return OK;

}

//�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��,����e������ֵ
Status ListDelete(LinkList L, int i, ElemType *e)
{
	LinkList p = L,q;
	int j = 0;
	while (p && j<i-1)	//�ҵ���i����㣬��ʹpָ����ǰ��
	{
		p = p->next;
		j++;
	}
	if (!p->next || j>i-1)	//ɾ��λ�ò�����
	{
		return ERROR;
	}
	q = p->next;	//ɾ�����ͷŽ��
	*e = q->data;
	p->next = q->next;
	free(q);

	return OK;
}

//���ζ�L��ÿ������Ԫ�ص��ú���visit()��һ��visit()ʧ��,�����ʧ��
Status ListTraverse(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");

	return OK;
}




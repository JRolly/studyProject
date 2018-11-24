/*
* link list,线性链表操作
*/

#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

//Functions

//构造一个空的线性链表L
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode));	//产生头结点，并使L指向此头结点
	if (!*L)
	{
		exit(OVERFLOW);
	}
	
	(*L)->next = NULL;

	return OK;
}

//销毁线性链表
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

//将线性链表重置为空表，并释放原链表的结点空间
Status ClearList(LinkList L)
{
	LinkList p,q;
	p = L->next;	//指向第一个结点
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;	//头结点指针域为空
	
	return OK;
}

//若L为空，返回TRUE，否则返回FALSE
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

//返回L中元素的个数
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

//若第i个元素存在，赋值给e，并返回OK，否则返回ERROR
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j = 1;
	while (L->next && j<i)
	{
		L->next = L->next->next;
		j++;
	}

	if (!L->next || j>i)
	{	//第i个元素不存在
		return ERROR;
	}

	*e = L->next->data;	//取第i个元素
	
	return OK;
}

//返回L中第1个与e满足compare()关系的数据元素的位置，若不存在，则返回0
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

//若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱,返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE 
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList p,q;
	p = L->next;
	while (p->next)
	{
		q = p->next;	//q为p的后继
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;		//p向后移
	}

	return INFEASIBLE;
}

//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继, 返回OK;否则操作失败，next_e无定义，返回INFEASIBLE
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

//带头结点的单链线性表L中第i个位置之前插入元素e
Status ListInsert(LinkList L, int i, ElemType e)
{
	LinkList p = L;
	LinkList node;
	int j = 0;
	while (p && j < i-1)	//寻找第i-1个结点
	{
		p = p->next;
		j++;
	}
	if (!p || j > i-1)		//i小于1或大于表长
	{
		return ERROR;
	}

	node = (LinkList)malloc(sizeof(struct LNode));	//生成新结点
	node->data = e;		//插入新元素
	node->next = p->next;
	p->next = node;

	return OK;

}

//在带头结点的单链线性表L中，删除第i个元素,并由e返回其值
Status ListDelete(LinkList L, int i, ElemType *e)
{
	LinkList p = L,q;
	int j = 0;
	while (p && j<i-1)	//找到第i个结点，并使p指向其前驱
	{
		p = p->next;
		j++;
	}
	if (!p->next || j>i-1)	//删除位置不合理
	{
		return ERROR;
	}
	q = p->next;	//删除并释放结点
	*e = q->data;
	p->next = q->next;
	free(q);

	return OK;
}

//依次对L的每个数据元素调用函数visit()。一旦visit()失败,则操作失败
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




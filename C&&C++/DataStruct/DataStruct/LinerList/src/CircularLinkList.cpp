/*
*	单循环链表,带有尾指针
*/
#include <stdio.h>
#include <stdlib.h>
#include "CircularLinkList.h"

Status InitList_CL(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode)); //产生头结点，并使L指向头结点
	if (!*L)
		exit(OVERFLOW);
	(*L)->next = *L;

	return OK;
}

//销毁
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

//重置为空表
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

//是否为空表
Status ListEmpty_CL(LinkList L)
{
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

//表长
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

//获取第i个元素，存入*e中
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

//返回与e满足compare关系的元素的位序
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

//返回cur_e的前驱
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

//返回cur_e的后继
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

//在第i个位置插入元素e
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
	if (p == *L)	//改变尾结点
		*L = node;
	return OK;
}

//删除第i个位置上的元素,并返回到e
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
	q = p->next;	//待删除结点
	p->next = q->next;
	*e = q->data;
	if (*L == q)
		*L = p;
	free(q);
	return OK;

}

//遍历
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
   i=InitList_CL(&L); /* 初始化单循环链表L */
   printf("初始化单循环链表L i=%d (1:初始化成功)\n",i);
   i=ListEmpty_CL(L);
   printf("L是否空 i=%d(1:空 0:否)\n",i);
   ListInsert_CL(&L,1,3); /* 在L中依次插入3,5 */
   ListInsert_CL(&L,2,5);
   i=GetElem_CL(L,1,&e);
   j=ListLength_CL(L);
   printf("L中数据元素个数=%d,第1个元素的值为%d。\n",j,e);
   printf("L中的数据元素依次为：");
   ListTraverse_CL(L,visit);
   PriorElem_CL(L,5,&e); /* 求元素5的前驱 */
   printf("5前面的元素的值为%d。\n",e);
   NextElem_CL(L,3,&e); /* 求元素3的后继 */
   printf("3后面的元素的值为%d。\n",e);
   printf("L是否空 %d(1:空 0:否)\n",ListEmpty_CL(L));
   j=LocateElem_CL(L,3,compare);
   if(j)
     printf("L的第%d个元素为3。\n",j);
   else
     printf("不存在值为3的元素\n");
   i=ListDelete_CL(&L,2,&e);
   printf("删除L的第2个元素：\n");
   if(i)
   {
     printf("删除的元素值为%d,现在L中的数据元素依次为：",e);
     ListTraverse_CL(L,visit);
   }
   else
   printf("删除不成功！\n");
   i = ClearList_CL(&L);
   printf("清空L：%d(1: 成功)\n",i);
   i = ListEmpty_CL(L);
   printf("清空L后，L是否空：%d(1:空 0:否)\n",i);
   i = DestroyList_CL(&L);
   printf("销毁L：%d(1: 成功)\n",i);
 }

/*
*	双向循环链表
*/
#include <stdio.h>
#include <stdlib.h>
#include "Define.h"
#include "DoubleLinkList.h"


//产生空的双向循环链表
Status InitList(DuLinkList *L)
{
	*L = (DuLinkList)malloc(sizeof(struct DuLNode));
	if (!*L)
		return OVERFLOW;
	(*L)->next = (*L)->prior = *L;
	return OK;
}

//销毁双向循环链表
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

//重置双向循环链表为空表
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

//检查是否为空表
Status ListEmpty(DuLinkList L)
{
	if (L->next==L && L->prior==L)
		return TRUE;
	else
		return FALSE;
}

//获取表长度
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

//获取第i个位置上的元素
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

//返回满足compare关系的元素的位序
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

//返回cur_e的前驱
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

//返回cur_e的后继
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

//返回第i个元素的位置指针
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

//在第i个位置之前插入元素
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

//删除第i个元素
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

//顺序遍历
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

//逆序遍历
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
Status compare(ElemType c1,ElemType c2) /* 数据元素判定函数(判定相等) */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void vd(ElemType c) /* ListTraverse()调用的函数(类型一致) */
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
     ListInsert(L,i,i); /* 在第i个结点之前插入i */
   printf("正序输出链表：");
   ListTraverse(L,vd); /* 正序输出 */
   printf("逆序输出链表：");
   ListTraverseBack(L,vd); /* 逆序输出 */
   n=2;
   ListDelete(L,n,&e); /* 删除并释放第n个结点 */
   printf("删除第%d个结点，值为%d，其余结点为：",n,e);
   ListTraverse(L,vd); /* 正序输出 */
   printf("链表的元素个数为%d\n",ListLength(L));
   printf("链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
   ClearList(L); /* 清空链表 */
   printf("清空后，链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* 重新插入5个结点 */
   ListTraverse(L,vd); /* 正序输出 */
   n=3;
   j=GetElem(L,n,&e); /* 将链表的第n个元素赋值给e */
   if(j)
     printf("链表的第%d个元素值为%d\n",n,e);
   else
     printf("不存在第%d个元素\n",n);
   n=4;
   i=LocateElem(L,n,compare);
   if(i)
     printf("等于%d的元素是第%d个\n",n,i);
   else
     printf("没有等于%d的元素\n",n);
   n = 1;
   j=PriorElem(L,n,&e);
   if(TRUE == j)
     printf("%d的前驱是%d\n",n,e);
   else
     printf("不存在%d的前驱\n",n);
   n = 5;
   j=NextElem(L,n,&e);
   if(TRUE == j)
     printf("%d的后继是%d\n",n,e);
   else
     printf("不存在%d的后继\n",n);
   DestroyList(&L);
 }

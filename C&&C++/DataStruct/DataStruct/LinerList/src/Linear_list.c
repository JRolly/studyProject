#include <stdio.h>
#include <stdlib.h>
#include "Linear_list.h"

//Functions

//构造一个空的线性表
Status InitList(Sqlist *L)
{
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
	{
		exit(OVERFLOW);		//存储空间分配失败
	}
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;

	return OK;
}

//销毁线性表
Status DestoryList(Sqlist *L)
{
	free((*L).elem);
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;

	return OK;
}

 void visit(ElemType *c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",*c);
 }

//将线性表重置为空表
Status ClearList(Sqlist *L)
{
	(*L).length = 0;

	return OK;
}

//判断线性表是否为空，是，返回TRUE，否，返回FALSE
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

//返回线性表中元素的个数
int ListLength(Sqlist L)
{
	return L.length;
}

//用e返回线性表中第i个元素的值
Status GetElem(Sqlist L, int i, ElemType *e)
{
	if (i < 1 || i > L.length)
	{
		exit(ERROR);
	}
	*e = *(L.elem + i-1); 

	return OK;
}

//返回L中第一个与e满足关系compar()的数据元素的位序，若不存在这样的数据元素，返回0
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

//若cur_e 是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
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

//若cur_e 是L的数据元素，且不是最后一个，则next_e返回它的后继，否则操作失败，next_e无定义
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

//在L中第i个位置之前插入新的数据元素额e，L的长度加1
Status ListInsert(Sqlist *L, int i, ElemType e)
{
	ElemType *newBase, *q, *p;

	if (i < 1 || i > (*L).length+1)
	{
		return ERROR;
	}

	if ((*L).length >= (*L).listsize)
	{	//当前存储空间已满，增加分配空间
		newBase = (ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
		if (!newBase)
		{
			exit(OVERFLOW);		//存储空间分配失败
		}
		(*L).elem = newBase;	//新基址
		(*L).listsize += LISTINCREMENT;	//增加存储容量
	}

	q = (*L).elem + i-1;	//q为插入位置
	for (p = (*L).elem+(*L).length-1; p >= q; --p)
	{	//插入位置及之后的元素右移
		*(p+1) = *p;
	}

	*q = e; //插入e
	++(*L).length;	//表长加1

	return OK;
}

//删除L的第i个数据元素，并用e返回其值，L的长度减1
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
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
   /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
   ElemType *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     visit(p++);
   printf("\n");
   return OK;
 }

//已知顺序线性表La 和 Lb 的元素按非递减排列，
//归并La和Lb到新的顺序线性表Lc,Lc的元素也按非递减排列
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
//	printf("初始化L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
//	for (i = 1; i <=5; i++)
//	{
//		stat = ListInsert(&L,1,i);
//	}
//	printf("\n");
//
//	printf("插入元素后L：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
//
//	stat = ListEmpty(L);
//	printf("L是否空：i=%d(1:是 0:否)\n",i);
//
//	stat = ClearList(&L);
//	printf("清空L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
//
//	stat = ListEmpty(L);
//	printf("L是否空：i=%d(1:是 0:否)\n",i);
//
//	for (i = 1; i <= 10; i++)
//	{
//		ListInsert(&L,i,i);
//	}
//	printf("在L的表尾依次插入1～10后：*L.elem=");
//	for (i = 1; i <= 10; i++)
//	{
//		printf("%d ",*(L.elem+i-1));
//	}
//	printf("\n");
//
//	GetElem(L,5,&e);
//    printf("第5个元素的值为：%d\n",e);
//
//	PriorElem(L, 5,&e);
//	printf("5的前驱是：%d\n",e);
//
//	NextElem(L,5,&e);
//	printf("5的后继是：%d\n",e);
//
//	ListDelete(&L,5,&e);
//	printf("删掉第5个元素:%d,删除后的表是：\n",e);
//	for (i = 1; i <= L.length; i++)
//	{
//		printf("%d ",*(L.elem+i-1));
//	}
//	printf("\n");
//
//	DestoryList(&L);
//}


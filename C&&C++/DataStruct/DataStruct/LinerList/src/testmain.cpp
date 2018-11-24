/*
*	test link list
*/
#include <stdio.h>
#include "LinkList.h"

Status comp(ElemType c1,ElemType c2)
 { /* 数据元素判定函数(相等为TRUE,否则为FALSE) */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c) /* 与main2-1.c不同 */
 {
   printf("%d ",c);
 }

void main(void)
{
	LinkList L; 
	Status i;
    int j,k;
	ElemType e;

    i=InitList(&L);

	for(j=1;j<=10;j++)
     ListInsert(L,j,j);
	ListTraverse(L,visit);

	i = ListDelete(L, 1, &e);
	if (OK != i)
		printf("删除失败\n");
	printf("删除了第1个元素%d\n",e);
	ListTraverse(L,visit);

	i = PriorElem(L,3,&e);
	if (OK != i)
		printf("元素3没有前驱\n");
	printf("元素3的前驱是%d\n",e);

	i = NextElem(L,3,&e);
	if (OK != i)
		printf("元素3没有后继\n");
	printf("元素3的后继是%d\n",e);

	ListTraverse(L,visit);
	i = ListLength(L);
	printf("表长：%d\n",i);

	i = DestroyList(&L);
	if (OK != i)
		printf("销毁链表失败\n");
}
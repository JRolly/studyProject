/*
*	test link list
*/
#include <stdio.h>
#include "LinkList.h"

Status comp(ElemType c1,ElemType c2)
 { /* ����Ԫ���ж�����(���ΪTRUE,����ΪFALSE) */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c) /* ��main2-1.c��ͬ */
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
		printf("ɾ��ʧ��\n");
	printf("ɾ���˵�1��Ԫ��%d\n",e);
	ListTraverse(L,visit);

	i = PriorElem(L,3,&e);
	if (OK != i)
		printf("Ԫ��3û��ǰ��\n");
	printf("Ԫ��3��ǰ����%d\n",e);

	i = NextElem(L,3,&e);
	if (OK != i)
		printf("Ԫ��3û�к��\n");
	printf("Ԫ��3�ĺ����%d\n",e);

	ListTraverse(L,visit);
	i = ListLength(L);
	printf("����%d\n",i);

	i = DestroyList(&L);
	if (OK != i)
		printf("��������ʧ��\n");
}
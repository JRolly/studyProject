/*
*  link_list,Ë«ÏòÑ­»·Á´±í
*/
#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__

//Struct
typedef struct DuLNode
{
    ElemType   data;
    struct DuLNode  *next, *prior;
} DuLNode, *DuLinkList;

//Function
//Status InitList(LinkList *L);
//Status DestroyList(LinkList *L);
//Status ClearList(LinkList L);
//Status ListEmpty(LinkList L);
//int ListLength(LinkList L);
//Status GetElem(LinkList L, int i, ElemType *e);
//int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType));
//Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
//Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
//Status ListInsert(LinkList L, int i, ElemType e);
//Status ListDelete(LinkList L, int i, ElemType *e);
//Status ListTraverse(LinkList L, void(*visit)(ElemType));


#endif //end #ifndef __DOUBLELINEAR_LIST_H__

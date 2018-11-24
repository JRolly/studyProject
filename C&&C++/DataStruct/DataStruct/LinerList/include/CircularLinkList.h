/*
*  link_list,循环链表
*/
#ifndef __CIRCULARLINKLIST_H__
#define __CIRCULARLINKLIST_H__


//Status code
#define TRUE			1
#define FALSE			-1
#define OK				1
#define ERROR			0
#define INFEASIBLE		-1
#define OVERFLOW		-2

typedef int Status;		//函数的类型，值为函数结构状态代码
typedef int ElemType;	//用来表示数据类型

//Struct
struct LNode
{
	ElemType	data;
	struct LNode *next;
};

typedef struct LNode *LinkList;

//Function
Status InitList(LinkList *L);
Status DestroyList(LinkList *L);
Status ClearList(LinkList L);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
Status GetElem(LinkList L, int i, ElemType *e);
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType));
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
Status ListInsert(LinkList L, int i, ElemType e);
Status ListDelete(LinkList L, int i, ElemType *e);
Status ListTraverse(LinkList L, void(*visit)(ElemType));


#endif //end #ifndef __LINEAR_LIST_H__

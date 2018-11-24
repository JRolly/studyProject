/*
*	具有实用意义的线性链表
*/

#include "Define.h"
#include "TLinkList.h"

//分配由p指向e的结点
Status MakeNode(Link *p, ElemType e)
{
	*p = (Link)malloc(sizeof(LNode));
	if (!*p)
		return ERROR;
	(*p)->data = e;
	return OK;
}

//释放结点
void FreeNode(Link *p)
{
	free(*p);
	*p = NULL;
}

//构造一个空的线性链表
Status InitList(LinkList *L)
{
	Link p;
	p = (Link)malloc(sizeof(LNode));
	if (p)
	{
		p->next = NULL;
		(*L).head = (*L).tail = p;
		(*L).len = 0;
		return OK;
	}
	else
		return ERROR;
}

//将线性链表置空
Status ClearList(LinkList *L)
{
	Link q,p;
	if ((*L).head != (*L).tail)
	{	//链表非空
		p = q = (*L).head->next;
		(*L).head->next = NULL;
		while (p != (*L).tail)
		{
			p = q->next;
			free(q);
			q = p;
		}
		free(q);
		(*L).tail = (*L).head;
		(*L).len = 0;
	}
	return OK;
}

//销毁
Status DestroyList(LinkList *L)
{
	ClearList(L);
	FreeNode(&(*L).head);
	(*L).tail =	NULL;
	(*L).len = 0;
	return OK;
}

//在第一个结点之前插入元素，h为头结点
Status InsFirst(LinkList *L, Link h, Link node)
{
	node->next = h->next;
	h->next = node;
	if (h == (*L).tail)	//h指向尾结点
	{
		(*L).tail = h->next;	//修改尾指针
	}
	(*L).len++;
	return OK;
}

//删除第一个结点，h为头结点，并以node返回
Status DelFirst(LinkList *L, Link h, Link *node)
{
	*node = h->next;
	if (*node)
	{
		h->next = (*node)->next;
		if (!h->next)	//删除尾结点
			(*L).tail = h;	//修改尾指针
		(*L).len--;
		return OK;
	}
	else
		return FALSE;	//空表
}

//将node所指向的一串结点连接在L的最后一个结点
Status Append(LinkList *L, Link node)
{
	int i = 1;
	(*L).tail->next = node;
	while (node->next)
	{
		i++;
		node = node->next;
	}
	(*L).tail = node;
	(*L).len += i;
	return OK;
}

//node指向一个结点，返回node的直接前驱的位置
Position PriorPos(LinkList L, Link node)
{
	Link p = L.head->next;
	if (node == p)
		return ERROR;
	else
	{
		while (p->next != node)
			p = p->next;
		return p;
	}
}

//删除尾结点,并以node返回
Status Remove(LinkList *L, Link *node)
{
	Link p = (*L).head;
	if (0 == (*L).len)	//空表
	{
		*node = NULL;
		return FALSE;
	}
	while (p->next != (*L).tail)
		p = p->next;
	*node = (*L).tail;
	(*L).tail = p;
	(*L).len--;
	return OK;
}

//p指向表中的一个结点，在p之前插入node结点，修改p指向新插入的结点
Status InsBefore(LinkList *L, Link *p, Link node)
{
	Link q = PriorPos(*L,*p);	//q是p的前驱
	if (!q)
		q = (*L).head;
	node->next = *p;
	q->next = node;
	*p = node;
	(*L).len++;
	return OK;
}

//p指向表中的一个结点，在p之后插入node结点，修改p指向新插入的结点
Status InsAfter(LinkList *L, Link *p, Link node)
{
	if (*p == (*L).tail)
		(*L).tail = node;
	node->next = (*p)->next;
	(*p)->next = node;
	*p = node;
	(*L).len++;
	return OK;
}

//p指向表中一个结点，用e更新p所指结点中数据元素的值
Status SetCurElem(Link p, ElemType e)
{
	p->data = e;
	return OK;
}

//p指向表中一个结点，返回p所指结点中数据元素的值
ElemType GetCurElem(Link p)
{
	return p->data;
}

//返回表长度
int ListLength(LinkList L)
{
	return L.len;
}

Status ListEmpty(LinkList L)
{
	if (0 == L.len)
		return TRUE;
	else
		return FALSE;
}
//返回表头结点位置
Position GetHead(LinkList L)
{
	return L.head;
}

//返回表尾结点的位置
Position GetTail(LinkList L)
{
	return L.tail;
}

//p指向表中一个结点，返回p的后继的位置
Position NextPos(Link p)
{
	return p->next;
}

//用p返回表中第i个元素的位置
Status LocatePos(LinkList L, int i, Link *p)
{
	if (i<0 || i>L.len)
		return ERROR;
	*p = L.head;
	for (int j=1; j<=i; j++)
	{
		*p = (*p)->next;
	}
	return OK;
}

//返回表中第一个与e满足compare关系的元素的位置
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	Link p = L.head->next;
	while (p && !compare(p->data,e))
		p = p->next;
	return p;
}

//遍历
Status ListTraverse(LinkList L,void(*visit)(ElemType))
{
	Link p = L.head->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//L为有序线性链表，将元素e按非降序插入到L中
Status OrderInsert(LinkList *L, ElemType e, int (*comp)(ElemType,ElemType))
{
	Link p, q, node;
	q = (*L).head;
	p = q->next;
	while (p && comp(p->data,e)<0)
	{
		q = p;
		p = p->next;
	}
	MakeNode(&node,e);
	//node = (Link)malloc(sizeof(LNode));
	//node->data = e;
	q->next = node;
	node->next = p;
	(*L).len++;
	if (!p)
		(*L).tail = node;
	return OK;
}

//用q返回L中第一个与e满足compare()取值为0的元素的位置，并返回TRUE
//若不存在，则返回第一个与e满足compare()取值>0的元素的直接前驱的位置，并返回FALSE
Status LocateElemP(LinkList L, ElemType e, Position *pos, int (*compare)(ElemType,ElemType))
{
	Link p,q;
	q = L.head;
	p = q->next;
	while (p && compare(p->data,e)<0)
	{
		q = p;
		p = p->next;
	}
	if (!p || compare(p->data,e)>0)
	{
		*pos = q;
		return FALSE;
	}
	else
	{
		*pos = p;
		return TRUE;
	}
}



//main
 Status compare(ElemType c1,ElemType c2) /* c1等于c2 */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 int cmp(ElemType a,ElemType b)
 { /* 根据a<、=或>b,分别返回-1、0或1 */
   if(a==b)
     return 0;
   else
     return (a-b)/abs(a-b);
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   Link p,h;
   LinkList L;
   Status i;
   int j,k;
   i=InitList(&L);
   if(!i) /* 初始化空的线性表L不成功 */
     exit(FALSE); /* 退出程序运行 */
   for(j=1;j<=2;j++)
   {
     MakeNode(&p,j); /* 生成由p指向、值为j的结点 */
     InsFirst(&L,L.tail,p); /* 插在表尾 */
   }
   OrderInsert(&L,0,cmp); /* 按升序插在有序表头 */
   for(j=0;j<=3;j++)
   {
     i=LocateElemP(L,j,&p,cmp);
     if(i)
       printf("链表中有值为%d的元素。\n",p->data);
     else
       printf("链表中没有值为%d的元素。\n",j);
   }
   printf("输出链表：");
   ListTraverse(L,visit); /* 输出L */
   for(j=1;j<=4;j++)
   {
     printf("删除表头结点：");
     DelFirst(&L,L.head,&p); /* 删除L的首结点，并以p返回 */
     if(p)
       printf("%d\n",GetCurElem(p));
     else
       printf("表空，无法删除 p=%u\n",p);
   }
   printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
   MakeNode(&p,10);
   p->next=NULL; /* 尾结点 */
   for(j=4;j>=1;j--)
   {
     MakeNode(&h,j*2);
     h->next=p;
     p=h;
   } /* h指向一串5个结点，其值依次是2 4 6 8 10 */
   Append(&L,h); /* 把结点h链接在线性链表L的最后一个结点之后 */
   OrderInsert(&L,12,cmp); /* 按升序插在有序表尾头 */
   OrderInsert(&L,7,cmp); /* 按升序插在有序表中间 */
   printf("输出链表：");
   ListTraverse(L,visit); /* 输出L */
   for(j=1;j<=2;j++)
   {
     p=LocateElem(L,j*5,compare);
     if(p)
       printf("L中存在值为%d的结点。\n",j*5);
     else
       printf("L中不存在值为%d的结点。\n",j*5);
   }
   for(j=1;j<=2;j++)
   {
     LocatePos(L,j,&p); /* p指向L的第j个结点 */
     h=PriorPos(L,p); /* h指向p的前驱 */
     if(h)
       printf("%d的前驱是%d。\n",p->data,h->data);
     else
       printf("%d没前驱。\n",p->data);
   }
   k=ListLength(L);
   for(j=k-1;j<=k;j++)
   {
     LocatePos(L,j,&p); /* p指向L的第j个结点 */
     h=NextPos(p); /* h指向p的后继 */
     if(h)
       printf("%d的后继是%d。\n",p->data,h->data);
     else
       printf("%d没后继。\n",p->data);
   }
   printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
   p=GetTail(L); /* p指向最后一个结点 */
   SetCurElem(p,15); /* 将最后一个结点的值变为15 */
   printf("第1个元素为%d 最后1个元素为%d\n",GetCurElem(GetHead(L)->next),GetCurElem(p));
   MakeNode(&h,10);
   InsBefore(&L,&p,h); /* 将10插到尾结点之前，p指向新结点 */
   p=p->next; /* p恢复为尾结点 */
   MakeNode(&h,20);
   InsAfter(&L,&p,h); /* 将20插到尾结点之后 */
   k=ListLength(L);
   printf("依次删除表尾结点并输出其值：");
   for(j=0;j<=k;j++)
   {
     i=Remove(&L,&p);
     if(!i) /* 删除不成功 */
       printf("删除不成功 p=%u\n",p);
     else
       printf("%d ",p->data);
   }
   MakeNode(&p,29); /* 重建具有1个结点(29)的链表 */
   InsFirst(&L,L.head,p);
   DestroyList(&L); /* 销毁线性链表L */
   printf("销毁线性链表L之后: L.head=%u L.tail=%u L.len=%d\n",L.head,L.tail,L.len);
 }

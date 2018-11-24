/*
*	����ʵ���������������
*/

#include "Define.h"
#include "TLinkList.h"

//������pָ��e�Ľ��
Status MakeNode(Link *p, ElemType e)
{
	*p = (Link)malloc(sizeof(LNode));
	if (!*p)
		return ERROR;
	(*p)->data = e;
	return OK;
}

//�ͷŽ��
void FreeNode(Link *p)
{
	free(*p);
	*p = NULL;
}

//����һ���յ���������
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

//�����������ÿ�
Status ClearList(LinkList *L)
{
	Link q,p;
	if ((*L).head != (*L).tail)
	{	//����ǿ�
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

//����
Status DestroyList(LinkList *L)
{
	ClearList(L);
	FreeNode(&(*L).head);
	(*L).tail =	NULL;
	(*L).len = 0;
	return OK;
}

//�ڵ�һ�����֮ǰ����Ԫ�أ�hΪͷ���
Status InsFirst(LinkList *L, Link h, Link node)
{
	node->next = h->next;
	h->next = node;
	if (h == (*L).tail)	//hָ��β���
	{
		(*L).tail = h->next;	//�޸�βָ��
	}
	(*L).len++;
	return OK;
}

//ɾ����һ����㣬hΪͷ��㣬����node����
Status DelFirst(LinkList *L, Link h, Link *node)
{
	*node = h->next;
	if (*node)
	{
		h->next = (*node)->next;
		if (!h->next)	//ɾ��β���
			(*L).tail = h;	//�޸�βָ��
		(*L).len--;
		return OK;
	}
	else
		return FALSE;	//�ձ�
}

//��node��ָ���һ�����������L�����һ�����
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

//nodeָ��һ����㣬����node��ֱ��ǰ����λ��
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

//ɾ��β���,����node����
Status Remove(LinkList *L, Link *node)
{
	Link p = (*L).head;
	if (0 == (*L).len)	//�ձ�
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

//pָ����е�һ����㣬��p֮ǰ����node��㣬�޸�pָ���²���Ľ��
Status InsBefore(LinkList *L, Link *p, Link node)
{
	Link q = PriorPos(*L,*p);	//q��p��ǰ��
	if (!q)
		q = (*L).head;
	node->next = *p;
	q->next = node;
	*p = node;
	(*L).len++;
	return OK;
}

//pָ����е�һ����㣬��p֮�����node��㣬�޸�pָ���²���Ľ��
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

//pָ�����һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
Status SetCurElem(Link p, ElemType e)
{
	p->data = e;
	return OK;
}

//pָ�����һ����㣬����p��ָ���������Ԫ�ص�ֵ
ElemType GetCurElem(Link p)
{
	return p->data;
}

//���ر���
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
//���ر�ͷ���λ��
Position GetHead(LinkList L)
{
	return L.head;
}

//���ر�β����λ��
Position GetTail(LinkList L)
{
	return L.tail;
}

//pָ�����һ����㣬����p�ĺ�̵�λ��
Position NextPos(Link p)
{
	return p->next;
}

//��p���ر��е�i��Ԫ�ص�λ��
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

//���ر��е�һ����e����compare��ϵ��Ԫ�ص�λ��
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	Link p = L.head->next;
	while (p && !compare(p->data,e))
		p = p->next;
	return p;
}

//����
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

//LΪ��������������Ԫ��e���ǽ�����뵽L��
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

//��q����L�е�һ����e����compare()ȡֵΪ0��Ԫ�ص�λ�ã�������TRUE
//�������ڣ��򷵻ص�һ����e����compare()ȡֵ>0��Ԫ�ص�ֱ��ǰ����λ�ã�������FALSE
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
 Status compare(ElemType c1,ElemType c2) /* c1����c2 */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 int cmp(ElemType a,ElemType b)
 { /* ����a<��=��>b,�ֱ𷵻�-1��0��1 */
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
   if(!i) /* ��ʼ���յ����Ա�L���ɹ� */
     exit(FALSE); /* �˳��������� */
   for(j=1;j<=2;j++)
   {
     MakeNode(&p,j); /* ������pָ��ֵΪj�Ľ�� */
     InsFirst(&L,L.tail,p); /* ���ڱ�β */
   }
   OrderInsert(&L,0,cmp); /* ��������������ͷ */
   for(j=0;j<=3;j++)
   {
     i=LocateElemP(L,j,&p,cmp);
     if(i)
       printf("��������ֵΪ%d��Ԫ�ء�\n",p->data);
     else
       printf("������û��ֵΪ%d��Ԫ�ء�\n",j);
   }
   printf("�������");
   ListTraverse(L,visit); /* ���L */
   for(j=1;j<=4;j++)
   {
     printf("ɾ����ͷ��㣺");
     DelFirst(&L,L.head,&p); /* ɾ��L���׽�㣬����p���� */
     if(p)
       printf("%d\n",GetCurElem(p));
     else
       printf("��գ��޷�ɾ�� p=%u\n",p);
   }
   printf("L�н�����=%d L�Ƿ�� %d(1:�� 0:��)\n",ListLength(L),ListEmpty(L));
   MakeNode(&p,10);
   p->next=NULL; /* β��� */
   for(j=4;j>=1;j--)
   {
     MakeNode(&h,j*2);
     h->next=p;
     p=h;
   } /* hָ��һ��5����㣬��ֵ������2 4 6 8 10 */
   Append(&L,h); /* �ѽ��h��������������L�����һ�����֮�� */
   OrderInsert(&L,12,cmp); /* ��������������βͷ */
   OrderInsert(&L,7,cmp); /* ���������������м� */
   printf("�������");
   ListTraverse(L,visit); /* ���L */
   for(j=1;j<=2;j++)
   {
     p=LocateElem(L,j*5,compare);
     if(p)
       printf("L�д���ֵΪ%d�Ľ�㡣\n",j*5);
     else
       printf("L�в�����ֵΪ%d�Ľ�㡣\n",j*5);
   }
   for(j=1;j<=2;j++)
   {
     LocatePos(L,j,&p); /* pָ��L�ĵ�j����� */
     h=PriorPos(L,p); /* hָ��p��ǰ�� */
     if(h)
       printf("%d��ǰ����%d��\n",p->data,h->data);
     else
       printf("%dûǰ����\n",p->data);
   }
   k=ListLength(L);
   for(j=k-1;j<=k;j++)
   {
     LocatePos(L,j,&p); /* pָ��L�ĵ�j����� */
     h=NextPos(p); /* hָ��p�ĺ�� */
     if(h)
       printf("%d�ĺ����%d��\n",p->data,h->data);
     else
       printf("%dû��̡�\n",p->data);
   }
   printf("L�н�����=%d L�Ƿ�� %d(1:�� 0:��)\n",ListLength(L),ListEmpty(L));
   p=GetTail(L); /* pָ�����һ����� */
   SetCurElem(p,15); /* �����һ������ֵ��Ϊ15 */
   printf("��1��Ԫ��Ϊ%d ���1��Ԫ��Ϊ%d\n",GetCurElem(GetHead(L)->next),GetCurElem(p));
   MakeNode(&h,10);
   InsBefore(&L,&p,h); /* ��10�嵽β���֮ǰ��pָ���½�� */
   p=p->next; /* p�ָ�Ϊβ��� */
   MakeNode(&h,20);
   InsAfter(&L,&p,h); /* ��20�嵽β���֮�� */
   k=ListLength(L);
   printf("����ɾ����β��㲢�����ֵ��");
   for(j=0;j<=k;j++)
   {
     i=Remove(&L,&p);
     if(!i) /* ɾ�����ɹ� */
       printf("ɾ�����ɹ� p=%u\n",p);
     else
       printf("%d ",p->data);
   }
   MakeNode(&p,29); /* �ؽ�����1�����(29)������ */
   InsFirst(&L,L.head,p);
   DestroyList(&L); /* ������������L */
   printf("������������L֮��: L.head=%u L.tail=%u L.len=%d\n",L.head,L.tail,L.len);
 }

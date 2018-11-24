/*
*	��ʽ���в���
*/

#include "queue.h"

//��ʼ��
Status InitQueue(LinkQueue *Q)
{
	(*Q).front = (*Q).rear = (QueuePtr )malloc(sizeof(QNode));
	if (!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
}

//����
Status DestroyQueue(LinkQueue *Q)
{
	while ((*Q).front)
	{
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
	return OK;
}

//��ն���
Status ClearQueue(LinkQueue *Q)
{
	QueuePtr p, q;
	(*Q).rear = (*Q).front;
	p = (*Q).front->next;
	(*Q).front->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	return OK;
}

//�����Ƿ�Ϊ��
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

//���г���
int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (p != Q.rear)
	{
		i++;
		p = p->next;
	}
	return i;
}

//���ض���ͷԪ��
Status GetHead_Q(LinkQueue Q, QElemType *e)
{
	if (!QueueEmpty(Q))
	{
		*e = Q.front->next->data;
		return OK;
	}
	else
		return ERROR;
}

//��β����Ԫ��
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr node = (QueuePtr)malloc(sizeof(QNode));
	if (!node)
		exit(OVERFLOW);
	node->data = e;
	node->next = NULL;
	(*Q).rear->next = node;
	(*Q).rear = node;
	return OK;
}

//ɾ������ͷԪ��
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if ((*Q).rear == (*Q).front)
		return ERROR;
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p)
		(*Q).rear = (*Q).front;
	free(p);
	return OK;	
}

//����ͷ������β����
Status QueueTraverse(LinkQueue Q, void(*visit)(QElemType))
{
	QueuePtr p = Q.front->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}


 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   int i;
   QElemType d;
   LinkQueue q;
   i=InitQueue(&q);
   if(i)
     printf("�ɹ��ع�����һ���ն���!\n");
   printf("�Ƿ�ն��У�%d(1:�� 0:��)  ",QueueEmpty(q));
   printf("���еĳ���Ϊ%d\n",QueueLength(q));
   EnQueue(&q,-5);
   EnQueue(&q,5);
   EnQueue(&q,10);
   printf("����3��Ԫ��(-5,5,10)��,���еĳ���Ϊ%d\n",QueueLength(q));
   printf("�Ƿ�ն��У�%d(1:�� 0:��)  ",QueueEmpty(q));
   printf("���е�Ԫ������Ϊ��");
   QueueTraverse(q,visit);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("��ͷԪ���ǣ�%d\n",d);
   DeQueue(&q,&d);
   printf("ɾ���˶�ͷԪ��%d\n",d);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("�µĶ�ͷԪ���ǣ�%d\n",d);
   ClearQueue(&q);
   printf("��ն��к�,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
   DestroyQueue(&q);
   printf("���ٶ��к�,q.front=%u q.rear=%u\n",q.front, q.rear);
 }

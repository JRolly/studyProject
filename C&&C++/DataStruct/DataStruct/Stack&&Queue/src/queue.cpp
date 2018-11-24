/*
*	链式队列操作
*/

#include "queue.h"

//初始化
Status InitQueue(LinkQueue *Q)
{
	(*Q).front = (*Q).rear = (QueuePtr )malloc(sizeof(QNode));
	if (!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
}

//销毁
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

//清空队列
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

//队列是否为空
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

//队列长度
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

//返回队列头元素
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

//队尾插入元素
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

//删除队列头元素
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

//队列头到队列尾遍历
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
     printf("成功地构造了一个空队列!\n");
   printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
   printf("队列的长度为%d\n",QueueLength(q));
   EnQueue(&q,-5);
   EnQueue(&q,5);
   EnQueue(&q,10);
   printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(q));
   printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
   printf("队列的元素依次为：");
   QueueTraverse(q,visit);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("队头元素是：%d\n",d);
   DeQueue(&q,&d);
   printf("删除了队头元素%d\n",d);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("新的队头元素是：%d\n",d);
   ClearQueue(&q);
   printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
   DestroyQueue(&q);
   printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
 }

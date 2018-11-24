/*
*	单链队列，队列的链式存储
*/

#ifndef	__QUEUE_H__
#define	__QUEUE_H__

#include "Define.h"
#include "linkTree.h"

typedef BiTree QElemType;

typedef struct QNode
{
	QElemType	data;
	struct QNode	*next;
}QNode, *QueuePtr;

typedef struct 
{
	QueuePtr front, rear;
}LinkQueue;


Status InitQueue(LinkQueue *Q);
Status DestroyQueue(LinkQueue *Q);
Status ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead_Q(LinkQueue Q, QElemType *e);
Status EnQueue(LinkQueue *Q, QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
Status QueueTraverse(LinkQueue Q, void(*visit)(QElemType));

#endif	//end #ifndef __QUEUE_H__
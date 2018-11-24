/*
*	�������У����е���ʽ�洢
*/

#ifndef	__QUEUE_H__
#define	__QUEUE_H__

#include "Define.h"
 
typedef struct QNode
{
	QElemType	data;
	struct QNode	*next;
}QNode, *QueuePtr;

typedef struct 
{
	QueuePtr front, rear;
}LinkQueue;


#endif	//end #ifndef __QUEUE_H__
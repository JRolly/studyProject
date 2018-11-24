/*
*	带头结点的线性链表类型,具有实际使用意义的
*/

typedef struct LNode	//结点类型
{
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct LinkList	//链表类型
{
	Link head, tail;	//分别为线性链表的头结点和最后一个结点
	int len;	//线性链表的数据元素个数
}LinkList;
/*
*	二叉树的 二叉链表存储
*/

#ifndef __LINKTREE_H__
#define __LINKTREE_H__

#define CHAR	/* 字符型*/
//#define INT		/* 整型*/	//字符整型二选一
#ifdef CHAR
	typedef char	TElemType;
#endif
#ifdef INT
	typedef int		TElemType;
#endif

typedef struct BiTNode
{
	TElemType	data;
	struct BiTNode	*lchild, *rchild;	//左右孩子指针
}BitNode, *BiTree;

#endif //__LINKTREE_H__
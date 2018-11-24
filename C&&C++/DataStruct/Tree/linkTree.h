/*
*	二叉树的 二叉链表存储
*/

#ifndef __LINKTREE_H__
#define __LINKTREE_H__

#define CHAR	/* 字符型*/
//#define INT		/* 整型*/	//字符整型二选一
#ifdef CHAR
	typedef char	TElemType;
	TElemType Nil = ' ';	//字符型以空格为空
#endif
#ifdef INT
	typedef int		TElemType;
	TElemType Nil = 0;
#endif

typedef struct BiTNode
{
	TElemType	data;
	struct BiTNode	*lchild, *rchild;	//左右孩子指针
}BitNode, *BiTree;

#endif //__LINKTREE_H__
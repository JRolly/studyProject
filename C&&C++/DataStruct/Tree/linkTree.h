/*
*	�������� ��������洢
*/

#ifndef __LINKTREE_H__
#define __LINKTREE_H__

#define CHAR	/* �ַ���*/
//#define INT		/* ����*/	//�ַ����Ͷ�ѡһ
#ifdef CHAR
	typedef char	TElemType;
	TElemType Nil = ' ';	//�ַ����Կո�Ϊ��
#endif
#ifdef INT
	typedef int		TElemType;
	TElemType Nil = 0;
#endif

typedef struct BiTNode
{
	TElemType	data;
	struct BiTNode	*lchild, *rchild;	//���Һ���ָ��
}BitNode, *BiTree;

#endif //__LINKTREE_H__
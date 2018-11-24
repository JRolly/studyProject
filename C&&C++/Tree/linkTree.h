/*
*	�������� ��������洢
*/

#ifndef __LINKTREE_H__
#define __LINKTREE_H__

#define CHAR	/* �ַ���*/
//#define INT		/* ����*/	//�ַ����Ͷ�ѡһ
#ifdef CHAR
	typedef char	TElemType;
#endif
#ifdef INT
	typedef int		TElemType;
#endif

typedef struct BiTNode
{
	TElemType	data;
	struct BiTNode	*lchild, *rchild;	//���Һ���ָ��
}BitNode, *BiTree;

#endif //__LINKTREE_H__
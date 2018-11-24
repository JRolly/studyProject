/*
*	�������Ķ�������洢
*/

#include "Define.h"
#include "linkTree.h"

//����ն�����
Status InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}

//���ٶ�����
void DestroyBiTree(BiTree *T)
{
	if (*T)	//�ǿ���
	{
		if ((*T)->lchild)	//�����ӣ�������������
			DestroyBiTree(&(*T)->lchild);
		if ((*T)->rchild)	//���Һ��ӣ������Һ�������
			DestroyBiTree(&(*T)->rchild);
		free(*T);	//�ͷŸ��ڵ�
		*T = NULL;
	}
}

//�������������������н���ֵ
void CreateBiTree(BiTree *T)
{
	TElemType ch;
#ifdef	CHAR
	scanf("%c",&ch);
#endif
#ifdef	INT
	scanf("%d",&ch);
#endif
	if (Nil == ch)
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BitNode));
		if (!*T)
			exit(OVERFLOW);
		(*T)->data = ch;	//���ɸ��ڵ�
		CreateBiTree(&(*T)->lchild);	//����������
		CreateBiTree(&(*T)->rchild);	//����������
	}
}

//�Ƿ�Ϊ����
Status BiTreeEmpty(BiTree T)
{
	if (T)
		return FALSE;
	else
		return TRUE;
}

#define ClearBiTree DestroyBiTree

//�������
int BiTreeDepth(BiTree T)
{
	int i,j;
	if (!T)
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild);
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);
	else
		j = 0;
	return i>j?i+1:j+1;
}

//�������ĸ�
TElemType Root(BiTree T)
{
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

//����pָ��Ľ���ֵ
TElemType Value(BiTree p)
{
	return p->data;
}

//��p��ָ��㸳ֵΪValue
void Assign(BiTree p, TElemType value)
{
	p->data = value;
}

//typedef BiTree QElemType;	//�����Ԫ��Ϊ��������ָ������

#include "queue.h"
//#include "queue.cpp"

//��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ�
TElemType Parent(BiTree T, TElemType e)
{
	LinkQueue	q;
	QElemType	a;
	if (T)
	{
		InitQueue(&q);
		EnQueue(&q,T);	//����������
		while (!QueueEmpty(q))	//���ǿ�
		{
			DeQueue(&q,&a);	//���ӣ���ֵ��a����a������Һ���������Һ��ӵ�ֵ����e���򷵻�a��e��˫��
			if (a->lchild&&a->lchild->data==e || a->rchild&&a->rchild->data==e)
				return a->data;
			else	//a���ǣ�����������Һ���ָ�루����ǿգ�
			{
				if (a->lchild)
					EnQueue(&q,a->lchild);
				if (a->rchild)
					EnQueue(&q,a->rchild);
			}
		}
	}
	return Nil;	//���ջ�û���ҵ�e
}

//����ָ��Ԫ��ֵΪs�Ľ���ָ��
BiTree Point(BiTree T, TElemType s)
{
	LinkQueue q;
	QElemType a;
	if (T)
	{
		InitQueue(&q);
		EnQueue(&q,T);
		while (!QueueEmpty(q))
		{
			DeQueue(&q,&a);
			if (a->data == s)
				return a;
			if (a->lchild)
				EnQueue(&q,a->lchild);
			if (a->rchild)
				EnQueue(&q,a->rchild);
		}
	}
	return NULL;
}

//����e�����ӡ���e������,�򷵻أ��գ�
TElemType LeftChild(BiTree T, TElemType e)
{
	BiTree a;
	if (T)
	{
		a = Point(T,e);
		if (a && a->lchild)
			return a->lchild->data;
	}
	return Nil;
}

//����e���Һ��ӡ���e���Һ���,�򷵻أ��գ�
TElemType RightChild(BiTree T, TElemType e)
{
	BiTree a;
	if (T)
	{
		a = Point(T,e);
		if (a && a->rchild)
			return a->rchild->data;
	}
	return Nil;
}

//����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ�
TElemType LeftSibling(BiTree T, TElemType e)
{
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T,e);	
		p = Point(T,a);
		if (p->lchild&&p->rchild && p->rchild->data==e)
			return p->lchild->data;
	}
	return Nil;
}

//����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ�
TElemType RightSibling(BiTree T, TElemType e)
{
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T,e);
		p = Point(T,a);
		if (p->lchild&&p->rchild && p->lchild->data==e)
			return p->rchild->data;
	}
	return Nil;
}

//�ǿն�����c��T���ཻ��������Ϊ��,����LRΪ0��1,����cΪT��p��ָ���������������
//p��ָ����ԭ��������������Ϊc��������
Status InsertChild(BiTree p, int LR, BiTree c)
{
	if (p)
	{
		if (LR == 0)
		{
			c->rchild = p->lchild;
			p->lchild = c;
		}
		else	//LR==1
		{
			c->rchild = p->rchild;
			p->rchild = c;
		}
		return OK;
	}
	return ERROR;
}

//����LRΪ0��1,ɾ��T��p��ָ�������������
Status DeleteChild(BiTree p, int LR)
{
	if (p)
	{
		if (0 == LR)
			ClearBiTree(&p->lchild);
		else
			ClearBiTree(&p->rchild);
		return OK;
	}
	return ERROR;
}

//����ݹ����
void PreOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	if (T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}

//����ݹ����
void InOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	if (T)
	{
		InOrderTraverse(T->lchild,visit);
		visit(T->data);
		InOrderTraverse(T->rchild,visit);
	}
}


//typedef BiTree SElemType;	//��ջԪ��Ϊ��������ָ������

#include "stack.h"
//#include "stack.cpp"

//����������������ǵݹ��㷨������ջ��
Status InOrderTraverse1(BiTree T, Status(*visit)(TElemType))
{
	SqStack S;
	InitStack(&S);
	while (T || !StackEmpty(S))
	{
		if (T)
		{
			Push(&S,T);
			T = T->lchild;
		}
		else
		{
			Pop(&S,&T);
			if (!visit(T->data))
				return ERROR;
			T = T->rchild;
		}
	}
	printf("\n");
	return OK;
}

//����������������ǵݹ��㷨������ջ��
Status InOrderTraverse2(BiTree T, Status(*visit)(TElemType))
{
	SqStack S;
	BiTree p;
	InitStack(&S);
	Push(&S,T);
	while (!StackEmpty(S))
	{
		while (GetTop(S,&p) && p)
			Push(&S,p->lchild);
		Pop(&S,&p);
		if (!StackEmpty(S))
		{
			Pop(&S,&p);
			if (!visit(p->data))
				return ERROR;
			Push(&S,p->rchild);
		}
	}
	printf("\n");
	return OK;
}

//����ݹ����
void PostOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	if (T)
	{
		PostOrderTraverse(T->lchild,visit);
		PostOrderTraverse(T->rchild,visit);
		visit(T->data);
	}
}

//������������ö��У�
void LevelOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	LinkQueue q;
	QElemType a;
	if (T)
	{
		InitQueue(&q);
		EnQueue(&q,T);
		while (!QueueEmpty(q))
		{
			DeQueue(&q,&a);
			visit(a->data);
			if (a->lchild != NULL)
				EnQueue(&q,a->lchild);
			if (a->rchild != NULL)
				EnQueue(&q,a->rchild);
		}
		printf("\n");
	}
}





Status visitT(TElemType e)
 {
 #ifdef CHAR
   printf("%c ",e);
 #endif
 #ifdef INT
   printf("%d ",e);
 #endif
   return OK;
 }

 void main()
 {
   int i;
   BiTree T,p,c;
   TElemType e1,e2;
   InitBiTree(&T);
   printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("�������ĸ�Ϊ: %c\n",e1);
 #endif
 #ifdef INT
     printf("�������ĸ�Ϊ: %d\n",e1);
 #endif
   else
     printf("���գ��޸�\n");
 #ifdef CHAR
   printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiTree(&T);
   printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("�������ĸ�Ϊ: %c\n",e1);
 #endif
 #ifdef INT
     printf("�������ĸ�Ϊ: %d\n",e1);
 #endif
   else
     printf("���գ��޸�\n");
   printf("����ݹ����������:\n");
   InOrderTraverse(T,visitT);
   printf("\n����ǵݹ����������:\n");
   InOrderTraverse1(T,visitT);
   printf("����ǵݹ����������(��һ�ַ���):\n");
   InOrderTraverse2(T,visitT);
   printf("����ݹ����������:\n");
   PostOrderTraverse(T,visitT);
   printf("\n�������������:\n");
   LevelOrderTraverse(T,visitT);
   printf("������һ������ֵ: ");
 #ifdef CHAR
   scanf("%*c%c",&e1);
 #endif
 #ifdef INT
   scanf("%d",&e1);
 #endif
   p=Point(T,e1); /* pΪe1��ָ�� */
 #ifdef CHAR
   printf("����ֵΪ%c\n",Value(p));
 #endif
 #ifdef INT
   printf("����ֵΪ%d\n",Value(p));
 #endif
   printf("���ı�˽���ֵ����������ֵ: ");
 #ifdef CHAR
   scanf("%*c%c%*c",&e2);
 #endif
 #ifdef INT
   scanf("%d",&e2);
 #endif
   Assign(p,e2);
   printf("�������������:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c��˫����%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d��˫����%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû��˫��\n",e2);
 #endif
 #ifdef INT
     printf("%dû��˫��\n",e2);
 #endif
   e1=LeftChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c��������%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d��������%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû������\n",e2);
 #endif
 #ifdef INT
     printf("%dû������\n",e2);
 #endif
   e1=RightChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c���Һ�����%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d���Һ�����%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû���Һ���\n",e2);
 #endif
 #ifdef INT
     printf("%dû���Һ���\n",e2);
 #endif
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c�����ֵ���%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d�����ֵ���%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû�����ֵ�\n",e2);
 #endif
 #ifdef INT
     printf("%dû�����ֵ�\n",e2);
 #endif
   e1=RightSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c�����ֵ���%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d�����ֵ���%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû�����ֵ�\n",e2);
 #endif
 #ifdef INT
     printf("%dû�����ֵ�\n",e2);
 #endif
   InitBiTree(&c);
   printf("����һ��������Ϊ�յĶ�����c:\n");
 #ifdef CHAR
   printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiTree(&c);
   printf("����ݹ����������c:\n");
   PreOrderTraverse(c,visitT);
   printf("\n��c�嵽��T��,��������T����c��˫�׽�� cΪ��(0)����(1)����: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1); /* p��T����c��˫�׽��ָ�� */
   InsertChild(p,i,c);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\nɾ������,�������ɾ��������˫�׽��  ��(0)����(1)����: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1);
   DeleteChild(p,i);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");
   DestroyBiTree(&T);
 }



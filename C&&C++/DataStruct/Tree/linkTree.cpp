/*
*	二叉树的二叉链表存储
*/

#include "Define.h"
#include "linkTree.h"

//构造空二叉树
Status InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}

//销毁二叉树
void DestroyBiTree(BiTree *T)
{
	if (*T)	//非空树
	{
		if ((*T)->lchild)	//有左孩子，销毁左孩子子树
			DestroyBiTree(&(*T)->lchild);
		if ((*T)->rchild)	//有右孩子，销毁右孩子子树
			DestroyBiTree(&(*T)->rchild);
		free(*T);	//释放根节点
		*T = NULL;
	}
}

//按先序次序输入二叉树中结点的值
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
		(*T)->data = ch;	//生成根节点
		CreateBiTree(&(*T)->lchild);	//构造左子树
		CreateBiTree(&(*T)->rchild);	//构造右子树
	}
}

//是否为空树
Status BiTreeEmpty(BiTree T)
{
	if (T)
		return FALSE;
	else
		return TRUE;
}

#define ClearBiTree DestroyBiTree

//树的深度
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

//返回树的根
TElemType Root(BiTree T)
{
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

//返回p指向的结点的值
TElemType Value(BiTree p)
{
	return p->data;
}

//给p所指结点赋值为Value
void Assign(BiTree p, TElemType value)
{
	p->data = value;
}

//typedef BiTree QElemType;	//设队列元素为二叉树的指针类型

#include "queue.h"
//#include "queue.cpp"

//若e是T的非根结点,则返回它的双亲,否则返回＂空＂
TElemType Parent(BiTree T, TElemType e)
{
	LinkQueue	q;
	QElemType	a;
	if (T)
	{
		InitQueue(&q);
		EnQueue(&q,T);	//树根结点入队
		while (!QueueEmpty(q))	//树非空
		{
			DeQueue(&q,&a);	//出队，赋值给a，若a有左或右孩子且左或右孩子的值等于e，则返回a是e的双亲
			if (a->lchild&&a->lchild->data==e || a->rchild&&a->rchild->data==e)
				return a->data;
			else	//a不是，则入队其左右孩子指针（如果非空）
			{
				if (a->lchild)
					EnQueue(&q,a->lchild);
				if (a->rchild)
					EnQueue(&q,a->rchild);
			}
		}
	}
	return Nil;	//树空或没有找到e
}

//返回指向元素值为s的结点的指针
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

//返回e的左孩子。若e无左孩子,则返回＂空＂
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

//返回e的右孩子。若e无右孩子,则返回＂空＂
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

//返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂
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

//返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
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

//非空二叉树c与T不相交且右子树为空,根据LR为0或1,插入c为T中p所指结点的左或右子树。
//p所指结点的原有左或右子树则成为c的右子树
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

//根据LR为0或1,删除T中p所指结点的左或右子树
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

//先序递归遍历
void PreOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	if (T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}

//中序递归遍历
void InOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	if (T)
	{
		InOrderTraverse(T->lchild,visit);
		visit(T->data);
		InOrderTraverse(T->rchild,visit);
	}
}


//typedef BiTree SElemType;	//设栈元素为二叉树的指针类型

#include "stack.h"
//#include "stack.cpp"

//中序遍历二叉树（非递归算法，利用栈）
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

//中序遍历二叉树（非递归算法，利用栈）
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

//后序递归遍历
void PostOrderTraverse(BiTree T, Status(*visit)(TElemType))
{
	if (T)
	{
		PostOrderTraverse(T->lchild,visit);
		PostOrderTraverse(T->rchild,visit);
		visit(T->data);
	}
}

//层序遍历（利用队列）
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
   printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&T);
   printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
   printf("中序递归遍历二叉树:\n");
   InOrderTraverse(T,visitT);
   printf("\n中序非递归遍历二叉树:\n");
   InOrderTraverse1(T,visitT);
   printf("中序非递归遍历二叉树(另一种方法):\n");
   InOrderTraverse2(T,visitT);
   printf("后序递归遍历二叉树:\n");
   PostOrderTraverse(T,visitT);
   printf("\n层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   printf("请输入一个结点的值: ");
 #ifdef CHAR
   scanf("%*c%c",&e1);
 #endif
 #ifdef INT
   scanf("%d",&e1);
 #endif
   p=Point(T,e1); /* p为e1的指针 */
 #ifdef CHAR
   printf("结点的值为%c\n",Value(p));
 #endif
 #ifdef INT
   printf("结点的值为%d\n",Value(p));
 #endif
   printf("欲改变此结点的值，请输入新值: ");
 #ifdef CHAR
   scanf("%*c%c%*c",&e2);
 #endif
 #ifdef INT
   scanf("%d",&e2);
 #endif
   Assign(p,e2);
   printf("层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的双亲是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的双亲是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有双亲\n",e2);
 #endif
 #ifdef INT
     printf("%d没有双亲\n",e2);
 #endif
   e1=LeftChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左孩子\n",e2);
 #endif
   e1=RightChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右孩子\n",e2);
 #endif
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左兄弟\n",e2);
 #endif
   e1=RightSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右兄弟\n",e2);
 #endif
   InitBiTree(&c);
   printf("构造一个右子树为空的二叉树c:\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&c);
   printf("先序递归遍历二叉树c:\n");
   PreOrderTraverse(c,visitT);
   printf("\n树c插到树T中,请输入树T中树c的双亲结点 c为左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1); /* p是T中树c的双亲结点指针 */
   InsertChild(p,i,c);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n删除子树,请输入待删除子树的双亲结点  左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1);
   DeleteChild(p,i);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");
   DestroyBiTree(&T);
 }



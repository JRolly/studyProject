/*
*	顺序栈
*/

#include "Define.h"
#include "stack.h"

Status InitStack(SqStack *S)
{
	(*S).base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

//销毁栈
Status DestroyStack(SqStack *S)
{
	free((*S).base);
	(*S).base =	NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	return OK;
}

//把栈置空
Status ClearStack(SqStack *S)
{
	(*S).top = (*S).base;
	return OK;
}

//是否为空栈
Status StackEmpty(SqStack S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

//栈元素个数
int StackLength(SqStack S)
{
	return S.top - S.base;
}

//用e返回栈顶元素
Status GetTop(SqStack S, SElemType *e)
{
	if (S.top != S.base)
	{
		*e = *--S.top;
		return OK;
	}
	else
		return ERROR;
}

//入栈
Status Push(SqStack *S, SElemType e)
{
	if ((*S).top-(*S).base >= (*S).stacksize)
	{
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if (!(*S).base)
			exit(OVERFLOW);
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top++) = e;
	return OK;
}

//出栈，用e返回
Status Pop(SqStack *S, SElemType *e)
{
	if ((*S).top==(*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

//从栈顶到栈底遍历
Status StackTraverse(SqStack S, Status(*visit)(SElemType))
{
	while (S.top != S.base)
		visit(*--S.top);
	printf("\n");
	return OK;
}



Status visit(SElemType c)
 {
   printf("%d ",c);
   return OK;
 }

//十进制转十六进制
void conversion()
{
	SqStack S;
	unsigned n;
	SElemType e;
	InitStack(&S);
	printf("Input n(n>0):");
	scanf("%d",&n);
	while (n)
	{
		Push(&S,n%16);
		n/=16;
	}
	while (!StackEmpty(S))
	{
		Pop(&S,&e);
		if (e<=9)
			printf("%d",e);
		else
			printf("%d",e+55);
	}
	printf("\n");
}

//检测括号匹配
 void check()
 { /* 对于输入的任意一个字符串，检验括号是否配对 */
   SqStack s;
   SElemType ch[80],*p,e;
   if(InitStack(&s)) /* 初始化栈成功 */
   {
     printf("请输入表达式\n");
     gets(ch);
     p=ch;
     while(*p) /* 没到串尾 */
       switch(*p)
       {
         case '(':
         case '[':Push(&s,*p++);
                  break; /* 左括号入栈，且p++ */
         case ')':
         case ']':if(!StackEmpty(s)) /* 栈不空 */
                  {
                    Pop(&s,&e); /* 弹出栈顶元素 */
                    if(*p==')'&&e!='('||*p==']'&&e!='[') /* 弹出的栈顶元素与*p不配对 */
                    {
                      printf("左右括号不配对\n");
                      exit(ERROR);
                    }
                    else
                    {
                      p++;
                      break; /* 跳出switch语句 */
                    }
                  }
                  else /* 栈空 */
                  {
                    printf("缺乏左括号\n");
                    exit(ERROR);
                  }
         default: p++; /* 其它字符不处理，指针向后移 */
       }
       if(StackEmpty(s)) /* 字符串结束时栈空 */
         printf("括号匹配\n");
       else
         printf("缺乏右括号\n");
   }
 }

 /*void main()
 {
   int j;
   SqStack s;
   SElemType e;
   if(InitStack(&s)==OK)
     for(j=1;j<=12;j++)
       Push(&s,j);
   printf("栈中元素依次为：");
   StackTraverse(s,visit);
   Pop(s,&e);
   printf("弹出的栈顶元素 e=%d\n",e);
   printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
   ClearStack(&s);
   printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("销毁栈后，s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
 }*/

void main()
{
	//conversion();
	check();
}
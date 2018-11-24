/*
*	˳��ջ
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

//����ջ
Status DestroyStack(SqStack *S)
{
	free((*S).base);
	(*S).base =	NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	return OK;
}

//��ջ�ÿ�
Status ClearStack(SqStack *S)
{
	(*S).top = (*S).base;
	return OK;
}

//�Ƿ�Ϊ��ջ
Status StackEmpty(SqStack S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

//ջԪ�ظ���
int StackLength(SqStack S)
{
	return S.top - S.base;
}

//��e����ջ��Ԫ��
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

//��ջ
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

//��ջ����e����
Status Pop(SqStack *S, SElemType *e)
{
	if ((*S).top==(*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

//��ջ����ջ�ױ���
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

//ʮ����תʮ������
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

//�������ƥ��
 void check()
 { /* �������������һ���ַ��������������Ƿ���� */
   SqStack s;
   SElemType ch[80],*p,e;
   if(InitStack(&s)) /* ��ʼ��ջ�ɹ� */
   {
     printf("��������ʽ\n");
     gets(ch);
     p=ch;
     while(*p) /* û����β */
       switch(*p)
       {
         case '(':
         case '[':Push(&s,*p++);
                  break; /* ��������ջ����p++ */
         case ')':
         case ']':if(!StackEmpty(s)) /* ջ���� */
                  {
                    Pop(&s,&e); /* ����ջ��Ԫ�� */
                    if(*p==')'&&e!='('||*p==']'&&e!='[') /* ������ջ��Ԫ����*p����� */
                    {
                      printf("�������Ų����\n");
                      exit(ERROR);
                    }
                    else
                    {
                      p++;
                      break; /* ����switch��� */
                    }
                  }
                  else /* ջ�� */
                  {
                    printf("ȱ��������\n");
                    exit(ERROR);
                  }
         default: p++; /* �����ַ�������ָ������� */
       }
       if(StackEmpty(s)) /* �ַ�������ʱջ�� */
         printf("����ƥ��\n");
       else
         printf("ȱ��������\n");
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
   printf("ջ��Ԫ������Ϊ��");
   StackTraverse(s,visit);
   Pop(s,&e);
   printf("������ջ��Ԫ�� e=%d\n",e);
   printf("ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("ջ��Ԫ�� e=%d ջ�ĳ���Ϊ%d\n",e,StackLength(s));
   ClearStack(&s);
   printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("����ջ��s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
 }*/

void main()
{
	//conversion();
	check();
}
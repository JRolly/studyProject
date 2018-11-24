/*
*	ѧ�������ǼǱ�ʵ��
*/

#include "Define.h"
#include "StuHealthList.h"

char sta[3][9] = {"���� ","һ�� ","��˥��"};	//����״��
FILE *fp;

//��ʼ��
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode));
	if (!*L)
		exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}

//���ǽ������Ԫ��
void InsertAscend(LinkList L, ElemType e)
{
	LinkList p, q;
	q = L;
	p = q->next;
	while (p && e.num>p->data.num)
	{
		q = p;
		p = p->next;
	}
	q->next = (LinkList)malloc(sizeof(struct LNode));
	q->next->data = e;
	q->next->next = p;	
}

//���ѧ����Ϣ
 void Print(struct Stu e)
 { /* ��ʾ��¼e������ */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" ��");
   else
     printf(" Ů");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

//¼��ѧ����Ϣ
void ReadIn(struct Stu *e)
{
	printf("����������(<=%d���ַ�)��",NAMELEN);
	scanf("%s",e->name);
	printf("������ѧ�ţ�");
	scanf("%ld",&e->num);
	printf("�������Ա�(m:�� f:Ů)��");
	scanf("%c",&e->sex);
    printf("����������: ");
    scanf("%d",&e->age);
    printf("������༶(<=%d���ַ�): ",CLASSLEN);
    scanf("%s",e->Class);
    printf("�����뽡��״��(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
    scanf("%d",&e->health);
}

//��ѧ����Ϣд���ļ�
void WriteToFile(struct Stu e)
{
	fwrite(&e,sizeof(struct Stu),1,fp);
}

//���ļ���ȡѧ����Ϣ
Status ReadFromFile(struct Stu *e)
{
	int i;
	i = fread(e,sizeof(struct Stu),1,fp);
	if (1 == i)
		return OK;
	else
		return ERROR;
}

//����ѧ��Ϊnum �Ľ�㣬�ҵ���qָ���㣬pָ��q��ǰ��������TRUE
//����ʧ�ܷ���FALSE
Status FindFromNum(LinkList L, long num, LinkList *p, LinkList *q)
{
	*p = L;
	while (*p)
	{
		*q = (*p)->next;
		if (*q && (*q)->data.num>num)
			break;
		if (*q && (*q)->data.num == num)
			return TRUE;
		*p = *q;
	}
	return FALSE;
}

//��������Ϊname�Ľ�㣬�ҵ���qָ���㣬pָ��q��ǰ��������TRUE
//����ʧ�ܷ���FALSE
Status FindFromName(LinkList L, char name[], LinkList *p, LinkList *q)
{
	*p = L;
	while (*p)
	{
		*q = (*p)->next;
		if (*q && !strcmp((*q)->data.name,name))
			return TRUE;
		*p = *q;
	}
	return FALSE;
}

//ɾ������ѧ��Ϊnum��Ԫ��
Status DeleteElemNum(LinkList L,long num)
{
	LinkList p,q;
	if (FindFromNum(L,num,&p,&q))
	{
		p->next = q->next;
		free(q);
		return TRUE;
	}
	return FALSE;
}

 Status DeleteElemName(LinkList L,char name[])
 { /* ɾ����������Ϊname��Ԫ�أ�������TRUE�����޴�Ԫ�أ��򷵻�FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* �ҵ��˽��,��qָ����,pָ����ǰ�� */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

//�޸�
void Modify(ElemType *e)
{
	char s[80];
   Print(*e); /* ��ʾԭ���� */
   printf("��������޸�������ݣ����޸ĵ���س�������ԭֵ:\n");
   printf("����������(<=%d���ַ�): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("������ѧ��: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("�������Ա�(m:�� f:Ů): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("����������: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("������༶(<=%d���ַ�): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("�����뽡��״��(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* �޸���� */
}

//����
Status ListTraverse(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}




#define N 5 /* Stuent��¼�ĸ��� */
 void main()
 {
   struct Stu Stuent[N]={{"��С��",790631,'m',18,"��91",0},
                           {"�º�",790632,'f',20,"��91",1},
                           {"����ƽ",790633,'m',21,"��91",0},
                           {"������",790634,'m',17,"��91",2}}; /* ��ĳ�ʼ��¼ */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* ��ʼ������ */
   while(flag)
   {
     printf("1:���ṹ������Stuent�еļ�¼��ѧ�ŷǽ����������\n");
     printf("2:���ļ��еļ�¼��ѧ�ŷǽ����������\n");
     printf("3:���������¼�¼�������䰴ѧ�ŷǽ����������\n");
     printf("4:ɾ�������е�һ���и���ѧ�ŵļ�¼\n");
     printf("5:ɾ�������е�һ���и��������ļ�¼\n");
     printf("6:�޸������е�һ���и���ѧ�ŵļ�¼\n");
     printf("7:�޸������е�һ���и��������ļ�¼\n");
     printf("8:���������е�һ���и���ѧ�ŵļ�¼\n");
     printf("9:���������е�һ���и��������ļ�¼\n");
     printf("10:��ʾ���м�¼ 11:�������е����м�¼�����ļ� 12:����\n");
     printf("��ѡ���������: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,Stuent[j]);
               break;
       case 2: printf("�������ļ���: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("���ļ�ʧ��!\n");
               else
               {
                 while(ReadFromFile(&e))
                   InsertAscend(T,e);
                 fclose(fp);
               }
               break;
       case 3: ReadIn(&e);
               InsertAscend(T,e);
               break;
       case 4: printf("�������ɾ����¼��ѧ��: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
               break;
       case 5: printf("�������ɾ����¼������: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("û������Ϊ%s�ļ�¼\n",name);
               break;
       case 6: printf("��������޸ļ�¼��ѧ��: ");
               scanf("%ld%*c",&num); /* %*c�Ե��س��� */
               if(!FindFromNum(T,num,&p,&q))
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* ѧ�ű��޸� */
                 {
                   p->next=q->next; /* ��q��ָ�Ľ���L��ɾ�� */
                   InsertAscend(T,q->data); /* ��Ԫ�ز���L */
                   free(q); /* ɾ��q */
                 }
               }
               break;
       case 7: printf("��������޸ļ�¼������: ");
               scanf("%s%*c",name); /* %*c�Ե��س��� */
               if(!FindFromName(T,name,&p,&q))
                 printf("û������Ϊ%s�ļ�¼\n",name);
               else
               {
                 num=q->data.num; /* ѧ�Ŵ���num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* ѧ�ű��޸� */
                 {
                   p->next=q->next; /* ��q��ָ�Ľ���L��ɾ�� */
                   InsertAscend(T,q->data); /* ��Ԫ�ز���L */
                   free(q); /* ɾ��q */
                 }
               }
               break;
       case 8: printf("����������Ҽ�¼��ѧ��: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("����������Ҽ�¼������: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("û������Ϊ%s�ļ�¼\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  ����    ѧ�� �Ա� ���� �༶ ����״��\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("�������ļ���: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("���ļ�ʧ��!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }


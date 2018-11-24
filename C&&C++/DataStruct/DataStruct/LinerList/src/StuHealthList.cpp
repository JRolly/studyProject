/*
*	学生健康登记表，实例
*/

#include "Define.h"
#include "StuHealthList.h"

char sta[3][9] = {"健康 ","一般 ","神经衰弱"};	//健康状况
FILE *fp;

//初始化
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode));
	if (!*L)
		exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}

//按非降序插入元素
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

//输出学生信息
 void Print(struct Stu e)
 { /* 显示记录e的内容 */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" 男");
   else
     printf(" 女");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

//录入学生信息
void ReadIn(struct Stu *e)
{
	printf("请输入姓名(<=%d个字符)：",NAMELEN);
	scanf("%s",e->name);
	printf("请输入学号：");
	scanf("%ld",&e->num);
	printf("请输入性别(m:男 f:女)：");
	scanf("%c",&e->sex);
    printf("请输入年龄: ");
    scanf("%d",&e->age);
    printf("请输入班级(<=%d个字符): ",CLASSLEN);
    scanf("%s",e->Class);
    printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
    scanf("%d",&e->health);
}

//将学生信息写入文件
void WriteToFile(struct Stu e)
{
	fwrite(&e,sizeof(struct Stu),1,fp);
}

//从文件读取学生信息
Status ReadFromFile(struct Stu *e)
{
	int i;
	i = fread(e,sizeof(struct Stu),1,fp);
	if (1 == i)
		return OK;
	else
		return ERROR;
}

//查找学号为num 的结点，找到后q指向结点，p指向q的前驱并返回TRUE
//查找失败返回FALSE
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

//查找姓名为name的结点，找到后q指向结点，p指向q的前驱并返回TRUE
//查找失败返回FALSE
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

//删除表中学号为num的元素
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
 { /* 删除表中姓名为name的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

//修改
void Modify(ElemType *e)
{
	char s[80];
   Print(*e); /* 显示原内容 */
   printf("请输入待修改项的内容，不修改的项按回车键保持原值:\n");
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("请输入学号: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("请输入性别(m:男 f:女): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("请输入年龄: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* 修改完毕 */
}

//遍历
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




#define N 5 /* Stuent记录的个数 */
 void main()
 {
   struct Stu Stuent[N]={{"王小林",790631,'m',18,"计91",0},
                           {"陈红",790632,'f',20,"计91",1},
                           {"刘建平",790633,'m',21,"计91",0},
                           {"张立立",790634,'m',17,"计91",2}}; /* 表的初始记录 */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* 初始化链表 */
   while(flag)
   {
     printf("1:将结构体数组Stuent中的记录按学号非降序插入链表\n");
     printf("2:将文件中的记录按学号非降序插入链表\n");
     printf("3:键盘输入新记录，并将其按学号非降序插入链表\n");
     printf("4:删除链表中第一个有给定学号的记录\n");
     printf("5:删除链表中第一个有给定姓名的记录\n");
     printf("6:修改链表中第一个有给定学号的记录\n");
     printf("7:修改链表中第一个有给定姓名的记录\n");
     printf("8:查找链表中第一个有给定学号的记录\n");
     printf("9:查找链表中第一个有给定姓名的记录\n");
     printf("10:显示所有记录 11:将链表中的所有记录存入文件 12:结束\n");
     printf("请选择操作命令: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,Stuent[j]);
               break;
       case 2: printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("打开文件失败!\n");
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
       case 4: printf("请输入待删除记录的学号: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("没有学号为%ld的记录\n",num);
               break;
       case 5: printf("请输入待删除记录的姓名: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("没有姓名为%s的记录\n",name);
               break;
       case 6: printf("请输入待修改记录的学号: ");
               scanf("%ld%*c",&num); /* %*c吃掉回车符 */
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 7: printf("请输入待修改记录的姓名: ");
               scanf("%s%*c",name); /* %*c吃掉回车符 */
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               {
                 num=q->data.num; /* 学号存入num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 8: printf("请输入待查找记录的学号: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("请输入待查找记录的姓名: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  姓名    学号 性别 年龄 班级 健康状况\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("打开文件失败!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }


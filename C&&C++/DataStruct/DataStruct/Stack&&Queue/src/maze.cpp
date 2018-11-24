/*
*	用递归实现迷宫求解问题
*/
#include <stdio.h>
#include <stdlib.h>

struct PosType	//迷宫坐标位置类型
{
	int x;	//行值
	int y;	//列值
};

#define	MAXLENGTH	25	//迷宫最大行列为25
typedef int MazeType[MAXLENGTH][MAXLENGTH];

//全局变量
struct PosType end;	//迷宫终点位置
MazeType m;	//迷宫数组
int x,y;	//迷宫行列数

/* 定义墙元素值为0,可通过路径为-1,通过路径为足迹 */

//输出解
void Print(int x, int y)
{
	int i,j;
	for (i=0; i<x; i++)
	{
		for (j=0; j<y; j++)
			printf("%3d",m[i][j]);
		printf("\n");
	}
	printf("\n");
}

//当前位置为cur,当前步骤curstep试探下一点
void Try(struct PosType cur, int curstep)
{
	int i;
	struct PosType next;	//下一个位置
	struct PosType direc[4] = {{0,1},{1,0},{0,-1},{-1,0}};	//移动方向，东南西北
	for (i=0; i<=3; i++)
	{
		next.x = cur.x + direc[i].x;
		next.y = cur.y + direc[i].y;
		if (m[next.x][next.y] == -1)	//是通路
		{
			m[next.x][next.y] = ++curstep;	//准备试探下一步
			if (next.x!=end.x || next.y!=end.y)	//没有到终点
				Try(next,curstep);		//递归，试探下一点
			else
				Print(x,y);
			//m[next.x][next.y] = -1;	//标记这一点为通路
			curstep--;	//递归试探下一点失败，则返回当前步骤，继续循环尝试下一个方向
		}
	}
}


void main()
 {
   struct PosType begin;
   int i,j,x1,y1;
   printf("请输入迷宫的行数,列数(包括外墙)：");
   scanf("%d,%d",&x,&y);
   for(i=0;i<x;i++) /* 定义周边值为0(同墙) */
   {
     m[0][i]=0; /* 行周边 */
     m[x-1][i]=0;
   }
   for(j=1;j<y-1;j++)
   {
     m[j][0]=0; /* 列周边 */
     m[j][y-1]=0;
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=-1; /* 定义通道初值为-1 */
   Print(x,y);
   printf("请输入迷宫内墙单元数：");
   scanf("%d",&j);
   if(j)
     printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0;
   }
   printf("迷宫结构如下:\n");
   Print(x,y);
   printf("请输入起点的行数,列数：");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("请输入终点的行数,列数：");
   scanf("%d,%d",&end.x,&end.y);
   m[begin.x][begin.y]=1;
   Try(begin,1); /* 由第一步起点试探起 */
 }




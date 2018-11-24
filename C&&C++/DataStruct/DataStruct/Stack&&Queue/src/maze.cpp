/*
*	�õݹ�ʵ���Թ��������
*/
#include <stdio.h>
#include <stdlib.h>

struct PosType	//�Թ�����λ������
{
	int x;	//��ֵ
	int y;	//��ֵ
};

#define	MAXLENGTH	25	//�Թ��������Ϊ25
typedef int MazeType[MAXLENGTH][MAXLENGTH];

//ȫ�ֱ���
struct PosType end;	//�Թ��յ�λ��
MazeType m;	//�Թ�����
int x,y;	//�Թ�������

/* ����ǽԪ��ֵΪ0,��ͨ��·��Ϊ-1,ͨ��·��Ϊ�㼣 */

//�����
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

//��ǰλ��Ϊcur,��ǰ����curstep��̽��һ��
void Try(struct PosType cur, int curstep)
{
	int i;
	struct PosType next;	//��һ��λ��
	struct PosType direc[4] = {{0,1},{1,0},{0,-1},{-1,0}};	//�ƶ����򣬶�������
	for (i=0; i<=3; i++)
	{
		next.x = cur.x + direc[i].x;
		next.y = cur.y + direc[i].y;
		if (m[next.x][next.y] == -1)	//��ͨ·
		{
			m[next.x][next.y] = ++curstep;	//׼����̽��һ��
			if (next.x!=end.x || next.y!=end.y)	//û�е��յ�
				Try(next,curstep);		//�ݹ飬��̽��һ��
			else
				Print(x,y);
			//m[next.x][next.y] = -1;	//�����һ��Ϊͨ·
			curstep--;	//�ݹ���̽��һ��ʧ�ܣ��򷵻ص�ǰ���裬����ѭ��������һ������
		}
	}
}


void main()
 {
   struct PosType begin;
   int i,j,x1,y1;
   printf("�������Թ�������,����(������ǽ)��");
   scanf("%d,%d",&x,&y);
   for(i=0;i<x;i++) /* �����ܱ�ֵΪ0(ͬǽ) */
   {
     m[0][i]=0; /* ���ܱ� */
     m[x-1][i]=0;
   }
   for(j=1;j<y-1;j++)
   {
     m[j][0]=0; /* ���ܱ� */
     m[j][y-1]=0;
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=-1; /* ����ͨ����ֵΪ-1 */
   Print(x,y);
   printf("�������Թ���ǽ��Ԫ����");
   scanf("%d",&j);
   if(j)
     printf("�����������Թ���ǽÿ����Ԫ������,������\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0;
   }
   printf("�Թ��ṹ����:\n");
   Print(x,y);
   printf("��������������,������");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("�������յ������,������");
   scanf("%d,%d",&end.x,&end.y);
   m[begin.x][begin.y]=1;
   Try(begin,1); /* �ɵ�һ�������̽�� */
 }




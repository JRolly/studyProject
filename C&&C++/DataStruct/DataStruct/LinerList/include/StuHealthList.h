/*
*	ѧ��������Ϣ�ǼǱ���
*/

#ifndef __STUHEALTHLIST_H__
#define __STUHEALTHLIST_H__

#define NAMELEN	8	//������󳤶�
#define CLASSLEN	4	//�༶����󳤶�

struct Stu
{
	char name[NAMELEN+1];
	long num;
	char sex;
	int age;
	char Class[CLASSLEN+1];
	int health;
};
typedef struct Stu ElemType;	//�߱�ṹԪ������

struct LNode
{
	ElemType data;
	struct LNode *next;
};
typedef struct LNode *LinkList;

#endif __STUHEALTHLIST_H__	//end ifndef __STUHEALTHLIST_H__
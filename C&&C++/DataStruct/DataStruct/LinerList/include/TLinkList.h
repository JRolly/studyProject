/*
*	��ͷ����������������,����ʵ��ʹ�������
*/

typedef struct LNode	//�������
{
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct LinkList	//��������
{
	Link head, tail;	//�ֱ�Ϊ���������ͷ�������һ�����
	int len;	//�������������Ԫ�ظ���
}LinkList;
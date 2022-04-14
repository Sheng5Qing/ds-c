#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //������

//������������ΪTElemType
typedef char TElemType;

//˫�ױ�ʾ��
//�����ṹ
typedef struct PTNode{
    TElemType data;
    int parent;
}PTNode;
//���ṹ
#define MAXSIZE 100
typedef struct PTree{
    PTNode nodes[MAXSIZE];
    int r,n;  //�����λ�úͽ�����
}PTree;
/*�ص㣺��˫�����ף��Һ�����*/ 

//��������洢�ṹ
//���ӽ��ṹ
typedef struct CTNode{
    int child;//����±�λ��
    struct CNode* next;//��һ�����ӵĵ�ַ
}*ChildPtr;
//˫�׽��ṹ
typedef struct CTBox{
    TElemType data;
    ChildPtr firstchild;//����������
}CTBox;
//���ṹ
typedef struct CTree{
    CTBox nodes[MAXSIZE];
    int r,n;//���ڵ��λ�úͽ�����
}CTree;

//�����ֵܱ�ʾ������������ʾ����
typedef struct CSNode{
    TElemType data;
    //��һ�����ӣ���һ���ֵ�
    struct CSNode *firstchild,*nexxtsibling;
}CSNode,*CSTree;


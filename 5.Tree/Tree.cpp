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

//�������в���ʱ�����Խ���ת��Ϊ�����������ö��������㷨���������в���
//�Զ�������Ϊý��

/*
����ת���ɶ�����
�ټ��ߣ����ֵܼ��һ����
��Ĩ�ߣ���ÿ����㣬���������ӣ�ȥ���������ຢ��֮��Ĺ�ϵ
����ת�������ĸ���㣨�����������㣩Ϊ���ģ�������˳ʱ��ת45��
�ھ����ֵ����������� 
*/

/*
��������ת������
�ټ��ߣ���p�����˫�׽������ӣ���p���Һ��ӣ��Һ��ӵ��Һ���...�ط�֧�ҵ������Һ��ӣ�����p��˫������������
��Ĩ�ߣ�Ĩ��ԭ��������˫�����Һ���֮�������
�۵���������㰴��������γ����ṹ
*/

/*
ɭ��ת���ɶ�����
�ٽ��������ֱ�ת���ɶ�����
�ڽ�ÿ�����ĸ������������
���Ե�һ���������Ϊ�������ĸ������Ը����Ϊ���ģ�˳ʱ����ת�����ɶ������ͽṹ
������������
*/

/*
������ת����ɭ��
��Ĩ�ߣ����������и���������Һ������ߣ������ҷ�֧�������������Һ��Ӽ������ȫ��Ĩ����ʹ֮��ɹ���������
�ڽ�������������ԭ����
ȥ��ȫ���Һ��ߣ����������ٻ�ԭ
*/


#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1//������
#define OVERFLOW -2 //���


typedef int Status;       //����״̬
typedef char ElemType;    //Ԫ������

typedef struct LNode{
	ElemType data;
	struct LNode* next; //ָ�򱾽ṹ��ָ��/����ָ����Ƕ�׶���
}LNode,*LinkList;//LinkListΪָ��ṹ��LNode��ָ������
/*LNode* ��LinkList�������ǵȼ۵ģ���ôд��Ϊ����߳���ɶ��ԡ�ͨ��ϰ������LinkList L�����嵥����LNode* node������*/

//������Ļ�������
//������ĳ�ʼ��
Status InitList_L(LinkList& L) ;
//�жϿձ�
int ListEmpty(LinkList L);
//���ٵ�����
Status DestoryList_L(LinkList &L);
//��յ�����
Status ClearList(LinkList &L);
//������ı�
int ListLength_L(LinkList L);
//ȡ��i��Ԫ�ص�ֵ
Status GetElem_L(LinkList L,int i,ElemType &e);
//������ֵ���ҡ�������λ��
LNode* LocateElem1_L(LinkList L,ElemType e);
//������ֵ���ҡ������ؽ���ַ
int LocateElem2_L(LinkList L,ElemType e);
//������������
Status ListInsert_L(LinkList &L, int i, ElemType e);
//������ɾ����i�����
Status ListDelete_L(LinkList &L, int i, ElemType &e);
//������Ľ���
//ͷ�巨
void CreateList_H(LinkList &L,int n);
//β�巨
void CreateList_R(LinkList &L,int n);


int main(){
    
    
    return 0;
}

//������ĳ�ʼ��
/*
1. �����½����Ϊͷ��㣬��ͷָ��ָ��ͷ���
2. ��ͷ����ָ�����ÿ�
*/
Status InitList_L(LinkList& L) {
	L = new LNode; //��L = (LinkLIst)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}
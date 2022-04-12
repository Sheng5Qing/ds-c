#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1//������


typedef int Status;       //����״̬
typedef char ElemType;    //Ԫ������

typedef struct DuLNode{
    ElemType data;     
    struct DuLNode* prior;  //ֱ��ǰ��
    struct DuLNode* next;   //ֱ�Ӻ��
}DuLNode,*DuLinkList;

//�ҵ���i�����
DuLNode* GetElem_DuL(DuLinkList L, int i){
    DuLNode* p = L->next;
    int j = 1;
    while(p && j < i){
        p = p->next;
        j++;
    }
    if(!p || j > i){
        return ERROR;
    }
    return p;
}
//˫������Ĳ���
Status ListInsert_DuL(DuLinkList &L,int i,ElemType e){
    DuLNode* p = GetElem_DuL(L,i);
    if(!p){
        return ERROR;
    }
    DuLNode* s = new DuLNode;
    s->data = e;
    p->prior->next = s;  //��s�ĵ�ַ���ӵ�pǰ�����ĺ������
    s->prior = p->prior;  //��p��ǰ�����ӵ�s��ǰ����
    p->prior = s;  //��s�ĵ�ַ���ӵ�p��ǰ����
    s->next = p;  //��p�ĵ�ַ���ӵ�s�ĺ����

    return OK;
}
//˫�������ɾ��
Status ListDelete_DuL(DuLinkList &L,int i,ElemType &e){
    DuLNode* p = GetElem_DuL(L,i);
    if(!p){
        return ERROR;
    }
    p->prior->next = p->next;   //�޸ı�ɾ������ǰ�����ĺ��ָ��
    p->next->prior = p->prior;  //�޸ı�ɾ�����ĺ�̽ڵ��ǰ��ָ��
    e = p->data; 
    delete p;
    return OK;
}
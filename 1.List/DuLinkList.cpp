#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1//不可行


typedef int Status;       //返回状态
typedef char ElemType;    //元素类型

typedef struct DuLNode{
    ElemType data;     
    struct DuLNode* prior;  //直接前驱
    struct DuLNode* next;   //直接后继
}DuLNode,*DuLinkList;

//找到第i个结点
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
//双向链表的插入
Status ListInsert_DuL(DuLinkList &L,int i,ElemType e){
    DuLNode* p = GetElem_DuL(L,i);
    if(!p){
        return ERROR;
    }
    DuLNode* s = new DuLNode;
    s->data = e;
    p->prior->next = s;  //把s的地址链接到p前驱结点的后继域上
    s->prior = p->prior;  //把p的前驱链接到s的前驱上
    p->prior = s;  //把s的地址连接到p的前驱上
    s->next = p;  //把p的地址连接到s的后继上

    return OK;
}
//双向链表的删除
Status ListDelete_DuL(DuLinkList &L,int i,ElemType &e){
    DuLNode* p = GetElem_DuL(L,i);
    if(!p){
        return ERROR;
    }
    p->prior->next = p->next;   //修改被删除结点的前驱结点的后继指针
    p->next->prior = p->prior;  //修改被删除结点的后继节点的前驱指针
    e = p->data; 
    delete p;
    return OK;
}
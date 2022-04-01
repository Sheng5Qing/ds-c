#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1//不可行
#define OVERFLOW -2 //溢出


typedef int Status;       //返回状态
typedef char ElemType;    //元素类型

typedef struct LNode{
	ElemType data;
	struct LNode* next; //指向本结构的指针/结点的指针域，嵌套定义
}LNode,*LinkList;//LinkList为指向结构体LNode的指针类型
/*LNode* 和LinkList本质上是等价的，这么写是为了提高程序可读性。通常习惯上用LinkList L来定义单链表，LNode* node定义结点*/

//单链表的基本操作
//单链表的初始化
Status InitList_L(LinkList& L) ;
//判断空表
int ListEmpty(LinkList L);
//销毁单链表
Status DestoryList_L(LinkList &L);
//清空单链表
Status ClearList(LinkList &L);
//求单链表的表长
int ListLength_L(LinkList L);
//取第i个元素的值
Status GetElem_L(LinkList L,int i,ElemType &e);
//单链表按值查找——返回位置
LNode* LocateElem1_L(LinkList L,ElemType e);
//单链表按值查找——返回结点地址
int LocateElem2_L(LinkList L,ElemType e);
//单链表插入操作
Status ListInsert_L(LinkList &L, int i, ElemType e);
//单链表删除第i个结点
Status ListDelete_L(LinkList &L, int i, ElemType &e);
//单链表的建立
//头插法
void CreateList_H(LinkList &L,int n);
//尾插法
void CreateList_R(LinkList &L,int n);


int main(){
    
    
    return 0;
}

//单链表的初始化
/*
1. 生成新结点作为头结点，用头指针指向头结点
2. 将头结点的指针域置空
*/
Status InitList_L(LinkList& L) {
	L = new LNode; //或L = (LinkLIst)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}
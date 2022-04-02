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
int LocateElem1_L(LinkList L,ElemType e);
//单链表按值查找——返回结点地址
LNode* LocateElem2_L(LinkList L,ElemType e);
//单链表插入操作
Status ListInsert_L(LinkList &L, int i, ElemType e);
//单链表删除第i个结点
Status ListDelete_L(LinkList &L, int i, ElemType &e);
//单链表的建立
//头插法
void CreateList_H(LinkList &L,int n);
//尾插法
void CreateList_R(LinkList &L,int n);


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
//判断空表
/*空表返回1 非空返回0*/
int ListEmpty(LinkList L){
	if(L->next == NULL){
		return TRUE;
	}
	else{
		return FAlSE;
	}		
}

//销毁单链表
Status DestoryList_L(LinkList &L){
	LNode* p;
	while (L)
	{
		p = L;
		L = L->next;
		delete p;
	}
	return OK;
}

//清空单链表
Status ClearList(LinkList &L){
	LNode* p = L->next;
	LNode* q;
	while(p){
		q = p;
		p = p->next;
		delete q;
	}
	L->next = NULL;             //头结点指针域置为空
	return OK;
}

//求单链表的表长
int ListLength_L(LinkList L){
	int len = 0;
	LNode* p = L;
	while(p){
		p = p->next;
		len++;
	}
	return len;
}

//取第i个元素的值
Status GetElem_L(LinkList L,int i,ElemType &e){
	LNode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) //向后扫描，直到p指向第i个元素或p为空
	{
		p = p->next;
		j++;
	}
	if(!p || j > i){ //若第i个元素不存在
		return ERROR;
	}
	e = p->data;
	return OK;
}

//单链表按值查找——返回位置
//找到返回元素序号，找不到返回元素位置序号
int LocateElem1_L(LinkList L,ElemType e){
	LNode* p = L->next;
	int j = 1;
	while(p&&p->data != e){ //顺序扫描，直到p为空或p的下一结点数据域等于e
		p = p->next;
		j++;
	}
	if(p){
		return j;
	}else{
		return 0;
	}

}

//单链表按值查找——返回结点地址
//找到返回结点地址，找不到返回NULL
LNode* LocateElem2_L(LinkList L,ElemType e){
	LNode* p = L->next;
	while(p&&p->data != e){ //顺序扫描，直到p为空或p的下一结点数据域等于e
		p = p->next;
	}
	if(p){
		return p;
	}else{
		return NULL;
	}
	
}

//单链表插入操作
Status ListInsert_L(LinkList &L, int i, ElemType e){
	LNode* p = L;
	int j = 0;
	while (p && j < i - 1)  //找到第i-1个结点，p指向这个结点
	{
		p = p->next;
		j++;
	}
	if(!p || j > i - 1){  //i大于表长+1(!p)或者i小于1(j > i - 1)，那么插入位置非法
		return ERROR;
	}
	LNode* s = new LNode; //生成新节点
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

//单链表删除第i个结点
Status ListDelete_L(LinkList &L, int i, ElemType &e){
	LNode* p = L->next;
	int j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if(!p || j > i){
		return ERROR;
	}
	e = p->data;
	delete p;
	return OK;
}

//单链表的建立
//头插法
void CreateList_H(LinkList &L,int n){
	L = new LNode;
	L->next = NULL;                          //先建立一个带头结点的单链表
	for(int i = 0; i < n; i++){
		LNode* s = new LNode;
		//LNode* s = (LNode*)malloc(sizeof(LNode));
		//scanf("%c",&(s->data));
		cin>>s->data;
		s->next = L->next;
		L->next = s;
	}
}

//尾插法
void CreateList_R(LinkList &L,int n){
	L = new LNode;
	L->next = NULL;
	LNode* tail =  L; //开始时尾指针指向头结点
	for(int i = 0; i < n; i++){
		LNode* s = new LNode;
		//LNode* s = (LNode*)malloc(sizeof(LNode));
		//scanf("%c",&(s->data));
		cin>>s->data;
		s->next = NULL;  //插入到表尾
		tail->next = s;  
		tail = s;	//tail指向新的尾结点
	}

}
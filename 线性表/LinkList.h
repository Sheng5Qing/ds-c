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
int LocateElem1_L(LinkList L,ElemType e);
//������ֵ���ҡ������ؽ���ַ
LNode* LocateElem2_L(LinkList L,ElemType e);
//������������
Status ListInsert_L(LinkList &L, int i, ElemType e);
//������ɾ����i�����
Status ListDelete_L(LinkList &L, int i, ElemType &e);
//������Ľ���
//ͷ�巨
void CreateList_H(LinkList &L,int n);
//β�巨
void CreateList_R(LinkList &L,int n);


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
//�жϿձ�
/*�ձ���1 �ǿշ���0*/
int ListEmpty(LinkList L){
	if(L->next == NULL){
		return TRUE;
	}
	else{
		return FAlSE;
	}		
}

//���ٵ�����
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

//��յ�����
Status ClearList(LinkList &L){
	LNode* p = L->next;
	LNode* q;
	while(p){
		q = p;
		p = p->next;
		delete q;
	}
	L->next = NULL;             //ͷ���ָ������Ϊ��
	return OK;
}

//������ı�
int ListLength_L(LinkList L){
	int len = 0;
	LNode* p = L;
	while(p){
		p = p->next;
		len++;
	}
	return len;
}

//ȡ��i��Ԫ�ص�ֵ
Status GetElem_L(LinkList L,int i,ElemType &e){
	LNode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) //���ɨ�裬ֱ��pָ���i��Ԫ�ػ�pΪ��
	{
		p = p->next;
		j++;
	}
	if(!p || j > i){ //����i��Ԫ�ز�����
		return ERROR;
	}
	e = p->data;
	return OK;
}

//������ֵ���ҡ�������λ��
//�ҵ�����Ԫ����ţ��Ҳ�������Ԫ��λ�����
int LocateElem1_L(LinkList L,ElemType e){
	LNode* p = L->next;
	int j = 1;
	while(p&&p->data != e){ //˳��ɨ�裬ֱ��pΪ�ջ�p����һ������������e
		p = p->next;
		j++;
	}
	if(p){
		return j;
	}else{
		return 0;
	}

}

//������ֵ���ҡ������ؽ���ַ
//�ҵ����ؽ���ַ���Ҳ�������NULL
LNode* LocateElem2_L(LinkList L,ElemType e){
	LNode* p = L->next;
	while(p&&p->data != e){ //˳��ɨ�裬ֱ��pΪ�ջ�p����һ������������e
		p = p->next;
	}
	if(p){
		return p;
	}else{
		return NULL;
	}
	
}

//������������
Status ListInsert_L(LinkList &L, int i, ElemType e){
	LNode* p = L;
	int j = 0;
	while (p && j < i - 1)  //�ҵ���i-1����㣬pָ��������
	{
		p = p->next;
		j++;
	}
	if(!p || j > i - 1){  //i���ڱ�+1(!p)����iС��1(j > i - 1)����ô����λ�÷Ƿ�
		return ERROR;
	}
	LNode* s = new LNode; //�����½ڵ�
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

//������ɾ����i�����
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

//������Ľ���
//ͷ�巨
void CreateList_H(LinkList &L,int n){
	L = new LNode;
	L->next = NULL;                          //�Ƚ���һ����ͷ���ĵ�����
	for(int i = 0; i < n; i++){
		LNode* s = new LNode;
		//LNode* s = (LNode*)malloc(sizeof(LNode));
		//scanf("%c",&(s->data));
		cin>>s->data;
		s->next = L->next;
		L->next = s;
	}
}

//β�巨
void CreateList_R(LinkList &L,int n){
	L = new LNode;
	L->next = NULL;
	LNode* tail =  L; //��ʼʱβָ��ָ��ͷ���
	for(int i = 0; i < n; i++){
		LNode* s = new LNode;
		//LNode* s = (LNode*)malloc(sizeof(LNode));
		//scanf("%c",&(s->data));
		cin>>s->data;
		s->next = NULL;  //���뵽��β
		tail->next = s;  
		tail = s;	//tailָ���µ�β���
	}

}
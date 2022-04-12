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
typedef char SElemType;    //ջԪ������

/*
��ջ���������޵ĵ�����ֻ��������ͷ�����в���
�����ͷָ�����ջ��
����Ҫͷ���
����������ջ�������
��ջ�൱��ͷָ��ָ���
�����ɾ������ջ����ִ��
*/
typedef struct StackNode{
    SElemType data;
    struct StackNode* next;
}StackNode,*LinkStack;

//��ջ�ĳ�ʼ��
Status InitStack(LinkStack &S);

//�ж���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S);

//��ջ����ջ
Status Push(LinkStack &S, SElemType e);

//��ջ�ĳ�ջ
Status Pop(LinkStack &S, SElemType &e);

//ȡջ��Ԫ��
Status GetTop(LinkStack S);

int main(){
    LinkStack s;
    InitStack(s);
    Push(s,'o');
    Push(s,'l');
    Push(s,'l');
    Push(s,'e');
    Push(s,'h');
    char e;
    for(int i = 0; i < 5; i++){
        Pop(s,e);
        printf("%c",e);
    }

    return 0;
}

//��ջ�ĳ�ʼ��
Status InitStack(LinkStack &S){
    S = NULL;
    return OK;
}

//�ж���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S){
    if(S == NULL) return TRUE;
    else return FAlSE;
}

//��ջ����ջ
Status Push(LinkStack &S, SElemType e){
    StackNode* p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK; 
}

//��ջ�ĳ�ջ
Status Pop(LinkStack &S, SElemType &e){
    if(S){
        e = S->data;
        StackNode *p = S;
        S = S->next;
        delete p;
        return OK;
    }else{
        return ERROR;
    }
}

//ȡջ��Ԫ��
Status GetTop(LinkStack S){
    if(S != NULL){
        return S->data;
    }
}


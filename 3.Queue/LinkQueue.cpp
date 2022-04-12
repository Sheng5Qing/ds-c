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
typedef char QElemType;    //ջԪ������

#define MAXQSIZE 100  //�����г���
typedef struct Qnode{
    QElemType data;
    struct Qnode* next;
}QNode,*Queueptr;

typedef struct{
    Queueptr front;  //��ͷָ��
    Queueptr rear;  //��βָ��
}LinkQueue;

//��ʼ��������
Status InitQueue(LinkQueue &Q);

//����������
Status DestoryQueue(LinkQueue &Q);

//��ն���
Status ClearQueue(LinkQueue &Q);

//�ж϶ӿ�
Status QueueEmpty(LinkQueue Q);

//����г���
int QueueLength(LinkQueue Q);

//��ȡ��ͷԪ��
QElemType GetHead(LinkQueue Q);

//��Ԫ�����
Status EnQueue(LinkQueue &Q, QElemType e);

//����
Status DeQueue(LinkQueue &Q, QElemType &e);

//�Ӷ�ͷ����β�����η��ʶ���Ԫ��
Status QueueTraverse(LinkQueue Q);

int main(){
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q,'h');
    EnQueue(Q,'e');
    EnQueue(Q,'l');
    EnQueue(Q,'l');
    EnQueue(Q,'o');
    QueueTraverse(Q);
    
    return 0;
}

//��ʼ��������
Status InitQueue(LinkQueue &Q){
    //Q.front = Q.rear = (Queueptr)malloc(sizeof(QNode));
    Q.front = new Qnode;
    Q.rear = Q.front;
    Q.rear->next = NULL;
    if(!Q.front) exit(OVERFLOW);
    return OK;
}

//����������
Status DestoryQueue(LinkQueue &Q){
    if(!QueueEmpty(Q)){
        Queueptr p;
        while(Q.front){
            p = Q.front->next;
            delete Q.front;
            Q.front = p;
        }
        return OK;
    }
    return ERROR;
}

//��ն���
Status ClearQueue(LinkQueue &Q){
    if(!QueueEmpty(Q)){
        Queueptr p = Q.front->next;
        while (p)
        {
            Q.rear = p->next;
            delete p;
            p = Q.rear;
        }
        return OK;
    }
    return ERROR; 
}

//�ж϶ӿ�
Status QueueEmpty(LinkQueue Q){
    if(Q.rear == Q.front)
        return TRUE;
    else
        return FAlSE;
}

//����г���
int QueueLength(LinkQueue Q){
    int count = 0;
    Queueptr p = Q.front->next;
    while (p)
    {
        count++;
        p = p->next;
    }
    return count;
}

//��ȡ��ͷԪ��
QElemType GetHead(LinkQueue Q){
    if (!QueueEmpty(Q))
    {
        return Q.front->next->data;
    }
    return '0';
}

//��Ԫ�����
Status EnQueue(LinkQueue &Q, QElemType e){
    Qnode* p = new Qnode;
    if(!p) exit(OVERFLOW);
    p->data = e;
    Q.rear->next = p; 
    Q.rear = p;
    return OK;
}

//����
Status DeQueue(LinkQueue &Q, QElemType &e){
    if(!QueueEmpty(Q)){
        Queueptr p = Q.front->next;
        e = Q.front->next->data;
        Q.front->next = Q.front->next->next;
        if(Q.rear == p) Q.rear = Q.front;
        delete p;
        return OK;
    }
    return ERROR;
}

//�Ӷ�ͷ����β�����η��ʶ���Ԫ��
Status QueueTraverse(LinkQueue Q){
    if(QueueEmpty(Q)) return ERROR;
    QNode* p = Q.front->next;
    while (p != Q.rear->next)
    {
        printf("%c",p->data);
        p = p->next;
    }
    return OK;
}

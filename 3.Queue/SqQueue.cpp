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
typedef char QElemType;    //����Ԫ������

#define MAXQSIZE 100  //���п��ܴﵽ����󳤶�
typedef struct{
    QElemType* base;  //���д洢�ռ�Ļ���ַ
    int front;  //��ͷָ��
    int rear;  //��βָ��
}SqQueue;

//��ʼ��˳�����
Status InitQueue(SqQueue &Q);

//����˳�����
Status DestoryQueue(SqQueue &Q);

//��ն���
Status ClearQueue(SqQueue &Q);

//�ж϶ӿ�
Status QueueEmpty(SqQueue Q);

//����г���
int QueueLength(SqQueue Q);

//��ȡ��ͷԪ��
QElemType GetHead(SqQueue Q);

//��Ԫ�����
Status EnQueue(SqQueue &Q, QElemType e);

//����
Status DeQueue(SqQueue &Q, QElemType &e);

//�Ӷ�ͷ����β�����η��ʶ���Ԫ��
Status QueueTraverse(SqQueue Q);

int main(){
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q,'h');
    EnQueue(Q,'e');
    EnQueue(Q,'l');
    EnQueue(Q,'l');
    EnQueue(Q,'o');
    QueueTraverse(Q);
    
    return 0;
}

//��ʼ��˳�����
Status InitQueue(SqQueue &Q){
    Q.base = new QElemType[MAXQSIZE];
    //Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q.base) exit(OVERFLOW);
    Q.front = 0;
    Q.rear = Q.front;
    return OK;
}

//����˳�����
Status DestoryQueue(SqQueue &Q){
    if(Q.rear == Q.front){
        return ERROR;
    }else{
        delete Q.base;
        Q.rear = 0;
        Q.front = 0;
    }
    return OK;
}

//��ն���
Status ClearQueue(SqQueue &Q){
    if(Q.rear == Q.front){
        return ERROR;
    }else{
        Q.rear = 0;
        Q.front =  0;
    }
    return OK;
}

//�ж϶ӿ�
Status QueueEmpty(SqQueue Q){
    if(Q.front == Q.rear)
        return TRUE;
    else
        return FAlSE;
}

//����г���
int QueueLength(SqQueue Q){
    //˳����в�����ֱ�Ӷ�β����ͷ
    return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
}

//��ȡ��ͷԪ��
QElemType GetHead(SqQueue Q){
    if(Q.front != Q.rear){
        return Q.base[Q.front];
    } 
    return '0';
}

//��Ԫ�����
Status EnQueue(SqQueue &Q, QElemType e){
    if(Q.rear + 1 == Q.front){
        return ERROR;
    }else{
        Q.base[Q.rear] = e;
        Q.rear = (Q.rear + 1) % MAXQSIZE;
    }
    return OK;
}

//����
Status DeQueue(SqQueue &Q, QElemType &e){
    if(Q.rear == Q.front){
        return ERROR;
    }else{
        e = Q.base[Q.front];
        Q.front = (Q.front + 1) % MAXQSIZE;
    }
    return OK;
}

//�Ӷ�ͷ����β�����η��ʶ���Ԫ��
Status QueueTraverse(SqQueue Q){
    if(Q.rear == Q.front){
        return ERROR;
    }else{
        int front = Q.front;
        int rear = Q.rear;
        while (front % MAXQSIZE != rear)
        {
            printf("%c",Q.base[front]);
            front++;
        }
    }
    return OK;
}


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
typedef char QElemType;    //栈元素类型

#define MAXQSIZE 100  //最大队列长度
typedef struct Qnode{
    QElemType data;
    struct Qnode* next;
}QNode,*Queueptr;

typedef struct{
    Queueptr front;  //队头指针
    Queueptr rear;  //队尾指针
}LinkQueue;

//初始化链队列
Status InitQueue(LinkQueue &Q);

//销毁链队列
Status DestoryQueue(LinkQueue &Q);

//清空队列
Status ClearQueue(LinkQueue &Q);

//判断队空
Status QueueEmpty(LinkQueue Q);

//求队列长度
int QueueLength(LinkQueue Q);

//获取队头元素
QElemType GetHead(LinkQueue Q);

//新元素入队
Status EnQueue(LinkQueue &Q, QElemType e);

//出队
Status DeQueue(LinkQueue &Q, QElemType &e);

//从队头到队尾，依次访问队列元素
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

//初始化链队列
Status InitQueue(LinkQueue &Q){
    //Q.front = Q.rear = (Queueptr)malloc(sizeof(QNode));
    Q.front = new Qnode;
    Q.rear = Q.front;
    Q.rear->next = NULL;
    if(!Q.front) exit(OVERFLOW);
    return OK;
}

//销毁链队列
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

//清空队列
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

//判断队空
Status QueueEmpty(LinkQueue Q){
    if(Q.rear == Q.front)
        return TRUE;
    else
        return FAlSE;
}

//求队列长度
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

//获取队头元素
QElemType GetHead(LinkQueue Q){
    if (!QueueEmpty(Q))
    {
        return Q.front->next->data;
    }
    return '0';
}

//新元素入队
Status EnQueue(LinkQueue &Q, QElemType e){
    Qnode* p = new Qnode;
    if(!p) exit(OVERFLOW);
    p->data = e;
    Q.rear->next = p; 
    Q.rear = p;
    return OK;
}

//出队
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

//从队头到队尾，依次访问队列元素
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

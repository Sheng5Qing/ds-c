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
typedef char QElemType;    //队列元素类型

#define MAXQSIZE 100  //队列可能达到的最大长度
typedef struct{
    QElemType* base;  //队列存储空间的基地址
    int front;  //队头指针
    int rear;  //队尾指针
}SqQueue;

//初始化顺序队列
Status InitQueue(SqQueue &Q);

//销毁顺序队列
Status DestoryQueue(SqQueue &Q);

//清空队列
Status ClearQueue(SqQueue &Q);

//判断队空
Status QueueEmpty(SqQueue Q);

//求队列长度
int QueueLength(SqQueue Q);

//获取队头元素
QElemType GetHead(SqQueue Q);

//新元素入队
Status EnQueue(SqQueue &Q, QElemType e);

//出队
Status DeQueue(SqQueue &Q, QElemType &e);

//从队头到队尾，依次访问队列元素
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

//初始化顺序队列
Status InitQueue(SqQueue &Q){
    Q.base = new QElemType[MAXQSIZE];
    //Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q.base) exit(OVERFLOW);
    Q.front = 0;
    Q.rear = Q.front;
    return OK;
}

//销毁顺序队列
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

//清空队列
Status ClearQueue(SqQueue &Q){
    if(Q.rear == Q.front){
        return ERROR;
    }else{
        Q.rear = 0;
        Q.front =  0;
    }
    return OK;
}

//判断队空
Status QueueEmpty(SqQueue Q){
    if(Q.front == Q.rear)
        return TRUE;
    else
        return FAlSE;
}

//求队列长度
int QueueLength(SqQueue Q){
    //顺序队列不可以直接队尾减队头
    return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
}

//获取队头元素
QElemType GetHead(SqQueue Q){
    if(Q.front != Q.rear){
        return Q.base[Q.front];
    } 
    return '0';
}

//新元素入队
Status EnQueue(SqQueue &Q, QElemType e){
    if(Q.rear + 1 == Q.front){
        return ERROR;
    }else{
        Q.base[Q.rear] = e;
        Q.rear = (Q.rear + 1) % MAXQSIZE;
    }
    return OK;
}

//出队
Status DeQueue(SqQueue &Q, QElemType &e){
    if(Q.rear == Q.front){
        return ERROR;
    }else{
        e = Q.base[Q.front];
        Q.front = (Q.front + 1) % MAXQSIZE;
    }
    return OK;
}

//从队头到队尾，依次访问队列元素
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


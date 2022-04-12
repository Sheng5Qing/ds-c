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
typedef char SElemType;    //栈元素类型

/*
链栈是运算受限的单链表，只能在链表头部进行操作
链表的头指针就是栈顶
不需要头结点
基本不存在栈满的情况
空栈相当于头指针指向空
插入和删除仅在栈顶处执行
*/
typedef struct StackNode{
    SElemType data;
    struct StackNode* next;
}StackNode,*LinkStack;

//链栈的初始化
Status InitStack(LinkStack &S);

//判断链栈是否为空
Status StackEmpty(LinkStack S);

//链栈的入栈
Status Push(LinkStack &S, SElemType e);

//链栈的出栈
Status Pop(LinkStack &S, SElemType &e);

//取栈顶元素
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

//链栈的初始化
Status InitStack(LinkStack &S){
    S = NULL;
    return OK;
}

//判断链栈是否为空
Status StackEmpty(LinkStack S){
    if(S == NULL) return TRUE;
    else return FAlSE;
}

//链栈的入栈
Status Push(LinkStack &S, SElemType e){
    StackNode* p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK; 
}

//链栈的出栈
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

//取栈顶元素
Status GetTop(LinkStack S){
    if(S != NULL){
        return S->data;
    }
}


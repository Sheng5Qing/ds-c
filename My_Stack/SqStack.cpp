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

#define MAXSIZE 100  //顺序栈存储空间
/*
base为栈底指针，初始化完成后，栈底指针base始终指向栈底的位置，若base的值为NULL，则说明栈结构不存在
top为栈顶指针，其初值指向栈底。每当插入新元素，top指针加1；删除栈顶元素时，top指针减1
栈空时，top和base的值相等；栈非空时，top指针始终指向栈顶元素上一个位置
*/
typedef struct SqStack{
    SElemType* base; //栈底指针
    SElemType* top;  //栈顶指针
    int stacksize;  //栈可用最大容量
}SqStack;

//顺序栈的初始化
Status InitStack(SqStack &S);

//判断栈空
Status StackEmpty(SqStack S);

//清空顺序栈
Status ClearStack(SqStack S);

//销毁顺序栈
Status DestoryStack(SqStack &S);

//顺序栈的入栈
Status Push(SqStack &S,SElemType e);

//顺序表出栈
Status Pop(SqStack &S,SElemType &e);

//取栈顶元素
SElemType GetTop(SqStack S);


int main(){
    SqStack s;
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

//顺序栈的初始化
/*
1、为顺序栈动态分配一个最大容量为MAXSIZE的数组空间，使栈底指针base指向这段空间的基地址
2、栈顶指针top初始化为top，表示栈为空
2、将stacksize置为栈的最大容量MAXSIZE
*/
Status InitStack(SqStack &S){
    S.base = new SElemType[MAXSIZE];  //为顺序栈动态分配一个MAXSIZE的空间
    if(!S.base) exit(OVERFLOW);  //存储分配失败
    S.top = S.base;  //空栈
    S.stacksize = MAXSIZE;  //stacksize置为顺序栈最大容量
    return OK;
}

//判断栈空
Status StackEmpty(SqStack S){
    if(S.base == S.top){
        return OK;
    }
    else{
        return ERROR;
    }
}

//清空顺序栈
Status ClearStack(SqStack S){
    if(S.base) S.top = S.base;
    return OK;
}

//销毁顺序栈
Status DestoryStack(SqStack &S){
    if(S.base){
        delete S.base;
        S.top = NULL;
        S.base = S.top;
        return OK;
    }else{
        return ERROR;
    }
    
}

//顺序栈的入栈
/*
1、判断栈是否满，若满，返回ERROR
2、将新元素压入栈中，top指针后移
*/
Status Push(SqStack &S,SElemType e){
    //两个指针相减，得到两指针之间的元素个数
    if(S.top - S.base == S.stacksize) return ERROR; //判断栈是否满
    //*S.top = e;
    //S.top++;
    *S.top++ = e;
    return OK;
}

//顺序表出栈
/*
1、判断栈是否为空
2、将栈顶元素弹出栈，top指针减1
*/
Status Pop(SqStack &S,SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

//取栈顶元素
SElemType GetTop(SqStack S){
    if(S.top != S.base)
        return *(S.top - 1);
    return '0';
}


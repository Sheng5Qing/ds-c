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
//对称矩阵
//对角矩阵
//稀疏矩阵 —— 三元组 —— 十字链表
typedef struct array{
    int* Array;  //数组名
    int n;  //维度
    int bound1;  //一维长度
    int bound2;  //二维长度
}Array;

//初始化数组
//数组，维度，各维长度
Status InitArray(Array &A, int n, int bound1, int bound2);

//销毁数组
Status DestoryArray(Array &A);

//赋值
Status Value(Array &A, int e, int index1,int index2);

int main(){
    Array a;
    InitArray(a, 2, 3, 3);
    Value(a, 5, 1, 1);
    printf("%d\n",*(a.Array + 4*sizeof(int)));
    return 0;
}

//初始化数组
//数组，维度，各维长度
Status InitArray(Array &A, int n, int bound1, int bound2){
    A.Array = new int[bound1*bound2];
    if(!A.Array) return ERROR;
    A.n = n;
    A.bound1 = bound1;
    A.bound2 = bound2;
    return OK;
}

//销毁数组
Status DestoryArray(Array &A){
    A.n = 0;
    A.bound1 = 0;
    A.bound2 = 0;
    delete A.Array;
    return OK;
}

//赋值
Status Value(Array &A, int e, int index1,int index2){
    if(!A.Array) return ERROR;
    *(A.Array + (index1 * A.bound2 + index2) * sizeof(int)) = e;
    return OK;
}



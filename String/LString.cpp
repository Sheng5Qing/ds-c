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

#define CHUNKSIZE 80 //块链字符串块的大小
typedef struct Chunk
{
    char ch[CHUNKSIZE];
    struct Chunk* next;
}Chunk;

typedef struct{
    Chunk *head, *tail;  //串的头指针和尾指针
    int curlen;  //串的当前长度
}LString;  //字符串的块链结构
/*使用块链结构可以增加串的存储密度
本结构密度 = CHUNKSIZE/(CHUNKSIZE + 4)
*/

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

#define CHUNKSIZE 80 //�����ַ�����Ĵ�С
typedef struct Chunk
{
    char ch[CHUNKSIZE];
    struct Chunk* next;
}Chunk;

typedef struct{
    Chunk *head, *tail;  //����ͷָ���βָ��
    int curlen;  //���ĵ�ǰ����
}LString;  //�ַ����Ŀ����ṹ
/*ʹ�ÿ����ṹ�������Ӵ��Ĵ洢�ܶ�
���ṹ�ܶ� = CHUNKSIZE/(CHUNKSIZE + 4)
*/

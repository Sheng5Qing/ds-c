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

#define MAXSIZE 100  //˳��ջ�洢�ռ�
/*
baseΪջ��ָ�룬��ʼ����ɺ�ջ��ָ��baseʼ��ָ��ջ�׵�λ�ã���base��ֵΪNULL����˵��ջ�ṹ������
topΪջ��ָ�룬���ֵָ��ջ�ס�ÿ��������Ԫ�أ�topָ���1��ɾ��ջ��Ԫ��ʱ��topָ���1
ջ��ʱ��top��base��ֵ��ȣ�ջ�ǿ�ʱ��topָ��ʼ��ָ��ջ��Ԫ����һ��λ��
*/
typedef struct SqStack{
    SElemType* base; //ջ��ָ��
    SElemType* top;  //ջ��ָ��
    int stacksize;  //ջ�����������
}SqStack;

//˳��ջ�ĳ�ʼ��
Status InitStack(SqStack &S);

//�ж�ջ��
Status StackEmpty(SqStack S);

//���˳��ջ
Status ClearStack(SqStack S);

//����˳��ջ
Status DestoryStack(SqStack &S);

//˳��ջ����ջ
Status Push(SqStack &S,SElemType e);

//˳����ջ
Status Pop(SqStack &S,SElemType &e);

//ȡջ��Ԫ��
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

//˳��ջ�ĳ�ʼ��
/*
1��Ϊ˳��ջ��̬����һ���������ΪMAXSIZE������ռ䣬ʹջ��ָ��baseָ����οռ�Ļ���ַ
2��ջ��ָ��top��ʼ��Ϊtop����ʾջΪ��
2����stacksize��Ϊջ���������MAXSIZE
*/
Status InitStack(SqStack &S){
    S.base = new SElemType[MAXSIZE];  //Ϊ˳��ջ��̬����һ��MAXSIZE�Ŀռ�
    if(!S.base) exit(OVERFLOW);  //�洢����ʧ��
    S.top = S.base;  //��ջ
    S.stacksize = MAXSIZE;  //stacksize��Ϊ˳��ջ�������
    return OK;
}

//�ж�ջ��
Status StackEmpty(SqStack S){
    if(S.base == S.top){
        return OK;
    }
    else{
        return ERROR;
    }
}

//���˳��ջ
Status ClearStack(SqStack S){
    if(S.base) S.top = S.base;
    return OK;
}

//����˳��ջ
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

//˳��ջ����ջ
/*
1���ж�ջ�Ƿ���������������ERROR
2������Ԫ��ѹ��ջ�У�topָ�����
*/
Status Push(SqStack &S,SElemType e){
    //����ָ��������õ���ָ��֮���Ԫ�ظ���
    if(S.top - S.base == S.stacksize) return ERROR; //�ж�ջ�Ƿ���
    //*S.top = e;
    //S.top++;
    *S.top++ = e;
    return OK;
}

//˳����ջ
/*
1���ж�ջ�Ƿ�Ϊ��
2����ջ��Ԫ�ص���ջ��topָ���1
*/
Status Pop(SqStack &S,SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

//ȡջ��Ԫ��
SElemType GetTop(SqStack S){
    if(S.top != S.base)
        return *(S.top - 1);
    return '0';
}


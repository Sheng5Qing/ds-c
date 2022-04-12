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
//�Գƾ���
//�ԽǾ���
//ϡ����� ���� ��Ԫ�� ���� ʮ������
typedef struct array{
    int* Array;  //������
    int n;  //ά��
    int bound1;  //һά����
    int bound2;  //��ά����
}Array;

//��ʼ������
//���飬ά�ȣ���ά����
Status InitArray(Array &A, int n, int bound1, int bound2);

//��������
Status DestoryArray(Array &A);

//��ֵ
Status Value(Array &A, int e, int index1,int index2);

int main(){
    Array a;
    InitArray(a, 2, 3, 3);
    Value(a, 5, 1, 1);
    printf("%d\n",*(a.Array + 4*sizeof(int)));
    return 0;
}

//��ʼ������
//���飬ά�ȣ���ά����
Status InitArray(Array &A, int n, int bound1, int bound2){
    A.Array = new int[bound1*bound2];
    if(!A.Array) return ERROR;
    A.n = n;
    A.bound1 = bound1;
    A.bound2 = bound2;
    return OK;
}

//��������
Status DestoryArray(Array &A){
    A.n = 0;
    A.bound1 = 0;
    A.bound2 = 0;
    delete A.Array;
    return OK;
}

//��ֵ
Status Value(Array &A, int e, int index1,int index2){
    if(!A.Array) return ERROR;
    *(A.Array + (index1 * A.bound2 + index2) * sizeof(int)) = e;
    return OK;
}



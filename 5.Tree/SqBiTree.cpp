#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //������

// ����������������ΪTElemType
typedef char TElemType;
// ��������˳��洢��ʾ
#define MAXSIZE 100
// ������һ��Ԫ������ΪTElemType������MAXSIZE��Ԫ�ص���������SqBiTree
// �����������Ľ���α��
typedef TElemType SqBiTree[MAXSIZE];
SqBiTree bt;
/*
�洢�ܶȵͣ��ռ��˷�����
ֻ�ʺ�������������ȫ������
*/

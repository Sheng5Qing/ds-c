/*ͼ��ʮ������洢�ṹ*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_typeinfo.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //����״̬
/*
�ʺ�����ͼ�����ڽӱ�����ڽӱ�������
�������Ķ���������
*/
/*----����ͼ��ʮ������洢�ṹ----*/
typedef char VerTexType;            //�������������Ϊ�ַ���
typedef int ArcType;                //����ߵ�Ȩֵ����Ϊ����
typedef int InfoType;              //�ͱ���ص�������Ϣ
#define MAX_VERTEX_NUM 20
typedef struct ArcBox{
    int tailvext,headvex;               //�û���β��ͷ�����λ��
    struct ArcBox *hlink,*tlink;        //�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
    InfoType *info;                     //�������Ϣ��ָ��
}ArcBox;
typedef struct VexNode{
    VerTexType data;                    
    ArcBox *firstin,*firstout;          //�ֱ�ָ��ö���ĵ�һ���뻡�ͳ���
}VexNode;
typedef struct{
    VexNode xlist[MAX_VERTEX_NUM];      //��ͷ����
    int vexnum,arcnum;                  //����ͼ��ǰ�Ķ������뻡��
}OLGraph;


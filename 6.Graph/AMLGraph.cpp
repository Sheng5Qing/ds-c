/*ͼ���ڽӶ��ر��洢�ṹ*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //����״̬
/*
�ʺ�����ͼ
���ÿ���ߴ洢��������
*/
/*----����ͼ���ڽӶ��ر�洢�ṹ----*/
typedef char VerTexType;            //�������������Ϊ�ַ���
typedef int ArcType;                //����ߵ�Ȩֵ����Ϊ����
typedef int InfoType;               //�ͱ���ص�������Ϣ
#define MAX_VERTEX_NUM 20
typedef enum{unvisited,visited} VisitIf;
typedef struct EBox{
    VisitIf mark;                   //��־�򣬱�Ǵ˱��Ƿ�������
    int ivex,jvex;                  //�ñ����������������λ��
    struct EBox *ilink,*jlink;      //ָ��������ivex����һ���ߺ�ָ��������jvex����һ����
    InfoType *info;                 //�ñߵ���Ϣָ��
}EBox;
typedef struct VexBox{
    VerTexType data;
    EBox *firstedge;                //ָ���һ�������ö���ı�
}VexBox;
typedef struct AMLGraph{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,edgenum;             //����ͼ��ǰ�������ͱ���
}AMLGraph;
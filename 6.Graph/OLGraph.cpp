/*图的十字链表存储结构*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_typeinfo.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //返回状态
/*
适合有向图，把邻接表和逆邻接表结合起来
解决求结点的度困难问题
*/
/*----有向图的十字链表存储结构----*/
typedef char VerTexType;            //顶点的数据类型为字符型
typedef int ArcType;                //假设边的权值类型为整型
typedef int InfoType;              //和边相关的其他信息
#define MAX_VERTEX_NUM 20
typedef struct ArcBox{
    int tailvext,headvex;               //该弧的尾和头顶点的位置
    struct ArcBox *hlink,*tlink;        //分别为弧头相同和弧尾相同的弧的链域
    InfoType *info;                     //弧相关信息的指针
}ArcBox;
typedef struct VexNode{
    VerTexType data;                    
    ArcBox *firstin,*firstout;          //分别指向该顶点的第一条入弧和出弧
}VexNode;
typedef struct{
    VexNode xlist[MAX_VERTEX_NUM];      //表头变量
    int vexnum,arcnum;                  //有向图当前的顶点数与弧数
}OLGraph;


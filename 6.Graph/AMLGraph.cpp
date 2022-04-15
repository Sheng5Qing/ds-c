/*图的邻接多重表表存储结构*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //返回状态
/*
适合无向图
解决每条边存储两遍问题
*/
/*----有向图的邻接多重表存储结构----*/
typedef char VerTexType;            //顶点的数据类型为字符型
typedef int ArcType;                //假设边的权值类型为整型
typedef int InfoType;               //和边相关的其他信息
#define MAX_VERTEX_NUM 20
typedef enum{unvisited,visited} VisitIf;
typedef struct EBox{
    VisitIf mark;                   //标志域，标记此边是否被搜索过
    int ivex,jvex;                  //该边依附的两个顶点的位置
    struct EBox *ilink,*jlink;      //指向依附于ivex的下一条边和指向依附于jvex的下一条边
    InfoType *info;                 //该边的信息指针
}EBox;
typedef struct VexBox{
    VerTexType data;
    EBox *firstedge;                //指向第一条依附该顶点的边
}VexBox;
typedef struct AMLGraph{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,edgenum;             //无向图当前顶点数和边数
}AMLGraph;
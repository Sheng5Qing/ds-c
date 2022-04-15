/*图的邻接表存储方式*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //返回状态
/*邻接表表示法的优缺点：
优点：
·便于增加和删除顶点
·便于统计边的数目，按照顶点表依次扫描所有边表即可，时间复杂度为O(n + e)
·空间效率高，空间复杂度为O(n + e))适合表示稀疏图
    n为顶点表结点数，e为边表节点数
缺点：
·不方便随机判断顶点之间是否有边，需要扫描边表，最坏时间复杂度为O(n)
·不方便计算有向图各个顶点的度，求入度需要遍历各个顶点的边表
*/


/*----图的邻接表存储表示----*/
#define MVNum 100                   //最大顶点值
typedef char VerTexType;            //顶点的数据类型为字符型
typedef int ArcType;                //假设边的权值类型为整型
typedef int OtherInfo;              //和边相关的其他信息
//定义边结点
typedef struct ArcNode{
    int adjvex;                     //该边所指向的顶点的位置
    struct ArcNode* nextarc;        //指向下一条边的指针
    OtherInfo info;                 //和边相关的其他信息
}ArcNode;
//顶点表
typedef struct VNode{
    VerTexType data;                //顶点信息
    ArcNode* firstarc;              //指向第一条依附于该顶点的边的指针
}VNode,AdjList[MVNum];              //AdhList表示邻接表类型，定义邻接表为AdjList v
//图的结构类型
typedef struct{
    AdjList vertices;               //顶点数组
    int vexnum,arcnum;              //图当前的顶点数和边数
}ALGraph;

//定位顶点下标
int LocsteVex(const ALGraph G, VerTexType u);

//邻接表创建无向图
Status CreateUDG(ALGraph &G);


//定位顶点下标
int LocateVex(const ALGraph G, VerTexType u){
    for(int i = 0; i < G.vexnum;i++){
        if(u == G.vertices[i].data) return i;
    }
    return -1;
}

//邻接表创建无向图
Status CreateUDG(ALGraph &G){
    //输入总顶点数，总边数
    cin>>G.vexnum>>G.arcnum;
    //初始化,建立顶点表
    for(int i = 0; i < G.vexnum; i++){
        //记录顶点值
        cin>>G.vertices[i].data;
        //初始化表头结点指针域为空
        G.vertices[i].firstarc = NULL;
    }
    //创建邻接表
    for(int k = 0; k < G.arcnum; k++){
        //输入一条边依附的两个顶点
        VerTexType v1,v2;
        cin>>v1>>v2;
        //确定两个顶点的序号i和j，建立边结点
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        //生成一个新的边结点*p1
        ArcNode* p1 = new ArcNode;
        //该边结点所指向的顶点位置为j
        p1->adjvex = j;
        //头插法把边结点插入单链表
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;
        //同理,建立有向图时把下面四行删除即可
        ArcNode* p2 = new ArcNode;
        p2->adjvex = i;
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
    }
    return OK;
}


/*图的邻接矩阵存储方式*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //返回状态

/*----图的邻接矩阵存储表示----*/
#define MaxInt 32767                //表示极大值，无限大
#define MVNum 100                   //最大顶点值
typedef char VerTexType;            //顶点的数据类型为字符型
typedef int ArcType;                //假设边的权值类型为整型
typedef struct{
    VerTexType vex[MVNum];          //顶点表
    ArcType arcs[MVNum][MVNum];     //邻接矩阵，顶点间存在边即为权值，没有则为0
    int vexnum,arcnum;              //顶点数和边数
}AMGraph;  //Adjacency Matrix Graph

//定位顶点下标
int LocsteVex(const AMGraph G, VerTexType u);
//邻接矩阵表示法创建无向网
Status CreateUDM(AMGraph &G);

int main(){

    return 0;
}

//定位顶点下标
int LocateVex(const AMGraph G, VerTexType u){
    for(int i = 0; i < G.vexnum;i++){
        if(u == G.vex[i]) return i;
    }
    return -1;
}

//邻接矩阵表示法创建无向网
/*
①输入总顶点数和边数
②依次输入点的信息存入顶点表中
③初始化邻接矩阵，使每个权值初始化为极大值
④构造邻接矩阵，依次输入每条边依附的顶点和其权值
*/
Status CreateUDM(AMGraph &G){
    //输入总顶点数和边数
    cin>>G.vexnum>>G.arcnum;
    //依次输入点的信息，存入顶点表中
    for(int i = 0; i < G.vexnum;i++){
        cin>>G.vex[i];
    }    
    //初始化邻接矩阵
    for(int i = 0; i < G.vexnum; i++){
        for(int j = 0; j < G.vexnum; j++){
            G.arcs[i][j] = MaxInt;
        }
    }
    //构造邻接矩阵
    VerTexType v1,v2;
    ArcType w;
    for(int k = 0; k < G.arcnum; k++){
        //输入每条边依附的顶点和权值
        cin>>v1>>v2>>w;
        //确定顶点在顶点数组中的下标
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        //边<v1,v2>的权值置为w
        G.arcs[i][j] = w;
        //无向图对称  
        G.arcs[j][i] = G.arcs[i][j];
    }
    return OK;
}


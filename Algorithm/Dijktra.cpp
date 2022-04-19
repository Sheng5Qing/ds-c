#include <iostream>

using namespace std;

//邻接矩阵数据结构
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
int LocateVex(const AMGraph G, VerTexType u){
    for(int i = 0; i < G.vexnum;i++){
        if(u == G.vex[i]) return i;
    }
    return -1;
}
//准备数据结构
extern ArcType dist[];      //最短路径
extern int path[];          //前驱结点的下标
extern bool flag[];         //访问标记

//Dijkstra算法
void Dijkstra(const AMGraph G, VerTexType u0){
    //定位源点下标
    int u = LocateVex(G, u0);
    //初始化操作
    for(int i = 0; i < G.vexnum; i++){
        dist[i] = G.arcs[u][i];
        flag[i] = false;
        //若无路径相连
        if(dist[i] == MaxInt){
            path[i] = -1;
        }else {
        path[i] = u;
        }
    }
    dist[u] = 0;
    flag[u] = true;
    //初始化完毕
    for(int i = 0; i < G.vexnum; i++){
        int temp = MaxInt, t = u;
        //在集合V-S中寻找距离源点最近的结点t
        for(int j = 0; j < G.vexnum; j++){
            if(!flag[j] && dist[j] < temp){
                t = j;
                temp = dist[j];
            }
        }
        //找不到直接跳出循环
        if(t == u) return;
        //找到了，将t加入集合V，继续算法
        flag[t] = true;
        for(int j = 0; j < G.vexnum; j++){
            if(!flag[j] && G.arcs[i][j] < MaxInt){
                if(dist[j] > (dist[t] + G.arcs[t][j])){
                    dist[j] = dist[t] + G.arcs[t][j];
                    path[j] = t;
                }
            }
        }
    }
}

//打印最短路径结点序列——递归
void findpath(const AMGraph G, VerTexType u0, VerTexType u1){
    int u = LocateVex(G, u0);
    int v = LocateVex(G, u1);
    if(path[v] == -1){
        cout << G.vex[v] << " ";
    }else{
        findpath(G, u0, path[v]);
        cout << G.vex[v] << " ";
    }
}

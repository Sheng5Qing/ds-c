#include <algorithm>
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
//辅助数组
int dist[MVNum][MVNum];
int path[MVNum][MVNum];
//Floyd算法
void Floyd(const AMGraph G){
    int dist[G.vexnum][G.vexnum];
    //初始化
    int i, j, k;
    for(i = 0; i < G.vexnum; i++){
        for(j = 0; j < G.vexnum; j++){
            dist[i][j] = G.arcs[i][j];
            //如果两点间有弧，则将j的前驱置为i
            if(dist[i][j] < MaxInt && i != j){
                path[i][j] = i;
            }else {//无弧，则前驱为-1
                path[i][j] = -1;
            }
        }
    }
    //初始化完毕
    for(k = 0; k < G.vexnum; k++){
        for(i = 0; i < G.vexnum; i++){
            for(j = 0; j < G.vexnum; j++){
                //如果i有一条经过k到j的更短路径
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    //更新最短路径
                    dist[i][j] = dist[i][k] + dist[k][j];
                    //更新j的前驱
                    path[i][j] = k;
                }
            }
        }
    }
}

//打印寻找最短路径
void printPath(const AMGraph G, VerTexType u0, VerTexType v0, int path[][MVNum]){
    int u = LocateVex(G,  u0);
    int v = LocateVex(G,  v0);
    if(path[u][v] == -1){
        cout << "<" << G.vex[u] << ","
        << G.vex[v] << ">";
    }else{
        int mid = path[u][v];
        printPath(G, G.vex[u], G.vex[mid], path);
        printPath(G, G.vex[mid], G.vex[v], path);
    }
}
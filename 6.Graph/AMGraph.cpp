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

//队列数据结构
typedef int QElemType;    //队列元素类型为顶点下标
#define MAXQSIZE 100  //队列可能达到的最大长度
//队列的顺序存储，实现层次遍历
typedef struct {
    QElemType* base;  //队列存储空间的基地址
    int front;  //队头指针
    int rear;  //队尾指针
}SqQueue;

//初始化顺序队列
Status InitQueue(SqQueue& Q);

//判断队空
Status QueueEmpty(SqQueue Q);

//入队
Status EnQueue(SqQueue& Q, QElemType e);

//出队
Status DeQueue(SqQueue& Q, QElemType& e);

//定位顶点下标
int LocsteVex(const AMGraph G, VerTexType u);

//邻接矩阵表示法创建无向网
Status CreateUDM(AMGraph &G);

//邻接矩阵实现深度优先搜索
void DFS(const AMGraph G,VerTexType v1);

//邻接矩阵实现广度优先搜索
void DFS(const AMGraph G,VerTexType v1);

int main(){

    return 0;
}

//初始化顺序队列
Status InitQueue(SqQueue& Q) {
    Q.base = new QElemType[MAXQSIZE];
    //Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base) exit(EOVERFLOW);
    Q.front = 0;
    Q.rear = Q.front;
    return OK;
}

//判断队空
Status QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FAlSE;
}

//入队
Status EnQueue(SqQueue& Q, QElemType e) {
    if (Q.rear + 1 == Q.front) {
        return ERROR;
    }
    else {
        Q.base[Q.rear] = e;
        Q.rear = (Q.rear + 1) % MAXQSIZE;
    }
    return OK;
}

//出队
Status DeQueue(SqQueue& Q, QElemType& e) {
    if (Q.rear == Q.front) {
        return ERROR;
    }
    else {
        e = Q.base[Q.front];
        Q.front = (Q.front + 1) % MAXQSIZE;
    }
    return OK;
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

//邻接矩阵实现深度优先搜索
void DFS(const AMGraph G,VerTexType v1){
    cout<<v1;
    //访问位标记
    int visited[MVNum] = {0};
    //找到v1下标
    int v = LocateVex(G, v1);
    //该顶点以访问
    visited[v] = 1;
    //递归实现深度优先搜索
    for(int w = 0; w < G.vexnum; w++){
        //两点之间有边，且未被访问
        if(G.arcs[v][w] != MaxInt && visited[w] == 0){
            DFS(G, G.vex[w]);        
        }
    }
}

//邻接矩阵实现广度优先搜索
void BFS(const AMGraph G,VerTexType v1){
    // 打印出发点
    cout << v1;
    //定位顶点下标
    int v = LocateVex(G,  v1);
    //设置访问标志数组
    int visited[MVNum] = {0};
    //置v1所在下标已访问
    visited[v] = 1;
    //声明队列，并初始化，用以实现广度优先搜索
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q,  v);
    //继续广度优先搜索的前提为队列非空
    while (!QueueEmpty(Q)) {
        //队头出队,声明u接收
        int u = 0;
        DeQueue(Q, u);
        //依次检查u的所有邻接点w
        for(int w = 0; w < G.vexnum; w++){
            if(G.arcs[u][w] != MaxInt && !visited[w]){
                cout << G.vex[w];
                visited[w] = 1;
                EnQueue(Q, w);
            }
        }
    }
}
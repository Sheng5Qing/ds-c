/*图的邻接矩阵存储方式*/
#include <corecrt_search.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

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

//Prim算法求最小生成树
//定义辅助数组，用来记录从顶点集U到V-U的权值最小的边
typedef struct{
    VerTexType adjvex;          //最小边在U中的那个顶点
    ArcType lowcost;            //最小边上的权值
}closedge[MVNum + 1];
void MiniSpanTree_Prim(const AMGraph G,const VerTexType u);

//Kruskal算法求最小生成树
//辅助边边权值结构体
typedef struct{
    VerTexType Head;            //边的始点
    VerTexType Tail;            //边的终点
    ArcType lowcost;            //该边上的权值
}Edge;
void MiniSpanTree_Kruskal(const AMGraph G);

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

//Prim算法
//从顶点u出发，构造G的最小生成树T，并输出T的各条边
void MiniSpanTree_Prim(const AMGraph G,const VerTexType u){
    closedge closedge;
    //找到u的下标
    int k = LocateVex(G, u);
    //初始化U,因为u本身就在U中，那么最小边就一定是0了
    closedge[k] = {u,0};                
    //对于V-U中的每一个顶点vj,初始化closedge[j]
    for(int j = 0; j < G.vexnum; j++){
        //本质上就是将V-U中所有顶点与u的边的权值赋值给辅助数组的lowcost,用于与以后的“距离”相比较
        if(j != k){
            closedge[j] = {u,G.arcs[k][j]};
        }
    }
    //最小生成树，连通n个节点，只需要n-1条边，循环n-1次
    for(int i = 1; i < G.vexnum; i++){
        //找出U中离V-U最近的顶点
        //即求出T的下一个结点：第k个顶点，closedge[k]中存有最小边
        //close[k].lowcost初值置为无限
        int k = MVNum;
        closedge[k].lowcost = MaxInt;
        for(int j = 0; j < G.vexnum; j++){
            //j所指向的顶点在V-U中，且小于当前lowcost值
            if(closedge[j].lowcost != 0 && closedge[j].lowcost < closedge[k].lowcost){
                k = j;
            }//if
        }//求最小边for
        //记u0为最小边在V中的一个顶点
        VerTexType u0 = closedge[k].adjvex;
        //v0为最小边在V-U中的另一顶点
        VerTexType v0 = G.vex[k];
        //输出当前最小边
        cout << u0  << " " << v0;
        //将第k个顶点并入U集中
        closedge[k].lowcost = 0;
        //新顶点并入U集后，旧顶点与其他顶点的最小边不变，可以从新顶点出发试探更新U与V-U的最小边
        for(int j = 0; j < G.vexnum; j++){
            //若发现新顶点与第j的距离小于辅助数组中的距离
            if(G.arcs[k][j] < closedge[j].lowcost){
                //替换最小边
                closedge[j] = {G.vex[k],G.arcs[k][j]};
            }
        }
    }
}

int cmp(const void* a, const void* b){
    //按升序排序
    return ((Edge*)a)->lowcost - ((Edge*)b)->lowcost;
}

//Kruskal算法求最小生成树
void MiniSpanTree_Kruskal(const AMGraph G){
    //初始化边数组并按权值排序
    Edge edge[G.arcnum];
    for(int i = 0; i < G.arcnum; i++){
        cin>>edge[i].Head>>edge[i].Tail>>edge[i].lowcost;
    }
    qsort(edge, G.arcnum, sizeof(Edge), cmp);
    //辅助数组，用来管理连通分量
    int Vexset[G.vexnum];
    //初始化辅助vexset数组，表示开始时所有顶点自成连通分量
    for(int i = 0; i < G.vexnum; i++){
        Vexset[i] = i;
    }
    //依次查看数组edge中所有的边
    for(int i = 0; i < G.arcnum; i++){
        //获得该边始点和终点下标
        int v1 = LocateVex(G, edge[i].Head);
        int v2 = LocateVex(G, edge[i].Tail);
        //若两点连通分量不同，则说明添加此边进去最小生成树不会形成回路
        if(Vexset[v1] != Vexset[v2]){
            //输出路径
            cout<<edge[i].Head<<" "<<edge[i].Tail;
            //合并两个分量，以防下次添加边形成回路
            for(int j = 0; j < G.vexnum; j++){
                //将当前最小生成树中连通点的vexset数组值改为一致
                if(Vexset[j] == Vexset[v2]){
                    Vexset[j] = Vexset[v1];
                }
            }
        }
    }
}
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
int LocsteVex(const ALGraph G, VerTexType u);

//邻接表创建无向图
Status CreateUDG(ALGraph &G);

//邻接表实现广度优先搜索
void DFS(const ALGraph G,VerTexType v1);

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

//邻接表实现广度优先搜索
void DFS(const ALGraph G,VerTexType v1){
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
        for (ArcNode* wptr = G.vertices[u].firstarc; !wptr; wptr = wptr->nextarc) {
            //如果该边所指向顶点未被访问，入队
            if(!visited[wptr->adjvex]){
                cout << G.vertices[wptr->adjvex].data;
                visited[wptr->adjvex] = 1;
                EnQueue(Q,  wptr->adjvex);
            }
        }
    }
}
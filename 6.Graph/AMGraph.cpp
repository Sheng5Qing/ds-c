/*ͼ���ڽӾ���洢��ʽ*/
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

typedef int Status; //����״̬

/*----ͼ���ڽӾ���洢��ʾ----*/
#define MaxInt 32767                //��ʾ����ֵ�����޴�
#define MVNum 100                   //��󶥵�ֵ
typedef char VerTexType;            //�������������Ϊ�ַ���
typedef int ArcType;                //����ߵ�Ȩֵ����Ϊ����
typedef struct{
    VerTexType vex[MVNum];          //�����
    ArcType arcs[MVNum][MVNum];     //�ڽӾ��󣬶������ڱ߼�ΪȨֵ��û����Ϊ0
    int vexnum,arcnum;              //�������ͱ���
}AMGraph;  //Adjacency Matrix Graph

//�������ݽṹ
typedef int QElemType;    //����Ԫ������Ϊ�����±�
#define MAXQSIZE 100  //���п��ܴﵽ����󳤶�
//���е�˳��洢��ʵ�ֲ�α���
typedef struct {
    QElemType* base;  //���д洢�ռ�Ļ���ַ
    int front;  //��ͷָ��
    int rear;  //��βָ��
}SqQueue;

//��ʼ��˳�����
Status InitQueue(SqQueue& Q);

//�ж϶ӿ�
Status QueueEmpty(SqQueue Q);

//���
Status EnQueue(SqQueue& Q, QElemType e);

//����
Status DeQueue(SqQueue& Q, QElemType& e);

//��λ�����±�
int LocsteVex(const AMGraph G, VerTexType u);

//�ڽӾ����ʾ������������
Status CreateUDM(AMGraph &G);

//�ڽӾ���ʵ�������������
void DFS(const AMGraph G,VerTexType v1);

//�ڽӾ���ʵ�ֹ����������
void DFS(const AMGraph G,VerTexType v1);

//Prim�㷨����С������
//���帨�����飬������¼�Ӷ��㼯U��V-U��Ȩֵ��С�ı�
typedef struct{
    VerTexType adjvex;          //��С����U�е��Ǹ�����
    ArcType lowcost;            //��С���ϵ�Ȩֵ
}closedge[MVNum + 1];
void MiniSpanTree_Prim(const AMGraph G,const VerTexType u);

//Kruskal�㷨����С������
//�����߱�Ȩֵ�ṹ��
typedef struct{
    VerTexType Head;            //�ߵ�ʼ��
    VerTexType Tail;            //�ߵ��յ�
    ArcType lowcost;            //�ñ��ϵ�Ȩֵ
}Edge;
void MiniSpanTree_Kruskal(const AMGraph G);

int main(){

    return 0;
}

//��ʼ��˳�����
Status InitQueue(SqQueue& Q) {
    Q.base = new QElemType[MAXQSIZE];
    //Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base) exit(EOVERFLOW);
    Q.front = 0;
    Q.rear = Q.front;
    return OK;
}

//�ж϶ӿ�
Status QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FAlSE;
}

//���
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

//����
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

//��λ�����±�
int LocateVex(const AMGraph G, VerTexType u){
    for(int i = 0; i < G.vexnum;i++){
        if(u == G.vex[i]) return i;
    }
    return -1;
}

//�ڽӾ����ʾ������������
/*
�������ܶ������ͱ���
��������������Ϣ���붥�����
�۳�ʼ���ڽӾ���ʹÿ��Ȩֵ��ʼ��Ϊ����ֵ
�ܹ����ڽӾ�����������ÿ���������Ķ������Ȩֵ
*/
Status CreateUDM(AMGraph &G){
    //�����ܶ������ͱ���
    cin>>G.vexnum>>G.arcnum;
    //������������Ϣ�����붥�����
    for(int i = 0; i < G.vexnum;i++){
        cin>>G.vex[i];
    }    
    //��ʼ���ڽӾ���
    for(int i = 0; i < G.vexnum; i++){
        for(int j = 0; j < G.vexnum; j++){
            G.arcs[i][j] = MaxInt;
        }
    }
    //�����ڽӾ���
    VerTexType v1,v2;
    ArcType w;
    for(int k = 0; k < G.arcnum; k++){
        //����ÿ���������Ķ����Ȩֵ
        cin>>v1>>v2>>w;
        //ȷ�������ڶ��������е��±�
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        //��<v1,v2>��Ȩֵ��Ϊw
        G.arcs[i][j] = w;
        //����ͼ�Գ�  
        G.arcs[j][i] = G.arcs[i][j];
    }
    return OK;
}

//�ڽӾ���ʵ�������������
void DFS(const AMGraph G,VerTexType v1){
    cout<<v1;
    //����λ���
    int visited[MVNum] = {0};
    //�ҵ�v1�±�
    int v = LocateVex(G, v1);
    //�ö����Է���
    visited[v] = 1;
    //�ݹ�ʵ�������������
    for(int w = 0; w < G.vexnum; w++){
        //����֮���бߣ���δ������
        if(G.arcs[v][w] != MaxInt && visited[w] == 0){
            DFS(G, G.vex[w]);        
        }
    }
}

//�ڽӾ���ʵ�ֹ����������
void BFS(const AMGraph G,VerTexType v1){
    // ��ӡ������
    cout << v1;
    //��λ�����±�
    int v = LocateVex(G,  v1);
    //���÷��ʱ�־����
    int visited[MVNum] = {0};
    //��v1�����±��ѷ���
    visited[v] = 1;
    //�������У�����ʼ��������ʵ�ֹ����������
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q,  v);
    //�����������������ǰ��Ϊ���зǿ�
    while (!QueueEmpty(Q)) {
        //��ͷ����,����u����
        int u = 0;
        DeQueue(Q, u);
        //���μ��u�������ڽӵ�w
        for(int w = 0; w < G.vexnum; w++){
            if(G.arcs[u][w] != MaxInt && !visited[w]){
                cout << G.vex[w];
                visited[w] = 1;
                EnQueue(Q, w);
            }
        }
    }
}

//Prim�㷨
//�Ӷ���u����������G����С������T�������T�ĸ�����
void MiniSpanTree_Prim(const AMGraph G,const VerTexType u){
    closedge closedge;
    //�ҵ�u���±�
    int k = LocateVex(G, u);
    //��ʼ��U,��Ϊu�������U�У���ô��С�߾�һ����0��
    closedge[k] = {u,0};                
    //����V-U�е�ÿһ������vj,��ʼ��closedge[j]
    for(int j = 0; j < G.vexnum; j++){
        //�����Ͼ��ǽ�V-U�����ж�����u�ıߵ�Ȩֵ��ֵ�����������lowcost,�������Ժ�ġ����롱��Ƚ�
        if(j != k){
            closedge[j] = {u,G.arcs[k][j]};
        }
    }
    //��С����������ͨn���ڵ㣬ֻ��Ҫn-1���ߣ�ѭ��n-1��
    for(int i = 1; i < G.vexnum; i++){
        //�ҳ�U����V-U����Ķ���
        //�����T����һ����㣺��k�����㣬closedge[k]�д�����С��
        //close[k].lowcost��ֵ��Ϊ����
        int k = MVNum;
        closedge[k].lowcost = MaxInt;
        for(int j = 0; j < G.vexnum; j++){
            //j��ָ��Ķ�����V-U�У���С�ڵ�ǰlowcostֵ
            if(closedge[j].lowcost != 0 && closedge[j].lowcost < closedge[k].lowcost){
                k = j;
            }//if
        }//����С��for
        //��u0Ϊ��С����V�е�һ������
        VerTexType u0 = closedge[k].adjvex;
        //v0Ϊ��С����V-U�е���һ����
        VerTexType v0 = G.vex[k];
        //�����ǰ��С��
        cout << u0  << " " << v0;
        //����k�����㲢��U����
        closedge[k].lowcost = 0;
        //�¶��㲢��U���󣬾ɶ����������������С�߲��䣬���Դ��¶��������̽����U��V-U����С��
        for(int j = 0; j < G.vexnum; j++){
            //�������¶������j�ľ���С�ڸ��������еľ���
            if(G.arcs[k][j] < closedge[j].lowcost){
                //�滻��С��
                closedge[j] = {G.vex[k],G.arcs[k][j]};
            }
        }
    }
}

int cmp(const void* a, const void* b){
    //����������
    return ((Edge*)a)->lowcost - ((Edge*)b)->lowcost;
}

//Kruskal�㷨����С������
void MiniSpanTree_Kruskal(const AMGraph G){
    //��ʼ�������鲢��Ȩֵ����
    Edge edge[G.arcnum];
    for(int i = 0; i < G.arcnum; i++){
        cin>>edge[i].Head>>edge[i].Tail>>edge[i].lowcost;
    }
    qsort(edge, G.arcnum, sizeof(Edge), cmp);
    //�������飬����������ͨ����
    int Vexset[G.vexnum];
    //��ʼ������vexset���飬��ʾ��ʼʱ���ж����Գ���ͨ����
    for(int i = 0; i < G.vexnum; i++){
        Vexset[i] = i;
    }
    //���β鿴����edge�����еı�
    for(int i = 0; i < G.arcnum; i++){
        //��øñ�ʼ����յ��±�
        int v1 = LocateVex(G, edge[i].Head);
        int v2 = LocateVex(G, edge[i].Tail);
        //��������ͨ������ͬ����˵����Ӵ˱߽�ȥ��С�����������γɻ�·
        if(Vexset[v1] != Vexset[v2]){
            //���·��
            cout<<edge[i].Head<<" "<<edge[i].Tail;
            //�ϲ������������Է��´���ӱ��γɻ�·
            for(int j = 0; j < G.vexnum; j++){
                //����ǰ��С����������ͨ���vexset����ֵ��Ϊһ��
                if(Vexset[j] == Vexset[v2]){
                    Vexset[j] = Vexset[v1];
                }
            }
        }
    }
}
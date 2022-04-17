/*ͼ���ڽӾ���洢��ʽ*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
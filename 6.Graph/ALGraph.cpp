/*ͼ���ڽӱ�洢��ʽ*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0

typedef int Status; //����״̬
/*�ڽӱ��ʾ������ȱ�㣺
�ŵ㣺
���������Ӻ�ɾ������
������ͳ�Ʊߵ���Ŀ�����ն��������ɨ�����б߱��ɣ�ʱ�临�Ӷ�ΪO(n + e)
���ռ�Ч�ʸߣ��ռ临�Ӷ�ΪO(n + e))�ʺϱ�ʾϡ��ͼ
    nΪ�����������eΪ�߱�ڵ���
ȱ�㣺
������������ж϶���֮���Ƿ��бߣ���Ҫɨ��߱��ʱ�临�Ӷ�ΪO(n)
���������������ͼ��������Ķȣ��������Ҫ������������ı߱�
*/


/*----ͼ���ڽӱ�洢��ʾ----*/
#define MVNum 100                   //��󶥵�ֵ
typedef char VerTexType;            //�������������Ϊ�ַ���
typedef int ArcType;                //����ߵ�Ȩֵ����Ϊ����
typedef int OtherInfo;              //�ͱ���ص�������Ϣ
//����߽��
typedef struct ArcNode{
    int adjvex;                     //�ñ���ָ��Ķ����λ��
    struct ArcNode* nextarc;        //ָ����һ���ߵ�ָ��
    OtherInfo info;                 //�ͱ���ص�������Ϣ
}ArcNode;
//�����
typedef struct VNode{
    VerTexType data;                //������Ϣ
    ArcNode* firstarc;              //ָ���һ�������ڸö���ıߵ�ָ��
}VNode,AdjList[MVNum];              //AdhList��ʾ�ڽӱ����ͣ������ڽӱ�ΪAdjList v
//ͼ�Ľṹ����
typedef struct{
    AdjList vertices;               //��������
    int vexnum,arcnum;              //ͼ��ǰ�Ķ������ͱ���
}ALGraph;

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
int LocsteVex(const ALGraph G, VerTexType u);

//�ڽӱ�������ͼ
Status CreateUDG(ALGraph &G);

//�ڽӱ�ʵ�ֹ����������
void DFS(const ALGraph G,VerTexType v1);

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
int LocateVex(const ALGraph G, VerTexType u){
    for(int i = 0; i < G.vexnum;i++){
        if(u == G.vertices[i].data) return i;
    }
    return -1;
}

//�ڽӱ�������ͼ
Status CreateUDG(ALGraph &G){
    //�����ܶ��������ܱ���
    cin>>G.vexnum>>G.arcnum;
    //��ʼ��,���������
    for(int i = 0; i < G.vexnum; i++){
        //��¼����ֵ
        cin>>G.vertices[i].data;
        //��ʼ����ͷ���ָ����Ϊ��
        G.vertices[i].firstarc = NULL;
    }
    //�����ڽӱ�
    for(int k = 0; k < G.arcnum; k++){
        //����һ������������������
        VerTexType v1,v2;
        cin>>v1>>v2;
        //ȷ��������������i��j�������߽��
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        //����һ���µı߽��*p1
        ArcNode* p1 = new ArcNode;
        //�ñ߽����ָ��Ķ���λ��Ϊj
        p1->adjvex = j;
        //ͷ�巨�ѱ߽����뵥����
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;
        //ͬ��,��������ͼʱ����������ɾ������
        ArcNode* p2 = new ArcNode;
        p2->adjvex = i;
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
    }
    return OK;
}

//�ڽӱ�ʵ�ֹ����������
void DFS(const ALGraph G,VerTexType v1){
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
        for (ArcNode* wptr = G.vertices[u].firstarc; !wptr; wptr = wptr->nextarc) {
            //����ñ���ָ�򶥵�δ�����ʣ����
            if(!visited[wptr->adjvex]){
                cout << G.vertices[wptr->adjvex].data;
                visited[wptr->adjvex] = 1;
                EnQueue(Q,  wptr->adjvex);
            }
        }
    }
}
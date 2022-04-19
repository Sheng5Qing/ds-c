#include <algorithm>
#include <iostream>

using namespace std;

//�ڽӾ������ݽṹ
#define MaxInt 32767                //��ʾ����ֵ�����޴�
#define MVNum 100                   //��󶥵�ֵ
typedef char VerTexType;            //�������������Ϊ�ַ���
typedef int ArcType;                //����ߵ�Ȩֵ����Ϊ����
typedef struct{
    VerTexType vex[MVNum];          //�����
    ArcType arcs[MVNum][MVNum];     //�ڽӾ��󣬶������ڱ߼�ΪȨֵ��û����Ϊ0
    int vexnum,arcnum;              //�������ͱ���
}AMGraph;  //Adjacency Matrix Graph

//��λ�����±�
int LocateVex(const AMGraph G, VerTexType u){
    for(int i = 0; i < G.vexnum;i++){
        if(u == G.vex[i]) return i;
    }
    return -1;
}
//��������
int dist[MVNum][MVNum];
int path[MVNum][MVNum];
//Floyd�㷨
void Floyd(const AMGraph G){
    int dist[G.vexnum][G.vexnum];
    //��ʼ��
    int i, j, k;
    for(i = 0; i < G.vexnum; i++){
        for(j = 0; j < G.vexnum; j++){
            dist[i][j] = G.arcs[i][j];
            //���������л�����j��ǰ����Ϊi
            if(dist[i][j] < MaxInt && i != j){
                path[i][j] = i;
            }else {//�޻�����ǰ��Ϊ-1
                path[i][j] = -1;
            }
        }
    }
    //��ʼ�����
    for(k = 0; k < G.vexnum; k++){
        for(i = 0; i < G.vexnum; i++){
            for(j = 0; j < G.vexnum; j++){
                //���i��һ������k��j�ĸ���·��
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    //�������·��
                    dist[i][j] = dist[i][k] + dist[k][j];
                    //����j��ǰ��
                    path[i][j] = k;
                }
            }
        }
    }
}

//��ӡѰ�����·��
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
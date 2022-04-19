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
//׼�����ݽṹ
extern ArcType dist[];      //���·��
extern int path[];          //ǰ�������±�
extern bool flag[];         //���ʱ��

//Dijkstra�㷨
void Dijkstra(const AMGraph G, VerTexType u0){
    //��λԴ���±�
    int u = LocateVex(G, u0);
    //��ʼ������
    for(int i = 0; i < G.vexnum; i++){
        dist[i] = G.arcs[u][i];
        flag[i] = false;
        //����·������
        if(dist[i] == MaxInt){
            path[i] = -1;
        }else {
        path[i] = u;
        }
    }
    dist[u] = 0;
    flag[u] = true;
    //��ʼ�����
    for(int i = 0; i < G.vexnum; i++){
        int temp = MaxInt, t = u;
        //�ڼ���V-S��Ѱ�Ҿ���Դ������Ľ��t
        for(int j = 0; j < G.vexnum; j++){
            if(!flag[j] && dist[j] < temp){
                t = j;
                temp = dist[j];
            }
        }
        //�Ҳ���ֱ������ѭ��
        if(t == u) return;
        //�ҵ��ˣ���t���뼯��V�������㷨
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

//��ӡ���·��������С����ݹ�
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

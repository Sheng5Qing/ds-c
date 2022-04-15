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

//��λ�����±�
int LocsteVex(const AMGraph G, VerTexType u);
//�ڽӾ����ʾ������������
Status CreateUDM(AMGraph &G);

int main(){

    return 0;
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


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

//��λ�����±�
int LocsteVex(const ALGraph G, VerTexType u);

//�ڽӱ�������ͼ
Status CreateUDG(ALGraph &G);


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


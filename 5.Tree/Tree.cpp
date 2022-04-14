#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //不可行

//树中数据类型为TElemType
typedef char TElemType;

//双亲表示法
//树结点结构
typedef struct PTNode{
    TElemType data;
    int parent;
}PTNode;
//树结构
#define MAXSIZE 100
typedef struct PTree{
    PTNode nodes[MAXSIZE];
    int r,n;  //根结点位置和结点个数
}PTree;
/*特点：找双亲容易，找孩子难*/ 

//孩子链表存储结构
//孩子结点结构
typedef struct CTNode{
    int child;//结点下标位置
    struct CNode* next;//下一个孩子的地址
}*ChildPtr;
//双亲结点结构
typedef struct CTBox{
    TElemType data;
    ChildPtr firstchild;//孩子链表域
}CTBox;
//树结构
typedef struct CTree{
    CTBox nodes[MAXSIZE];
    int r,n;//根节点的位置和结点个数
}CTree;

//孩子兄弟表示法（二叉树表示法）
typedef struct CSNode{
    TElemType data;
    //第一个孩子，下一个兄弟
    struct CSNode *firstchild,*nexxtsibling;
}CSNode,*CSTree;


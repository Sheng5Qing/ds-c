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

//对树进行操作时，可以将树转化为二叉树，利用二叉树的算法来对树进行操作
//以二叉链表为媒介

/*
将树转换成二叉树
①加线：在兄弟间加一连线
②抹线：对每个结点，除了其左孩子，去除其与其余孩子之间的关系
③旋转：以树的根结点（相对于其他结点）为轴心，将整树顺时针转45°
口诀：兄弟相连留长子 
*/

/*
将二叉树转换成树
①加线：若p结点是双亲结点的左孩子，则将p的右孩子，右孩子的右孩子...沿分支找到所有右孩子，都与p的双亲用线连起来
②抹线：抹掉原二叉树中双亲与右孩子之间的连线
③调整：将结点按层次排序，形成树结构
*/

/*
森林转换成二叉树
①将各棵树分别转换成二叉树
②将每棵树的根结点用线相连
③以第一棵树根结点为二叉树的根，再以根结点为轴心，顺时针旋转，构成二叉树型结构
树变二叉根相连
*/

/*
二叉树转换成森林
①抹线：将二叉树中根结点与其右孩子连线，及沿右分支搜索到的所有右孩子间的连线全部抹掉，使之变成孤立二叉树
②将孤立二叉树还原成树
去掉全部右孩线，孤立二叉再还原
*/


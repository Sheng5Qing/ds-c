#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //不可行

typedef int Status; //返回状态

// 二叉树中数据类型为TElemType
typedef char TElemType;

//二叉树的链式存储结构
typedef struct BiNode {
    TElemType data;                 //数据域
    struct BiNode* lchild, * rchild; //左右孩子指针
} BiNode, * BiTree;

//三叉树的链式存储结构
typedef struct TriNode {
    TElemType data;                          //数据域
    struct BiNode* parent, * lchild, * rchild; //父母左右孩子指针
} TriTNode, * TriTree;

typedef BiTree SElemType; //栈元素类型为二叉树
// 链栈的链式存储结构
//用以实现中序遍历的非递归算法
typedef struct StackNode {
    SElemType data;
    struct StackNode* next;
} StackNode, * LinkStack;

//链栈的初始化
Status InitStack(LinkStack& S);

//判断链栈是否为空
Status StackEmpty(LinkStack S);

//链栈的入栈
Status Push(LinkStack& S, SElemType e);

//链栈的出栈
Status Pop(LinkStack& S, SElemType& e);

typedef BiTree QElemType;    //队列元素类型为二叉树
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

/*
遍历二叉树（规定先左后右）
DLR —— 先序（根）遍历
LDR —— 中序遍历
LRD —— 后序遍历
*/

//访问二叉树
void visit(const BiTree T);

//先序遍历二叉树(递归实现)
Status PreOrderTraverse(const BiTree T);

//中序遍历二叉树(递归实现)
Status InOrderTraverse(const BiTree T);

//后序遍历二叉树(递归实现)
Status PostOrderTraverse(const BiTree T);

//中序遍历二叉树(非递归实现)
Status InOrderTraverse_Stack(const BiTree T);

//层次遍历
void LevelOrder(const BiTree T);

//先序遍历建立二叉树
Status CreateBiTree(BiTree& T);

//复制二叉树
Status CopyBiTree(const BiTree T, BiTree &NewT);

//计算二叉树的深度
int Depth(const BiTree T);

//计算二叉树结点总数
int NodeCount(const BiTree T);

//计算二叉树叶子数
int LeafCount(const BiTree T);

int main() {
    BiTree T;
    CreateBiTree(T);
    LevelOrder(T);
    return 0;
}

//链栈的初始化
Status InitStack(LinkStack& S) {
    S = NULL;
    return OK;
}

//判断链栈是否为空
Status StackEmpty(LinkStack S) {
    if (S == NULL)
        return TRUE;
    else
        return FAlSE;
}

//链栈的入栈
Status Push(LinkStack& S, SElemType e) {
    StackNode* p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

//链栈的出栈
Status Pop(LinkStack& S, SElemType& e) {
    if (S) {
        e = S->data;
        StackNode* p = S;
        S = S->next;
        delete p;
        return OK;
    }
    else {
        return ERROR;
    }
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

//访问二叉树
void visit(const BiTree T) { printf("%c\t", T->data); }

/*
先序遍历二叉树(递归实现)
若二叉树为空，则空操作
否则
（1） 访问根结点
（2） 先序遍历左子树（递归）
（3） 先序遍历右子树
其他遍历同理
*/
//时间复杂度O(n)  空间复杂度O(n)
Status PreOrderTraverse(const BiTree T) {
    if (T == NULL)
        return OK;
    else {
        visit(T); //访问根节点
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    return OK;
}

//中序遍历二叉树(递归实现)
Status InOrderTraverse(const BiTree T) {
    if (T == NULL)
        return OK;
    else {
        InOrderTraverse(T->lchild);
        visit(T);
        InOrderTraverse(T->rchild);
    }
    return OK;
}

//后序遍历二叉树(递归实现)
Status PostOrderTraverse(const BiTree T) {
    if (T == NULL)
        return OK;
    else {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T);
    }
    return OK;
}

//中序遍历二叉树(非递归实现)
Status InOrderTraverse_Stack(const BiTree T) {
    BiTree p, q;
    p = T;
    LinkStack S; //存放要访问其左节点的二叉树
    InitStack(S);
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->lchild;
        }
        else {
            Pop(S, q);
            visit(q);
            p = q->rchild;
        }
    }
    return OK;
}

//层次遍历
void LevelOrder(const BiTree T) {
    BiTree p = T;
    SqQueue qu;
    InitQueue(qu);  //初始化队列
    EnQueue(qu, T);  //根节点指针进入队列
    while (!QueueEmpty(qu)) {  //队列非空，则继续循环
        DeQueue(qu, p);  //队头出队
        visit(p);  //对队头结点进行访问
        if (p->lchild) EnQueue(qu, p->lchild);  //若左孩子非空，入队
        if (p->rchild) EnQueue(qu, p->rchild);  //若右孩子非空，入队
    }
}

//先序遍历建立二叉树
Status CreateBiTree(BiTree& T) {
    printf("Input Node:");
    char ch;
    cin >> ch;
    if (ch == '#') {
        T = NULL;
    }
    else {
        T = new BiNode;
        if (!T) return ERROR;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

//复制二叉树
Status CopyBiTree(const BiTree T, BiTree &NewT){
    //空树，递归结束
	if(T == NULL){
		NewT = NULL;
		return OK;
	}else{
		NewT = new BiNode;
		NewT->data = T->data;
        //递归复制左子树
		CopyBiTree(T->lchild, NewT->lchild);
		CopyBiTree(T->rchild, NewT->rchild);

	}
	return OK;
}

//计算二叉树的深度
int Depth(const BiTree T){
    int m,n;
    if(T == NULL) return 0;
    else{
        m = Depth(T->lchild);
        n = Depth(T->rchild);
        return m > n ? (m + 1) : (n + 1);
    }
}

//计算二叉树结点总数
int NodeCount(const BiTree T){
    if(T == NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

//计算二叉树叶子数
int LeafCount(const BiTree T){
    if(T == NULL){
        return 0;
    }else if(T->lchild == NULL && T->rchild == NULL){
        return 1;
    }else{
        return LeafCount(T->lchild) + LeafCount(T->rchild);
    }
}
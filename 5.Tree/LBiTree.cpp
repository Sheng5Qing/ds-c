#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //������

typedef int Status; //����״̬

// ����������������ΪTElemType
typedef char TElemType;

//����������ʽ�洢�ṹ
typedef struct BiNode {
    TElemType data;                 //������
    struct BiNode* lchild, * rchild; //���Һ���ָ��
} BiNode, * BiTree;

//����������ʽ�洢�ṹ
typedef struct TriNode {
    TElemType data;                          //������
    struct BiNode* parent, * lchild, * rchild; //��ĸ���Һ���ָ��
} TriTNode, * TriTree;

typedef BiTree SElemType; //ջԪ������Ϊ������
// ��ջ����ʽ�洢�ṹ
//����ʵ����������ķǵݹ��㷨
typedef struct StackNode {
    SElemType data;
    struct StackNode* next;
} StackNode, * LinkStack;

//��ջ�ĳ�ʼ��
Status InitStack(LinkStack& S);

//�ж���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S);

//��ջ����ջ
Status Push(LinkStack& S, SElemType e);

//��ջ�ĳ�ջ
Status Pop(LinkStack& S, SElemType& e);

typedef BiTree QElemType;    //����Ԫ������Ϊ������
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

/*
�������������涨������ң�
DLR ���� ���򣨸�������
LDR ���� �������
LRD ���� �������
*/

//���ʶ�����
void visit(const BiTree T);

//�������������(�ݹ�ʵ��)
Status PreOrderTraverse(const BiTree T);

//�������������(�ݹ�ʵ��)
Status InOrderTraverse(const BiTree T);

//�������������(�ݹ�ʵ��)
Status PostOrderTraverse(const BiTree T);

//�������������(�ǵݹ�ʵ��)
Status InOrderTraverse_Stack(const BiTree T);

//��α���
void LevelOrder(const BiTree T);

//�����������������
Status CreateBiTree(BiTree& T);

//���ƶ�����
Status CopyBiTree(const BiTree T, BiTree &NewT);

//��������������
int Depth(const BiTree T);

//����������������
int NodeCount(const BiTree T);

//���������Ҷ����
int LeafCount(const BiTree T);

int main() {
    BiTree T;
    CreateBiTree(T);
    LevelOrder(T);
    return 0;
}

//��ջ�ĳ�ʼ��
Status InitStack(LinkStack& S) {
    S = NULL;
    return OK;
}

//�ж���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S) {
    if (S == NULL)
        return TRUE;
    else
        return FAlSE;
}

//��ջ����ջ
Status Push(LinkStack& S, SElemType e) {
    StackNode* p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

//��ջ�ĳ�ջ
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

//���ʶ�����
void visit(const BiTree T) { printf("%c\t", T->data); }

/*
�������������(�ݹ�ʵ��)
��������Ϊ�գ���ղ���
����
��1�� ���ʸ����
��2�� ����������������ݹ飩
��3�� �������������
��������ͬ��
*/
//ʱ�临�Ӷ�O(n)  �ռ临�Ӷ�O(n)
Status PreOrderTraverse(const BiTree T) {
    if (T == NULL)
        return OK;
    else {
        visit(T); //���ʸ��ڵ�
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    return OK;
}

//�������������(�ݹ�ʵ��)
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

//�������������(�ݹ�ʵ��)
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

//�������������(�ǵݹ�ʵ��)
Status InOrderTraverse_Stack(const BiTree T) {
    BiTree p, q;
    p = T;
    LinkStack S; //���Ҫ��������ڵ�Ķ�����
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

//��α���
void LevelOrder(const BiTree T) {
    BiTree p = T;
    SqQueue qu;
    InitQueue(qu);  //��ʼ������
    EnQueue(qu, T);  //���ڵ�ָ��������
    while (!QueueEmpty(qu)) {  //���зǿգ������ѭ��
        DeQueue(qu, p);  //��ͷ����
        visit(p);  //�Զ�ͷ�����з���
        if (p->lchild) EnQueue(qu, p->lchild);  //�����ӷǿգ����
        if (p->rchild) EnQueue(qu, p->rchild);  //���Һ��ӷǿգ����
    }
}

//�����������������
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

//���ƶ�����
Status CopyBiTree(const BiTree T, BiTree &NewT){
    //�������ݹ����
	if(T == NULL){
		NewT = NULL;
		return OK;
	}else{
		NewT = new BiNode;
		NewT->data = T->data;
        //�ݹ鸴��������
		CopyBiTree(T->lchild, NewT->lchild);
		CopyBiTree(T->rchild, NewT->rchild);

	}
	return OK;
}

//��������������
int Depth(const BiTree T){
    int m,n;
    if(T == NULL) return 0;
    else{
        m = Depth(T->lchild);
        n = Depth(T->rchild);
        return m > n ? (m + 1) : (n + 1);
    }
}

//����������������
int NodeCount(const BiTree T){
    if(T == NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

//���������Ҷ����
int LeafCount(const BiTree T){
    if(T == NULL){
        return 0;
    }else if(T->lchild == NULL && T->rchild == NULL){
        return 1;
    }else{
        return LeafCount(T->lchild) + LeafCount(T->rchild);
    }
}
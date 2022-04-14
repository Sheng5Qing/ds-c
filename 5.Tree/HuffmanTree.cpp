#define _CRT_SECURE_NO_WARNINGS

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

// 哈夫曼树构造算法的实现
// 顺序存储结构 —— 一维结构数组
typedef struct{
    int weight;  //叶子的权值
    int parent,lch,rch;  //结点的双亲，左孩子，右孩子下标
}HTNode,*HuffmanTree;  //动态分配数组存储哈夫曼树
//n个叶子，数组大小为2n，使用1~2n-1的空间

//找到权重最小的两个结点
void select(HuffmanTree Hu, int i, int &s1, int &s2);

// 构造哈夫曼树
void CreateHuffmanTree(HuffmanTree &Hu, int n);

// 打印哈夫曼树
void PrintHuffman(const HuffmanTree Hu,int n);

int main(){
    HuffmanTree Hu;
    CreateHuffmanTree(Hu, 8);
    PrintHuffman(Hu, 8);
    return 0;
}

//找到权重最小的两个根结点下标位置
void select(HuffmanTree Hu, int i, int &s1, int &s2){
    //先给s1赋一个初值
    int x = 1;
    //扫描数组，找到第一个根节点
    while (x <= i)
    {
        if (Hu[x].parent == 0) {
            s1 = x;
            break;
        }
        else x++;
    }
    //扫描数组，找到s1
    for (int j = 1; j <= i; j++) {
        //若此下标是根结点且权重小于等于s1下标权重，将此下标赋值给s1
        if (Hu[j].parent == 0 && Hu[j].weight < Hu[s1].weight) {
            s1 = j;
        }
    }
    x = 1;
    while (x <= i)
    {
        //给s2赋一个不同于s2的初值
        if (x != s1 && Hu[x].parent == 0) {
            s2 = x;
            break;
        }
        else x++;
    }
    //寻找s2
    for (int j = 1; j <= i; j++) {
        //此下标不可与s1重复
        if (j != s1 && Hu[j].parent == 0 && Hu[j].weight < Hu[s2].weight) {
            s2 = j;
        }
    }
}

// 构造哈夫曼树
void CreateHuffmanTree(HuffmanTree &Hu, int n){
    if(n <= 1) return;
    //对哈夫曼树进行初始化
    int m = 2 * n - 1;
    Hu = new HTNode[m + 1];
    for(int i = 1; i <= m; i++){
        if(i <= n){
        //输入以初始化权重
        int weight;
        printf("请输入第%d位权重：",i);
        scanf("%d",&weight);
        Hu[i].weight = weight;
        }
        //将双亲孩子结点下标置0
        Hu[i].parent = 0;
        Hu[i].lch = 0;
        Hu[i].rch = 0;
    }
    //初始化完毕，开始构造哈夫曼树
    int s1,s2;  //当前森林中权重最小的两个根的下标
    for (int i = n + 1; i <= m; i++) {
        //在i之前的n个结点中找出最小的两个
        select(Hu, i - 1, s1, s2);
        //新结点权重为s1,s2权重之和
        Hu[i].weight = Hu[s1].weight + Hu[s2].weight;
        //s1,s2位置双亲结点为i
        Hu[s1].parent = i;
        Hu[s2].parent = i;
        //i结点左右孩子为s1,s2
        Hu[i].lch = s1;
        Hu[i].rch = s2;
    }
}

// 打印哈夫曼树
void PrintHuffman(const HuffmanTree Hu,int n){
    int m = 2 * n - 1;
    printf("%-10s%-10s%-10s%-10s%-10s\n","结点i","weight","parent","lchild","rchild");
    for(int i = 1; i <= m; i++){
        printf("%-10d%-10d%-10d%-10d%-10d\n",i,Hu[i].weight,Hu[i].parent,Hu[i].lch,Hu[i].rch);
    }
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//哈夫曼编码
//前缀码（避免歧义） —— 最优前缀码（总长度最短）
//1、统计字符集中每个字符在电文中出现的平均概论（概率越大，要求编码越短）
//2、利用哈夫曼树的特点：权越大的叶子离根越近；将每个字符的概率值作为权值，构造哈夫曼树。则概率越大的结点，路径越短
//3、在哈夫曼树的每个分支上标上0或1（结点的左分支标0，右分支标1）
//把从根结点到每个叶子的路径上的标号连接起来，作为该叶子代表的字符的编码
//为什么哈夫曼编码能够保证是前缀码？
//  因为没有一片树叶是另一片树叶的祖先
//为什么哈夫曼编码能保证字符编码总长最短？
//  因为哈夫曼树的带权路径长度最短，故字符编码总长最短

//哈夫曼编码表的存储表示
//由于每个哈夫曼编码是变长编码，因此使用一个指针数组来存放每个字符编码的串的首地址
typedef char** HuffmanCode;  //动态分配数组存储哈夫曼编码表

//根据哈夫曼树求哈夫曼编码
void CreateHuffmanCode(const HuffmanTree HT, HuffmanCode &HC, int n); 

int main(){
    HuffmanTree Hu;
    CreateHuffmanTree(Hu, 8);
    PrintHuffman(Hu, 8);
    return 0;
}

//文件编码和译码

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

//根据哈夫曼树求哈夫曼编码
void CreateHuffmanCode(const HuffmanTree HT, HuffmanCode &HC, int n){
    //从叶子到根逆向求每个字符的哈夫曼编码，存储在编码表中
    HC = new char*[n + 1];  //与哈夫曼树存储结构类似，第一个位置不放任何内容
    char* cd = new char[n];  //分配临时存放每个字符编码的动态数组空间，其实对于n片叶子的哈夫曼树来说，每个字符的哈夫曼编码最多有n-2位
    cd[n - 1] = '\0';  //设置结束位，方便之后编码的复制 
    for(int i = 1; i <= n; i++){  //逐个字符求哈夫曼编码
        int start = n - 1;  //start开始时指向编码结束符位置
        int c = i;  //c用以判断此节点是其双亲结点的左孩子还是右孩子
        int f = HT[i].parent;  //f指向该结点的双亲结点
        //从叶子结点开始向上回溯，直到根结点
        while (f != 0) {
            --start;  //回溯成功一次，即该字符至少有一位哈夫曼编码，start向前指一位置，用以存储该字符最后一位哈夫曼编码
            if(HT[f].lch == c) cd[start] = '0';
            else cd[start] = '1';
            //继续向上回溯
            c = f;
            f = HT[f].parent;
        }//while
        //求出第i个字符的编码
        HC[i] = new char[n - start + 1]; //为第i个字符编码分配空间，最后留一位用来结束符，否则会有未知错误
        strcpy(HC[i], &cd[start]);//将求得的编码从临时空间cd拷贝到HC中
    }//for
    delete [] cd;
}


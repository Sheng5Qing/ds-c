#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //������

//������������ΪTElemType
typedef char TElemType;

// �������������㷨��ʵ��
// ˳��洢�ṹ ���� һά�ṹ����
typedef struct{
    int weight;  //Ҷ�ӵ�Ȩֵ
    int parent,lch,rch;  //����˫�ף����ӣ��Һ����±�
}HTNode,*HuffmanTree;  //��̬��������洢��������
//n��Ҷ�ӣ������СΪ2n��ʹ��1~2n-1�Ŀռ�

//�ҵ�Ȩ����С���������
void select(HuffmanTree Hu, int i, int &s1, int &s2);

// �����������
void CreateHuffmanTree(HuffmanTree &Hu, int n);

// ��ӡ��������
void PrintHuffman(const HuffmanTree Hu,int n);

int main(){
    HuffmanTree Hu;
    CreateHuffmanTree(Hu, 8);
    PrintHuffman(Hu, 8);
    return 0;
}

//�ҵ�Ȩ����С������������±�λ��
void select(HuffmanTree Hu, int i, int &s1, int &s2){
    //�ȸ�s1��һ����ֵ
    int x = 1;
    //ɨ�����飬�ҵ���һ�����ڵ�
    while (x <= i)
    {
        if (Hu[x].parent == 0) {
            s1 = x;
            break;
        }
        else x++;
    }
    //ɨ�����飬�ҵ�s1
    for (int j = 1; j <= i; j++) {
        //�����±��Ǹ������Ȩ��С�ڵ���s1�±�Ȩ�أ������±긳ֵ��s1
        if (Hu[j].parent == 0 && Hu[j].weight < Hu[s1].weight) {
            s1 = j;
        }
    }
    x = 1;
    while (x <= i)
    {
        //��s2��һ����ͬ��s2�ĳ�ֵ
        if (x != s1 && Hu[x].parent == 0) {
            s2 = x;
            break;
        }
        else x++;
    }
    //Ѱ��s2
    for (int j = 1; j <= i; j++) {
        //���±겻����s1�ظ�
        if (j != s1 && Hu[j].parent == 0 && Hu[j].weight < Hu[s2].weight) {
            s2 = j;
        }
    }
}

// �����������
void CreateHuffmanTree(HuffmanTree &Hu, int n){
    if(n <= 1) return;
    //�Թ����������г�ʼ��
    int m = 2 * n - 1;
    Hu = new HTNode[m + 1];
    for(int i = 1; i <= m; i++){
        if(i <= n){
        //�����Գ�ʼ��Ȩ��
        int weight;
        printf("�������%dλȨ�أ�",i);
        scanf("%d",&weight);
        Hu[i].weight = weight;
        }
        //��˫�׺��ӽ���±���0
        Hu[i].parent = 0;
        Hu[i].lch = 0;
        Hu[i].rch = 0;
    }
    //��ʼ����ϣ���ʼ�����������
    int s1,s2;  //��ǰɭ����Ȩ����С�����������±�
    for (int i = n + 1; i <= m; i++) {
        //��i֮ǰ��n��������ҳ���С������
        select(Hu, i - 1, s1, s2);
        //�½��Ȩ��Ϊs1,s2Ȩ��֮��
        Hu[i].weight = Hu[s1].weight + Hu[s2].weight;
        //s1,s2λ��˫�׽��Ϊi
        Hu[s1].parent = i;
        Hu[s2].parent = i;
        //i������Һ���Ϊs1,s2
        Hu[i].lch = s1;
        Hu[i].rch = s2;
    }
}

// ��ӡ��������
void PrintHuffman(const HuffmanTree Hu,int n){
    int m = 2 * n - 1;
    printf("%-10s%-10s%-10s%-10s%-10s\n","���i","weight","parent","lchild","rchild");
    for(int i = 1; i <= m; i++){
        printf("%-10d%-10d%-10d%-10d%-10d\n",i,Hu[i].weight,Hu[i].parent,Hu[i].lch,Hu[i].rch);
    }
}
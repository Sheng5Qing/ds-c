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

//����������
//ǰ׺�루�������壩 ���� ����ǰ׺�루�ܳ�����̣�
//1��ͳ���ַ�����ÿ���ַ��ڵ����г��ֵ�ƽ�����ۣ�����Խ��Ҫ�����Խ�̣�
//2�����ù����������ص㣺ȨԽ���Ҷ�����Խ������ÿ���ַ��ĸ���ֵ��ΪȨֵ��������������������Խ��Ľ�㣬·��Խ��
//3���ڹ���������ÿ����֧�ϱ���0��1���������֧��0���ҷ�֧��1��
//�ѴӸ���㵽ÿ��Ҷ�ӵ�·���ϵı��������������Ϊ��Ҷ�Ӵ�����ַ��ı���
//Ϊʲô�����������ܹ���֤��ǰ׺�룿
//  ��Ϊû��һƬ��Ҷ����һƬ��Ҷ������
//Ϊʲô�����������ܱ�֤�ַ������ܳ���̣�
//  ��Ϊ���������Ĵ�Ȩ·��������̣����ַ������ܳ����

//�����������Ĵ洢��ʾ
//����ÿ�������������Ǳ䳤���룬���ʹ��һ��ָ�����������ÿ���ַ�����Ĵ����׵�ַ
typedef char** HuffmanCode;  //��̬��������洢�����������

//���ݹ������������������
void CreateHuffmanCode(const HuffmanTree HT, HuffmanCode &HC, int n); 

int main(){
    HuffmanTree Hu;
    CreateHuffmanTree(Hu, 8);
    PrintHuffman(Hu, 8);
    return 0;
}

//�ļ����������

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

//���ݹ������������������
void CreateHuffmanCode(const HuffmanTree HT, HuffmanCode &HC, int n){
    //��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ������
    HC = new char*[n + 1];  //����������洢�ṹ���ƣ���һ��λ�ò����κ�����
    char* cd = new char[n];  //������ʱ���ÿ���ַ�����Ķ�̬����ռ䣬��ʵ����nƬҶ�ӵĹ���������˵��ÿ���ַ��Ĺ��������������n-2λ
    cd[n - 1] = '\0';  //���ý���λ������֮�����ĸ��� 
    for(int i = 1; i <= n; i++){  //����ַ������������
        int start = n - 1;  //start��ʼʱָ����������λ��
        int c = i;  //c�����жϴ˽ڵ�����˫�׽������ӻ����Һ���
        int f = HT[i].parent;  //fָ��ý���˫�׽��
        //��Ҷ�ӽ�㿪ʼ���ϻ��ݣ�ֱ�������
        while (f != 0) {
            --start;  //���ݳɹ�һ�Σ������ַ�������һλ���������룬start��ǰָһλ�ã����Դ洢���ַ����һλ����������
            if(HT[f].lch == c) cd[start] = '0';
            else cd[start] = '1';
            //�������ϻ���
            c = f;
            f = HT[f].parent;
        }//while
        //�����i���ַ��ı���
        HC[i] = new char[n - start + 1]; //Ϊ��i���ַ��������ռ䣬�����һλ�������������������δ֪����
        strcpy(HC[i], &cd[start]);//����õı������ʱ�ռ�cd������HC��
    }//for
    delete [] cd;
}


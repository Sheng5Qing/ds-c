#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1//������

typedef int Status;       //����״̬
/*
һ��ʹ��˳��洢�ṹ����Ϊʵ�����ڶԴ����в���ʱ�����ٻ��в��룬ɾ����һ��Ϊ��ѯ
*/
#define MAXLEN 255

typedef struct{
    char ch[MAXLEN + 1];  //����0��λ��ʹ�ã��������
    int length;  //����ǰ����
}SString;  //˳���ַ���

//�����ַ���
Status StrAssign(SString &T, char chars[]);

//�����ַ���
Status StrCopy(SString &T, const SString S);

//�ַ����п�
Status StrEmpty(const SString S);

//�ַ�������
int StrLength(const SString S);

//����ַ���
Status ClearString(SString &S);

//�ַ�������
Status Contact(SString &T, const SString S1, const SString S2);

//�ַ����ָ�
//���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
Status SubString(SString &Sub, const SString S, int pos, int len);

//��ӡ�ַ���
void PrintStr(const SString S);

//����ģʽƥ���㷨����BF�㷨
int Index_BF(const SString S, const SString T);
//KMP�㷨

//������S�д����봮Tֵ��ͬ���Ӵ����򷵻���������S�е�pos���ַ�֮���һ�γ��ֵ�λ�ã����򷵻�0
int Index(const SString S, const SString T, int pos);

//��V�滻����S��������T��ȵĲ��ص����Ӵ�
Status Replace(SString &S, const SString T, const SString V);

//�ڴ�S�е�pos���ַ�֮ǰ���봮T
Status StrInsert(SString &S, int pos, const SString T);

//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
Status StrDelete(SString &S, int pos, int len);

//�����ַ���
Status DeleteString(SString &S);

int main(){
    SString s1;
    SString s2;
    char p[] = "hello";
    StrAssign(s1,p);
    StrCopy(s2,s1);
    //���ӣ�char*���ᱨ�������ISO C++ forbids converting a string constant to 'char*'
    //StrAssign(s,(char*)"hello");
    PrintStr(s1);
    printf("\n");
    PrintStr(s2);
    printf("\n");
    SString index1;
    StrAssign(index1,(char*)"aaaaab");
    SString index2;
    StrAssign(index2,(char*)"aaab");
    //��ʹ�����������ն��޷�����
    printf("\"aaab\" is positioned in the %d positon of \"aaaaab\"",Index_BF(index1,index2));
    
    return 0;
}

//�����ַ���
Status StrAssign(SString &T,char chars[]){
    T.length = 0;
    int i = 1;
    while(chars[i - 1] != '\0'){
        T.ch[i] = chars[i - 1];
        i++;
        T.length++;
    }
    return OK;
}

//�����ַ���
Status StrCopy(SString &T, const SString S){
    if(S.length == 0) return ERROR;
    for(int i = 1; i <= S.length; i++){
        T.ch[i] = S.ch[i];
    }
    T.length = S.length;
    return OK;
}

//�ַ����п�
Status StrEmpty(const SString S){
    if(S.length == 0) return TRUE;
    else return FAlSE;
}

//����ַ���
Status ClearString(SString &S){
    for(int i = 1; i <= S.length; i++){
        S.ch[i] = '\0';
    }
    return OK;
}

//�ַ�������
Status Contact(SString &T, const SString S1, const SString S2){
    if(S2.length == 0) return ERROR;
    StrCopy(T,S1);
    int j = 1;
    for(int i = T.length + 1; i <= T.length + 1 + S2.length; i++){
        T.ch[i] = S2.ch[j++];
    }
    return OK;
}

//�ַ����ָ�
//���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
Status SubString(SString &Sub, const SString S, int pos, int len){
    if(S.length == 0)  return ERROR;
    int j = 1;
    for(int i = pos; i <= pos + len; i++){
        Sub.ch[j++] = S.ch[i];
    }
    return OK;
}

//��ӡ�ַ���
void PrintStr(const SString S){
    for(int i = 1; i <= S.length + 1; i++){
        printf("%c", S.ch[i]);
    }
}

//����ģʽƥ���㷨����BF�㷨
int Index_BF(const SString S, const SString T){
    int i = 1;  //��S���α�
    int j = 1;  //��T���α�
    while(T.ch[j] != '\0'){
        if(S.ch[i] == T.ch[j]){  //��ƥ�䣬��i,j�α�ǰ��
            i++;
            j++;
        }else{  //����ƥ�䣬i�����ϴ�λ�õ���һλ��j���һλ
            i = i - j + 2;
            j = 1;
            if(i > S.length - T.length + 1){  //������S�ַ���ʣ�೤��С��T�ַ������ȣ����ʾ��ƥ�䣬����0
                return 0;
            }
        }
    }
    return (i - T.length);  //����ƥ�䵽��λ��
}
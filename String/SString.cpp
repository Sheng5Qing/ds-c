#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1//不可行
#define OVERFLOW -2 //溢出

typedef int Status;       //返回状态
/*
一般使用顺序存储结构，因为实际上在对串进行操作时，很少会有插入，删除。一般为查询
*/
#define MAXLEN 255

typedef struct{
    char ch[MAXLEN + 1];  //数组0号位不使用，方便操作
    int length;  //串当前长度
}SString;  //顺序字符串

//生成字符串
Status StrAssign(SString &T, char chars[]);

//复制字符串
Status StrCopy(SString &T, const SString S);

//字符串判空
Status StrEmpty(const SString S);

//字符串长度
int StrLength(const SString S);

//清空字符串
Status ClearString(SString &S);

//字符串连接
Status Contact(SString &T, const SString S1, const SString S2);

//字符串分割
//返回串S的第pos个字符起长度为len的子串
Status SubString(SString &Sub, const SString S, int pos, int len);

//打印字符串
void PrintStr(const SString S);

//串的模式匹配算法——BF算法

//KMP算法

//若主串S中存在与串T值相同的子串，则返回它在主串S中第pos个字符之后第一次出现的位置；否则返回0
int Index(const SString S, const SString T, int pos);

//用V替换主串S中所有与T相等的不重叠的子串
Status Replace(SString &S, const SString T, const SString V);

//在串S中第pos个字符之前插入串T
Status StrInsert(SString &S, int pos, const SString T);

//从串S中删除第pos个字符起长度为len的子串
Status StrDelete(SString &S, int pos, int len);

//销毁字符串
Status DeleteString(SString &S);

int main(){
    SString s1;
    SString s2;
    char p[] = "hello";
    StrAssign(s1,p);
    StrCopy(s2,s1);
    //不加（char*）会报编译错误：ISO C++ forbids converting a string constant to 'char*'
    //StrAssign(s,(char*)"hello");
    PrintStr(s1);
    printf("\n");
    PrintStr(s2);
    
    return 0;
}

//生成字符串
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

//复制字符串
Status StrCopy(SString &T, const SString S){
    if(S.length == 0) return ERROR;
    for(int i = 1; i <= S.length; i++){
        T.ch[i] = S.ch[i];
    }
    T.length = S.length;
    return OK;
}

//字符串判空
Status StrEmpty(const SString S){
    if(S.length == 0) return TRUE;
    else return FAlSE;
}

//清空字符串
Status ClearString(SString &S){
    for(int i = 1; i <= S.length; i++){
        S.ch[i] = '\0';
    }
}

//字符串连接
Status Contact(SString &T, const SString S1, const SString S2){
    if(S2.length == 0) return ERROR;
    StrCopy(T,S1);
    int j = 1;
    for(int i = T.length + 1; i <= T.length + 1 + S2.length; i++){
        T.ch[i] = S2.ch[j++];
    }
    return OK;
}

//字符串分割
//返回串S的第pos个字符起长度为len的子串
Status SubString(SString &Sub, const SString S, int pos, int len){
    if(S.length == 0)  return ERROR;
    int j = 1;
    for(int i = pos; i <= pos + len; i++){
        Sub.ch[j++] = S.ch[i];
    }
    return OK;
}

//打印字符串
void PrintStr(const SString S){
    for(int i = 1; i <= S.length + 1; i++){
        printf("%c", S.ch[i]);
    }
}
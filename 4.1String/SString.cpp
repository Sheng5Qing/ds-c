#include <iterator>
#include <stdint.h>
#include <string.h>
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

typedef int Status; //返回状态
/*
一般使用顺序存储结构，因为实际上在对串进行操作时，很少会有插入，删除。一般为查询
*/
#define MAXLEN 255

typedef struct {
  char ch[MAXLEN + 1]; //数组0号位不使用，方便操作
  int length;          //串当前长度
} SString;             //顺序字符串

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
int Index_BF(const SString S, const SString T);
// KMP算法
//计算next数组
void get_next(const SString T, int next[]);
//优化next数组
void get_nextval(const SString T, int next[], int nextval[]);

int Index_KMP(const SString S, const SString T, int pos);

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

//病毒检测算法
Status CheckVirus(const SString person, const SString virus);

int main() {
  SString s1;
  SString s2;
  char p[] = "hello";
  StrAssign(s1, p);
  StrCopy(s2, s1);
  //不加（char*）会报编译错误：ISO C++ forbids converting a string constant to
  //'char*' StrAssign(s,(char*)"hello");
  PrintStr(s1);
  printf("\n");
  PrintStr(s2);
  printf("\n");
  SString index1;
  StrAssign(index1, (char *)"aaaaab");
  SString index2;
  StrAssign(index2, (char *)"aaab");
  //若使用中文内置终端无法调试
  printf("\"aaab\" is positioned in the %d positon of \"aaaaab\"\n",
         Index_KMP(index1, index2, 1));
  //字符串替换的实现
  SString rep1;
  StrAssign(rep1, (char *)"abc");
  SString rep2;
  StrAssign(rep2, (char *)"asd");
  SString rep;
  StrAssign(rep, (char *)"wabcwabcwabcwabc");
  Replace(rep, rep1, rep2);
  PrintStr(rep);
  //字符串插入的实现
  SString add;
  StrAssign(add, (char *)"abcabcabcabc");
  SString add2;
  StrAssign(add2, (char *)"123");
  StrInsert(add, 2, add2);
  PrintStr(add);
  //字符串删除操作
  SString del;
  StrAssign(del, (char *)"helloxxxworld");
  StrDelete(del, 6, 3);
  PrintStr(del);
  //病毒检测
  SString person;
  StrAssign(person, (char *)"aaabbbba");
  SString virus;
  StrAssign(virus, (char *)"baa");
  if (CheckVirus(person, virus)) {
    printf("yes\n");
  } else {
    printf("no\n");
  }
  return 0;
}

//生成字符串
Status StrAssign(SString &T, char chars[]) {
  T.length = 0;
  int i = 1;
  while (chars[i - 1] != '\0') {
    T.ch[i] = chars[i - 1];
    i++;
    T.length++;
  }
  return OK;
}

//复制字符串
Status StrCopy(SString &T, const SString S) {
  if (S.length == 0)
    return ERROR;
  for (int i = 1; i <= S.length; i++) {
    T.ch[i] = S.ch[i];
  }
  T.length = S.length;
  return OK;
}

//字符串判空
Status StrEmpty(const SString S) {
  if (S.length == 0)
    return TRUE;
  else
    return FAlSE;
}

//字符串长度
int StrLength(const SString S) {
  if (StrEmpty(S))
    return 0;
  int i = 1;
  int count = 0;
  while (S.ch[i] != '\0') {
    count++;
  }
  return count;
}

//清空字符串
Status ClearString(SString &S) {
  for (int i = 1; i <= S.length; i++) {
    S.ch[i] = '\0';
  }
  return OK;
}

//字符串连接
Status Contact(SString &T, const SString S1, const SString S2) {
  if (S2.length == 0)
    return ERROR;
  StrCopy(T, S1);
  int j = 1;
  for (int i = T.length + 1; i <= T.length + 1 + S2.length; i++) {
    T.ch[i] = S2.ch[j++];
  }
  T.length = S1.length + S2.length;
  return OK;
}

//字符串分割
//返回串S的第pos个字符起长度为len的子串
Status SubString(SString &Sub, const SString S, int pos, int len) {
  if (S.length == 0)
    return ERROR;
  int j = 1;
  for (int i = pos; i <= pos + len; i++) {
    Sub.ch[j++] = S.ch[i];
  }
  Sub.length = len;
  return OK;
}

//打印字符串
void PrintStr(const SString S) {
  printf("\n");
  for (int i = 1; i <= S.length; i++) {
    printf("%c", S.ch[i]);
  }
}

//串的模式匹配算法——BF算法
/*
时间复杂度分析：
令n = S.length
  m = T.length
最好：比较m次
最坏：比较(n - m + 1) * m
若m << n，则算法复杂度为O(n*m)
*/
int Index_BF(const SString S, const SString T) {
  int i = 1; //串S的游标
  int j = 1; //串T的游标
  while (j <= T.length) {
    if (S.ch[i] == T.ch[j]) { //若匹配，则i,j游标前进
      i++;
      j++;
    } else { //若不匹配，i返回上次位置的下一位，j会第一位
      i = i - j + 2;
      j = 1;
      if (i >
          S.length - T.length +
              1) { //若发现S字符串剩余长度小于T字符串长度，则表示不匹配，返回0
        return 0;
      }
    }
  }
  return (i - T.length); //返回匹配到的位置
}

//网课老师写法
// int Index_BF(const SString S, const SString T){
//     int i = 1;
//     int j = 1;
//     while (i <= S.length && j <= T.length) {
//         if (S.ch[i] == T.ch[j]) { //主串和子串依次匹配下一字符
//         ++i;
//         ++j;
//         }else{ //主串，子串回溯重新开始下一次匹配
//             i = i - j + 2;
//             j = 1;
//         }
//     }
//     if(j >= T.length){
//         return  i - T.length;  //返回匹配的第一个字符下标
//     }else {
//     return 0;  //模式匹配不成功
//     }
// }

//计算next数组
//不可以声明为int &next[]，C++不允许在数组中存放引用
//因为next先和[]结合，那么声明的就是引用数组，意思是在数组中元素是引用，而引用不占内存空间，也就不能分配内存
void get_next(
    const SString T,
    int next
        []) { //这才是数组引用，存放数组的别名**补充说明见：/exercise/test.cpp
  next[1] = 0;
  int i = 1;
  int j = 0;
  while (i < T.length) {
    if (j == 0 || T.ch[i] == T.ch[j]) {
      ++i;
      ++j;
      next[i] = j;
    } else {
      j = next[j];
    }
  }
}

//优化next数组
void get_nextval(const SString T, int next[], int nextval[]) {
  nextval[1] = 0;
  for (int j = 2; j <= T.length; j++) {
    if (T.ch[next[j]] == T.ch[j]) { //如果相等，那么继续比较就没有意义了
      nextval[j] = nextval[next[j]];
    } else {
      nextval[j] = next[j];
    }
  }
}

// KMP
int Index_KMP(const SString S, const SString T, int pos) {
  int i = pos;
  int j = 1;
  int *next = new int[T.length + 1];
  int *nextval = new int[T.length + 1];
  get_next(T, next);
  get_nextval(T, next, nextval);
  while (i <= S.length && j <= T.length) {
    if (j == 0 || S.ch[i] == T.ch[j]) {
      i++;
      j++;
    } else {
      j = nextval[j];
    }
  }
  if (j >= T.length) {
    return i - T.length;
  } else {
    return 0;
  }
}

//若主串S中存在与串T值相同的子串，则返回它在主串S中第pos个字符之后第一次出现的位置；否则返回0
int Index(const SString S, const SString T, int pos) {
  int i = pos; // i从pos开始找
  int j = 1;   //串T的游标
  while (T.ch[j] != '\0') {
    if (S.ch[i] == T.ch[j]) { //若匹配，则i,j游标前进
      i++;
      j++;
    } else { //若不匹配，i返回上次位置的下一位，j会第一位
      i = i - j + 2;
      j = 1;
      if (i >
          S.length - T.length +
              1) { //若发现S字符串剩余长度小于T字符串长度，则表示不匹配，返回0
        return 0;
      }
    }
  }
  return (i - T.length); //返回匹配到的位置
}

//用V替换主串S中所有与T相等的不重叠的子串
Status Replace(SString &S, const SString T, const SString V) {
  int pos = 1;
  if (T.length != V.length || !Index_KMP(S, T, pos))
    return ERROR;
  while (Index_KMP(S, T, pos) != 0) { //只要后面存在子串即替换
    pos = Index_KMP(S, T, pos);       //下一子串起始位置
    //替换函数
    int j = 1;
    for (int i = pos; i < pos + V.length; i++) {
      S.ch[i] = V.ch[j++];
    }
  }
  return OK;
}

//在串S中第pos个字符之前插入串T
Status StrInsert(SString &S, int pos, const SString T) {
  if (pos < 1 || pos > S.length + 1)
    return ERROR;
  S.length += T.length;
  //先将待插入位置字符后移，空出插入区域
  for (int i = S.length; i >= pos + T.length; i--) {
    S.ch[i + pos] = S.ch[i];
  }
  //插入，j用以标志串T的
  int j = 1;
  for (int i = pos; i < pos + T.length; i++) {
    S.ch[i] = T.ch[j];
    j++;
  }
  return OK;
}

//从串S中删除第pos个字符起长度为len的子串
Status StrDelete(SString &S, int pos, int len) {
  if (pos < 1 || pos > S.length || len > S.length)
    return ERROR;
  int tmp = 1;
  //一个一个删除，亦可一整块的删除
  while (tmp <= len) {
    for (int i = pos; i < S.length; i++) {
      S.ch[i] = S.ch[i + 1];
    }
    tmp++;
    S.length--;
  }
  return OK;
}

//销毁字符串
Status DeleteString(SString &S) {
  if (S.length < 1)
    return ERROR;
  //将字符串全部置为空格
  for (int i = 1; i <= S.length; i++) {
    S.ch[i] = ' ';
  }
  S.length = 0;
  return OK;
}

//病毒检测算法
Status CheckVirus(const SString person, const SString virus) {
  SString Vring; //病毒环状连接
  SString Vtmp;  //从环状病毒中的临时切片，用以进行匹配
  Contact(Vring, virus, virus);
  int flag = 0;
  int start = 1;
  while (!flag) {
    SubString(Vtmp, Vring, start, virus.length);
    flag = Index_KMP(person, Vtmp, 1);
    start++;
    if (start + virus.length > Vring.length) {
      return FAlSE;
    }
  }
  return TRUE;
}
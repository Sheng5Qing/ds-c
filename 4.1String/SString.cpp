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
#define INFEASIBLE -1 //������

typedef int Status; //����״̬
/*
һ��ʹ��˳��洢�ṹ����Ϊʵ�����ڶԴ����в���ʱ�����ٻ��в��룬ɾ����һ��Ϊ��ѯ
*/
#define MAXLEN 255

typedef struct {
  char ch[MAXLEN + 1]; //����0��λ��ʹ�ã��������
  int length;          //����ǰ����
} SString;             //˳���ַ���

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
// KMP�㷨
//����next����
void get_next(const SString T, int next[]);
//�Ż�next����
void get_nextval(const SString T, int next[], int nextval[]);

int Index_KMP(const SString S, const SString T, int pos);

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

//��������㷨
Status CheckVirus(const SString person, const SString virus);

int main() {
  SString s1;
  SString s2;
  char p[] = "hello";
  StrAssign(s1, p);
  StrCopy(s2, s1);
  //���ӣ�char*���ᱨ�������ISO C++ forbids converting a string constant to
  //'char*' StrAssign(s,(char*)"hello");
  PrintStr(s1);
  printf("\n");
  PrintStr(s2);
  printf("\n");
  SString index1;
  StrAssign(index1, (char *)"aaaaab");
  SString index2;
  StrAssign(index2, (char *)"aaab");
  //��ʹ�����������ն��޷�����
  printf("\"aaab\" is positioned in the %d positon of \"aaaaab\"\n",
         Index_KMP(index1, index2, 1));
  //�ַ����滻��ʵ��
  SString rep1;
  StrAssign(rep1, (char *)"abc");
  SString rep2;
  StrAssign(rep2, (char *)"asd");
  SString rep;
  StrAssign(rep, (char *)"wabcwabcwabcwabc");
  Replace(rep, rep1, rep2);
  PrintStr(rep);
  //�ַ��������ʵ��
  SString add;
  StrAssign(add, (char *)"abcabcabcabc");
  SString add2;
  StrAssign(add2, (char *)"123");
  StrInsert(add, 2, add2);
  PrintStr(add);
  //�ַ���ɾ������
  SString del;
  StrAssign(del, (char *)"helloxxxworld");
  StrDelete(del, 6, 3);
  PrintStr(del);
  //�������
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

//�����ַ���
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

//�����ַ���
Status StrCopy(SString &T, const SString S) {
  if (S.length == 0)
    return ERROR;
  for (int i = 1; i <= S.length; i++) {
    T.ch[i] = S.ch[i];
  }
  T.length = S.length;
  return OK;
}

//�ַ����п�
Status StrEmpty(const SString S) {
  if (S.length == 0)
    return TRUE;
  else
    return FAlSE;
}

//�ַ�������
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

//����ַ���
Status ClearString(SString &S) {
  for (int i = 1; i <= S.length; i++) {
    S.ch[i] = '\0';
  }
  return OK;
}

//�ַ�������
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

//�ַ����ָ�
//���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
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

//��ӡ�ַ���
void PrintStr(const SString S) {
  printf("\n");
  for (int i = 1; i <= S.length; i++) {
    printf("%c", S.ch[i]);
  }
}

//����ģʽƥ���㷨����BF�㷨
/*
ʱ�临�Ӷȷ�����
��n = S.length
  m = T.length
��ã��Ƚ�m��
����Ƚ�(n - m + 1) * m
��m << n�����㷨���Ӷ�ΪO(n*m)
*/
int Index_BF(const SString S, const SString T) {
  int i = 1; //��S���α�
  int j = 1; //��T���α�
  while (j <= T.length) {
    if (S.ch[i] == T.ch[j]) { //��ƥ�䣬��i,j�α�ǰ��
      i++;
      j++;
    } else { //����ƥ�䣬i�����ϴ�λ�õ���һλ��j���һλ
      i = i - j + 2;
      j = 1;
      if (i >
          S.length - T.length +
              1) { //������S�ַ���ʣ�೤��С��T�ַ������ȣ����ʾ��ƥ�䣬����0
        return 0;
      }
    }
  }
  return (i - T.length); //����ƥ�䵽��λ��
}

//������ʦд��
// int Index_BF(const SString S, const SString T){
//     int i = 1;
//     int j = 1;
//     while (i <= S.length && j <= T.length) {
//         if (S.ch[i] == T.ch[j]) { //�������Ӵ�����ƥ����һ�ַ�
//         ++i;
//         ++j;
//         }else{ //�������Ӵ��������¿�ʼ��һ��ƥ��
//             i = i - j + 2;
//             j = 1;
//         }
//     }
//     if(j >= T.length){
//         return  i - T.length;  //����ƥ��ĵ�һ���ַ��±�
//     }else {
//     return 0;  //ģʽƥ�䲻�ɹ�
//     }
// }

//����next����
//����������Ϊint &next[]��C++�������������д������
//��Ϊnext�Ⱥ�[]��ϣ���ô�����ľ����������飬��˼����������Ԫ�������ã������ò�ռ�ڴ�ռ䣬Ҳ�Ͳ��ܷ����ڴ�
void get_next(
    const SString T,
    int next
        []) { //������������ã��������ı���**����˵������/exercise/test.cpp
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

//�Ż�next����
void get_nextval(const SString T, int next[], int nextval[]) {
  nextval[1] = 0;
  for (int j = 2; j <= T.length; j++) {
    if (T.ch[next[j]] == T.ch[j]) { //�����ȣ���ô�����ȽϾ�û��������
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

//������S�д����봮Tֵ��ͬ���Ӵ����򷵻���������S�е�pos���ַ�֮���һ�γ��ֵ�λ�ã����򷵻�0
int Index(const SString S, const SString T, int pos) {
  int i = pos; // i��pos��ʼ��
  int j = 1;   //��T���α�
  while (T.ch[j] != '\0') {
    if (S.ch[i] == T.ch[j]) { //��ƥ�䣬��i,j�α�ǰ��
      i++;
      j++;
    } else { //����ƥ�䣬i�����ϴ�λ�õ���һλ��j���һλ
      i = i - j + 2;
      j = 1;
      if (i >
          S.length - T.length +
              1) { //������S�ַ���ʣ�೤��С��T�ַ������ȣ����ʾ��ƥ�䣬����0
        return 0;
      }
    }
  }
  return (i - T.length); //����ƥ�䵽��λ��
}

//��V�滻����S��������T��ȵĲ��ص����Ӵ�
Status Replace(SString &S, const SString T, const SString V) {
  int pos = 1;
  if (T.length != V.length || !Index_KMP(S, T, pos))
    return ERROR;
  while (Index_KMP(S, T, pos) != 0) { //ֻҪ��������Ӵ����滻
    pos = Index_KMP(S, T, pos);       //��һ�Ӵ���ʼλ��
    //�滻����
    int j = 1;
    for (int i = pos; i < pos + V.length; i++) {
      S.ch[i] = V.ch[j++];
    }
  }
  return OK;
}

//�ڴ�S�е�pos���ַ�֮ǰ���봮T
Status StrInsert(SString &S, int pos, const SString T) {
  if (pos < 1 || pos > S.length + 1)
    return ERROR;
  S.length += T.length;
  //�Ƚ�������λ���ַ����ƣ��ճ���������
  for (int i = S.length; i >= pos + T.length; i--) {
    S.ch[i + pos] = S.ch[i];
  }
  //���룬j���Ա�־��T��
  int j = 1;
  for (int i = pos; i < pos + T.length; i++) {
    S.ch[i] = T.ch[j];
    j++;
  }
  return OK;
}

//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
Status StrDelete(SString &S, int pos, int len) {
  if (pos < 1 || pos > S.length || len > S.length)
    return ERROR;
  int tmp = 1;
  //һ��һ��ɾ�������һ�����ɾ��
  while (tmp <= len) {
    for (int i = pos; i < S.length; i++) {
      S.ch[i] = S.ch[i + 1];
    }
    tmp++;
    S.length--;
  }
  return OK;
}

//�����ַ���
Status DeleteString(SString &S) {
  if (S.length < 1)
    return ERROR;
  //���ַ���ȫ����Ϊ�ո�
  for (int i = 1; i <= S.length; i++) {
    S.ch[i] = ' ';
  }
  S.length = 0;
  return OK;
}

//��������㷨
Status CheckVirus(const SString person, const SString virus) {
  SString Vring; //������״����
  SString Vtmp;  //�ӻ�״�����е���ʱ��Ƭ�����Խ���ƥ��
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
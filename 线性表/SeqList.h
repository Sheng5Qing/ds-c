#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 //���

#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

/*
˳�����ȱ�㣺
�ŵ㣺
1. �洢�ܶȴ󣨽�㱾����ռ�洢��/���ṹ��ռ�洢����
2. ���������ȡ������һԪ��
ȱ��:
1. �ڲ��롢ɾ��ĳһԪ��ʱ����Ҫ�ƶ�����Ԫ��
2. �˷Ѵ洢�ռ�
3. ���ھ�̬�洢��ʽ������Ԫ�صĸ���������������
*/
typedef struct {
	ElemType* elem;  //�洢�ռ����ַ
	int length;
}SqList;//��sequence - ˳��˳���

//��ʼ��
Status InitList_Sq(SqList& L) {//C++���ò�����Cʹ��SqList* L
	//L.elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);//Cд��
	L.elem = new ElemType[MAXSIZE];//C++д��
	if (!L.elem) exit(OVERFLOW);                            //�洢����ʧ��
	L.length = 0;                                           //�ձ���Ϊ0
	return OK;
}

//����
void DistoryList(SqList& L) {
	if (L.elem) delete L.elem;         //���ǿգ��ͷ��ڴ�ռ�
	//free(L.elem);
}

//������Ա�
void ClearList(SqList& L) {
	L.length = 0;                      
}

//�����Ա�
int GetLength(SqList L) {//�����޸����Ա��ʲ�ʹ������
	return L.length;
}

//���Ա��п�
int IsEmpty(SqList L) {
	if (L.length == 0) return 1;
	else return 0;
}

//ȡ��(��ȡλ��i�ϵ�Ԫ��)
int GetElem(SqList L, int i, ElemType& e) {
	if (i < 1 || i>L.length) return ERROR;
	else
	{
		e = L.elem[i - 1];
		return OK;
	}
}

//˳���Ĳ���
//�ӱ��һ�˿�ʼ��������м�¼�Ĺؼ��ֺ͸���ֵ�ıȽϡ��ҵ�������Ԫ����ţ�δ�ҵ�������0
//ʱ�临�Ӷ�O(n)
int LocateElem(SqList L, ElemType e) {
	for (int i = 0; i < L.length; i++) {
		if (e == L.elem[i]) return i + 1;  //���ҳɹ�������λ��
	}
	return 0; //����ʧ�ܣ�����0
}

//˳���Ĳ���
//ʱ�临�Ӷ�O(n)
int ListInsert(SqList& L, int i, ElemType e) {
	if (i < 1 || i > L.length + 1) return ERROR;//iֵ���Ϸ�
	if (L.length == MAXSIZE) return ERROR;//�洢�ռ�����
	for (int j = L.length - 1; j >= i - 1; j--) {
		L.elem[j + 1] = L.elem[j];
	}
	L.elem[i - 1] = e;//����Ԫ��e�����i ��λ��
	L.length++;//������1
	return OK;
}

//ɾ�����Ա�L�е�i��λ��Ԫ�أ���e����
//ʱ�临�Ӷ�O(n)
Status ListDelete(SqList& L, int i) {
	if (i < 1 || i > L.length + 1) return ERROR;//iֵ���Ϸ�
	if(L.length == 0) return ERROR;
	//e = L.elem[i - 1];                         //����ɾ����Ԫ��
	for (int j = i; j < L.length; j++) {       //��ɾ��Ԫ�غ��Ԫ��ÿ����ǰλ��һλ
		L.elem[j - 1] = L.elem[j];
	}
	L.length--;                                //����1
	return OK;
}
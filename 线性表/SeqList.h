#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 //溢出

#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

/*
顺序表优缺点：
优点：
1. 存储密度大（结点本身所占存储量/结点结构所占存储量）
2. 可以随机存取表中任一元素
缺点:
1. 在插入、删除某一元素时，需要移动大量元素
2. 浪费存储空间
3. 属于静态存储形式，数据元素的个数不能自由扩充
*/
typedef struct {
	ElemType* elem;  //存储空间基地址
	int length;
}SqList;//（sequence - 顺序）顺序表

//初始化
Status InitList_Sq(SqList& L) {//C++引用操作，C使用SqList* L
	//L.elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);//C写法
	L.elem = new ElemType[MAXSIZE];//C++写法
	if (!L.elem) exit(OVERFLOW);                            //存储分配失败
	L.length = 0;                                           //空表长度为0
	return OK;
}

//销毁
void DistoryList(SqList& L) {
	if (L.elem) delete L.elem;         //若非空，释放内存空间
	//free(L.elem);
}

//清空线性表
void ClearList(SqList& L) {
	L.length = 0;                      
}

//求线性表长
int GetLength(SqList L) {//无需修改线性表，故不使用引用
	return L.length;
}

//线性表判空
int IsEmpty(SqList L) {
	if (L.length == 0) return 1;
	else return 0;
}

//取数(获取位置i上的元素)
int GetElem(SqList L, int i, ElemType& e) {
	if (i < 1 || i>L.length) return ERROR;
	else
	{
		e = L.elem[i - 1];
		return OK;
	}
}

//顺序表的查找
//从表的一端开始，逐个进行记录的关键字和给定值的比较。找到，返回元素序号，未找到，返回0
//时间复杂度O(n)
int LocateElem(SqList L, ElemType e) {
	for (int i = 0; i < L.length; i++) {
		if (e == L.elem[i]) return i + 1;  //查找成功，返回位置
	}
	return 0; //查找失败，返回0
}

//顺序表的插入
//时间复杂度O(n)
int ListInsert(SqList& L, int i, ElemType e) {
	if (i < 1 || i > L.length + 1) return ERROR;//i值不合法
	if (L.length == MAXSIZE) return ERROR;//存储空间已满
	for (int j = L.length - 1; j >= i - 1; j--) {
		L.elem[j + 1] = L.elem[j];
	}
	L.elem[i - 1] = e;//将新元素e放入第i 个位置
	L.length++;//表长增加1
	return OK;
}

//删除线性表L中第i个位置元素，用e返回
//时间复杂度O(n)
Status ListDelete(SqList& L, int i) {
	if (i < 1 || i > L.length + 1) return ERROR;//i值不合法
	if(L.length == 0) return ERROR;
	//e = L.elem[i - 1];                         //保存删除的元素
	for (int j = i; j < L.length; j++) {       //将删除元素后的元素每个向前位移一位
		L.elem[j - 1] = L.elem[j];
	}
	L.length--;                                //表长减1
	return OK;
}
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FAlSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //不可行

// 二叉树中数据类型为TElemType
typedef char TElemType;
// 二叉树的顺序存储表示
#define MAXSIZE 100
// 定义了一个元素类型为TElemType，含有MAXSIZE个元素的数组类型SqBiTree
// 按满二叉树的结点层次编号
typedef TElemType SqBiTree[MAXSIZE];
SqBiTree bt;
/*
存储密度低，空间浪费量大
只适合满二叉树和完全二叉树
*/

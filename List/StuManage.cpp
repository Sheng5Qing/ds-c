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


typedef int Status;       //返回状态

typedef struct Score {  //三科成绩
    int Chinese;
    int Math;
    int English;
}Score;

typedef struct Student {  //学生
    char id[10];
    char name[20];
    char sex[10];
    int age;
    Score score;
}Student;

typedef struct LNode {
    Student data;
    struct LNode* next; //指向本结构的指针/结点的指针域，嵌套定义
}LNode, * LinkList;//LinkList为指向结构体LNode的指针类型
/*LNode* 和LinkList本质上是等价的，这么写是为了提高程序可读性。通常习惯上用LinkList L来定义单链表，LNode* node定义结点*/

//单链表的初始化
Status InitList_L(LinkList& L) {
    L = new LNode; //或L = (LinkLIst)malloc(sizeof(LNode));
    L->next = NULL;
    return OK;
}

//求单链表的表长
int ListLength_L(LinkList L) {
    int len = 0;
    LNode* p = L->next;
    while (p) {
        p = p->next;
        len++;
    }
    return len;
}

//打印学生数据
void PrintStu(const LinkList L, int i) {
    LNode* p = L->next;
    int j = 1;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    printf("%-10s%-10s%-10d%-10s%-10d%-10d%-10d\n", p->data.name, p->data.id, p->data.age, p->data.sex, p->data.score.Chinese, p->data.score.Math, p->data.score.English);
}


//单链表尾插法增加学生记录
void CreateList_R(LinkList& L) {
    LNode* tail = L; //开始时尾指针指向头结点
    //找到尾指针
    while (tail->next) {
        tail++;
    }
    LNode* s = new LNode;
    //LNode* s = (LNode*)malloc(sizeof(LNode));
    //scanf("%c",&(s->data));
    //cin>>s->data;
    printf("请输入第%d位学生信息：\n", ListLength_L(L) + 1);
    printf("姓名：");
    scanf("%s", s->data.name);
    printf("学号：");
    scanf("%s", s->data.id);
    printf("年龄：");
    scanf("%d", &(s->data.age));
    printf("性别：");
    scanf("%s", s->data.sex);
    printf("语文成绩：");
    scanf("%d", &(s->data.score.Chinese));
    printf("数学成绩：");
    scanf("%d", &(s->data.score.Math));
    printf("英语成绩：");
    scanf("%d", &(s->data.score.English));
    s->next = NULL;  //插入到表尾
    tail->next = s;
    printf("增加成功！\n");
}

//单链表按值查找——返回位置
//找到返回元素序号，找不到返回元素位置序号
int LocateElem1_L(LinkList L, char e[]) {
    LNode* p = L->next;
    int j = 1;
    while (p && p->data.name == e) { //顺序扫描，直到p为空或p的下一结点数据域等于e
        p = p->next;
        j++;
    }
    if (p) {
        return j;
    }
    else {
        return 0;
    }

}

//单链表删除第i个结点
Status ListDelete_L(LinkList& L) {
    char e[20] = { 0 };
    int i;
    printf("请输入要删除的学生姓名：");
    scanf("%s", e);
    i = LocateElem1_L(L, e);
    LNode* p = L->next;
    int j = 1;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        printf("删除失败！\n");
        return ERROR;
    }
    delete p;
    printf("删除成功！\n");
    return OK;
}
//查找学生记录
void SearchStu(const LinkList L) {
    char e[20] = { 0 };
    int i;
    printf("请输入要查找的学生姓名：");
    scanf("%s", e);
    if (LocateElem1_L(L, e)) {
        i = LocateElem1_L(L, e);
        printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "姓名", "学号", "年龄", "性别", "语文成绩", "数学成绩", "英语成绩");
        PrintStu(L, i);
    }
    else {
        printf("查无此人！\n");
    }
}

//修改学生记录
void ModifyStu(LinkList& L) {
    char e[20] = { 0 };
    int i;
    printf("请输入要修改的学生姓名：");
    scanf("%s", e);
    if (LocateElem1_L(L, e)) {
        i = LocateElem1_L(L, e);
        LNode* p = L->next;
        int j = 1;
        while (p && j < i)
        {
            p = p->next;
            j++;
        }
        printf("请输入要修改的学生信息：\n");
        printf("姓名：");
        scanf("%s", p->data.name);
        printf("学号：");
        scanf("%s", p->data.id);
        printf("年龄：");
        scanf("%d", &(p->data.age));
        printf("性别：");
        scanf("%s", p->data.sex);
        printf("语文成绩：");
        scanf("%d", &(p->data.score.Chinese));
        printf("数学成绩：");
        scanf("%d", &(p->data.score.Math));
        printf("英语成绩：");
        scanf("%d", &(p->data.score.English));
        printf("修改成功！\n");
    }
    else {
        printf("查无此人！\n");
    }
}

//定义提示菜单
void myMenu() {
    printf("\n");
    printf(" * * * * * * * * * 菜     单 * * * * * * * * * *\n");
    printf("     1 增加学生记录            2 删除学生记录    \n");
    printf("     3 查找学生记录            4 修改学生记录    \n");
    printf("     5 统计学生人数            6 显示学生记录    \n");
    printf("     0 退出系统                                 \n");
    printf(" * * * * * * * * * * * * * * * * * * * * * * * *\n");
}



int main() {
    int input = 0;
    LinkList L;
    InitList_L(L);
    do
    {
        myMenu();
        printf("请输入选项：");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            CreateList_R(L);
            break;
        case 2:
            ListDelete_L(L);
            break;
        case 3:
            SearchStu(L);
            break;
        case 4:
            ModifyStu(L);
            break;
        case 5:
            printf("学生人数为：%d\n", ListLength_L(L) + 1);
            break;
        case 6:
            printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "姓名", "学号", "年龄", "性别", "语文成绩", "数学成绩", "英语成绩");
            for (int i = 1; i < ListLength_L(L) + 1; i++) {
                PrintStu(L, i);
            }
            break;
        case 0:
            printf("退出系统!\n");
            break;
        default:
            printf("错误操作数！\n");
            break;
        }
    } while (input);

    return 0;
}
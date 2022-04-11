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

typedef struct Score {  //���Ƴɼ�
    int Chinese;
    int Math;
    int English;
}Score;

typedef struct Student {  //ѧ��
    char id[10];
    char name[20];
    char sex[10];
    int age;
    Score score;
}Student;

typedef struct LNode {
    Student data;
    struct LNode* next; //ָ�򱾽ṹ��ָ��/����ָ����Ƕ�׶���
}LNode, * LinkList;//LinkListΪָ��ṹ��LNode��ָ������
/*LNode* ��LinkList�������ǵȼ۵ģ���ôд��Ϊ����߳���ɶ��ԡ�ͨ��ϰ������LinkList L�����嵥����LNode* node������*/

//������ĳ�ʼ��
Status InitList_L(LinkList& L) {
    L = new LNode; //��L = (LinkLIst)malloc(sizeof(LNode));
    L->next = NULL;
    return OK;
}

//������ı�
int ListLength_L(LinkList L) {
    int len = 0;
    LNode* p = L->next;
    while (p) {
        p = p->next;
        len++;
    }
    return len;
}

//��ӡѧ������
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


//������β�巨����ѧ����¼
void CreateList_R(LinkList& L) {
    LNode* tail = L; //��ʼʱβָ��ָ��ͷ���
    //�ҵ�βָ��
    while (tail->next) {
        tail++;
    }
    LNode* s = new LNode;
    //LNode* s = (LNode*)malloc(sizeof(LNode));
    //scanf("%c",&(s->data));
    //cin>>s->data;
    printf("�������%dλѧ����Ϣ��\n", ListLength_L(L) + 1);
    printf("������");
    scanf("%s", s->data.name);
    printf("ѧ�ţ�");
    scanf("%s", s->data.id);
    printf("���䣺");
    scanf("%d", &(s->data.age));
    printf("�Ա�");
    scanf("%s", s->data.sex);
    printf("���ĳɼ���");
    scanf("%d", &(s->data.score.Chinese));
    printf("��ѧ�ɼ���");
    scanf("%d", &(s->data.score.Math));
    printf("Ӣ��ɼ���");
    scanf("%d", &(s->data.score.English));
    s->next = NULL;  //���뵽��β
    tail->next = s;
    printf("���ӳɹ���\n");
}

//������ֵ���ҡ�������λ��
//�ҵ�����Ԫ����ţ��Ҳ�������Ԫ��λ�����
int LocateElem1_L(LinkList L, char e[]) {
    LNode* p = L->next;
    int j = 1;
    while (p && p->data.name == e) { //˳��ɨ�裬ֱ��pΪ�ջ�p����һ������������e
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

//������ɾ����i�����
Status ListDelete_L(LinkList& L) {
    char e[20] = { 0 };
    int i;
    printf("������Ҫɾ����ѧ��������");
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
        printf("ɾ��ʧ�ܣ�\n");
        return ERROR;
    }
    delete p;
    printf("ɾ���ɹ���\n");
    return OK;
}
//����ѧ����¼
void SearchStu(const LinkList L) {
    char e[20] = { 0 };
    int i;
    printf("������Ҫ���ҵ�ѧ��������");
    scanf("%s", e);
    if (LocateElem1_L(L, e)) {
        i = LocateElem1_L(L, e);
        printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "����", "ѧ��", "����", "�Ա�", "���ĳɼ�", "��ѧ�ɼ�", "Ӣ��ɼ�");
        PrintStu(L, i);
    }
    else {
        printf("���޴��ˣ�\n");
    }
}

//�޸�ѧ����¼
void ModifyStu(LinkList& L) {
    char e[20] = { 0 };
    int i;
    printf("������Ҫ�޸ĵ�ѧ��������");
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
        printf("������Ҫ�޸ĵ�ѧ����Ϣ��\n");
        printf("������");
        scanf("%s", p->data.name);
        printf("ѧ�ţ�");
        scanf("%s", p->data.id);
        printf("���䣺");
        scanf("%d", &(p->data.age));
        printf("�Ա�");
        scanf("%s", p->data.sex);
        printf("���ĳɼ���");
        scanf("%d", &(p->data.score.Chinese));
        printf("��ѧ�ɼ���");
        scanf("%d", &(p->data.score.Math));
        printf("Ӣ��ɼ���");
        scanf("%d", &(p->data.score.English));
        printf("�޸ĳɹ���\n");
    }
    else {
        printf("���޴��ˣ�\n");
    }
}

//������ʾ�˵�
void myMenu() {
    printf("\n");
    printf(" * * * * * * * * * ��     �� * * * * * * * * * *\n");
    printf("     1 ����ѧ����¼            2 ɾ��ѧ����¼    \n");
    printf("     3 ����ѧ����¼            4 �޸�ѧ����¼    \n");
    printf("     5 ͳ��ѧ������            6 ��ʾѧ����¼    \n");
    printf("     0 �˳�ϵͳ                                 \n");
    printf(" * * * * * * * * * * * * * * * * * * * * * * * *\n");
}



int main() {
    int input = 0;
    LinkList L;
    InitList_L(L);
    do
    {
        myMenu();
        printf("������ѡ�");
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
            printf("ѧ������Ϊ��%d\n", ListLength_L(L) + 1);
            break;
        case 6:
            printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "����", "ѧ��", "����", "�Ա�", "���ĳɼ�", "��ѧ�ɼ�", "Ӣ��ɼ�");
            for (int i = 1; i < ListLength_L(L) + 1; i++) {
                PrintStu(L, i);
            }
            break;
        case 0:
            printf("�˳�ϵͳ!\n");
            break;
        default:
            printf("�����������\n");
            break;
        }
    } while (input);

    return 0;
}
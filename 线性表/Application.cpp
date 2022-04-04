#include"LinkList.h"
#include"SeqList.h"

//���Ա�ĺϲ�
void uniList(LinkList &La,LinkList &Lb){
    int La_len = ListLength_L(La);
    int Lb_len = ListLength_L(Lb);
    ElemType e;
    for(int i = 1; i < Lb_len; i++){ //��������Lb
        GetElem_L(Lb,i,e);  //��ȡ��Ӧλ��Ԫ��
        if(!LocateElem2_L(La,e)){  //�����Lb��iλ���ϵ�Ԫ�ز���La�ϣ�����Ԫ�ز���La��β
            ListInsert_L(La,++La_len,e);
        }
    }
}

//������ǵݼ����ĺϲ� ���� ˳���ʵ��
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
    ElemType* pa = La.elem;
    ElemType* pb = Lb.elem;  //�ֱ�ָ���ĵ�һ��Ԫ��   
    ElemType* pa_last = pa + La.length - 1;
    ElemType* pb_last = pb + Lb.length - 1;
    Lc.length = La.length + Lb.length;
    Lc.elem = new ElemType[Lc.length];  //Ϊ�±����һ������ռ�
    ElemType* pc = Lc.elem;  
    while(pa < pa_last && pb < pb_last){  //��������������δ�ﵽ��β
        if(*pa <= *pb){  //��СԪ�ط����±���
            *pc++ = *pa++;
        }else{
            *pc++ = *pb++;
        }
    }
    while(pa <= pa_last){
        *pc++ = *pa++;
    }
    while(pb <= pb_last){
        *pc++ = *pb++;
    }
}

//������ǵݼ����ĺϲ� ���� ˳���ʵ��
void MergeList_L(LinkList &La,LinkList &Lb, LinkList &Lc){
    Lc = La;    //La��ΪLc��ͷ���
    LNode* pc = Lc;
    LNode* pa = La->next;
    LNode* pb = Lb->next;
    while (pa && pb)
    {
        if(pa->data <= pb->data){
            pc->next = pa;  //pa��ָ������ӵ�pc��next��
            pc = pa;  //pcָ��pa
            pa = pa->next;  //pa����ƶ�һλ
        }else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;  //���ǿյ��������ӵ�pc֮��
    delete Lb;  //�ͷ�Lb�Ľ��
}

int main(){
    //˳���ʵ�������ĺϲ�
    // SqList La,Lb,Lc;
    // InitList_Sq(La);
    // InitList_Sq(Lb);
    // InitList_Sq(Lc);
    // ListInsert(La,1,3);
    // ListInsert(La,2,5);
    // ListInsert(La,3,8);
    // ListInsert(La,4,11);
    // ListInsert(Lb,1,2);
    // ListInsert(Lb,2,6);
    // ListInsert(Lb,3,8);
    // ListInsert(Lb,4,9);
    // ListInsert(Lb,5,11);
    // ListInsert(Lb,6,15);
    // ListInsert(Lb,7,20);
    // MergeList_Sq(La,Lb,Lc);
    // ElemType* pc = Lc.elem;
    // for(int i = 0;i < Lc.length;i++){
    //     printf("%d ",*pc++);
    // }


    return 0;
}

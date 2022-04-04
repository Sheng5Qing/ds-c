#include"LinkList.h"
#include"SeqList.h"

//线性表的合并
void uniList(LinkList &La,LinkList &Lb){
    int La_len = ListLength_L(La);
    int Lb_len = ListLength_L(Lb);
    ElemType e;
    for(int i = 1; i < Lb_len; i++){ //遍历链表Lb
        GetElem_L(Lb,i,e);  //获取相应位置元素
        if(!LocateElem2_L(La,e)){  //如果表Lb第i位置上的元素不再La上，将该元素插入La表尾
            ListInsert_L(La,++La_len,e);
        }
    }
}

//有序表（非递减）的合并 —— 顺序表实现
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
    ElemType* pa = La.elem;
    ElemType* pb = Lb.elem;  //分别指向表的第一个元素   
    ElemType* pa_last = pa + La.length - 1;
    ElemType* pb_last = pb + Lb.length - 1;
    Lc.length = La.length + Lb.length;
    Lc.elem = new ElemType[Lc.length];  //为新表分配一个数组空间
    ElemType* pc = Lc.elem;  
    while(pa < pa_last && pb < pb_last){  //遍历两表且两表都未达到表尾
        if(*pa <= *pb){  //将小元素放入新表中
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

//有序表（非递减）的合并 —— 顺序表实现
void MergeList_L(LinkList &La,LinkList &Lb, LinkList &Lc){
    Lc = La;    //La作为Lc的头结点
    LNode* pc = Lc;
    LNode* pa = La->next;
    LNode* pb = Lb->next;
    while (pa && pb)
    {
        if(pa->data <= pb->data){
            pc->next = pa;  //pa所指结点链接到pc的next域
            pc = pa;  //pc指向pa
            pa = pa->next;  //pa向后移动一位
        }else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;  //将非空的链表链接到pc之后
    delete Lb;  //释放Lb的结点
}

int main(){
    //顺序表实现有序表的合并
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

#include"LinkList.h"

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
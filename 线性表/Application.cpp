#include"LinkList.h"

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
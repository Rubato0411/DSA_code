#include "insfirst.h"

LinkList *InsFirst(LinkList *L, ElemType e){
    if(!L){
        return NULL;
    }
    Node p=(Node)malloc(sizeof(struct LNode));
    if(!p){
        return NULL;
    }else{
        p->data=e;
        p->next=L->head->next;
        L->head->next=p;
        if (L->len==0){
        L->tail=p;
        }//尾指针维护
        L->len++;
        return L;
    }
}

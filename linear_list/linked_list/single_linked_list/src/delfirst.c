#include "delfirst.h"

LinkList *DelFirst(LinkList *L, ElemType *e){
    if(!L||L->len==0){
        return NULL;
    }
    Node p=L->head->next;
    *e=p->data;
    L->head->next=p->next;
    if(L->len==1){
        L->tail=L->head;
    }
    free(p);
    L->len--;
    return L;
}

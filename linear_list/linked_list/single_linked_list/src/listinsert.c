#include "listinsert.h"
LinkList *ListInsert(LinkList *L,int i,ElemType e){
    if(!L||i<1||i>L->len+1){ return NULL; }
    Node q=L->head;
    for(int j=1;j<i;j++){ q=q->next; }
    Node p=(Node)malloc(sizeof(struct LNode));
    if(!p){ return NULL; }
    p->data=e;
    p->next=q->next;
    q->next=p;
    if(i==L->len+1){ L->tail=p; }
    L->len++;
    return L;
}

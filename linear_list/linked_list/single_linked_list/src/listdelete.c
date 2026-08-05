#include "listdelete.h"
LinkList *ListDelete(LinkList *L,int i,ElemType *e){
    if(!L||i<1||i>L->len){ return NULL; }
    Node q=L->head;
    for(int j=1;j<i;j++){ q=q->next; }
    Node p=q->next;
    *e=p->data;
    q->next=p->next;
    if(i==L->len){ L->tail=q; }
    free(p);
    L->len--;
    return L;
}

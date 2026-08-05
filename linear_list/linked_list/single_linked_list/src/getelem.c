#include "getelem.h"
ElemType GetElem(LinkList *L,int i){
    if(!L||i<1||i>L->len){ exit(1); }
    Node p=L->head->next;
    for(int j=1;j<i;j++){ p=p->next; }
    return p->data;
}

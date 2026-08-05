#include "listtraverse.h"
bool ListTraverse(LinkList *L,void(*visit)(ElemType)){
    if(!L){ return false; }
    Node p=L->head->next;
    while(p){ visit(p->data); p=p->next; }
    return true;
}

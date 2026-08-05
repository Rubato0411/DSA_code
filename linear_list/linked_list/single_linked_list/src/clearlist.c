#include "clearlist.h"
#include "freenode.h"

bool ClearList(LinkList *L){
    if(L){
        Node p=L->head->next;
        while(p){
            Node q=p->next;
            FreeNode(&p);
            p=q;
        }
        L->head->next=NULL;
        L->tail=L->head;
        L->len=0;
        return true;
    }
    return false;
}

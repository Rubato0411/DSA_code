#include "destroylist.h"

LinkList *DestroyList(LinkList *L){
    if(L){
        Node p=L->head;
        while(p){
            Node q=p->next;
            free(p);
            p=q;
        }
        free(L);
    }
    return NULL;
}
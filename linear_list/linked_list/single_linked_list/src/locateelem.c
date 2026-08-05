#include "locateelem.h"
int LocateElem(LinkList *L,ElemType e,bool(*compare)(ElemType,ElemType)){
    if(!L){ return 0; }
    Node p=L->head->next;
    int i=1;
    while(p){
        if(compare(p->data,e)){ return i; }
        p=p->next;
        i++;
    }
    return 0;
}

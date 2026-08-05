
#include "init_list.h"

Sqlist* InitList_Sq(Sqlist *L){
    L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L->elem){
        return NULL;
    }
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return L;
}

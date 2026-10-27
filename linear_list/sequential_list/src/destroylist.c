
#include "destroylist.h"

void DestroyList_Sq(Sqlist *L){
    free(L->elem);
    L->length=0;
    L->listsize=0;
    L->elem=NULL;
}
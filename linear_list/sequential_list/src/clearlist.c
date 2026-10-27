#include "clearlist.h"

Sqlist *ClearList_Sq(Sqlist *L){
    L->length=0;
    return L;
}
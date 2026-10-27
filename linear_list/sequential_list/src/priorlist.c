#include "priorlist.h"

ElemType *PriorList(Sqlist *L,ElemType cur_e){
    if(&cur_e==L->elem||L->elem==NULL){
        return NULL;
    }
    int i=1;
    for(i=1;i<L->length;i++){
        if(L->elem[i]==cur_e){
            return &L->elem[i-1];
        }
    }
    return NULL;
}
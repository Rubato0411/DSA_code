#include "nextelem.h"

ElemType *NextElem(Sqlist *L,ElemType cur_e){
    if(&cur_e==&L->elem[L->length-1]||L->elem==NULL){
        return NULL;
    }
    int i=0;
    for(i=0;i<L->length-1;i++){
        if(L->elem[i]==cur_e){
            return &L->elem[i+1];
        }
    }
    return NULL;
}
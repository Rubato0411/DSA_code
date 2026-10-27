#include "getelem.h"

ElemType GetElem(Sqlist *L, int i){
    if(i<1||i>L->length||L->elem==NULL){
        exit(1);
    }
    return L->elem[i-1];
}
#include "listdelete.h"

Sqlist *ListDelete(Sqlist *L,int i,ElemType *e){
    if(i<1||i>L->length||L->elem==NULL){
        exit(1);
    }
    *e=L->elem[i-1];
    for(int j=i;j<L->length;j++){
        L->elem[j-1]=L->elem[j];
    }
    L->length--;
    return L;
}
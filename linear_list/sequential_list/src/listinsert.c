#include "listinsert.h"

Sqlist *ListInsert(Sqlist *L,int i,ElemType e){
    if(i<1||i>L->length+1){
        exit(1);
    }
    if(L->length>=L->listsize){
        L->elem=(ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        L->listsize+=LISTINCREMENT;
    }
    for(int j=L->length;j>=i;j--){
        L->elem[j]=L->elem[j-1];
    }
    L->elem[i-1]=e;
    L->length++;
    return L;
}
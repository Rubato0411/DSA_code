#include "mergelist.h"

Sqlist *MergeList(Sqlist *la,Sqlist *lb,Sqlist *lc,bool(*compare)(ElemType,ElemType)){
    lc->length=la->length+lb->length;
    lc->listsize=lc->length;
    lc->elem=(ElemType *)malloc(lc->listsize*sizeof(ElemType));
    if(!lc->elem){
        exit(1);
    }
    ElemType *pa=la->elem;
    ElemType *pb=lb->elem;
    ElemType *pa_end=la->elem+la->length-1;
    ElemType *pb_end=lb->elem+lb->length-1;
    ElemType *pc=lc->elem;
    while(pa<=pa_end&&pb<=pb_end){
        if(compare(*pa,*pb)){
            *pc++=*pa++;
        }else{
            *pc++=*pb++;
        }
    }
    while(pa<=pa_end){
        *pc++=*pa++;
    }
    while(pb<=pb_end){
        *pc++=*pb++;
    }
    return lc;
}
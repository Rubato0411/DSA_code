#include "locateelem.h"

int LocateElem(Sqlist *L,ElemType e,bool(*compare)(ElemType,ElemType)){
    for(int i=0;i<L->length;i++){
        if(compare(L->elem[i],e)){
            return i+1;
        }
    }
    return 0;
} //返回满足compare()的第一个元素的位序，若不存在则返回0
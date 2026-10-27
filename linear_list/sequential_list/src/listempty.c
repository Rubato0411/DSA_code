#include "listempty.h"

bool ListEmpty(Sqlist *L){
    if(L->length==0){
        return true;
    }else{
        return false;
    }
}
#include "listtraverse.h"

bool ListTraverse(Sqlist *L,void(*visit)(ElemType)){
    for(int i=0;i<L->length;i++){
        visit(L->elem[i]);
    }
    return true;
} //visit 只负责“处理/打印”元素，不返回成功或失败状态
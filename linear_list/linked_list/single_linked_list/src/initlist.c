#include "initlist.h"

LinkList *InitList(LinkList **L){
    *L=(LinkList*)malloc(sizeof(LinkList));
    if(!(*L)){
        return NULL;
    }else{
        (*L)->head=(Node)malloc(sizeof(struct LNode));
        if(!(*L)->head){
            free(*L);
            return NULL;
        }else{
            (*L)->head->next=NULL;
            (*L)->tail = (*L)->head;   
            (*L)->len = 0;
        }
    }
    return *L;
}
//头节点是哑节点，需要分配内存，尾节点只是标记，不需要单独分配内存
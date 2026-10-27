#include "makenode.h"

bool MakeNode(Node *p,ElemType e){
    if(!p||!*p){
        return false;
    }
    Node q=(Node)malloc(sizeof(struct LNode));
    if(!q){
        return false;
    }else{
        q->data=e;
        q->next=NULL;
        (*p)->next=q;
        return true;
    }
}

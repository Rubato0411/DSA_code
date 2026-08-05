#include "freenode.h"

void FreeNode(Node *p){
    if(*p){
        free(*p);
        *p=NULL;
    }
}
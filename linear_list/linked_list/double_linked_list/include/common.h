#ifndef DOUBLE_LINKED_LIST_COMMON_H
#define DOUBLE_LINKED_LIST_COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior,*next;
}*Node;

typedef struct{
    Node head,tail;
    int len;
}DuLinkList;

#endif

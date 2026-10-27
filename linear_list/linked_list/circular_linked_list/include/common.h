#ifndef CIRCULAR_LINKED_LIST_COMMON_H
#define CIRCULAR_LINKED_LIST_COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct CLNode{
    ElemType data;
    struct CLNode *next;
}*Node;

typedef struct{
    Node head,tail;
    int len;
}CLinkList;

#endif

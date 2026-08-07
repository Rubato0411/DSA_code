#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int SElemType;

typedef struct StackNode{
    SElemType data;
    struct StackNode *next;
}StackNode,*StackNodePtr;

typedef struct{
    StackNodePtr top;
    int len;
}LinkedStack;
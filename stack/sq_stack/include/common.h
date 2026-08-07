#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;

typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
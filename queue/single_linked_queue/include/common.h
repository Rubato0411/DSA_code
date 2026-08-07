#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int QElemType;

typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 100

typedef int QElemType;

typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

//注意，循环队列通常牺牲一个存储单元来区分队列满和队列空的状态，实际只能存储99个元素
#ifndef SEQUENTIAL_LIST_COMMON_H
#define SEQUENTIAL_LIST_COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10 //线性表存储空间的分配增量

typedef int ElemType;
typedef struct{
    ElemType *elem; //存储空间基址
    int length;
    int listsize;
}Sqlist;

#endif

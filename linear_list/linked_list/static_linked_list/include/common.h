#define MAXSIZE 1000
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct{
    ElemType data;
    int cur;
}component,SLinkList[MAXSIZE];
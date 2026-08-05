#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    float coef;
    int expn;
}term,ElemType;

typedef struct PolyNode {
    term data;
    struct PolyNode *next;
} PolyNode, *polynomial; 
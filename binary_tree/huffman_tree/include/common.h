#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>//使用UINT_MAX宏作为最小权值的初始哨兵值

typedef struct{
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
}HNode,*HuffmanTree;

typedef char **HuffmanCode;
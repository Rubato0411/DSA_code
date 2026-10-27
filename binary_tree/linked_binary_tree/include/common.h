#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int TElemType;

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
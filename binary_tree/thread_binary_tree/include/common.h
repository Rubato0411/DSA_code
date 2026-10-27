#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int TElemType;

typedef enum PointTag{
    Link,Thread
};
//枚举类型，下标代值

typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointTag ltag,rtag;
}BiThrNode,*BiThrTree;
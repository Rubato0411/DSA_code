#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_VERTEX_NUM 100

typedef int VertexType;
typedef int EdgeType;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

//邻接表存储表示
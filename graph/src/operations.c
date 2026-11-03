#include "../include/operations.h"

/* 本文件按无向图处理：每条边在邻接表中保存两个方向的弧结点。 */

/* 从顶点 v 的边链表中删除一条指向 w 的弧 */
static bool RemoveArc(ALGraph *G, int v, int w) {
    ArcNode **pp = &G->vertices[v].firstarc;
    while (*pp != NULL) {
        if ((*pp)->adjvex == w) {
            ArcNode *temp = *pp;
            *pp = temp->nextarc;
            free(temp);
            return true;
        }
        pp = &(*pp)->nextarc;
    }
    return false;
}

/* 无向图边数 = 所有顶点度数之和 / 2 */
static void RecountArcs(ALGraph *G) {
    int degreeSum = 0;
    for (int i = 0; i < G->vexnum; i++) {
        for (ArcNode *p = G->vertices[i].firstarc; p != NULL; p = p->nextarc) {
            degreeSum++;
        }
    }
    G->arcnum = degreeSum / 2;
}

void InitGraph(ALGraph *G) {
    if (G == NULL) {
        return;
    }
    G->vexnum = 0;
    G->arcnum = 0;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        G->vertices[i].data = 0;
        G->vertices[i].firstarc = NULL;
    }
}

bool DestroyGraph(ALGraph *G) {
    if (G == NULL) {
        return false;
    }
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
        G->vertices[i].firstarc = NULL;
    }
    G->vexnum = 0;
    G->arcnum = 0;
    return true;
}

bool GetVex(ALGraph G, int v, VertexType *value) {
    if (value == NULL || v < 0 || v >= G.vexnum) {
        return false;
    }
    *value = G.vertices[v].data;
    return true;
}

bool PutVex(ALGraph *G, int v, VertexType value) {
    if (G == NULL || v < 0 || v >= G->vexnum) {
        return false;
    }
    G->vertices[v].data = value;
    return true;
}

VertexType FirstAdjVex(ALGraph G, int v) {
    if (v < 0 || v >= G.vexnum) {
        return -1;
    }
    ArcNode *p = G.vertices[v].firstarc;
    return (p != NULL) ? p->adjvex : -1;
}

VertexType NextAdjVex(ALGraph G, int v, int w) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) {
        return -1;
    }
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL) {
        if (p->adjvex == w) {
            return (p->nextarc != NULL) ? p->nextarc->adjvex : -1;
        }
        p = p->nextarc;
    }
    return -1;
}

bool InsertVex(ALGraph *G, VertexType v) {
    if (G == NULL || G->vexnum >= MAX_VERTEX_NUM) {
        return false;
    }
    G->vertices[G->vexnum].data = v;
    G->vertices[G->vexnum].firstarc = NULL;
    G->vexnum++;
    return true;
}

bool DeleteVex(ALGraph *G, int v) {
    if (G == NULL || v < 0 || v >= G->vexnum) {
        return false;
    }

    /* 1. 删除其他顶点中指向 v 的弧，并修正大于 v 的顶点下标 */
    for (int i = 0; i < G->vexnum; i++) {
        if (i == v) {
            continue;
        }

        ArcNode **pp = &G->vertices[i].firstarc;
        while (*pp != NULL) {
            ArcNode *cur = *pp;
            if (cur->adjvex == v) {
                *pp = cur->nextarc;
                free(cur);
            } else {
                if (cur->adjvex > v) {
                    cur->adjvex--;
                }
                pp = &cur->nextarc;
            }
        }
    }

    /* 2. 释放被删顶点自己的边链表 */
    ArcNode *p = G->vertices[v].firstarc;
    while (p != NULL) {
        ArcNode *temp = p;
        p = p->nextarc;
        free(temp);
    }
    G->vertices[v].firstarc = NULL;

    /* 3. 顶点表前移，保持顶点顺序 */
    for (int i = v; i < G->vexnum - 1; i++) {
        G->vertices[i] = G->vertices[i + 1];
    }
    G->vertices[G->vexnum - 1].firstarc = NULL;
    G->vexnum--;

    /* 4. 重新统计边数 */
    RecountArcs(G);
    return true;
}

bool InsertArc(ALGraph *G, int v, int w) {
    if (G == NULL || v < 0 || v >= G->vexnum || w < 0 || w >= G->vexnum) {
        return false;
    }

    /* 判重：无向图中若 v 的链表中已有 w，则边已存在 */
    for (ArcNode *p = G->vertices[v].firstarc; p != NULL; p = p->nextarc) {
        if (p->adjvex == w) {
            return false;
        }
    }

    /* 先分配两个结点，避免只插入一个方向 */
    ArcNode *toW = (ArcNode *)malloc(sizeof(ArcNode));
    ArcNode *toV = (ArcNode *)malloc(sizeof(ArcNode));
    if (toW == NULL || toV == NULL) {
        free(toW);
        free(toV);
        return false;
    }

    toW->adjvex = w;
    toW->nextarc = G->vertices[v].firstarc;
    G->vertices[v].firstarc = toW;

    toV->adjvex = v;
    toV->nextarc = G->vertices[w].firstarc;
    G->vertices[w].firstarc = toV;

    G->arcnum++;
    return true;
}

bool DeleteArc(ALGraph *G, int v, int w) {
    if (G == NULL || v < 0 || v >= G->vexnum || w < 0 || w >= G->vexnum) {
        return false;
    }

    if (!RemoveArc(G, v, w)) {
        return false;
    }

    /* 无向图还要删除对称弧；v == w 时清掉第二个自环结点 */
    RemoveArc(G, w, v);

    G->arcnum--;
    return true;
}

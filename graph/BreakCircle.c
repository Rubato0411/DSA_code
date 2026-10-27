//from dpsk

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 1000

typedef struct {
    int u, v, w;
    bool deleted;
} Edge;

Edge edges[MAXM];
int head[MAXN];
int next[MAXM * 2];
int to[MAXM * 2];
int edgeIdx[MAXM * 2];
int cnt = 0;
int n, m;

void addEdge(int u, int v, int idx) {
    to[cnt] = v;
    edgeIdx[cnt] = idx;
    next[cnt] = head[u];
    head[u] = cnt++;

    to[cnt] = u;
    edgeIdx[cnt] = idx;
    next[cnt] = head[v];
    head[v] = cnt++;
}

/* ---------- 找环相关 ---------- */
bool visited[MAXN];
bool inStack[MAXN];
int parent[MAXN];
int parentEdge[MAXN];
int cycleEdges[MAXM];   // 保存环上的边索引
int cycleLen = 0;
bool foundCycle = false;

void dfs(int u) {
    if (foundCycle) return;

    visited[u] = true;
    inStack[u] = true;

    for (int e = head[u]; e != -1; e = next[e]) {
        int v = to[e];
        int idx = edgeIdx[e];

        if (edges[idx].deleted) continue;       // 已删除的边跳过
        if (idx == parentEdge[u]) continue;     // 不走来时的父边

        if (!visited[v]) {
            parent[v] = u;
            parentEdge[v] = idx;
            dfs(v);
            if (foundCycle) return;
        } else if (inStack[v]) {
            // 发现回边 (u, v)，构成一个环
            cycleLen = 0;
            int cur = u;
            while (cur != v) {
                cycleEdges[cycleLen++] = parentEdge[cur];
                cur = parent[cur];
            }
            cycleEdges[cycleLen++] = idx;       // 加上回边 (u, v)
            foundCycle = true;
            return;
        }
    }

    inStack[u] = false;
}

/* 在图中找任意一个环，找到返回 true，并填充 cycleEdges */
bool findAnyCycle() {
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
        inStack[i] = false;
        parent[i] = -1;
        parentEdge[i] = -1;
    }
    foundCycle = false;
    cycleLen = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            if (foundCycle) return true;
        }
    }
    return false;
}

/* ---------- 主函数：破圈法 ---------- */
int main(void) {
    for (int i = 0; i < MAXN; i++) head[i] = -1;

    printf("请输入顶点数和边数：");
    scanf("%d %d", &n, &m);

    printf("请输入每条边的两个顶点和权值（u v w）：\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].deleted = false;
        addEdge(edges[i].u, edges[i].v, i);
    }

    /* 反复找环，删除环中权值最大的边 */
    while (findAnyCycle()) {
        int maxIdx = cycleEdges[0];
        for (int i = 1; i < cycleLen; i++) {
            int idx = cycleEdges[i];
            if (edges[idx].w > edges[maxIdx].w) {
                maxIdx = idx;
            }
        }
        edges[maxIdx].deleted = true;
        printf("删除边：%d -- %d，权值：%d\n",
               edges[maxIdx].u, edges[maxIdx].v, edges[maxIdx].w);
    }

    /* 输出最小生成树 */
    printf("\n最小生成树的边：\n");
    int total = 0;
    for (int i = 0; i < m; i++) {
        if (!edges[i].deleted) {
            printf("%d -- %d  权值：%d\n", edges[i].u, edges[i].v, edges[i].w);
            total += edges[i].w;
        }
    }
    printf("总权值：%d\n", total);

    return 0;
}
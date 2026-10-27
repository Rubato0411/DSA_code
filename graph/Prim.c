#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#define MAX 100
#define INF 0x3f3f3f3f   // 安全无穷大，避免加法溢出

/* typedef struct{
    int u;
    int v;
    int w;
}graph;
 */
int graph[MAX][MAX]={0};
int visited[MAX]={-1};
int dist[MAX]={0};
int pre[MAX]={-1};

void initgraph(int n){
    int i=0;
    int j=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                graph[i][j]=0;
            }else{
                graph[i][j]=INF;
            }
        }
    }
}

void edge(int u,int v,int w){
    graph[u][v]=w;
    graph[v][u]=w;
}

int Prim(int n,int v0){
    int i=0;
    int j=0;
    for(i=0;i<n;i++){
        dist[i]=INF;
        visited[i]=0;
        pre[i]=-1;
    }
    visited[v0]=1;
    dist[v0]=0;
    int totalw=0;
    for(i=0;i<n;i++){
        int min=INF;
        int u=-1;//处理边不连通的特殊情况
        for(j=0;j<n;j++){
            if(visited[j]==0&&dist[j]<min){
                min=dist[j];
                u=j;
            }
        }
        if(u==-1){
            break;
        }
        visited[u]=1;
        totalw+=min;
        int k=0;
        for(k=0;k<n;k++){
            if(visited[k]==0&&graph[u][k]<dist[k]){
                dist[k]=graph[u][k];
                pre[k]=u;
            }
        }
    }
    for(i=0;i<n;i++){
        if(visited[i]==0){
            return -1;
        }
    }
    return totalw;
}
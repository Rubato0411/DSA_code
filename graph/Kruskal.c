#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//注意“并查集”中查找和合并的两个关键操作，递归查找，然后合并树根
typedef struct{
    int u;
    int v;
    int w;
}graph;
int parent[MAX]={0};
//int selected=0;
int edges[MAX]={0};
graph G[MAX]={0};

void init(int n){
    int i=0;
    for(i=0;i<n;i++){
        parent[i]=i;//初始状态下每个节点都是自己的树根
    }
}

int find(int x){
    if(parent[x]!=x){
        parent[x]=find(parent[x]);
    }
    return parent[x];
}

void Union(int v1,int v2){
    int x=find(v1);
    int y=find(v2);
    if(x!=y){
        parent[x]=y;
    }
}

int cmp(const void* a,const void* b){
    return ((graph*)a)->w-((graph*)b)->w;
}

void Kruskal(int v,int e,graph* G){
    init(v);
    qsort(G,e,sizeof(graph),cmp);
    int selected=0;
    int totalw=0;
    int i=0;
    for(i=0;i<e;i++){
        int x=find(G[i].u);
        int y=find(G[i].v);
        if(x!=y){
            Union(G[i].u,G[i].v);
            totalw+=G[i].w;
            selected++;
        }
    }
    if(selected!=v-1){
        exit(-1);
    }else{
        printf("%d\n",totalw);
    }
}

int main(){
    int v=0;
    int e=0;
    scanf("%d %d",&v,&e);
    int i=0;
    for(i=0;i<e;i++){
        scanf("%d %d %d",&G[i].u,&G[i].v,&G[i].w);
    }
    Kruskal(v,e,G);
    return 0;
}
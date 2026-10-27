#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
#include<windows.h>
#endif

#define MAX 100
#define INF INT_MAX //标记无穷大

int graph[MAX][MAX];
int dist[MAX];
bool visited[MAX];
int pre[MAX];

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

void dijkstra(int n,int v0){
    int i=0;
    int j=0;
    for(i=0;i<n;i++){
        dist[i]=INF;
        visited[i]=false;
        pre[i]=-1;
    }
    dist[v0]=0;
    int cnt=0;
    for(cnt=0;cnt<n;cnt++){
        int min=INF;
        int k=-1;
        for(i=0;i<n;i++){
            if(!visited[i]&&dist[i]<min){
                min=dist[i];
                k=i;
            }
        }
        if(k==-1){
            break;
        }
        visited[k]=true;
        for(i=0;i<n;i++){
            if(!visited[i]&&graph[k][i]!=INF){
                if(dist[k]+graph[k][i]<dist[i]){
                    dist[i]=dist[k]+graph[k][i];
                    pre[i]=k;
                }
            }
        }
    }
}

void printpath(int v0,int v){
    if(v==v0){
        printf("%d",v0);
        return;
    }
    printpath(v0,pre[v]);
    printf(" -> %d", v);
}

int main(){
#ifdef _WIN32
    // 源文件和中文输出使用 UTF-8，让 Windows 控制台使用相同编码。
    SetConsoleOutputCP(CP_UTF8);
#endif
    int n=6;
    initgraph(n);
    edge(0,1,50);
    edge(0,3,40);
    edge(0,4,25);
    edge(0,5,10);
    edge(1,2,15);
    edge(1,3,20);
    edge(1,5,25);
    edge(2,3,10);
    edge(2,4,20);
    edge(3,4,10);
    edge(3,5,25);
    edge(4,5,55);
    dijkstra(n,0);
    int i=0;
    for(i=0;i<n;i++){
        printf("从%d到%d的最短路径长度为：%d\n",0,i,dist[i]);
        printf("路径为：");
        printpath(0,i);
        printf("\n");
    }
    return 0;
}

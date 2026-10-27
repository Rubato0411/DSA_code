#include "../include/operations.h"

void CreateGraph(ALGraph *G);
void InitGraph(ALGraph *G){
    G->vexnum=0;
    G->arcnum=0;
    int i=0;
    for(i=0;i<MAX_VERTEX_NUM;i++){
        G->vertices[i].firstarc=NULL;
    }
}
bool DestroyGraph(ALGraph *G){
    if(!G){
        return false;
    }
    int i=0;
    for(i=0;i<G->vexnum;i++){
        ArcNode *p=G->vertices[i].firstarc;
        while(p!=NULL){
            ArcNode *temp=p;
            p=p->nextarc;
            free(temp);
        }
        G->vertices[i].firstarc=NULL;
    }
    G->vexnum=0;
    G->arcnum=0;
    return true;
}
bool GetVex(ALGraph G,int v,VertexType *value){
    if(v<0||v>=G.vexnum){
        return false;
    }
    *value=G.vertices[v].data;
    return true;
}
bool PutVex(ALGraph *G,int v,VertexType value){
    if(v<0||v>=G->vexnum){
        return false;
    }
    G->vertices[v].data=value;
    return true;
}
VertexType FirstAdjVex(ALGraph G,int v){
    if(v<0||v>=G.vexnum){
        return -1;
    }
    ArcNode *p=G.vertices[v].firstarc;
    if(p!=NULL){
        return p->adjvex;
    }else{
        return -1;
    }
}
VertexType NextAdjVex(ALGraph G,int v,int w){
    if(v<0||v>=G.vexnum||w<0||w>=G.vexnum){
        return -1;
    }
    ArcNode *p=G.vertices[v].firstarc;
    while(p!=NULL){
        if(p->adjvex==w){
            if(p->nextarc!=NULL){
                return p->nextarc->adjvex;
            }else{
                return -1;
            }
        }
        p=p->nextarc;
    }
    return -1;
}
bool InsertVex(ALGraph *G,VertexType v){
    if(G->vexnum>=MAX_VERTEX_NUM){
        return false;
    }
    G->vertices[G->vexnum].data=v;
    G->vertices[G->vexnum].firstarc=NULL;
    G->vexnum++;
    return true;
}
bool DeleteVex(ALGraph *G,int v){
    if(v<0||v>=G->vexnum){
        return false;
    }
    ArcNode *p=G->vertices[v].firstarc;
    while(p!=NULL){
        ArcNode *temp=p;
        p=p->nextarc;
        free(temp);
    }
    int i=0;
    for(i=0;i<G->vexnum-1;i++){
        if(i==v){
            continue;
        }
        ArcNode *pre=NULL;
        ArcNode *cur=G->vertices[i].firstarc;
        while(cur!=NULL){
            if(cur->adjvex==v){
                ArcNode *temp=cur;
                if(pre==NULL){
                    G->vertices[i].firstarc=cur->nextarc;
                }else{
                    pre->nextarc=cur->nextarc;
                }
                cur=cur->nextarc;
                free(temp);
                G->arcnum--;
            }else{
                if(cur->adjvex>v){
                    cur->adjvex--;
                }
                pre=cur;
                cur=cur->nextarc;
            }
        }
    }
    // 3. 如果删除的不是最后一个顶点，把最后一个顶点移到 v 的位置
    if(v!=G->vexnum-1){
        G->vertices[v]=G->vertices[G->vexnum-1];
        G->vertices[v].firstarc=G->vertices[G->vexnum-1].firstarc;
        ArcNode *p=G->vertices[v].firstarc;
        while(p!=NULL){
            if(p->adjvex==G->vexnum-1){
                p->adjvex=v;
            }
            p=p->nextarc;
        }
    }
}
bool InsertArc(ALGraph *G,int v,int w){
    if(v<0||v>=G->vexnum||w<0||w>=G->vexnum){
        return false;
    }
    ArcNode *p=G->vertices[v].firstarc;
    while(p!=NULL){
        if(p->adjvex==w){
            return false;
        }
        p=p->nextarc;
    }
    ArcNode *newArc=(ArcNode*)malloc(sizeof(ArcNode));
    if(!newArc){
        return false;
    }
    newArc->adjvex=w;
    newArc->nextarc=G->vertices[v].firstarc;
    G->vertices[v].firstarc=newArc;
    G->arcnum++;
    ArcNode *newArc2=(ArcNode*)malloc(sizeof(ArcNode));
    if(!newArc2){
        return false;
    }
    newArc2->adjvex=v;
    newArc2->nextarc=G->vertices[w].firstarc;
    G->vertices[w].firstarc=newArc2;
    return true;
}
bool DeleteArc(ALGraph *G,int v,int w){
    if(v<0||v>=G->vexnum||w<0||w>=G->vexnum){
        return false;
    }
    ArcNode *pre=NULL;
    ArcNode *cur=G->vertices[v].firstarc;
    while(cur&&cur->adjvex!=w){
        pre=cur;
        cur=cur->nextarc;
    }
    if(!cur){
        return false;
    }
    if(pre){
        pre->nextarc=cur->nextarc;
    }else{
        G->vertices[v].firstarc=cur->nextarc;
    }
    free(cur);
    pre=NULL;
    cur=G->vertices[w].firstarc;
    while(cur&&cur->adjvex!=v){
        pre=cur;
        cur=cur->nextarc;
    }
    G->arcnum--;
    return true;
}

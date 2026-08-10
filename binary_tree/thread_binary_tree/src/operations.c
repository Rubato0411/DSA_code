#include "../include/operations.h"



void createbithrtree(BiThrTree *t){
    TElemType val;
    scanf("%d",&val);
    if(val==-1){
        *t=NULL;
    }else{
        *t=(BiThrTree)malloc(sizeof(BiThrNode));
        if(!(*t)){
            exit(-1);
        }
        (*t)->data=val;
        (*t)->ltag=Link;
        (*t)->rtag=Link;
        createbithrtree(&((*t)->lchild));
        createbithrtree(&((*t)->rchild));
    }
}
void inordertraverse(BiThrTree thrt,void(*visit)(TElemType)){
    if(!thrt||thrt->lchild==thrt){
        return;
    }
    BiThrTree p=thrt->lchild;
    while(p!=thrt){
        while(p->ltag==Link){
            p=p->lchild;
        }
        visit(p->data);
        while(p->rtag==Thread&&p->rchild!=thrt){
            p=p->rchild; // 跳到中序后继
            visit(p->data);  // 访问后继
        }
        p=p->rchild;
    }
}
static void inthreading(BiThrTree p,BiThrTree *pre){
    if(p){
        inthreading(p->lchild,pre);
        if(!p->lchild){
            p->ltag=Thread;
            p->lchild=*pre;
        }
        if(*pre&&!(*pre)->rchild){
            (*pre)->rtag=Thread;
            (*pre)->rchild=p;
        }
        *pre=p;
        inthreading(p->rchild,pre);
    }
}
void inorderthreading(BiThrTree t,BiThrTree *thrt){
    *thrt=(BiThrTree)malloc(sizeof(BiThrTree));
    if(!(*thrt)){
        exit(-1);
    }
    (*thrt)->ltag=Link;
    (*thrt)->rtag=Thread;
    (*thrt)->rchild=*thrt;//保证空树也成立
    if(!t){
        (*thrt)->lchild=*thrt;
        return;
    }
    (*thrt)->lchild=t;
    BiThrTree pre=*thrt;
    inthreading(t,&pre);
    pre->rchild=*thrt;
    pre->rtag=Thread;
    (*thrt)->rchild=pre;
}
void destroybithrtree(BiThrTree *t){
    if(!(*t)){
        return;
    }
    if((*t)->ltag==Link){
        destroybithrtree(&((*t)->lchild));
    }
    if((*t)->rtag==Link){
        destroybithrtree(&((*t)->rchild));
    }
    free(*t);
    *t=NULL;
}
bool bithrtreeempty(BiThrTree t){
    if(!t||t->lchild==t){
        return true;
    }
    return false;//注意此处t->lchild==t条件是为了判断有头节点没有数据节点的情况
}
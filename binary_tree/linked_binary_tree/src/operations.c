#include "../include/operations.h"

void createbitree(BiTree *t){
    TElemType val;
    scanf("%d",&val);
    if(val==-1){
        *t=NULL;
    }else{
        *t=(BiTree)malloc(sizeof(BiTNode));
        if(!(*t)){
            exit(-1);
        }
        (*t)->data=val;
        createbitree(&((*t)->lchild));
        createbitree(&((*t)->rchild));
    }
}
void preordertraverse(BiTree t,void(*visit)(TElemType)){
    if(t){
        visit(t->data);
        preordertraverse(t->lchild,visit);
        preordertraverse(t->rchild,visit);
    }
}
void inordertraverse(BiTree t,void(*visit)(TElemType)){
    if(t){
        inordertraverse(t->lchild,visit);
        visit(t->data);
        inordertraverse(t->rchild,visit);
    }
}
void postordertraverse(BiTree t,void(*visit)(TElemType)){
    if(t){
        postordertraverse(t->lchild,visit);
        postordertraverse(t->rchild,visit);
        visit(t->data);
    }
}
void levelordertraverse(BiTree t,void(*visit)(TElemType)){
    if(!t){
        return;
    }
    int max=100;
    BiTree queue[max];
    int front=0;
    int rear=0;
    queue[rear]=t;
    rear=(rear+1)%max;
    while(front!=rear){
        BiTree p=queue[front];
        front=(front+1)%max;
        visit(p->data);
        if(p->lchild){
            queue[rear]=p->lchild;
            rear=(rear+1)%max;
        }
        if(p->rchild){
            queue[rear]=p->rchild;
            rear=(rear+1)%max;
        }
    }
}
void initbitree(BiTree *t){
    *t=NULL;
}
void destroybitree(BiTree *t){
    if(*t){
        destroybitree(&((*t)->lchild));
        destroybitree(&((*t)->rchild));
        free(*t);
        *t=NULL;
    }
}
bool bitreeempty(BiTree t){
    return t==NULL;
}
int bitreedepth(BiTree t){
    if(!t){
        return 0;
    }
    int ldepth=bitreedepth(t->lchild);
    int rdepth=bitreedepth(t->rchild);
    if(ldepth>rdepth){
        return ldepth+1;
    }else{
        return rdepth+1;
    }
}
BiTree findnode(BiTree t,TElemType e){
    if(!t){
        return NULL;
    }
    if(t->data==e){
        return t;
    }
    BiTree p=findnode(t->lchild,e);
    if(p){
        return p;
    }
    return findnode(t->rchild,e);
}
bool parent(BiTree t,TElemType e,TElemType *res){
    if(!t){
        return false;
    }
    if(t->lchild&&t->lchild->data==e){
        *res=t->data;
        return true;
    }
    if(t->rchild&&t->rchild->data==e){
        *res=t->data;
        return true;
    }
    if(parent(t->lchild,e,res)){
        return true;
    }
    return parent(t->rchild,e,res);
}
void clearbitree(BiTree *t){
    destroybitree(t);
}
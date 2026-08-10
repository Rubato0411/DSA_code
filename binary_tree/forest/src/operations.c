#include "../include/operations.h"

static CSTree createcsnode(TElemType e){
    CSTree p=(CSTree)malloc(sizeof(CSNode));
    if(!p){
        exit(-1);
    }
    p->data=e;
    p->firstchild=NULL;
    p->nextsibling=NULL;
    return p;
}
BiTree TreeToBiTree(CSTree t){
    if(!t){
        return NULL;
    }
    BiTree p=(BiTree)malloc(sizeof(BiTNode));
    if(!p){
        exit(-1);
    }
    p->data=t->data;
    p->lchild=TreeToBiTree(t->firstchild);
    p->rchild=TreeToBiTree(t->nextsibling);
    return p;
}
BiTree ForestToBiTree(CSTree f){
    return TreeToBiTree(f);
}
CSTree BiTreeToTree(BiTree t){
    if(!t){
        return NULL;
    }
    CSTree p=createcsnode(t->data);
    p->firstchild=BiTreeToTree(t->lchild);
    p->nextsibling=BiTreeToTree(t->rchild);
    return p;
}
CSTree BiTreeToForest(BiTree t){
    return BiTreeToTree(t);
}
#include "../include/operations.h"

DuLinkList *InitList(DuLinkList **L){
    *L=(DuLinkList*)malloc(sizeof(DuLinkList));
    if(!*L){ return NULL; }
    (*L)->head=(Node)malloc(sizeof(struct DuLNode));
    if(!(*L)->head){ free(*L); *L=NULL; return NULL; }
    (*L)->head->prior=NULL;
    (*L)->head->next=NULL;
    (*L)->tail=(*L)->head;
    (*L)->len=0;
    return *L;
}

bool ClearList(DuLinkList *L){
    if(!L){ return false; }
    Node p=L->head->next;
    while(p){ Node q=p->next; free(p); p=q; }
    L->head->next=NULL;
    L->tail=L->head;
    L->len=0;
    return true;
}

DuLinkList *DestroyList(DuLinkList *L){
    if(L){ ClearList(L); free(L->head); free(L); }
    return NULL;
}

bool ListEmpty(DuLinkList *L){ return L&&L->len==0; }
int ListLength(DuLinkList *L){ return L?L->len:0; }

ElemType GetElem(DuLinkList *L,int i){
    if(!L||i<1||i>L->len){ exit(1); }
    Node p=L->head->next;
    for(int j=1;j<i;j++){ p=p->next; }
    return p->data;
}

int LocateElem(DuLinkList *L,ElemType e,bool(*compare)(ElemType,ElemType)){
    if(!L){ return 0; }
    Node p=L->head->next;
    int i=1;
    while(p){
        if(compare(p->data,e)){ return i; }
        p=p->next;
        i++;
    }
    return 0;
}

DuLinkList *ListInsert(DuLinkList *L,int i,ElemType e){
    if(!L||i<1||i>L->len+1){ return NULL; }
    Node q=L->head;
    for(int j=1;j<i;j++){ q=q->next; }
    Node p=(Node)malloc(sizeof(struct DuLNode));
    if(!p){ return NULL; }
    p->data=e;
    p->prior=q;
    p->next=q->next;
    if(q->next){ q->next->prior=p; }
    q->next=p;
    if(i==L->len+1){ L->tail=p; }
    L->len++;
    return L;
}

DuLinkList *ListDelete(DuLinkList *L,int i,ElemType *e){
    if(!L||i<1||i>L->len){ return NULL; }
    Node p=L->head->next;
    for(int j=1;j<i;j++){ p=p->next; }
    *e=p->data;
    p->prior->next=p->next;
    if(p->next){ p->next->prior=p->prior; }
    else{ L->tail=p->prior; }
    free(p);
    L->len--;
    return L;
}

bool ListTraverse(DuLinkList *L,void(*visit)(ElemType)){
    if(!L){ return false; }
    Node p=L->head->next;
    while(p){ visit(p->data); p=p->next; }
    return true;
}

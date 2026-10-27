#include "../include/operations.h"

CLinkList *InitList(CLinkList **L){
    *L=(CLinkList*)malloc(sizeof(CLinkList));
    if(!*L){ return NULL; }
    (*L)->head=(Node)malloc(sizeof(struct CLNode));
    if(!(*L)->head){ free(*L); *L=NULL; return NULL; }
    (*L)->head->next=(*L)->head;
    (*L)->tail=(*L)->head;
    (*L)->len=0;
    return *L;
}

bool ClearList(CLinkList *L){
    if(!L){ return false; }
    Node p=L->head->next;
    while(p!=L->head){ Node q=p->next; free(p); p=q; }
    L->head->next=L->head;
    L->tail=L->head;
    L->len=0;
    return true;
}

CLinkList *DestroyList(CLinkList *L){
    if(L){ ClearList(L); free(L->head); free(L); }
    return NULL;
}

bool ListEmpty(CLinkList *L){ return L&&L->len==0; }
int ListLength(CLinkList *L){ return L?L->len:0; }

ElemType GetElem(CLinkList *L,int i){
    if(!L||i<1||i>L->len){ exit(1); }
    Node p=L->head->next;
    for(int j=1;j<i;j++){ p=p->next; }
    return p->data;
}

int LocateElem(CLinkList *L,ElemType e,bool(*compare)(ElemType,ElemType)){
    if(!L){ return 0; }
    Node p=L->head->next;
    int i=1;
    while(p!=L->head){
        if(compare(p->data,e)){ return i; }
        p=p->next;
        i++;
    }
    return 0;
}

CLinkList *ListInsert(CLinkList *L,int i,ElemType e){
    if(!L||i<1||i>L->len+1){ return NULL; }
    Node q=L->head;
    for(int j=1;j<i;j++){ q=q->next; }
    Node p=(Node)malloc(sizeof(struct CLNode));
    if(!p){ return NULL; }
    p->data=e;
    p->next=q->next;
    q->next=p;
    if(i==L->len+1){ L->tail=p; }
    L->tail->next=L->head;
    L->len++;
    return L;
}

CLinkList *ListDelete(CLinkList *L,int i,ElemType *e){
    if(!L||i<1||i>L->len){ return NULL; }
    Node q=L->head;
    for(int j=1;j<i;j++){ q=q->next; }
    Node p=q->next;
    *e=p->data;
    q->next=p->next;
    if(i==L->len){ L->tail=q; }
    free(p);
    L->tail->next=L->head;
    L->len--;
    return L;
}

bool ListTraverse(CLinkList *L,void(*visit)(ElemType)){
    if(!L){ return false; }
    Node p=L->head->next;
    while(p!=L->head){ visit(p->data); p=p->next; }
    return true;
}

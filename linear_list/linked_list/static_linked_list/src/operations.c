#include "../include/operations.h"

int LocateElem(SLinkList L,ElemType e,bool(*compare)(ElemType,ElemType)){
    int p=L[1].cur;
    int pos=1;
    while(p!=0){
        if(compare(L[p].data,e)==true){
            return pos;
        }
        p=L[p].cur;
        pos++;
    }
    return 0;
}
//SLinkList *InitList(SLinkList L);
void InitSpace(SLinkList space){
    int i=0;
    for(i=0;i<MAXSIZE-1;i++){
        space[i].cur=i+1;
    }
    space[MAXSIZE-1].cur=0;
}
//初始化备用链表
int Malloc_SLL(SLinkList space){
    int i=space[0].cur;
    if(i!=0){
        space[0].cur=space[i].cur;
    }
    return i;
}
//从备用链表头取下一个空闲节点准备链入主链表
void Free_SLL(SLinkList space,int i){
    space[i].cur=space[0].cur;
    space[0].cur=i;
}
//释放主链表节点，头插法返回备用链表
bool ListInsert(SLinkList L,int i,ElemType e){
    int j=Malloc_SLL(L);
    if(j==0){
        return false;
    }
    L[j].data=e;
    int k=1;
    int pos=0;
    while(k!=0&&pos<i-1){
        pos++;
        k=L[k].cur;
    }
    if(k==0||pos!=i-1){
        Free_SLL(L,j);
        return false;
    }
    L[j].cur=L[k].cur;
    L[k].cur=j;
    return true;
}
//按位序插入元素
bool ListDelete(SLinkList L,int i,ElemType *e){
    int k=1;
    int pos=0;
    while(k!=0&&pos<i-1){
        pos++;
        k=L[k].cur;
    }
    if(k==0||pos!=i-1){
        return false;
    }
    *e=L[k].cur;
    L[k].cur=L[L[k].cur].cur;
    Free_SLL(L,L[k].cur);
    return true;
}
bool GetElem(SLinkList L,int i,ElemType *e){
    int k=1;
    int pos=0;
    while(k!=0&&pos<i-1){
        pos++;
        k=L[k].cur;
    }
    if(k==0||pos!=i-1){
        return false;
    }
    *e=L[L[k].cur].data;
    return true;
}
bool ListTraverse(SLinkList L,void(*visit)(ElemType)){
    int p=L[1].cur;
    while(p!=0){
        visit(L[p].data);
        p=L[p].cur;
    }
    return true;
}
int ListLength(SLinkList L){
    int p=L[1].cur;
    int len=0;
    while(p!=0){
        len++;
        p=L[p].cur;
    }
    return len;
}
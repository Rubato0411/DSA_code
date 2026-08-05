#include "common.h"

int LocateElem(SLinkList L,ElemType e,bool(*compare)(ElemType,ElemType));
//SLinkList *InitList(SLinkList L);
void InitSpace(SLinkList space);
int Malloc_SLL(SLinkList space);
void Free_SLL(SLinkList space,int i);
bool ListInsert(SLinkList L,int i,ElemType e);
bool ListDelete(SLinkList L,int i,ElemType *e);
bool GetElem(SLinkList L,int i,ElemType *e);
bool ListTraverse(SLinkList L,void(*visit)(ElemType));
int ListLength(SLinkList L);
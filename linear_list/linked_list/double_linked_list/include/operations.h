#include "common.h"

DuLinkList *InitList(DuLinkList **L);
DuLinkList *DestroyList(DuLinkList *L);
bool ClearList(DuLinkList *L);
bool ListEmpty(DuLinkList *L);
int ListLength(DuLinkList *L);
ElemType GetElem(DuLinkList *L,int i);
int LocateElem(DuLinkList *L,ElemType e,bool(*compare)(ElemType,ElemType));
DuLinkList *ListInsert(DuLinkList *L,int i,ElemType e);
DuLinkList *ListDelete(DuLinkList *L,int i,ElemType *e);
bool ListTraverse(DuLinkList *L,void(*visit)(ElemType));

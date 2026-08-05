#include "common.h"

CLinkList *InitList(CLinkList **L);
CLinkList *DestroyList(CLinkList *L);
bool ClearList(CLinkList *L);
bool ListEmpty(CLinkList *L);
int ListLength(CLinkList *L);
ElemType GetElem(CLinkList *L,int i);
int LocateElem(CLinkList *L,ElemType e,bool(*compare)(ElemType,ElemType));
CLinkList *ListInsert(CLinkList *L,int i,ElemType e);
CLinkList *ListDelete(CLinkList *L,int i,ElemType *e);
bool ListTraverse(CLinkList *L,void(*visit)(ElemType));

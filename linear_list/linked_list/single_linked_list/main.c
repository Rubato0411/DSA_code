#include "initlist.h"
#include "destroylist.h"
#include "listinsert.h"
#include "listdelete.h"
#include "listlength.h"
#include "locateelem.h"
#include "listtraverse.h"

void PrintElem(ElemType e){ printf("%d ",e); }
bool Equal(ElemType a,ElemType b){ return a==b; }

int main(){
    LinkList *L=NULL;
    ElemType e;
    if(!InitList(&L)){ return 1; }
    ListInsert(L,1,10);
    ListInsert(L,2,20);
    ListInsert(L,3,30);
    printf("list: ");
    ListTraverse(L,PrintElem);
    printf("\nlength: %d\n",ListLength(L));
    printf("20 is at: %d\n",LocateElem(L,20,Equal));
    ListDelete(L,2,&e);
    printf("delete: %d\n",e);
    L=DestroyList(L);
    return 0;
}

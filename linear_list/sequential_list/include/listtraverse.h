#include "common.h"

bool ListTraverse(Sqlist *L,void(*visit)(ElemType)); //依次对L的每个元素调用visit()，一旦visit()失败，则操作失败
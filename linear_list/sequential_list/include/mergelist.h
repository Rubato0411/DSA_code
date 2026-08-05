#include "common.h"

Sqlist *MergeList(Sqlist *la,Sqlist *lb,Sqlist *lc,bool(*compare)(ElemType,ElemType));
//将两个有序顺序表la和lb归并为一个新的有序顺序表lc，并由函数compare()确定元素的先后顺序
#include "common.h"

void CreatPolyn(polynomial *p,int m);
void DestroyPolyn(polynomial *p);
void PrintPolyn(polynomial p);
int PolynLength(polynomial p);
void AddPolyn(polynomial *p1,polynomial *p2);
void SubtractPolyn(polynomial *p1,polynomial *p2);
void MultiplyPolyn(polynomial *p1,polynomial *p2);
int cmp(term a,term b);
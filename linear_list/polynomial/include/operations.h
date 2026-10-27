#include "common.h"

void CreatPolyn(polynomial *p,int m);
void DestroyPolyn(polynomial *p);
void PrintPolyn(polynomial p);
int PolynLength(polynomial p);
void AddPolyn(polynomial *p1,polynomial *p2);
void SubtractPolyn(polynomial *p1,polynomial *p2);
void MultiplyPolyn(polynomial *p1,polynomial *p2);//选做3 乘积多项式
int cmp(term a,term b);
void SortPolynomial(polynomial *p);
float calculate(polynomial p,float x); //选做1 计算多项式在x的值
void Derivative(polynomial *p); //选做2 求导
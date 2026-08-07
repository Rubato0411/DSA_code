#include "common.h"

void InitStack(SqStack *s);
void DestroyStack(SqStack *s);
void ClearStack(SqStack *s);
bool StackEmpty(SqStack s);
int StackLength(SqStack s);
bool GetTop(SqStack s,SElemType *e);
void Push(SqStack *s,SElemType e);
bool Pop(SqStack *s,SElemType *e);
void StackTraverse(SqStack s,void(*visit)(SElemType));
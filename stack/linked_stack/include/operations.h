#include "common.h"

void InitStack(LinkedStack *s);
void DestroyStack(LinkedStack *s);
void ClearStack(LinkedStack *s);
bool StackEmpty(LinkedStack s);
int StackLength(LinkedStack s);
bool GetTop(LinkedStack s, SElemType *e);
void Push(LinkedStack *s, SElemType e);
bool Pop(LinkedStack *s, SElemType *e);
void StackTraverse(LinkedStack s, void (*visit)(SElemType));

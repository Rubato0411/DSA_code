#include "../include/operations.h"

void InitStack(LinkedStack *s){
    if(!s){
        exit(-1);
    }
    s->top=NULL;
    s->len=0;
}
void DestroyStack(LinkedStack *s){
    if(s==NULL){
        return;
    }
    ClearStack(s);
    s->top=NULL;
    s->len=0;
}
void ClearStack(LinkedStack *s){
    if(s==NULL){
        return;
    }
    StackNodePtr p=s->top;
    while(p){
        StackNodePtr q=p;
        p=p->next;
        free(q);
    }
    s->top=NULL;
    s->len=0;
}
bool StackEmpty(LinkedStack s){
    return(s.len==0);
}
int StackLength(LinkedStack s){
    return s.len;
}
bool GetTop(LinkedStack s, SElemType *e){
    if(s.len==0){
        return false;
    }
    *e=s.top->data;
    return true;
}
void Push(LinkedStack *s, SElemType e){
    if(s==NULL){
        exit(-1);
    }
    StackNodePtr p=(StackNodePtr)malloc(sizeof(StackNode));
    if(!p){
        exit(-1);
    }
    p->data=e;
    p->next=s->top;
    s->top=p;
    s->len++;
}
bool Pop(LinkedStack *s, SElemType *e){
    if(s==NULL||s->len==0){
        return false;
    }
    StackNodePtr p=s->top;
    *e=p->data;
    s->top=p->next;
    free(p);
    s->len--;
    return true;
}
void StackTraverse(LinkedStack s, void (*visit)(SElemType)){
    if(s.top==NULL||visit==NULL){
        return;
    }
    StackNodePtr p=s.top;
    while(p){
        visit(p->data);
        p=p->next;
    }
}

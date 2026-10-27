#include "../include/operations.h"

void InitStack(SqStack *s){
    if(!s){
        exit(-1);
    }
    s->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!s->base){
        exit(-1);
    }
    s->top=s->base;
    s->stacksize=STACK_INIT_SIZE;
}
void DestroyStack(SqStack *s){
    if(s==NULL||s->base==NULL){
        return;
    }
    free(s->base);
    s->base=NULL;
    s->top=NULL;
    s->stacksize=0;
}
void ClearStack(SqStack *s){
    if(s==NULL||s->base==NULL){
        return;
    }
    s->top=s->base;
}
bool StackEmpty(SqStack s){
    return(s.top==s.base);
}
int StackLength(SqStack s){
    return s.top;
}
bool GetTop(SqStack s,SElemType *e){
    if(s.base==NULL||s.top==s.base){
        return false;
    }
    *e=*(s.top-1);// 非空栈的栈顶指针始终在栈顶元素的下一个位置上
    return true;
}
void Push(SqStack *s,SElemType e){
    if(s==NULL||s->base==NULL){
        exit(-1);
    }
    if(s->top>=s->stacksize){
        int newsize=s->stacksize+STACKINCREMENT;
        SElemType *newbase=(SElemType*)realloc(s->base,newsize*sizeof(SElemType));
        if(!newbase){
            exit(-1);
        }
        s->base=newbase;
        s->stacksize=newsize;
    }
}
bool Pop(SqStack *s,SElemType *e){
    if(s==NULL||s->base==NULL){
        return false;
    }
    s->top--;
    *e=*(s->top);
    return true;
}
void StackTraverse(SqStack s,void(*visit)(SElemType)){
    if(s.base==NULL||visit==NULL){
        return;
    }
    int i=0;
    for(i=0;i<s.top;i++){
        visit(*(s.base+i));
    }
}
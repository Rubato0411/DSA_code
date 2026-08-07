#include "../include/operations.h"

void InitQueue(SqQueue *q){
    if(q==NULL){
        return;
    }
    q->base=(QElemType *)malloc(MAXSIZE*sizeof(QElemType));
    if(!q->base){
        exit(-1);
    }
    q->front=0;
    q->rear=0;
}
void DestroyQueue(SqQueue *q){
    if(q==NULL||q->base==NULL){
        return;
    }
    free(q->base);
    q->base=NULL;
    q->front=0;
    q->rear=0;
}
void ClearQueue(SqQueue *q){
    if(q==NULL||q->base==NULL){
        return;
    }
    q->front=0;
    q->rear=0;
}
bool QueueEmpty(SqQueue q){
    return q.front==q.rear;
}
int QueueLength(SqQueue q){
    return (q.rear-q.front+MAXSIZE)%MAXSIZE;
}
bool GetHead(SqQueue q, QElemType *e){
    if(q.front==q.rear){
        return false;
    }
    *e=q.base[q.front];
    return true;
}
bool EnQueue(SqQueue *q, QElemType e){
    if((q->rear+1)%MAXSIZE==q->front){
        return false;
    }
    q->base[q->rear]=e;
    q->rear=(q->rear+1)%MAXSIZE;
    return true;
}
bool DeQueue(SqQueue *q, QElemType *e){
    if(q->front==q->rear){
        return false;
    }
    *e=q->base[q->front];
    q->front=(q->front+1)%MAXSIZE;
    return true;
}
void QueueTraverse(SqQueue q, void (*visit)(QElemType)){
    int i=q.front;
    while(i!=q.rear){
        visit(q.base[i]);
        i=(i+1)%MAXSIZE;
    }
}
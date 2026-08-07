#include "../include/operations.h"

void InitQueue(LinkQueue *q){
    if(q==NULL){
        return;
    }
    q->front=(QueuePtr)malloc(sizeof(QNode));
    if(!q->front){
        exit(-1);
    }
    q->front->next=NULL;
    q->rear=q->front;
}
//为了方便后续操作使用哑头节点
void DestroyQueue(LinkQueue *q){
    if(q==NULL){
        return;
    }
    QueuePtr p=q->front;
    while(p){
        q->front=q->front->next;
        free(p);
        p=q->front;
    }
    q->rear=NULL;
    q->front=NULL;
}
void ClearQueue(LinkQueue *q){
    if(q==NULL){
        return;
    }
    DestroyQueue(q);
    InitQueue(q);
}
bool QueueEmpty(LinkQueue q){
    return q.front==q.rear;
}
int QueueLength(LinkQueue q){
    int len=0;
    if(q.front==q.rear){
        return len;
    }
    QueuePtr p=q.front->next;
    while(p){
        len++;
        p=p->next;
    }
    return len;
}
bool GetHead(LinkQueue q,QElemType *e){
    if(q.front==q.rear){
        return false;
    }
    *e=q.front->next->data;
    return true;
}
void EnQueue(LinkQueue *q,QElemType e){
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p){
        exit(-1);
    }
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
}
bool DeQueue(LinkQueue *q,QElemType *e){
    if(q->front==q->rear){
        return false;
    }
    QueuePtr p=q->front->next;
    *e=p->data;
    q->front->next=p->next;
    if(q->rear==p){
        q->rear=q->front;
    }
    free(p);
    return true;
}
void QueueTraverse(LinkQueue q,void(*visit)(QElemType)){
    if(q.front==q.rear){
        return;
    }
    QueuePtr p=q.front->next;
    while(p){
        visit(p->data);
        p=p->next;
    }
}
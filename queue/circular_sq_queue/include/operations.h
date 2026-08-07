#include "common.h"

void InitQueue(SqQueue *q);
void DestroyQueue(SqQueue *q);
void ClearQueue(SqQueue *q);
bool QueueEmpty(SqQueue q);
int QueueLength(SqQueue q);
bool GetHead(SqQueue q, QElemType *e);
bool EnQueue(SqQueue *q, QElemType e);
bool DeQueue(SqQueue *q, QElemType *e);
void QueueTraverse(SqQueue q, void (*visit)(QElemType));
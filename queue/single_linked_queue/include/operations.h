#include "common.h"

void InitQueue(LinkQueue *q);
void DeatroyQueue(LinkQueue *q);
void ClearQueue(LinkQueue *q);
bool QueueEmpty(LinkQueue q);
int QueueLength(LinkQueue q);
bool GetHead(LinkQueue q,QElemType *e);
void EnQueue(LinkQueue *q,QElemType e);
bool DeQueue(LinkQueue *q,QElemType *e);
void QueueTraverse(LinkQueue q,void(*visit)(QElemType));
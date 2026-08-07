#include "single_linked_queue/include/operations.h"

#define ARRIVAL    0    
#define DEPARTURE  1    

typedef struct EventNode {
    int time;               
    int type;               
    int customerNo;         
    struct EventNode *next;
} EventNode, *EventList;

void InitEventList(EventList *L) {
    *L = NULL;
}

bool IsEventListEmpty(EventList L) {
    return L == NULL;
}

void InsertEvent(EventList *L, int time, int type, int customerNo) {
    EventNode *p = (EventNode*)malloc(sizeof(EventNode));
    if (!p) exit(-1);
    p->time = time;
    p->type = type;
    p->customerNo = customerNo;
    p->next = NULL;
    if (*L == NULL || time < (*L)->time) {
        p->next = *L;
        *L = p;
        return;
    }
    EventNode *cur = *L;
    while (cur->next != NULL && cur->next->time <= time) {
        cur = cur->next;
    }
    p->next = cur->next;
    cur->next = p;
}

bool PopEvent(EventList *L, int *time, int *type, int *customerNo) {
    if (*L == NULL) return false;
    EventNode *p = *L;
    *time = p->time;
    *type = p->type;
    *customerNo = p->customerNo;
    *L = p->next;
    free(p);
    return true;
}

void DestroyEventList(EventList *L) {
    int t, type, no;
    while (PopEvent(L, &t, &type, &no)) ;
}

void BankSimulation() {
    EventList events;
    LinkQueue customerQueue;   
    InitEventList(&events);
    InitQueue(&customerQueue);  
    int arrivals[]  = {10, 15, 16, 22, 25, -1};
    int services[]  = {5,  3,  4,  2,  6,  0};
    int totalCust = 0;
    while (arrivals[totalCust] != -1) totalCust++;
    for (int i = 0; i < totalCust; i++) {
        InsertEvent(&events, arrivals[i], ARRIVAL, i);
    }
    int currentTime, eventType, customerNo;
    bool windowBusy = false;      
    int totalWaitTime = 0;        
    int servedCount = 0;         
    printf("总客户数: %d\n\n", totalCust);
    while (!IsEventListEmpty(events) || !QueueEmpty(customerQueue) || windowBusy) {
        if (IsEventListEmpty(events) && windowBusy) {
            break;
        }
        if (!PopEvent(&events, &currentTime, &eventType, &customerNo)) {
            break; 
        }
        if (eventType == ARRIVAL) {
            printf("时间 %d: 客户 %d 到达 (需要服务 %d 分钟)\n", 
                   currentTime, customerNo+1, services[customerNo]);

            if (!windowBusy) {
                int departTime = currentTime + services[customerNo];
                InsertEvent(&events, departTime, DEPARTURE, customerNo);
                windowBusy = true;
                printf("  → 窗口空闲，客户 %d 直接开始服务，预计 %d 离开\n", 
                       customerNo+1, departTime);
            } else {
                EnQueue(&customerQueue, customerNo);
                printf("  → 窗口忙，客户 %d 进入排队 (队列长度 %d)\n", 
                       customerNo+1, QueueLength(customerQueue));
            }
        }
        else if (eventType == DEPARTURE) {
            printf("时间 %d: 客户 %d 服务完成并离开\n", currentTime, customerNo+1);
            servedCount++;
            int waitTime = currentTime - arrivals[customerNo] - services[customerNo];
            if (waitTime > 0) {
                totalWaitTime += waitTime;
                printf("  → 该客户等待了 %d 分钟\n", waitTime);
            } else {
                printf("  → 该客户无需等待\n");
            }
            if (!QueueEmpty(customerQueue)) {
                int nextCustomer;
                DeQueue(&customerQueue, &nextCustomer);
                int departTime = currentTime + services[nextCustomer];
                InsertEvent(&events, departTime, DEPARTURE, nextCustomer);
                printf("  → 队列中客户 %d 开始服务，预计 %d 离开 (队列剩余 %d)\n",
                       nextCustomer+1, departTime, QueueLength(customerQueue));
            } else {
                windowBusy = false;
                printf("  → 队列为空，窗口变为空闲\n");
            }
        }
    }
    printf("服务客户总数: %d\n", servedCount);
    printf("总等待时间: %d 分钟\n", totalWaitTime);
    if (servedCount > 0) {
        printf("平均等待时间: %.2f 分钟\n", (float)totalWaitTime / servedCount);
    } else {
        printf("平均等待时间: 0.00 分钟\n");
    }
    ClearQueue(&customerQueue);   
    DestroyQueue(&customerQueue); 
    DestroyEventList(&events);    
}
int main() {
    BankSimulation();
    return 0;
}
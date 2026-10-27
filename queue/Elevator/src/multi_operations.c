#include "../include/multi_operations.h"

Person people[MAXSIZE];
int personState[MAXSIZE];
int personcnt=0;

void InitEventList(EventList *L){
    *L=NULL;
}

bool IsEventListEmpty(EventList L){
    return L==NULL;
}

void InsertEvent(EventList *L,int time,int floor,int type,int personNo,int elevatorNo){
    EventNode *p=(EventNode*)malloc(sizeof(EventNode));
    if(!p){
        exit(-1);
    }
    p->time=time;
    p->floor=floor;
    p->type=type;
    p->personNo=personNo;
    p->elevatorNo=elevatorNo;
    p->next=NULL;
    if(*L==NULL||time<(*L)->time){
        p->next=*L;
        *L=p;
        return;
    }
    EventNode *cur=*L;
    while(cur->next!=NULL&&cur->next->time<=time){
        cur=cur->next;
    }
    p->next=cur->next;
    cur->next=p;
}

bool PopEvent(EventList *L,int *time,int *floor,int *type,int *personNo,int *elevatorNo){
    if(*L==NULL){
        return false;
    }
    EventNode *p=*L;
    *time=p->time;
    *floor=p->floor;
    *type=p->type;
    *personNo=p->personNo;
    *elevatorNo=p->elevatorNo;
    *L=p->next;
    free(p);
    return true;
}

void DestroyEventList(EventList *L){
    int time,floor,type,personNo,elevatorNo;
    while(PopEvent(L,&time,&floor,&type,&personNo,&elevatorNo));
}

//以上是事件操作函数

bool personDelete(LinkQueue *q,int personNo){
    QueuePtr pre=q->front;
    QueuePtr cur=pre->next;
    while(cur!=NULL&&cur->data!=personNo){
        pre=cur;
        cur=cur->next;
    }
    if(cur==NULL){
        return false;
    }
    pre->next=cur->next;
    if(q->rear==cur){
        q->rear=pre;
    }
    free(cur);
    return true;
}

char *StateName(int state){
    if(state==GoingUp){
        return "GoingUp";
    }
    if(state==GoingDown){
        return "GoingDown";
    }
    return "Idle";
}

char *EventName(int type){
    char *name[]={"","M1","M2","M3","M4","M5","M6","","","","","E1","E2","E3","E4","E5","E6","E7","E8","E9"};
    if(type>=1&&type<=19){
        return name[type];
    }
    return "false";
}

bool requestTrue(Simulator *simulator,int elevatorNo,int floor){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    if(elevator->CallCar[floor]){
        return true;
    }
    if(simulator->CallUp[floor]&&simulator->assignedUp[floor]==elevatorNo){
        return true;
    }
    if(simulator->CallDown[floor]&&simulator->assignedDown[floor]==elevatorNo){
        return true;
    }
    return false;
}

bool eventTrue(Simulator *simulator,int type,int elevatorNo){
    EventNode *cur=simulator->events;
    while(cur!=NULL){
        if(cur->type==type&&cur->elevatorNo==elevatorNo){
            return true;
        }
        cur=cur->next;
    }
    return false;
}

bool personEventTrue(Simulator *simulator,int elevatorNo){
    EventNode *cur=simulator->events;
    while(cur!=NULL){
        if((cur->type==M5||cur->type==M6)&&cur->elevatorNo==elevatorNo){
            return true;
        }
        cur=cur->next;
    }
    return false;
}

void DeleteEvent(Simulator *simulator,int type,int elevatorNo){
    EventNode **cur=&simulator->events;
    while(*cur!=NULL){
        if((*cur)->type==type&&(*cur)->elevatorNo==elevatorNo){
            EventNode *temp=*cur;
            *cur=temp->next;
            free(temp);
        }else{
            cur=&(*cur)->next;
        }
    }
}

//类似单电梯的验证函数，只是多了elevatorNo参数，判断是否是指定电梯的事件

int nextFloor(Simulator *simulator,int elevatorNo){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    int i;
    if(elevator->state==GoingUp){
        for(i=elevator->floor+1;i<5;i++){
            if(requestTrue(simulator,elevatorNo,i)){
                return i;
            }
        }
        for(i=elevator->floor-1;i>=0;i--){
            if(requestTrue(simulator,elevatorNo,i)){
                return i;
            }
        }
    }else if(elevator->state==GoingDown){
        for(i=elevator->floor-1;i>=0;i--){
            if(requestTrue(simulator,elevatorNo,i)){
                return i;
            }
        }
        for(i=elevator->floor+1;i<5;i++){
            if(requestTrue(simulator,elevatorNo,i)){
                return i;
            }
        }
    }else{
        int goal=-1;
        int distance=10;
        for(i=0;i<5;i++){
            if(requestTrue(simulator,elevatorNo,i)){
                int d=i-elevator->floor;
                if(d<0){
                    d=-d;
                }
                if(d<distance){
                    distance=d;
                    goal=i;
                }
            }
        }
        return goal;
    }
    return -1;
}

//由于有多个电梯，选择距离目标楼层更近的电梯

void renewCall(Simulator *simulator,int floor){
    simulator->CallUp[floor]=0;
    simulator->CallDown[floor]=0;
    QueuePtr cur=simulator->waitingQueue[floor].front->next;
    while(cur!=NULL){
        Person *person=&people[cur->data];
        if(personState[person->No]==Waiting||personState[person->No]==Assigned){
            if(person->OutFloor>floor){
                simulator->CallUp[floor]=1;
            }else if(person->OutFloor<floor){
                simulator->CallDown[floor]=1;
            }
        }
        cur=cur->next;
    }
}

void renewCar(Simulator *simulator,int elevatorNo,int floor){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    elevator->CallCar[floor]=0;
    QueuePtr cur=elevator->InElevator.front->next;
    while(cur!=NULL){
        if(people[cur->data].OutFloor==floor){
            elevator->CallCar[floor]=1;
            return;
        }
        cur=cur->next;
    }
}

int DispatchCost(Simulator *simulator,int elevatorNo,int floor,int direction){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    int distance=elevator->floor-floor;
    if(distance<0){
        distance=-distance;
    }
    if(elevator->state==Idle){
        return distance*10+QueueLength(elevator->InElevator);
    }
    if(elevator->state==GoingUp&&floor>=elevator->floor&&direction==GoingUp){
        return distance*10+QueueLength(elevator->InElevator);
    }
    if(elevator->state==GoingDown&&floor<=elevator->floor&&direction==GoingDown){
        return distance*10+QueueLength(elevator->InElevator);
    }
    return distance*10+50+QueueLength(elevator->InElevator);
}

//代价的设计：综合考虑距离和顺路的情况
//*10是为了让距离更远的电梯代价更大，+50即加上了全部楼层的距离*10，代价更大

int DispatchElevator(Simulator *simulator,int floor,int direction){
    int elevatorNo=0;
    int minCost=DispatchCost(simulator,0,floor,direction);
    int i;
    for(i=1;i<ELEVATOR_COUNT;i++){
        int cost=DispatchCost(simulator,i,floor,direction);
        if(cost<minCost){
            minCost=cost;
            elevatorNo=i;
        }
    }
    return elevatorNo;
}

void AssignCall(Simulator *simulator,int floor,int direction){
    int elevatorNo;
    if(direction==GoingUp){
        if(simulator->assignedUp[floor]!=-1){
            return;
        }
        elevatorNo=DispatchElevator(simulator,floor,direction);
        simulator->assignedUp[floor]=elevatorNo;
    }else{
        if(simulator->assignedDown[floor]!=-1){
            return;
        }
        elevatorNo=DispatchElevator(simulator,floor,direction);
        simulator->assignedDown[floor]=elevatorNo;
    }
    Controller(simulator,elevatorNo);
}

void CancelAssignment(Simulator *simulator,int floor,int direction){
    if(direction==GoingUp&&simulator->CallUp[floor]==0){
        simulator->assignedUp[floor]=-1;
    }else if(direction==GoingDown&&simulator->CallDown[floor]==0){
        simulator->assignedDown[floor]=-1;
    }
}

//放弃的时候要调用来取消电梯的分配

void InitElevator(Elevator *elevator,int elevatorNo){
    int i;
    elevator->No=elevatorNo;
    elevator->floor=1;
    elevator->D1=0;
    elevator->D2=0;
    elevator->D3=0;
    elevator->state=Idle;
    InitQueue(&elevator->InElevator);
    for(i=0;i<5;i++){
        elevator->CallCar[i]=0;
    }
}

void InitSimulator(Simulator *simulator){
    int i;
    simulator->time=0;
    InitEventList(&simulator->events);
    for(i=0;i<ELEVATOR_COUNT;i++){
        InitElevator(&simulator->elevators[i],i);
    }
    for(i=0;i<5;i++){
        InitQueue(&simulator->waitingQueue[i]);
        simulator->CallUp[i]=0;
        simulator->CallDown[i]=0;
        simulator->assignedUp[i]=-1;
        simulator->assignedDown[i]=-1;
    }
}

void DestroySimulator(Simulator *simulator){
    int i;
    for(i=0;i<5;i++){
        DestroyQueue(&simulator->waitingQueue[i]);
    }
    for(i=0;i<ELEVATOR_COUNT;i++){
        DestroyQueue(&simulator->elevators[i].InElevator);
    }
    DestroyEventList(&simulator->events);
}

void StateChange(Simulator *simulator,int time,int elevatorNo,int floor,int state){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    simulator->time=time;
    elevator->floor=floor;
    elevator->state=state;
    printf("Time=%d Elevator=%d Floor=%d State=%s\n",time,elevatorNo,elevator->floor,StateName(elevator->state));
}

void PersonState(Simulator *simulator,Person *person,int time,int type,int no){
    printf("Time=%d Event=%s Person=%d Floor=%d\n",time,EventName(type),no,person->InFloor);
    switch(type){
        case M1:
            personState[no]=NotArrived;
            person->elevatorNo=-1;
            InsertEvent(&simulator->events,time,person->InFloor,M2,no,-1);
            break;
        case M2:
            InsertEvent(&simulator->events,time,person->InFloor,M3,no,-1);
            break;
        case M3:
            if(personState[no]!=NotArrived){
                break;
            }
            EnQueue(&simulator->waitingQueue[person->InFloor],no);
            personState[no]=Waiting;
            if(person->OutFloor>person->InFloor){
                simulator->CallUp[person->InFloor]=1;
                AssignCall(simulator,person->InFloor,GoingUp);
            }else{
                simulator->CallDown[person->InFloor]=1;
                AssignCall(simulator,person->InFloor,GoingDown);
            }
            InsertEvent(&simulator->events,person->ArrivalTime+person->GiveupTime,person->InFloor,M4,no,-1);
            break;
        case M4:
            if(personState[no]!=Waiting&&personState[no]!=Assigned){
                break;
            }
            if(personDelete(&simulator->waitingQueue[person->InFloor],no)){
                personState[no]=GaveUp;
                renewCall(simulator,person->InFloor);
                CancelAssignment(simulator,person->InFloor,GoingUp);
                CancelAssignment(simulator,person->InFloor,GoingDown);
                printf("Time=%d Person=%d GaveUp at floor %d\n",time,no,person->InFloor);
            }
            break;
        case M5:{
            int elevatorNo=person->elevatorNo;
            if(personState[no]!=Assigned||elevatorNo<0||elevatorNo>=ELEVATOR_COUNT){
                break;
            }
            Elevator *elevator=&simulator->elevators[elevatorNo];
            if(personDelete(&simulator->waitingQueue[person->InFloor],no)){
                EnQueue(&elevator->InElevator,no);
                personState[no]=In_Elevator;
                elevator->CallCar[person->OutFloor]=1;
                renewCall(simulator,person->InFloor);
                CancelAssignment(simulator,person->InFloor,GoingUp);
                CancelAssignment(simulator,person->InFloor,GoingDown);
                printf("Time=%d Person=%d InElevator=%d at floor %d\n",time,no,elevatorNo,person->InFloor);
            }
            if(personEventTrue(simulator,elevatorNo)==false){
                elevator->D1=0;
                elevator->D3=1;
            }
            break;
        }
        case M6:{
            int elevatorNo=person->elevatorNo;
            if(personState[no]!=In_Elevator||elevatorNo<0||elevatorNo>=ELEVATOR_COUNT){
                break;
            }
            Elevator *elevator=&simulator->elevators[elevatorNo];
            if(personDelete(&elevator->InElevator,no)){
                personState[no]=Left;
                renewCar(simulator,elevatorNo,person->OutFloor);
                printf("Time=%d Person=%d Left Elevator=%d at floor %d\n",time,no,elevatorNo,person->OutFloor);
            }
            if(personEventTrue(simulator,elevatorNo)==false){
                elevator->D1=0;
                elevator->D3=1;
            }
            break;
        }
    }
}

int Controller(Simulator *simulator,int elevatorNo){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    int goal;
    if(elevator->D3!=0){
        return elevator->floor;
    }
    if(requestTrue(simulator,elevatorNo,elevator->floor)){
        DeleteEvent(simulator,E1,elevatorNo);
        if(eventTrue(simulator,E3,elevatorNo)==false){
            InsertEvent(&simulator->events,simulator->time+20,elevator->floor,E3,-1,elevatorNo);
        }
        return elevator->floor;
    }
    goal=nextFloor(simulator,elevatorNo);
    if(goal==-1){
        elevator->state=Idle;
        if(eventTrue(simulator,E1,elevatorNo)==false){
            InsertEvent(&simulator->events,simulator->time+300,elevator->floor,E1,-1,elevatorNo);
        }
        return -1;
    }
    if(goal>elevator->floor){
        elevator->state=GoingUp;
    }else{
        elevator->state=GoingDown;
    }
    DeleteEvent(simulator,E1,elevatorNo);
    if(eventTrue(simulator,E6,elevatorNo)==false){
        InsertEvent(&simulator->events,simulator->time,elevator->floor,E6,-1,elevatorNo);
    }
    return goal;
}

void ElevatorState(Simulator *simulator,int time,int floor,int state,int elevatorNo){
    Elevator *elevator=&simulator->elevators[elevatorNo];
    int person[MAXSIZE];
    int cnt=0;
    int delay=0;
    int goal;
    int i;
    simulator->time=time;
    printf("Time=%d Event=%s Elevator=%d Floor=%d State=%s\n",time,EventName(state),elevatorNo,elevator->floor,StateName(elevator->state));
    switch(state){
        case E1:
            if(elevator->state!=Idle){
                break;
            }
            if(nextFloor(simulator,elevatorNo)!=-1||requestTrue(simulator,elevatorNo,elevator->floor)){
                Controller(simulator,elevatorNo);
            }else if(elevator->floor!=1){
                elevator->CallCar[1]=1;
                Controller(simulator,elevatorNo);
            }
            break;
        case E2:
            if(requestTrue(simulator,elevatorNo,elevator->floor)){
                if(eventTrue(simulator,E3,elevatorNo)==false){
                    InsertEvent(&simulator->events,time,elevator->floor,E3,-1,elevatorNo);
                }
            }else{
                Controller(simulator,elevatorNo);
            }
            break;
        case E3:
            elevator->D1=1;
            elevator->D2=1;
            elevator->D3=0;
            InsertEvent(&simulator->events,time+20,elevator->floor,E4,-1,elevatorNo);
            InsertEvent(&simulator->events,time+76,elevator->floor,E5,-1,elevatorNo);
            InsertEvent(&simulator->events,time+300,elevator->floor,E9,-1,elevatorNo);
            break;
        case E4:{
            QueuePtr cur=elevator->InElevator.front->next;
            while(cur!=NULL){
                if(people[cur->data].OutFloor==elevator->floor){
                    person[cnt++]=cur->data;
                }
                cur=cur->next;
            }
            for(i=cnt-1;i>=0;i--){
                delay+=25;
                InsertEvent(&simulator->events,time+delay,elevator->floor,M6,person[i],elevatorNo);
            }
            cur=simulator->waitingQueue[elevator->floor].front->next;
            while(cur!=NULL){
                Person *p=&people[cur->data];
                int assigned=p->OutFloor>p->InFloor?simulator->assignedUp[elevator->floor]:simulator->assignedDown[elevator->floor];
                if(assigned==elevatorNo&&personState[p->No]==Waiting){
                    delay+=25;
                    p->elevatorNo=elevatorNo;
                    personState[p->No]=Assigned;
                    InsertEvent(&simulator->events,time+delay,elevator->floor,M5,p->No,elevatorNo);
                }
                cur=cur->next;
            }
            if(delay==0){
                elevator->D1=0;
                elevator->D3=1;
            }
            break;
        }
        case E5:
            if(elevator->D1!=0){
                InsertEvent(&simulator->events,time+40,elevator->floor,E5,-1,elevatorNo);
            }else{
                elevator->D3=0;
                InsertEvent(&simulator->events,time+20,elevator->floor,E6,-1,elevatorNo);
            }
            break;
        case E6:
            DeleteEvent(simulator,E9,elevatorNo);
            DeleteEvent(simulator,E7,elevatorNo);
            DeleteEvent(simulator,E8,elevatorNo);
            elevator->D2=0;
            renewCar(simulator,elevatorNo,elevator->floor);
            goal=nextFloor(simulator,elevatorNo);
            if(goal==-1){
                elevator->state=Idle;
                if(eventTrue(simulator,E1,elevatorNo)==false){
                    InsertEvent(&simulator->events,time+300,elevator->floor,E1,-1,elevatorNo);
                }
            }else if(goal>elevator->floor){
                elevator->state=GoingUp;
                InsertEvent(&simulator->events,time+66,elevator->floor,E7,-1,elevatorNo);
            }else if(goal<elevator->floor){
                elevator->state=GoingDown;
                InsertEvent(&simulator->events,time+76,elevator->floor,E8,-1,elevatorNo);
            }else{
                InsertEvent(&simulator->events,time,elevator->floor,E3,-1,elevatorNo);
            }
            break;
        case E7:
            if(elevator->floor>=4){
                Controller(simulator,elevatorNo);
                break;
            }
            elevator->floor++;
            if(requestTrue(simulator,elevatorNo,elevator->floor)){
                InsertEvent(&simulator->events,time+14,elevator->floor,E2,-1,elevatorNo);
            }else if(nextFloor(simulator,elevatorNo)==-1){
                Controller(simulator,elevatorNo);
            }else{
                InsertEvent(&simulator->events,time+51,elevator->floor,E7,-1,elevatorNo);
            }
            break;
        case E8:
            if(elevator->floor<=0){
                Controller(simulator,elevatorNo);
                break;
            }
            elevator->floor--;
            if(requestTrue(simulator,elevatorNo,elevator->floor)){
                InsertEvent(&simulator->events,time+23,elevator->floor,E2,-1,elevatorNo);
            }else if(nextFloor(simulator,elevatorNo)==-1){
                Controller(simulator,elevatorNo);
            }else{
                InsertEvent(&simulator->events,time+61,elevator->floor,E8,-1,elevatorNo);
            }
            break;
        case E9:
            elevator->D2=0;
            Controller(simulator,elevatorNo);
            break;
    }
    floor=floor;
}

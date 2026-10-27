#include "../include/operations.h"

Person people[MAXSIZE];
int personState[MAXSIZE];
int personcnt=0;

void InitEventList(EventList *L){
    *L=NULL;
}

bool IsEventListEmpty(EventList L){
    return L==NULL;
}

void InsertEvent(EventList *L,int time,int floor, int type, int personNo){
    EventNode *p=(EventNode*)malloc(sizeof(EventNode));
    if(!p){
        exit(-1);
    }
    p->time=time;
    p->type=type;
    p->personNo=personNo;
    p->floor=floor;
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

bool PopEvent(EventList *L,int *time,int *floor,int *type,int *personNo){
    if(*L==NULL){
        return false;
    }
    EventNode* p=*L;
    *time=p->time;
    *floor=p->floor;
    *type=p->type;
    *personNo=p->personNo;
    *L=p->next;
    free(p);
    return true;
}

void DestroyEventList(EventList *L){
    int t,f,type,no;
    while(PopEvent(L,&t,&f,&type,&no));//在循环内全部pop出去，直到返回false函数结束
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
}//用于删除已经处理过的人，包括giveup的对象

char *StateName(int state){
    if(state==GoingUp){
        return "GoingUp";
    }
    if(state==GoingDown){
        return "GoingDown";
    }
    return "Idle";
}//辅助函数

char *EventName(int type){
    char *name[]={"","M1","M2","M3","M4","M5","M6","","","","","E1","E2","E3","E4","E5","E6","E7","E8","E9"};
    if(type>=1&&type<=19){
        return name[type];
    }
    return "false";
}//辅助函数

bool requestTrue(Simulator *simulator,int floor){
    if(simulator->CallUp[floor]==1||simulator->CallDown[floor]==1||simulator->CallCar[floor]==1){
        return true;
    }else{
        return false;
    }
}//辅助判断当前是否有需要完成的请求

bool eventTrue(Simulator *simulator,int type){
    EventNode *cur=simulator->events;
    while(cur!=NULL){
        if(cur->type==type){
            return true;
        }
        cur=cur->next;
    }
    return false;
}//辅助判断当前是否有需要完成的事件

bool personEventTrue(Simulator *simulator){
    EventNode *cur=simulator->events;
    while(cur!=NULL){
        if(cur->type==M5||cur->type==M6){
            return true;
        }
        cur=cur->next;
    }
    return false;
}//辅助判断是否还有人正在进出电梯

void DeleteEvent(Simulator *simulator,int type){
    EventNode **cur=&simulator->events;
    while(*cur!=NULL){
        if((*cur)->type==type){
            EventNode *temp=*cur;
            *cur=temp->next;
            free(temp);
        }else{
            cur=&(*cur)->next;
        }
    }
}//删除指定类型的事件

int nextFloor(Simulator *simulator){
    int i;
    if(simulator->state==GoingUp){
        for(i=simulator->floor+1;i<5;i++){
            if(requestTrue(simulator,i)){
                return i;
            }
        }
        for(i=simulator->floor-1;i>=0;i--){
            if(requestTrue(simulator,i)){
                return i;
            }
        }
    }else if(simulator->state==GoingDown){
        for(i=simulator->floor-1;i>=0;i--){
            if(requestTrue(simulator,i)){
                return i;
            }
        }
        for(i=simulator->floor+1;i<5;i++){
            if(requestTrue(simulator,i)){
                return i;
            }
        }
    }else{
        int goal=-1;
        int distance=10;
        for(i=0;i<5;i++){
            if(requestTrue(simulator,i)){
                int d=i-simulator->floor;
                if(d<0){
                    d=-d;
                }
                if(d<distance){
                    distance=d;
                    goal=i;
                }
            }
        }//idle状态下寻找最近的请求
        return goal;
    }

    return -1;
}//辅助函数，寻找下一个去的楼层，否则返回-1

void renewCall(Simulator *simulator,int floor){
    simulator->CallUp[floor]=0;
    simulator->CallDown[floor]=0;
    QueuePtr cur=simulator->waitingQueue[floor].front->next;
    while(cur!=NULL){
        Person* person=&people[cur->data];
        if(person->OutFloor>floor){
            simulator->CallUp[floor]=1;
        }else if(person->OutFloor<floor){
            simulator->CallDown[floor]=1;
        }
        cur=cur->next;
    }
}//更新请求状态

void renewCar(Simulator* simulator,int floor){
    simulator->CallCar[floor]=0;
    QueuePtr cur=simulator->InElevator.front->next;
    while(cur!=NULL){
        if(people[cur->data].OutFloor==floor){
            simulator->CallCar[floor]=1;
            break;
        }
        cur=cur->next;
    }
}//更新轿厢内的状态

void StateChange(Simulator *simulator,int time,int floor,int state){
    simulator->time=time;
    simulator->floor=floor;
    simulator->state=state;
    printf("Time=%d Floor=%d State=%s\n",simulator->time,simulator->floor,StateName(simulator->state));
}

void PersonState(Simulator *simulator,Person *person,int time,int type,int no){
    printf("Time=%d Event=%s Person=%d Floor=%d\n",time,EventName(type),no,person->InFloor);
    switch(type){
        case M1:
            personState[no]=NotArrived;
            InsertEvent(&simulator->events,time,person->InFloor,M2,no);
            break;
        case M2:
            InsertEvent(&simulator->events,time,person->InFloor,M3,no);
            break;
        case M3:
            if(personState[no]!=NotArrived){
                break;
            }
            EnQueue(&simulator->waitingQueue[person->InFloor],no);
            personState[no]=Waiting;
            if(person->OutFloor>person->InFloor){
                simulator->CallUp[person->InFloor]=1;
            }
            else{
                simulator->CallDown[person->InFloor]=1;
            }
            InsertEvent(&simulator->events,person->ArrivalTime+person->GiveupTime,person->InFloor,M4,no);
            if(simulator->state==Idle&&simulator->D3==0){
                Controller(simulator);
            }
            break;
        case M4:
            if(personState[no]!=Waiting){
                break;
            }
            if(personDelete(&simulator->waitingQueue[person->InFloor],no)){
                personState[no]=GaveUp;
                renewCall(simulator,person->InFloor);
                printf("Time=%d Person=%d GaveUp at floor %d\n",time,no,person->InFloor);
            }
            break;
        case M5:
            if(personState[no]!=Waiting){
                break;
            }
            if(personDelete(&simulator->waitingQueue[person->InFloor],no)){
                EnQueue(&simulator->InElevator,no);
                personState[no]=In_Elevator;
                renewCall(simulator,person->InFloor);//需要更新请求状态，因为有人进入电梯
                simulator->CallCar[person->OutFloor]=1;
                printf("Time=%d Person=%d InElevator at floor %d\n",time,no,person->InFloor);
            }
            if(personEventTrue(simulator)==false){
                simulator->D1=0;
                simulator->D3=1;
            }
            break;
        case M6:
            if(personState[no]!=In_Elevator){
                break;
            }
            if(personDelete(&simulator->InElevator,no)){
                personState[no]=Left;
                renewCar(simulator,person->OutFloor);//需要更新请求状态，因为有人离开电梯
                printf("Time=%d Person=%d Left at floor %d\n",time,no,person->OutFloor);
            }
            if(personEventTrue(simulator)==false){
                simulator->D1=0;
                simulator->D3=1;
            }
            break;
    }
}
int Controller(Simulator *simulator){
    int goal;
    if(simulator->D3!=0){
        return simulator->floor;
    }
    if(requestTrue(simulator,simulator->floor)){
        DeleteEvent(simulator,E1);
        if(eventTrue(simulator,E3)==false){
            InsertEvent(&simulator->events,simulator->time+20,simulator->floor,E3,-1);
        }
        return simulator->floor;
    }//如果当前楼层有请求，则直接处理
    goal=nextFloor(simulator);
    if(goal==-1){
        simulator->state=Idle;
        if(requestTrue(simulator,simulator->floor)==false&&eventTrue(simulator,E1)==false){
            InsertEvent(&simulator->events,simulator->time+300,simulator->floor,E1,-1);
        }
        return -1;
    }
    if(goal>simulator->floor){
        simulator->state=GoingUp;
    }else{
        simulator->state=GoingDown;
    }
    DeleteEvent(simulator,E1);//取消原本的返回1层事件
    if(eventTrue(simulator,E6)==false){
        InsertEvent(&simulator->events,simulator->time,simulator->floor,E6,-1);
    }
    return goal;

}
void ElevatorState(Simulator *simulator,int time,int floor,int state){
    int person[MAXSIZE];
    int cnt=0;
    int delay;
    int goal;
    int i=0;
    simulator->time=time;
    printf("Time=%d Floor=%d State=%s\n",simulator->time,simulator->floor,StateName(simulator->state));
    switch(state){
        case E1:
            if(simulator->state!=Idle){
                break;
            }
            if(nextFloor(simulator)!=-1||requestTrue(simulator,simulator->floor)==true){
                Controller(simulator);
            }else if(simulator->floor!=1){
                simulator->CallCar[1]=1;
                Controller(simulator);
            }else{
                simulator->state=Idle;
            }
            break;
        case E2:
            if(requestTrue(simulator,simulator->floor)==true){
                if(eventTrue(simulator,E3)==false){
                    InsertEvent(&simulator->events,time,simulator->floor,E3,-1);
                }
            }else{
                Controller(simulator);
            }
            break;
        case E3:
            simulator->D1=1;
            simulator->D2=1;
            simulator->D3=0;
            InsertEvent(&simulator->events,time+20,simulator->floor,E4,-1);
            InsertEvent(&simulator->events,time+76,simulator->floor,E5,-1);
            InsertEvent(&simulator->events,time+300,simulator->floor,E9,-1);
            break;
        case E4:
            cnt=0;
            delay=0;
            QueuePtr cur=simulator->InElevator.front->next;
            while(cur!=NULL){
                if(people[cur->data].OutFloor==simulator->floor){
                    person[cnt++]=cur->data;
                }
                cur=cur->next;
            }
            for(i=cnt-1;i>=0;i--){
                delay+=25;
                InsertEvent(&simulator->events,time+delay,simulator->floor,M6,person[i]);
            }
            cur=simulator->waitingQueue[simulator->floor].front->next;
            while(cur!=NULL){
                delay+=25;
                InsertEvent(&simulator->events,time+delay,simulator->floor,M5,cur->data);
                cur=cur->next;
            }
            if(delay==0){
                simulator->D1=0;
                simulator->D3=1;
            }
            break;
        case E5:
            if(simulator->D1!=0){
                InsertEvent(&simulator->events,time+40,simulator->floor,E5,-1);
            }else{
                simulator->D3=0;
                InsertEvent(&simulator->events,time+20,simulator->floor,E6,-1);
            }
            break;
        case E6:
            DeleteEvent(simulator,E9);
            DeleteEvent(simulator,E7);
            DeleteEvent(simulator,E8);
            simulator->D2=0;
            renewCall(simulator,simulator->floor);
            renewCar(simulator,simulator->floor);
            goal=nextFloor(simulator);
            if(goal==-1){
                simulator->state=Idle;
                if(requestTrue(simulator,simulator->floor)==false){
                    if(eventTrue(simulator,E1)==false){
                        InsertEvent(&simulator->events,time+300,simulator->floor,E1,-1);
                    }
                }
            }else if(goal>simulator->floor){
                simulator->state=GoingUp;
                if(eventTrue(simulator,E7)==false){
                    InsertEvent(&simulator->events,time+66,simulator->floor,E7,-1);
                }
            }else if(goal<simulator->floor){
                simulator->state=GoingDown;
                if(eventTrue(simulator,E8)==false){
                    InsertEvent(&simulator->events,time+76,simulator->floor,E8,-1);
                }
            }else{
                InsertEvent(&simulator->events,time,simulator->floor,E3,-1);
            }
            break;
        case E7:
            if(simulator->floor>=4){
                simulator->state=GoingDown;
                Controller(simulator);
                break;
            }
            simulator->floor++;
            if(requestTrue(simulator,simulator->floor)){
                if(eventTrue(simulator,E2)==false){
                    InsertEvent(&simulator->events,time+14,simulator->floor,E2,-1);
                }
            }else{
                if(eventTrue(simulator,E7)==false){
                    InsertEvent(&simulator->events,time+51,simulator->floor,E7,-1);
                }
            }
            break;
        case E8:
            if(simulator->floor<=0){
                simulator->state=GoingUp;
                Controller(simulator);
                break;
            }
            simulator->floor--;
            if(requestTrue(simulator,simulator->floor)){
                if(eventTrue(simulator,E2)==false){
                    InsertEvent(&simulator->events,time+23,simulator->floor,E2,-1);
                }
            }else{
                if(eventTrue(simulator,E8)==false){
                    InsertEvent(&simulator->events,time+61,simulator->floor,E8,-1);
                }
            }
            break;
        case E9:
            simulator->D2=0;
            Controller(simulator);
            break;
    }
    floor=floor;
}



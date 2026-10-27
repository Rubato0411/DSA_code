#include "include/operations.h"

typedef struct TestPerson{
    int No;
    int ArrivalTime;
    int InFloor;
    int OutFloor;
    int GiveupTime;
}TestPerson;

int main(){
    TestPerson Data[]={
        {1,0,1,4,500},
        {2,100,0,3,300},
        {3,150,2,0,500},
        {4,200,3,1,500},
        {5,250,4,0,500},
        {6,300,1,2,100},
        {7,400,0,4,500},
        {8,500,2,3,500},
        {9,1000,1,0,500},
        {10,1500,3,2,500},
        {11,2000,4,1,500},
        {12,2500,0,4,200},
        {13,3000,2,1,500},
        {14,3500,1,3,500},
        {15,4000,3,0,500}
    };
    personcnt=15;

    Simulator simulator;
    int time;
    int floor;
    int type;
    int personNo;
    int i;
    simulator.time=0;
    simulator.floor=1;
    simulator.D1=0;
    simulator.D2=0;
    simulator.D3=0;
    simulator.state=Idle;
    InitEventList(&simulator.events);
    InitQueue(&simulator.InElevator);
    for(i=0;i<5;i++){
        InitQueue(&simulator.waitingQueue[i]);
        simulator.CallCar[i]=0;
        simulator.CallUp[i]=0;
        simulator.CallDown[i]=0;
    }
    for(i=0;i<MAXSIZE;i++){
        personState[i]=NotArrived;
    }
    for(i=0;i<personcnt;i++){
        int no=Data[i].No;
        people[no].No=no;
        people[no].ArrivalTime=Data[i].ArrivalTime;
        people[no].InFloor=Data[i].InFloor;
        people[no].OutFloor=Data[i].OutFloor;
        people[no].GiveupTime=Data[i].GiveupTime;
        if(i<personcnt-1){
            people[no].InterTime=Data[i+1].ArrivalTime-Data[i].ArrivalTime;
        }else{
            people[no].InterTime=0;
        }
        InsertEvent(&simulator.events,people[no].ArrivalTime,people[no].InFloor,M1,no);
    }
    while(PopEvent(&simulator.events,&time,&floor,&type,&personNo)){
        if(time>END_TIME){
            break;
        }
        simulator.time=time;
        if(type>=M1&&type<=M6){
            PersonState(&simulator,&people[personNo],time,type,personNo);
        }else if(type>=E1&&type<=E9){
            ElevatorState(&simulator,time,floor,type);
        }
    }
    printf("Simulation finished.\n");
    for(i=0;i<5;i++){
        DestroyQueue(&simulator.waitingQueue[i]);
    }
    DestroyQueue(&simulator.InElevator);
    DestroyEventList(&simulator.events);
    return 0;
}

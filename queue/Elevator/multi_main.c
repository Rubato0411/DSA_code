#include "include/multi_operations.h"

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
    Simulator simulator;
    int time;
    int floor;
    int type;
    int personNo;
    int elevatorNo;
    int i;
    int left=0;
    int gaveup=0;

    InitSimulator(&simulator);

    for(i=0;i<MAXSIZE;i++){
        personState[i]=NotArrived;
    }

    personcnt=15;
    for(i=0;i<personcnt;i++){
        int no=Data[i].No;
        people[no].No=no;
        people[no].ArrivalTime=Data[i].ArrivalTime;
        people[no].InFloor=Data[i].InFloor;
        people[no].OutFloor=Data[i].OutFloor;
        people[no].GiveupTime=Data[i].GiveupTime;
        people[no].elevatorNo=-1;
        if(i<personcnt-1){
            people[no].InterTime=Data[i+1].ArrivalTime-Data[i].ArrivalTime;
        }else{
            people[no].InterTime=0;
        }
        InsertEvent(&simulator.events,people[no].ArrivalTime,people[no].InFloor,M1,no,-1);
    }

    while(PopEvent(&simulator.events,&time,&floor,&type,&personNo,&elevatorNo)){
        if(time>END_TIME){
            break;
        }
        simulator.time=time;
        if(type>=M1&&type<=M6){
            PersonState(&simulator,&people[personNo],time,type,personNo);
        }else if(type>=E1&&type<=E9&&elevatorNo>=0&&elevatorNo<ELEVATOR_COUNT){
            ElevatorState(&simulator,time,floor,type,elevatorNo);
        }
    }

    for(i=1;i<=personcnt;i++){
        if(personState[i]==Left){
            left++;
        }else if(personState[i]==GaveUp){
            gaveup++;
        }
    }

    printf("Simulation finished at Time=%d\n",simulator.time);
    printf("Left=%d GaveUp=%d Total=%d\n",left,gaveup,left+gaveup);
    for(i=0;i<ELEVATOR_COUNT;i++){
        printf("Elevator=%d Floor=%d State=%s\n",i,simulator.elevators[i].floor,StateName(simulator.elevators[i].state));
    }

    DestroySimulator(&simulator);
    return 0;
}

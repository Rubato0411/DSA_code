#ifndef ELEVATOR_COMMON_H
#define ELEVATOR_COMMON_H

#include "../../single_linked_queue/include/operations.h"

#define GoingUp 1
#define GoingDown -1
#define Idle 0

#define NotArrived 0
#define Waiting 1
#define In_Elevator 2
#define Left 3
#define GaveUp 4

#define timeUnit 0.1
#define END_TIME 6000

#define M1 1
#define M2 2
#define M3 3
#define M4 4
#define M5 5
#define M6 6

#define E1 11
#define E2 12
#define E3 13
#define E4 14
#define E5 15
#define E6 16
#define E7 17
#define E8 18
#define E9 19

#define MAXSIZE 100

typedef struct EventNode{
    int time;
    int type;
    int personNo;
    int floor;
    struct EventNode *next;
}EventNode,*EventList;

typedef struct Simulator{
    int time;
    int floor;
    int D1;
    int D2;
    int D3;
    int state;
    LinkQueue waitingQueue[5];
    int CallCar[5];
    int CallUp[5];
    int CallDown[5];
    LinkQueue InElevator;
    EventList events;
}Simulator;

typedef struct Person{
    int No;
    int InFloor;
    int OutFloor;
    int GiveupTime;
    int InterTime;
    int ArrivalTime;
}Person;

extern Person people[MAXSIZE];
extern int personState[MAXSIZE];
extern int personcnt;

#endif

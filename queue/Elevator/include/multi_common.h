#ifndef MULTI_ELEVATOR_COMMON_H
#define MULTI_ELEVATOR_COMMON_H

#include "../../single_linked_queue/include/operations.h"

#define ELEVATOR_COUNT 2
#define MAXSIZE 100
#define END_TIME 6000

#define GoingUp 1
#define GoingDown -1
#define Idle 0

#define NotArrived 0
#define Waiting 1
#define Assigned 2
#define In_Elevator 3
#define Left 4
#define GaveUp 5

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

typedef struct EventNode{
    int time;
    int type;
    int personNo;
    int elevatorNo;
    int floor;
    struct EventNode *next;
}EventNode,*EventList;

typedef struct Elevator{
    int No;
    int floor;
    int D1;
    int D2;
    int D3;
    int state;
    int CallCar[5];
    LinkQueue InElevator;
}Elevator;

typedef struct Simulator{
    int time;
    Elevator elevators[ELEVATOR_COUNT];
    LinkQueue waitingQueue[5];
    int CallUp[5];
    int CallDown[5];
    int assignedUp[5];
    int assignedDown[5];
    EventList events;
}Simulator;

typedef struct Person{
    int No;
    int InFloor;
    int OutFloor;
    int GiveupTime;
    int InterTime;
    int ArrivalTime;
    int elevatorNo;
}Person;

extern Person people[MAXSIZE];
extern int personState[MAXSIZE];
extern int personcnt;

#endif
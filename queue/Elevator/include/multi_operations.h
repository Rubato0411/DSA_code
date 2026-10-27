#ifndef MULTI_ELEVATOR_OPERATIONS_H
#define MULTI_ELEVATOR_OPERATIONS_H

#include "multi_common.h"

void InitEventList(EventList *L);
bool IsEventListEmpty(EventList L);
void InsertEvent(EventList *L,int time,int floor,int type,int personNo,int elevatorNo);
bool PopEvent(EventList *L,int *time,int *floor,int *type,int *personNo,int *elevatorNo);
void DestroyEventList(EventList *L);

bool personDelete(LinkQueue *q,int personNo);

char *StateName(int state);
char *EventName(int type);
bool requestTrue(Simulator *simulator,int elevatorNo,int floor);
bool eventTrue(Simulator *simulator,int type,int elevatorNo);
bool personEventTrue(Simulator *simulator,int elevatorNo);

void DeleteEvent(Simulator *simulator,int type,int elevatorNo);

int nextFloor(Simulator *simulator,int elevatorNo);
void renewCall(Simulator *simulator,int floor);
void renewCar(Simulator *simulator,int elevatorNo,int floor);

int DispatchCost(Simulator *simulator,int elevatorNo,int floor,int direction);
int DispatchElevator(Simulator *simulator,int floor,int direction);
void AssignCall(Simulator *simulator,int floor,int direction);
void CancelAssignment(Simulator *simulator,int floor,int direction);

void InitElevator(Elevator *elevator,int elevatorNo);
void InitSimulator(Simulator *simulator);
void DestroySimulator(Simulator *simulator);

void StateChange(Simulator *simulator,int time,int elevatorNo,int floor,int state);
void PersonState(Simulator *simulator,Person *person,int time,int type,int no);
int Controller(Simulator *simulator,int elevatorNo);
void ElevatorState(Simulator *simulator,int time,int floor,int state,int elevatorNo);


#endif
#ifndef MULTI_ELEVATOR_OPERATIONS_H
#define MULTI_ELEVATOR_OPERATIONS_H

#include "multi_common.h"

void InitEventList(EventList *L);
bool IsEventListEmpty(EventList L);
void InsertEvent(EventList *L,int time,int floor,int type,int personNo,int elevatorNo);
bool PopEvent(EventList *L,int *time,int *floor,int *type,int *personNo,int *elevatorNo);
void DestroyEventList(EventList *L);

bool personDelete(LinkQueue *q,int personNo);
char *StateName(int state);
char *EventName(int type);
bool requestTrue(Simulator *simulator,int elevatorNo,int floor);
bool eventTrue(Simulator *simulator,int type,int elevatorNo);
bool personEventTrue(Simulator *simulator,int elevatorNo);
void DeleteEvent(Simulator *simulator,int type,int elevatorNo);
int nextFloor(Simulator *simulator,int elevatorNo);
void renewCall(Simulator *simulator,int floor);
void renewCar(Simulator *simulator,int elevatorNo,int floor);

int DispatchCost(Simulator *simulator,int elevatorNo,int floor,int direction);
int DispatchElevator(Simulator *simulator,int floor,int direction);
void AssignCall(Simulator *simulator,int floor,int direction);
void CancelAssignment(Simulator *simulator,int floor,int direction);

void InitElevator(Elevator *elevator,int elevatorNo);
void InitSimulator(Simulator *simulator);
void DestroySimulator(Simulator *simulator);

void StateChange(Simulator *simulator,int time,int elevatorNo,int floor,int state);
void PersonState(Simulator *simulator,Person *person,int time,int type,int no);
int Controller(Simulator *simulator,int elevatorNo);
void ElevatorState(Simulator *simulator,int time,int floor,int state,int elevatorNo);

#endif

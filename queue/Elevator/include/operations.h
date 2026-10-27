#ifndef ELEVATOR_OPERATIONS_H
#define ELEVATOR_OPERATIONS_H

#include "common.h"

void InitEventList(EventList *L);
bool IsEventListEmpty(EventList L);
void InsertEvent(EventList *L,int time,int floor,int type,int personNo);
bool PopEvent(EventList *L,int *time,int *floor,int *type,int *personNo);
void DestroyEventList(EventList *L);

void StateChange(Simulator *simulator,int time,int floor,int state);
void PersonState(Simulator *simulator,Person *person,int time,int type,int no);
int Controller(Simulator *simulator);
void ElevatorState(Simulator *simulator,int time,int floor,int state);

#endif

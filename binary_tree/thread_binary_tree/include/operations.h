#include"common.h"

void createbithrtree(BiThrTree *t);
void inordertraverse(BiThrTree t,void(*visit)(TElemType));
void inorderthreading(BiThrTree t,BiThrTree *thrt);
void destroybithrtree(BiThrTree *t);
bool bithrtreeempty(BiThrTree t);

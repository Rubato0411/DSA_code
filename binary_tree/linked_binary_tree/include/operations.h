#include "common.h"

void createbitree(BiTree *t);
void preordertraverse(BiTree t,void(*visit)(TElemType));
void inordertraverse(BiTree t,void(*visit)(TElemType));
void postordertraverse(BiTree t,void(*visit)(TElemType));
void levelordertraverse(BiTree t,void(*visit)(TElemType));
void initbitree(BiTree *t);
void destroybitree(BiTree *t);
bool bitreeempty(BiTree t);
int bitreedepth(BiTree t);
BiTree findnode(BiTree t,TElemType e);
bool parent(BiTree t,TElemType e,TElemType *res);
void clearbitree(BiTree *t);
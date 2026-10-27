#include "common.h"

void CreateGraph(ALGraph *G);
void InitGraph(ALGraph *G);
bool DestroyGraph(ALGraph *G);
bool GetVex(ALGraph G,int v,VertexType *value);
bool PutVex(ALGraph *G,int v,VertexType value);
VertexType FirstAdjVex(ALGraph G,int v);
VertexType NextAdjVex(ALGraph G,int v,int w);
bool InsertVex(ALGraph *G,VertexType v);
bool DeleteVex(ALGraph *G,int v);
bool InsertArc(ALGraph *G,int v,int w);
bool DeleteArc(ALGraph *G,int v,int w);

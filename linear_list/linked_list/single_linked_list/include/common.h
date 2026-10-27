#ifndef SINGLE_LINKED_LIST_COMMON_H
#define SINGLE_LINKED_LIST_COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}*Node, *position;
//单链表结点类型定义

typedef struct{
    Node head,tail;
    int len;
}LinkList;

#endif
//单链表类型定义

//所有函数实现全部采用哑结点的方式，即链表的第一个结点不存储数据，作为头结点使用

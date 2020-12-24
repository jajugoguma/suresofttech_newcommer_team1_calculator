/********************
* ���ϸ� : lstack.h
* �ۼ��� : ����
* ���� : ���� ���� ����
* ����� :
* ������� : experssiontree.cpp
* ���ѻ��� : �߰� �ʿ�
* ���ó�� : �߰� �ʿ�
* �̷»��� :
*			2020.12.21 ����
*				1. �����ۼ�
********************/

#pragma once

#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE 1
#define FALSE 0

#include "btree.h"

typedef BTreeNode * Data;

typedef struct _node {
	Data data;
	struct _node *next;
} treeNode;

typedef struct _listStack {
	treeNode *head;
} ListStack;

typedef ListStack Stack;

void StackInit(Stack *pstack);
int SIsEmpty(Stack *pstack);

void SPush(Stack *pstack, Data data);
Data SPop(Stack *pstack);
Data SPeek(Stack *pstack);

#endif
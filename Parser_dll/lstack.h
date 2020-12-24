/********************
* 파일명 : lstack.h
* 작성자 : 이혁
* 설명 : 스택 구조 구현
* 사용방식 :
* 사용파일 : experssiontree.cpp
* 제한사항 : 추가 필요
* 요류처리 : 추가 필요
* 이력사항 :
*			2020.12.21 이혁
*				1. 최초작성
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
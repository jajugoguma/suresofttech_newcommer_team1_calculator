/********************
* 파일명 : btree.h
* 작성자 : 이혁
* 설명 : 이진트리 구현
* 사용방식 :
* 사용파일 : btree.cpp, experssiontree.cpp
* 제한사항 : 추가 필요
* 요류처리 : 추가 필요
* 이력사항 :
*			2020.12.21 이혁
*				1. 최초작성
********************/


#pragma once


#ifndef __BINARY_TREE2_H__
#define __BINARY_TREE2_H__

typedef int BTData;

typedef struct _bTreeNode {
	BTData data;
	struct _bTreeNode *left;
	struct _bTreeNode *right;
} BTreeNode;

BTreeNode *MakeBTreeNode(void);

BTData GetData(BTreeNode *bt);
void SetData(BTreeNode *bt, BTData data);

BTreeNode *GetLeftSubTree(BTreeNode *bt);
BTreeNode *GetRightSubTree(BTreeNode *bt);

void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub);
void MakeRightSubTree(BTreeNode *main, BTreeNode *sub);

typedef void VisitFuncPtr(BTData data);

void PreorderTraverses(BTreeNode *bt, VisitFuncPtr action);
void InorderTraverses(BTreeNode *bt, VisitFuncPtr action);
void PostorderTraverses(BTreeNode *bt, VisitFuncPtr action);

void DeleteTree(BTreeNode *bt);

#endif
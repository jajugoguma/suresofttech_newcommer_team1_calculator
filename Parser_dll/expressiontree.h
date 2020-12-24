/********************
* 파일명 : expressiontree.h
* 작성자 : 이혁
* 설명 : 수식트리 구현
* 사용방식 :
* 사용파일 : experssiontree.cpp
* 제한사항 : 추가 필요
* 요류처리 : 추가 필요
* 이력사항 :
*			2020.12.21 이혁
*				1. 최초작성
********************/

#pragma once

#ifndef __EXPRESSION_TREE_H__
#define __EXPRESSION_TREE_H__

#include "btree.h"
#include "lstack.h"
#include <string>

BTreeNode *MakeExpTree(std::string &exp);
double EvaluateExpTree(BTreeNode *bt);
std::string RetResult(double data);

void ShowPrefixTypeExp(BTreeNode *bt);
void ShowInfixTypeExp(BTreeNode *bt);
void ShowPostfixTypeExp(BTreeNode *bt);

BTreeNode* MakeExpTree(std::string& exp) {
	Stack stack;
	BTreeNode* pnode = NULL;

	int expLen = exp.size();
	int i;
	double tmp = 0;
	char ctmp = 0, numflag = 0, signflag = 0;

	StackInit(&stack);

	for (i = 0; i < expLen; i++) {

		if (isdigit(exp[i])) {
			numflag = 1;
			tmp = tmp + exp[i] - '0';
		}
		else if (exp[i] == '#') {
			if (numflag) {
				if (signflag)
					tmp = tmp * (-1);
				pnode = MakeBTreeNode();
				SetData(pnode, tmp / 10);
				tmp = 0;
				SPush(&stack, pnode);
			}
			else {
				pnode = MakeBTreeNode();
				MakeRightSubTree(pnode, SPop(&stack));
				MakeLeftSubTree(pnode, SPop(&stack));
				SetData(pnode, ctmp);
				SPush(&stack, pnode);
				ctmp = 0;
			}
			signflag = 0;
			numflag = 0;
		}
		else {
			ctmp = exp[i];
			signflag = 1;
		}
		if (numflag)
			tmp *= 10;
	}

	return SPop(&stack);
}

//결과값을 문자열로 변환
std::string RetResult(double data) {
	if (data == (double)INT_MAX + 2)		//0으로 나누었을때 에러처리
		return "error:worng expreesion";
	else if (data > INT_MAX)
		return "error:Overflow";
	else if (data < INT_MIN)
		return "error:Underflow";
	else
		return std::to_string(data);
}

/*생성된 수식트리 계산
* 
* 오버플로우와 언더플로우처리하여 
* 계산식의 하나라도 범위를 벗어나면 에러처리함
* 
* */
double EvaluateExpTree(BTreeNode* bt) {
	double op1, op2;

	if (GetLeftSubTree(bt) == NULL || GetRightSubTree(bt) == NULL)
		return GetData(bt);

	op1 = (double)EvaluateExpTree(GetLeftSubTree(bt));
	op2 = (double)EvaluateExpTree(GetRightSubTree(bt));

	if (op1 > INT_MAX || op2 > INT_MAX)		// 인자가 이미 오버플로우인 상태
		return (double)INT_MAX + 1;

	if (op1 < INT_MIN || op2 < INT_MIN)		// 인자가 이미 언더플로우인 상태
		return (double)INT_MIN - 1;

	switch (GetData(bt)) {
	case '+':
		if (op2 > 0)						//덧셈시 오버플로우, 언더플로우 판단
		{
			if (op1 > INT_MAX - op2)
				return (double)INT_MAX + 1;
			else
				return op1 + op2;
		}
		else {
			if (op1 < INT_MIN - op2)
				return (double)INT_MIN - 1;
			else
				return op1 + op2;
		}
	case '-':								//뺄셈시 오버플로우, 언더플로우 판단
		if (op2 > 0) {
			if (op1 < INT_MIN + op2)
				return (double)INT_MIN - 1;
			else
				return op1 - op2;
		}
			else {
				if (op1 > INT_MAX + op2)
				return (double)INT_MAX + 1;
			else
				return op1 - op2;
		}
	case '*':								// 곱셈시 오버플로우, 언더플로우 판단
		if ((op1 > 0 && op2 > 0) || (op1 < 0 && op2 < 0)) {
			if (abs(op2) > (INT_MAX / abs(op1)))
				return (double)INT_MAX + 1;
			else
				return op1 * op2;
		}
		else {
			if (-abs(op2) < (INT_MIN / abs(op1)))
				return (double)INT_MIN - 1;
			else
				return op1 * op2;
		}
	case '/':
		if (op2 == 0)
		{
			return (double)INT_MAX + 2;
		}
		else
			return op1 / op2;
	}

	return 0;
}

void ShowNodeData(int data) {
	if (data == '+' || data == '-' || data == '*' || data == '/')
		printf("%c ", data);
	else
		printf("%d ", data);
}

void ShowPrefixTypeExp(BTreeNode* bt) {
	PreorderTraverses(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode* bt) {
	InorderTraverses(bt, ShowNodeData);
}

void ShowPostfixTypeExp(BTreeNode* bt) {
	PostorderTraverses(bt, ShowNodeData);
}

std::string calculate(std::string exp) {
	BTreeNode* tree = MakeExpTree(exp);
	double result = EvaluateExpTree(tree);
	return RetResult(result);
}

#endif
/*
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include "expressiontree.h"
#include "lstack.h"


//수식 트리구조 생성
BTreeNode *MakeExpTree(std::string &exp) {
	Stack stack;
	BTreeNode *pnode=NULL;

	int expLen = exp.size();
	int i,tmp=0;
	char ctmp = 0, numflag = 0, signflag = 0;

	StackInit(&stack);

	for (i = 0; i < expLen; i++) {

		if (isdigit(exp[i])) {
			numflag = 1;
			tmp = tmp + exp[i] - '0';
		}
		else if (exp[i] == '#'){
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
		else{
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
	return std::to_string(data);
}

//생성된 수식트리 계산
double EvaluateExpTree(BTreeNode *bt) {
	double op1, op2;

	if (GetLeftSubTree(bt) == NULL || GetRightSubTree(bt) == NULL)
		return GetData(bt);

	op1 = (double)EvaluateExpTree(GetLeftSubTree(bt));
	op2 = (double)EvaluateExpTree(GetRightSubTree(bt));
	
	switch (GetData(bt)) {
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}

void ShowNodeData(int data) {
	if (data=='+' || data=='-' || data == '*' || data =='/')
		printf("%c ", data);
	else
		printf("%d ", data);
}

void ShowPrefixTypeExp(BTreeNode *bt) {
	PreorderTraverses(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode *bt) {
	InorderTraverses(bt, ShowNodeData);
}

void ShowPostfixTypeExp(BTreeNode *bt) {
	PostorderTraverses(bt, ShowNodeData);
}
*/
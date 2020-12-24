#pragma once
#include <vector>
#include "Node.h"
#include "iter.h"
#include "Checker.h"

class ParserTree {
	Node* proot = NULL;
	std::string result = "";
	std::string treeStream = "";
public:
	// 지원하는 정수 범위 내인지 체크
	int findIndexOfLastHash();
	bool intRangeChecker(int i);
	// 결과출력(result)함수
	void iterPop(char c);
	// 트리 만드는 함수 (순서대로 수행)
	std::string makePostFixWithHash(std::string str);
	void makeTree(std::string postFixWithHash);
	void makeTreeStream(Node* node);
	//get()
	Node* getProot();
	std::string getResult();
	std::string getTreeStream();
};

int ParserTree::findIndexOfLastHash() {
	for (int i = result.length() - 1; i >= 0; i--) {
		if (result[i] == '#') return i;
	}
	return -1;
}

bool ParserTree::intRangeChecker(int i) {
	std::string INTMAX = "2147483647";
	std::string INTMIN = "-2147483648";

	std::string num = "";
	int size = 10 - (result.length() - 1 - i);

	for (int i = 0; i < size; i++) num += '0';
	//	if (result[i + 1 ] == '-') num[0] = '-';

	num += result.substr(i + 1, result.length());

	if (num[0] == '-') {
		if (num > INTMIN) return true;
	}
	else if (num[0] >= '0' && num[0] <= '9') {
		if (num > INTMAX) return true;
	}
	return false;
}

void ParserTree::iterPop(char c) {
	result += "#";
	result += c;
	result += "#";
}

std::string ParserTree::makePostFixWithHash(std::string str) {
	int cntINT = 0, cntITER = 0;
	std::vector<char> vstack;
	bool bf = false, nf = false; // 이전/현재의 값이 숫자면 true, 아니면 false를 저장하는 변수

	for (int i = 0; str[i] != '\0'; i++)
	{
		bf = nf;
		if (str[i] == '(') {
			nf = false;
			if (bf) return std::string("잘못된 수식입니다."); // 숫자 뒤에 바로 '(' 이 온 경우
			vstack.push_back(str[i]);
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			nf = true;
			if (!bf) {
				result += "#";
				cntINT++;
			}
			result += str[i];
		}
		else if (str[i] == ')')
		{
			nf = false;
			if (bf) {
				if (intRangeChecker(findIndexOfLastHash())) {
					return std::string("지원하는 숫자의 범위를 초과했습니다.");
				}
				result += "#"; //str[i-1]이 숫자고 str[i]가 ) 인 경우 # 출력
			}
			while (vstack.back() != '(') //여는 괄호가 나올때까지 pop
			{
				iterPop(vstack.back());
				vstack.pop_back();
			}
			vstack.pop_back();
		}
		else //연산자
		{
			if (str[i] == '-' && i >= 1 && str[i - 1] == '(') { //뺄셈 연산자가 아니고 음수 연산자일 경우
				cntINT++;
				nf = true; // 음수 기호이므로 숫자취급 해야 한다.
				result += '#';
				do {
					result += str[i];
					i++;
				} while (str[i] >= '0' && str[i] <= '9');
				i--;
			}
			else {
				cntITER++;
				nf = false;
				if (bf) {
					if (intRangeChecker(findIndexOfLastHash())) {
						return std::string("지원하는 숫자의 범위를 초과했습니다.");
					}
					result += "#"; //str[i-1]이 숫자고 str[i]가 연산자인 경우 # 출력
				}

				while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]]) //연산자 우선순위가 stack.top() >= str[i] 이면 stack.pop() 
				{
					iterPop(vstack.back());
					vstack.pop_back();
				}

				vstack.push_back(str[i]); //연산자 우선순위가 stack.top()<str[i] 이거나, stack이 비었으면 stack.push()
			}

		}
	}
	if (cntITER == 0) result += '#'; //입력된 문자열이 연산자가 없는 단순 정수일 때, 형식을 맞춰주기 위해 마지막에 # 출력.
	if (result[result.length() - 2] >= '0' && result[result.length() - 2] <= '9') {
		if (intRangeChecker(findIndexOfLastHash())) {
			return std::string("지원하는 숫자의 범위를 초과했습니다.");
		}
	}
	if (cntINT - 1 != cntITER) return std::string("잘못된 수식입니다.");
	//스택에 남은연산 출력
	if (!vstack.empty()) result += "#";
	while (!vstack.empty())
	{
		iterPop(vstack.back());
		vstack.pop_back();
	}

	return result;
}

void ParserTree::makeTree(std::string postFixWithHash) {
	std::vector<Node*> vstack;
	Node* pnode;
	int n = 0; //정수를 계산해서 넣을 변수

	for (int i = 0; i < postFixWithHash.length(); i++) {
		if (postFixWithHash[i] != '#') {
			// postFixWithHash[i]가 숫자
			if (postFixWithHash[i] >= '0' && postFixWithHash[i] <= '9') {
				if (postFixWithHash[i] == '0' && postFixWithHash[i - 1] == '#') {
					pnode = new Node(std::to_string(n));
					vstack.push_back(pnode);
				}
				else {
					n *= 10;
					n += postFixWithHash[i] - '0';
				}
			}
			// postFixWithHash[i]가 사칙 연산자 or 음수 연산자
			else {
				// 음수 연산자
				if (postFixWithHash[i] == '-' && postFixWithHash[i + 1] >= '0' && postFixWithHash[i + 1] <= '9') {
					i++;
					do {
						//cout << postFixWithHash[i] << "%" << endl;
						n *= 10;
						n -= postFixWithHash[i] - '0';
						i++;
					} while (postFixWithHash[i] >= '0' && postFixWithHash[i] <= '9');
					i--;
					//cout << n << "$"<<endl;

					pnode = new Node(std::to_string(n));
					vstack.push_back(pnode);
					n = 0;
				}
				// postFixWithHash[i]가 사칙 연산자
				// stack에서 2개 꺼내 부분트리 만들기 + 스택에 넣기 
				// => 이를 반복하다보면 최종적으로 하나의 트리만 스택에 남게 된다.
				else {
					Node* a = vstack.back();
					vstack.pop_back();
					Node* b = vstack.back();
					vstack.pop_back();
					std::string ts = ""; ts += postFixWithHash[i];

					pnode = new Node(ts, b, a);
					vstack.push_back(pnode);
				}
			}
		}
		// postFixWithHash[i]가 구분자 '#'
		else {
			if (n) {
				pnode = new Node(std::to_string(n));
				vstack.push_back(pnode);
				n = 0;
			}
		}
	}

	proot = vstack[0];
}

void ParserTree::makeTreeStream(Node* node) {
	if (node == NULL) return;

	this->makeTreeStream(node->getLeftChild());
	this->makeTreeStream(node->getRightChild());
	treeStream += node->getVal();
	treeStream += " ";
}

inline Node* ParserTree::getProot()
{
	return proot;
}

inline std::string ParserTree::getResult()
{
	return result;
}

inline std::string ParserTree::getTreeStream()
{
	return treeStream;
}
std::string parsing(std::string expression) {
	std::string result = "";
	Checker inputstr(expression);

	if (inputstr.runner()) {
		result = " error:wrongexp";
	}
	else {
		mapInit();

		ParserTree BTroot;

		std::string postFixWithHash = BTroot.makePostFixWithHash(inputstr.getOutput());
		if (postFixWithHash == "error:overflow" || postFixWithHash == "error:wrongexp") {
			result = postFixWithHash;
		}
		else {
			BTroot.makeTree(postFixWithHash);

			BTroot.makeTreeStream(BTroot.getProot());
			result = BTroot.getTreeStream();
		}
	}
	return result;
}
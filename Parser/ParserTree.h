#pragma once
#include <vector>
#include "Node.h"
#include "iter.h"

class ParserTree {
	Node* proot = NULL;
	std::string treeStream = "";
public:
	std::string makePostFixWithHash(std::string str);
	void makeTree(std::string postFixWithHash);
	void makeTreeStream(Node* node);
	Node* getProot();
	std::string getTreeStream();
};

std::string ParserTree::makePostFixWithHash(std::string str) {
	std::vector<char> vstack;
	std::string result = "";
	bool bf = false, nf = false; // 이전/현재의 값이 숫자면 true, 아니면 false를 저장하는 변수

	for (int i = 0; str[i] != '\0'; i++)
	{
		bf = nf;
		if (str[i] == '(') {
			nf = false;
			if (bf && !nf) result += "#"; //str[i-1]이 숫자고 str[i]가 ( 인 경우 # 출력
			vstack.push_back(str[i]);
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			nf = true;
			if (!bf) {
				result += "#";
			}
			result += str[i];
		}
		else if (str[i] == ')')
		{
			nf = false;
			if (bf && !nf) result += "#"; //str[i-1]이 숫자고 str[i]가 ) 인 경우 # 출력
			while (vstack.back() != '(') //여는 괄호가 나올때까지 pop
			{
				char a = vstack.back();
				result += "#";
				result += a;
				result += "#";
				vstack.pop_back();
			}
			vstack.pop_back();
		}
		else //연산자
		{
			if (str[i] == '-' && i >= 1 && str[i - 1] == '(') { //뺄셈 연산자가 아니고 음수 연산자일 경우
				nf = true; // 음수 기호이므로 숫자취급 해야 한다.
				result += '#';
				do {
					result += str[i];
					i++;
				} while (str[i] >= '0' && str[i] <= '9');
				i--;
			}
			else {
				nf = false;
				if (bf && !nf) result += "#"; //str[i-1]이 숫자고 str[i]가 연산자인 경우 # 출력

				while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]]) //연산자 우선순위가 stack.top() >= str[i] 이면 stack.pop() 
				{
					result += "#";
					result += vstack.back();
					result += "#";
					vstack.pop_back();
				}

				vstack.push_back(str[i]); //연산자 우선순위가 stack.top()<str[i] 이거나, stack이 비었으면 stack.push()
			}

		}
	}

	//스택에 남은연산 출력
	if (!vstack.empty()) result += "#";
	while (!vstack.empty())
	{
		result += "#";
		result += vstack.back();
		result += "#";
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
				n *= 10;
				n += postFixWithHash[i] - '0';
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
	treeStream += "#";
}

inline Node* ParserTree::getProot()
{
	return proot;
}

inline std::string ParserTree::getTreeStream()
{
	return treeStream;
}

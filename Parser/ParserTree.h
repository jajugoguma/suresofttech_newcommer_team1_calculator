#pragma once
#include <vector>
#include "Node.h"
#include "iter.h"

class ParserTree {
	Node* proot = NULL;
	std::string result = "";
	std::string treeStream = "";
public:
	int findIndexOfLastHash(int n);
	bool intRangeChecker(int i);
	void iterPop(char c);
	std::string makePostFixWithHash(std::string str);
	void makeTree(std::string postFixWithHash);
	void makeTreeStream(Node* node);
	Node* getProot();
	std::string getResult();
	std::string getTreeStream();
};

int ParserTree::findIndexOfLastHash(int n) {
	for (int i = n - 1; i >= 0; i--) {
		if (result[i] == '#') return i;
	}
	return -1;
}

bool ParserTree::intRangeChecker(int i) {
	std::string INTMAX = "2147483647";
	std::string INTMIN = "-2147483648";
	std::string num = result.substr(i + 1, result.length());
	if (num[0] == '-') {
		if (num > INTMIN) return true;
	}
	else {
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
	std::vector<char> vstack;
	bool bf = false, nf = false; // ����/������ ���� ���ڸ� true, �ƴϸ� false�� �����ϴ� ����

	for (int i = 0; str[i] != '\0'; i++)
	{
		bf = nf;
		if (str[i] == '(') {
			nf = false;
			if (bf && !nf) {
				if (intRangeChecker(findIndexOfLastHash(i))) {
					return std::string("�߸��� �����Դϴ�.");
				}
				result += "#"; //str[i-1]�� ���ڰ� str[i]�� ( �� ��� # ���
			}
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
			if (bf && !nf) {
				if (intRangeChecker(findIndexOfLastHash(i))) {
					return std::string("�߸��� �����Դϴ�.");
				}
				result += "#"; //str[i-1]�� ���ڰ� str[i]�� ) �� ��� # ���
			}
			while (vstack.back() != '(') //���� ��ȣ�� ���ö����� pop
			{
				iterPop(vstack.back());
				vstack.pop_back();
			}
			vstack.pop_back();
		}
		else //������
		{
			if (str[i] == '-' && i >= 1 && str[i - 1] == '(') { //���� �����ڰ� �ƴϰ� ���� �������� ���
				nf = true; // ���� ��ȣ�̹Ƿ� ������� �ؾ� �Ѵ�.
				result += '#';
				do {
					result += str[i];
					i++;
				} while (str[i] >= '0' && str[i] <= '9');
				i--;
			}
			else {
				nf = false;
				if (bf && !nf) {
					if (intRangeChecker(findIndexOfLastHash(i))) {
						return std::string("�߸��� �����Դϴ�.");
					}
					result += "#"; //str[i-1]�� ���ڰ� str[i]�� �������� ��� # ���
				}

				while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]]) //������ �켱������ stack.top() >= str[i] �̸� stack.pop() 
				{
					iterPop(vstack.back());
					vstack.pop_back();
				}

				vstack.push_back(str[i]); //������ �켱������ stack.top()<str[i] �̰ų�, stack�� ������� stack.push()
			}

		}
	}

	//���ÿ� �������� ���
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
	int n = 0; //������ ����ؼ� ���� ����

	for (int i = 0; i < postFixWithHash.length(); i++) {
		if (postFixWithHash[i] != '#') {
			// postFixWithHash[i]�� ����
			if (postFixWithHash[i] >= '0' && postFixWithHash[i] <= '9') {
				n *= 10;
				n += postFixWithHash[i] - '0';
			}
			// postFixWithHash[i]�� ��Ģ ������ or ���� ������
			else {
				// ���� ������
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
				// postFixWithHash[i]�� ��Ģ ������
				// stack���� 2�� ���� �κ�Ʈ�� ����� + ���ÿ� �ֱ� 
				// => �̸� �ݺ��ϴٺ��� ���������� �ϳ��� Ʈ���� ���ÿ� ���� �ȴ�.
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
		// postFixWithHash[i]�� ������ '#'
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

inline std::string ParserTree::getResult()
{
	return result;
}

inline std::string ParserTree::getTreeStream()
{
	return treeStream;
}

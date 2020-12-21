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
	bool bf = false, nf = false; // ����/������ ���� ���ڸ� true, �ƴϸ� false�� �����ϴ� ����

	for (int i = 0; str[i] != '\0'; i++)
	{
		bf = nf;
		if (str[i] == '(') {
			nf = false;
			if (bf && !nf) result += "#"; //str[i-1]�� ���ڰ� str[i]�� ( �� ��� # ���
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
			if (bf && !nf) result += "#"; //str[i-1]�� ���ڰ� str[i]�� ) �� ��� # ���
			while (vstack.back() != '(') //���� ��ȣ�� ���ö����� pop
			{
				char a = vstack.back();
				result += "#";
				result += a;
				result += "#";
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
				if (bf && !nf) result += "#"; //str[i-1]�� ���ڰ� str[i]�� �������� ��� # ���

				while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]]) //������ �켱������ stack.top() >= str[i] �̸� stack.pop() 
				{
					result += "#";
					result += vstack.back();
					result += "#";
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

inline std::string ParserTree::getTreeStream()
{
	return treeStream;
}

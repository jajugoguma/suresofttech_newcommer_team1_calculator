#include "Node.h"

Node* BTroot;
string answer = "";
map<char, int> iter; //������ �켱����

void mapInit() {
	iter['+'] = 0;
	iter['-'] = 0;
	iter['*'] = 1;
	iter['/'] = 1;
	iter['('] = -1;
}

string makePostFixWithHash(string str) {
	vector<char> vstack;
	string result = "";
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

void makeTree(string postFixWithHash) {
	vector<Node*> vstack;
	Node* pnode;
	int n = 0; //������ ����ؼ� ���� ����

	for (int i = 0; i < postFixWithHash.length(); i++) {
		char c = postFixWithHash[i];

		if (c != '#') {
			// c = postFixWithHash[i]�� ����
			if (c >= '0' && c <= '9') {
				n *= 10;
				n += c - '0';
			}
			// c = postFixWithHash[i]�� ��Ģ ������ or ���� ������
			else {
				// ���� ������
				if (c == '-' && postFixWithHash[i + 1] >= '0' && postFixWithHash[i + 1] <= '9') {
					i++;
					do {
						n *= 10;
						n -= c - '0';
						i++;
					} while (c >= '0' && c <= '9');
					i--;

					pnode = new Node(to_string(n));
					vstack.push_back(pnode);
					n = 0;
				}
				// c = postFixWithHash[i]�� ��Ģ ������
				// stack���� 2�� ���� �κ�Ʈ�� ����� + ���ÿ� �ֱ� 
				// => �̸� �ݺ��ϴٺ��� ���������� �ϳ��� Ʈ���� ���ÿ� ���� �ȴ�.
				else {
					Node* a = vstack.back();
					vstack.pop_back();
					Node* b = vstack.back();
					vstack.pop_back();
					string ts = ""; ts += c;

					pnode = new Node(ts, b, a);
					vstack.push_back(pnode);
				}
			}
		}
		// c = postFixWithHash[i]�� ������ '#'
		else {
			if (n) {
				pnode = new Node(to_string(n));
				vstack.push_back(pnode);
				n = 0;
			}
		}
	}

	BTroot = vstack[0];
}

void makeTreeStream(Node* node) {
	if (node == NULL) return;

	makeTreeStream(node->getLeftChild());
	makeTreeStream(node->getRightChild());
	answer += node->getVal();
	answer += "#";
}

int main()
{
	string str = "";
	cin >> str;

	mapInit();

	string postFixWithHash = makePostFixWithHash(str);

	makeTree(postFixWithHash);

	makeTreeStream(BTroot);
	//answer = answer.substr(0, answer.length() - 1);
	cout << answer << endl;

	return 0;
}


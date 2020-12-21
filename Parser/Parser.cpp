#include "Node.h"

Node* BTroot;
map<char, int> iter; //������ �켱����

void mapInit() {
	iter['+'] = 0;
	iter['-'] = 0;
	iter['*'] = 1;
	iter['/'] = 1;
	iter['('] = -1;
}

void printPostFixWithHash(string str) {
	vector<char> vstack;
	bool bf = false, nf = false;

	for (int i = 0; str[i] != '\0'; i++)
	{
		bf = nf;
		if (str[i] == '(') {
			nf = false;
			if (bf && !nf) printf("^");
			//
			vstack.push_back(str[i]);
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			nf = true;
			if (!bf) {
				printf("^");
			}
			printf("%c", str[i]);
		}
		else if (str[i] == ')')
		{
			nf = false;
			if (bf && !nf) printf("^");
			//
			while (vstack.back() != '(')    //���� ��ȣ�� ���ö����� pop
			{
				printf("#%c#", vstack.back());
				vstack.pop_back();
			}
			vstack.pop_back();
		}
		else
		{
			nf = false;
			if (bf && !nf) printf("^");
			//
			//���ų� ������ ��ӻ���
			while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]])
			{
				char a = vstack.back();
				printf("#%c#", a);
				vstack.pop_back();
			}

			//���� �������� �켱������ ������ Ǫ��
			vstack.push_back(str[i]);


		}


	}


	//���ÿ� �������� ���
	if (!vstack.empty()) printf("^");
	while (!vstack.empty())
	{
		printf("#%c#", vstack.back());
		vstack.pop_back();
	}
	printf("\n");
}

string makePostFixWithHash(string str) {
	vector<char> vstack;
	string result = "";
	bool bf = false, nf = false;

	for (int i = 0; str[i] != '\0'; i++)
	{
		bf = nf;
		if (str[i] == '(') {
			nf = false;
			if (bf && !nf) result += "#";
			//
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
			if (bf && !nf) result += "#";
			//
			while (vstack.back() != '(')    //���� ��ȣ�� ���ö����� pop
			{
				char a = vstack.back();
				result += "#";
				result += a;
				result += "#";
				vstack.pop_back();
			}
			vstack.pop_back();
		}
		else
		{
			nf = false;
			if (bf && !nf) result += "#";
			//
			//���ų� ������ ��ӻ���
			while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]])
			{
				char a = vstack.back();
				result += "#";
				result += a;
				result += "#";
				vstack.pop_back();
			}

			//���� �������� �켱������ ������ Ǫ��
			vstack.push_back(str[i]);
		}
	}


	//���ÿ� �������� ���
	if (!vstack.empty()) result += "#";
	while (!vstack.empty())
	{
		char a = vstack.back();
		result += "#";
		result += a;
		result += "#";
		vstack.pop_back();
	}

	return result;
}

void makeTree(string postFixWithHash) {
	vector<Node*> vstack;
	Node* pnode;
	int n = 0; //������ ����ؼ� ���� ����
	int size = postFixWithHash.length();

	for (int i = 0; i < size; i++) {
		char c = postFixWithHash[i];
		if (c != '#') {
			if (c >= '0' && c <= '9') {
				n *= 10;
				n += c - '0';
			}
			else {
				// make tree : stack���� 2�� ���� �κ�Ʈ�� ����� + ���ÿ� �ֱ� 
				// => �̸� �ݺ��ϴٺ��� ���������� �ϳ��� Ʈ���� ���ÿ� ���� �ȴ�.
				Node* a = vstack.back();
				vstack.pop_back();
				Node* b = vstack.back();
				vstack.pop_back();
				string ts = ""; ts += c;

				pnode = new Node(ts, b, a);
				vstack.push_back(pnode);
				//cout << vstack.back()->getLeftChild()->getVal() << vstack.back()->getVal() << vstack.back()->getRightChild()->getVal() << endl;
			}
		}
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

// makeTreeStream() : dfs�ϸ鼭 ���Ĵ�� �����.

void printDFS(Node* node) {
	if (node == NULL) return;
	printDFS(node->getLeftChild());
	cout << node->getVal() << " ";
	printDFS(node->getRightChild());
}

void ShowPrefixTypeExp(Node* node) {
	if (node == NULL) return;

	if (left != NULL && right != NULL) {
		;// printf("( ");
	}

	cout << node->getVal() << " ";
	ShowPrefixTypeExp(node->getLeftChild());
	ShowPrefixTypeExp(node->getRightChild());

	if (left != NULL && right != NULL) {
		;// printf(") ");

	}
}

void ShowInfixTypeExp(Node* node) {
	if (node == NULL) return;

	if (left != NULL && right != NULL) {
		;// printf("( ");
	}

	ShowInfixTypeExp(node->getLeftChild());
	cout << node->getVal() << " ";
	ShowInfixTypeExp(node->getRightChild());

	if (left != NULL && right != NULL) {
		;// printf(") ");
	}
}

void ShowPostfixTypeExp(Node* node) {
	if (node == NULL) return;

	if (left != NULL && right != NULL) {
		;// printf("( ");
	}

	ShowPostfixTypeExp(node->getLeftChild());
	ShowPostfixTypeExp(node->getRightChild());
	cout << node->getVal() << " ";

	if (left != NULL && right != NULL) {
		;// printf(") ");
	}

}

int main()
{
	string str = "";
	cin >> str;

	mapInit();

	string postFixWithHash = makePostFixWithHash(str);
	//cout << postFixWithHash << endl;

	makeTree(postFixWithHash);
	//printDFS(BTroot); cout << endl;
	//ShowPrefixTypeExp(BTroot); cout << endl;
	//ShowInfixTypeExp(BTroot); cout << endl;
	ShowPostfixTypeExp(BTroot); cout << endl;


	return 0;
}


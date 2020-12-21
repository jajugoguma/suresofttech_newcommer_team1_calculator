#include "Node.h"

Node* BTroot;
map<char, int> iter; //연산자 우선순위

void mapInit() {
	iter['+'] = 0;
	iter['-'] = 0;
	iter['*'] = 1;
	iter['/'] = 1;
	iter['('] = -1;
}

/*void printPostFixWithHash(string str) {
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
			while (vstack.back() != '(')    //여는 괄호가 나올때까지 pop
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
			//높거나 같으면 계속뽑음
			while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]])
			{
				char a = vstack.back();
				printf("#%c#", a);
				vstack.pop_back();
			}

			//스택 위에보다 우선순위가 낮으면 푸쉬
			vstack.push_back(str[i]);


		}


	}


	//스택에 남은연산 출력
	if (!vstack.empty()) printf("^");
	while (!vstack.empty())
	{
		printf("#%c#", vstack.back());
		vstack.pop_back();
	}
	printf("\n");
}*/

string makePostFixWithHash(string str) {
	vector<char> vstack;
	string result = "";
	bool bf = false, nf = false;

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
			while (vstack.back() != '(')    //여는 괄호가 나올때까지 pop
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
				result += '#';
				do {
					result += str[i];
					i++;
				} while (str[i] >= '0' && str[i] <= '9');
				i--;
				nf = true; //숫자취급
			}
			else {
				nf = false;
				if (bf && !nf) result += "#"; //str[i-1]이 숫자고 str[i]가 연산자인 경우 # 출력

				//높거나 같으면 계속뽑음
				while (!vstack.empty() && iter[vstack.back()] >= iter[str[i]])
				{
					char a = vstack.back();
					result += "#";
					result += a;
					result += "#";
					vstack.pop_back();
				}

				//스택 위에보다 우선순위가 낮으면 푸쉬
				vstack.push_back(str[i]);
			}

		}
	}


	//스택에 남은연산 출력
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
	int n = 0; //정수를 계산해서 넣을 변수
	int size = postFixWithHash.length();

	for (int i = 0; i < size; i++) {
		char c = postFixWithHash[i];
		if (c != '#') {
			if (c >= '0' && c <= '9') {
				n *= 10;
				n += c - '0';
			}
			else { //사칙연산자
				if (c == '-' && postFixWithHash[i + 1] >= '0' && postFixWithHash[i + 1] <= '9') { //음수연산자인 경우
					i++;
					do {
						n *= 10;
						n -= postFixWithHash[i] - '0';
						i++;
					} while (postFixWithHash[i] >= '0' && postFixWithHash[i] <= '9');
					i--;

					pnode = new Node(to_string(n));
					vstack.push_back(pnode);
					n = 0;
				}
				else {
					// make tree : stack에서 2개 꺼내 부분트리 만들기 + 스택에 넣기 
				// => 이를 반복하다보면 최종적으로 하나의 트리만 스택에 남게 된다.
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
		}
		else { // c == '#'
			if (n) {
				pnode = new Node(to_string(n));
				vstack.push_back(pnode);
				n = 0;
			}
		}
	}

	BTroot = vstack[0];
}

// makeTreeStream() : dfs하면서 형식대로 만든다.

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
	cout << postFixWithHash << endl;

	makeTree(postFixWithHash);
	//printDFS(BTroot); cout << endl;
	//ShowPrefixTypeExp(BTroot); cout << endl;
	//ShowInfixTypeExp(BTroot); cout << endl;
	ShowPostfixTypeExp(BTroot); cout << endl;


	return 0;
}


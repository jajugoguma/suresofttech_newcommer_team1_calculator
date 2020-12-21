#include "Node.h"

Node* BTroot;
string answer = "";
map<char, int> iter; //연산자 우선순위

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

void makeTree(string postFixWithHash) {
	vector<Node*> vstack;
	Node* pnode;
	int n = 0; //정수를 계산해서 넣을 변수

	for (int i = 0; i < postFixWithHash.length(); i++) {
		char c = postFixWithHash[i];

		if (c != '#') {
			// c = postFixWithHash[i]가 숫자
			if (c >= '0' && c <= '9') {
				n *= 10;
				n += c - '0';
			}
			// c = postFixWithHash[i]가 사칙 연산자 or 음수 연산자
			else {
				// 음수 연산자
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
				// c = postFixWithHash[i]가 사칙 연산자
				// stack에서 2개 꺼내 부분트리 만들기 + 스택에 넣기 
				// => 이를 반복하다보면 최종적으로 하나의 트리만 스택에 남게 된다.
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
		// c = postFixWithHash[i]가 구분자 '#'
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


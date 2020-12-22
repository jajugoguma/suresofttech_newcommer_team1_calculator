#include "Node.h"
#include "ParserTree.h"

bool checker(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= '(' && s[i] <= '9') {
			if (s[i] == ',' || s[i] == '.') {
				return false;
			}
			else return true;
		}
		else return false;
	}
}

int main()
{
	std::string str = "";
	std::cin >> str;

	if (!checker(str)) {
		std::cout << "�߸��� �����Դϴ�." << std::endl;
		return 0;
	}

	mapInit();

	ParserTree BTroot;

	std::string postFixWithHash = BTroot.makePostFixWithHash(str);
	if (postFixWithHash == "�߸��� �����Դϴ�.") {
		std::cout << postFixWithHash << std::endl;
		return -1;
	}

	BTroot.makeTree(postFixWithHash);

	BTroot.makeTreeStream(BTroot.getProot());
	std::cout << BTroot.getTreeStream() << std::endl;

	return 0;
}


#include "Node.h"
#include "ParserTree.h"
#include "Checker.h"

int main()
{
	while (1) {
		std::string str = "";
		std::cin >> str;

		Checker inputstr(str);

		if (inputstr.runner()) {
			std::cout << "        �߸��� �����Դϴ�." << std::endl;
			//continue;
			return -1;
		}

		mapInit();

		ParserTree BTroot;

		std::string postFixWithHash = BTroot.makePostFixWithHash(inputstr.getOutput());
		if (postFixWithHash == "�����ϴ� ������ ������ �ʰ��߽��ϴ�." || postFixWithHash == "�߸��� �����Դϴ�.") {
			std::cout << "        " << postFixWithHash << std::endl;
			//continue;
			return -1;
		}

		BTroot.makeTree(postFixWithHash);

		BTroot.makeTreeStream(BTroot.getProot());
		std::cout << "        " << BTroot.getTreeStream() << std::endl;
	}

	return 0;
}


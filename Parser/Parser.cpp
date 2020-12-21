#include "Node.h"
#include "ParserTree.h"


int main()
{
	std::string str = "";
	std::cin >> str;

	mapInit();

	ParserTree BTroot;

	std::string postFixWithHash = BTroot.makePostFixWithHash(str);

	BTroot.makeTree(postFixWithHash);

	BTroot.makeTreeStream(BTroot.getProot());
	std::cout << BTroot.getTreeStream() << std::endl;

	return 0;
}


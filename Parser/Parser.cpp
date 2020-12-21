#include "Node.h"
#include "ParserTree.h"


int main()
{
	string str = "";
	cin >> str;

	mapInit();

	ParserTree BTroot;

	string postFixWithHash = BTroot.makePostFixWithHash(str);

	BTroot.makeTree(postFixWithHash);

	BTroot.makeTreeStream(BTroot.getProot());
	cout << BTroot.getTreeStream() << endl;

	return 0;
}


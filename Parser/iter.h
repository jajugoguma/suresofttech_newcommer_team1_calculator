#pragma once
#include <map>
map<char, int> iter; //������ �켱����
void mapInit() {
	iter['+'] = 0;
	iter['-'] = 0;
	iter['*'] = 1;
	iter['/'] = 1;
	iter['('] = -1;
}

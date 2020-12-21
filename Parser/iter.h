#pragma once
#include <map>
std::map<char, int> iter; //연산자 우선순위
void mapInit() {
	iter['+'] = 0;
	iter['-'] = 0;
	iter['*'] = 1;
	iter['/'] = 1;
	iter['('] = -1;
}

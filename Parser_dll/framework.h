#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <locale>
#include <codecvt>
#include "ParserTree.h"

std::string wstringToString(std::wstring wst) {
	std::string result;
	result.assign(wst.begin(), wst.end());

	return result;
}

std::wstring stringToWstring(std::string str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring result = converter.from_bytes(str);

	return result;
}


extern "C" __declspec(dllexport) int* retString(WCHAR* str) {
	std::wstring wstr = str;

	auto st = wstringToString(wstr);
	auto result = stringToWstring(parsing(st));

    return (int*)result.c_str();
}



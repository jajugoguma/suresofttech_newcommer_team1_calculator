#pragma once
#include <iostream>

class Checker {
	std::string input = "";
	std::string output = "";
public:
	//생성자, 소멸자
	Checker();
	Checker(std::string s);
	~Checker() = default;
	//runner
	bool runner();
	//get()
	std::string getInput();
	std::string getOutput();
	//유효성 체크
	bool empty();
	bool character();
	bool bracket();
	//유효한 문자열 변환
	void iterator();
};

inline Checker::Checker()
{
	input = "";
	output = "";
}

inline Checker::Checker(std::string s)
{
	input = s;
	output = "";
}

inline bool Checker::runner()
{
	if (empty() || character() || bracket()) {
		return true;
	}
	iterator();
	return false;
}

std::string Checker::getInput()
{
	return input;
}

std::string Checker::getOutput()
{
	return output;
}

bool Checker::empty()
{
	// 빈 문자열일 때, 빈 문자열입니다 출력 OR 잘못된 수식 처리
	if (input == "") return true;
	else return false;
}

bool Checker::character() {
	// 0~9, +, -, *, / 외의 문자가 포함된 수식, 잘못된 수식 처리
	for (auto c : input) {
		if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
			;
		}
		else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '/' || c == '*') {
			;
		}
		else {
			return true;
		}
	}
	return false;
}

bool Checker::bracket() {
	// '('보다 ')'가 먼저 나오는 경우, 잘못된 수식 처리
	int open = 0, close = 0;
	for (auto i : input) {
		if (i == '(') open++;
		else if (i == ')') {
			close++;
			if (open < close) return true;
		}
	}
	// '('와 ')' 개수가 맞지 않는 경우, 잘못된 수식 처리
	if (open != close) return true;
	else return false;
}

void Checker::iterator()
{
	// 연산자 n개가 연속으로 들어오는 경우, 마지막 연산자만 남김
	for (int i = 0; i < input.length(); i++) {
		char c = input[i];

		if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (i < input.length() - 1) { // 마지막 원소가 아니고
				char c2 = input[i + 1];
				if (c2 == '+' || c2 == '-' || c2 == '*' || c2 == '/') { // 다음 원소가 연산자면
					;
				}
				else { // 다음 원소가 숫자 or ( or ) 면
					output += c;
				}

			}
			// 입력이 연산자로 끝나는 경우, 해당 연산자 생략 처리
			else {
				;
			}
		}
		else output += c;
	}
}

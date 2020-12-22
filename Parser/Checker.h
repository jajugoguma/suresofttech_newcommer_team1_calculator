#pragma once
#include <iostream>

class Checker {
	std::string input = "";
	std::string output = "";
public:
	//������, �Ҹ���
	Checker();
	Checker(std::string s);
	~Checker() = default;
	//runner
	bool runner();
	//get()
	std::string getInput();
	std::string getOutput();
	//��ȿ�� üũ
	bool empty();
	bool character();
	bool bracket();
	//��ȿ�� ���ڿ� ��ȯ
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
	// �� ���ڿ��� ��, �� ���ڿ��Դϴ� ��� OR �߸��� ���� ó��
	if (input == "") return true;
	else return false;
}

bool Checker::character() {
	// 0~9, +, -, *, / ���� ���ڰ� ���Ե� ����, �߸��� ���� ó��
	for (auto c : input) {
		if (c >= '(' && c <= '9') { // ASCII ����
			if (c == ',' || c == '.') return true;
			else return false;
		}
		else return true;
	}
}

bool Checker::bracket() {
	// '('���� ')'�� ���� ������ ���, �߸��� ���� ó��
	int open = 0, close = 0;
	for (auto i : input) {
		if (i == '(') open++;
		else if (i == ')') {
			close++;
			if (open < close) return true;
		}
	}
	// '('�� ')' ������ ���� �ʴ� ���, �߸��� ���� ó��
	if (open != close) return true;
	else return false;
}

void Checker::iterator()
{
	// ������ n���� �������� ������ ���, ������ �����ڸ� ����
	for (int i = 0; i < input.length(); i++) {
		char c = input[i];

		if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (i < input.length() - 1) { // ������ ���Ұ� �ƴϰ�
				char c2 = input[i + 1];
				if (c2 == '+' || c2 == '-' || c2 == '*' || c2 == '/') { // ���� ���Ұ� �����ڸ�
					;
				}
				else { // ���� ���Ұ� ���� or ( or ) ��
					output += c;
				}

			}
			// �Է��� �����ڷ� ������ ���, �ش� ������ ���� ó��
			else {
				;
			}
		}
		else output += c;
	}
}

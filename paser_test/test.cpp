#include "pch.h"
#include "../Parser/ParserTree.h"
#include "../Parser/Checker.h"
#include <string>

std::string parserrr(std::string str) {
	Checker chec(str);

	if (chec.runner())
		return "�߸��� �����Դϴ�.";

	mapInit();
	ParserTree Btree1;
	std::string hashing = Btree1.makePostFixWithHash(chec.getOutput());

	return hashing;
}

TEST(Paser, right_) {
	EXPECT_EQ(parserrr("2*(2+3)*4"), "1");
	EXPECT_EQ(parserrr("12*(12+13)*14"), "1");
	EXPECT_EQ(parserrr("12*(12+3)*4"), "1");
	EXPECT_EQ(parserrr("(3+4)*8/"), "1");
	EXPECT_EQ(parserrr("12*(13-12)*14"), "1");
	EXPECT_EQ(parserrr("3+20*3/2-1/"), "1");
	EXPECT_EQ(parserrr("1234*((-56)*789)+1200/"), "1");
	EXPECT_EQ(parserrr("12*((-1)+13)*14"), "1");
	EXPECT_EQ(parserrr("12*((-11)+13)*14"), "1");
	EXPECT_EQ(parserrr("12*((-11)+13)*(-12)"), "1");
	EXPECT_EQ(parserrr("12+(-13)+"), "1");
	EXPECT_EQ(parserrr("123*+/456"), "1");
	EXPECT_EQ(parserrr("123*+/456++"), "1");
	EXPECT_EQ(parserrr("12*((-11)+13)*14"), "1");
	EXPECT_EQ(parserrr("12*((-11)+13)*(-12)"), "1");
	
	EXPECT_TRUE(true);
}

TEST(Paser, worng_) {
	EXPECT_EQ(parserrr(")12+3("), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr(")12+33"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("(12+33"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("(12+33))"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("()1234"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("(1+1)1234"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("(1234+5678*91)"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("(1+1)1234"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("a12+34"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("12(-123)"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("12(123)"), "�߸��� �����Դϴ�.");
	EXPECT_EQ(parserrr("12*345(67)"), "�߸��� �����Դϴ�.");

	EXPECT_TRUE(true);
}

TEST(Paser, MaxMin_) {

	EXPECT_EQ(parserrr("2147483647+1"), "1");
	EXPECT_EQ(parserrr("1+2147483647"), "1");
	EXPECT_EQ(parserrr("2147483648+1"), "�����ϴ� ������ ������ �ʰ��߽��ϴ�.");
	EXPECT_EQ(parserrr("1+2147483648"), "�����ϴ� ������ ������ �ʰ��߽��ϴ�.");
	EXPECT_EQ(parserrr("(-2147483648)-1"), "1");
	EXPECT_EQ(parserrr("1-(-2147483648)"), "1");

	EXPECT_TRUE(true);
}
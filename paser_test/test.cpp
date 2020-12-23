#include "pch.h"
#include "../Parser/ParserTree.h"
#include "../Parser/Checker.h"
#include <string>

std::string parserrr(std::string str) {
	Checker chec(str);

	if (chec.runner())
		return "잘못된 수식입니다.";

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
	EXPECT_EQ(parserrr(")12+3("), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr(")12+33"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(12+33"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(12+33))"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("()1234"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(1+1)1234"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(1234+5678*91)"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(1+1)1234"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("a12+34"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("12(-123)"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("12(123)"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("12*345(67)"), "잘못된 수식입니다.");

	EXPECT_TRUE(true);
}

TEST(Paser, MaxMin_) {

	EXPECT_EQ(parserrr("2147483647+1"), "1");
	EXPECT_EQ(parserrr("1+2147483647"), "1");
	EXPECT_EQ(parserrr("2147483648+1"), "지원하는 숫자의 범위를 초과했습니다.");
	EXPECT_EQ(parserrr("1+2147483648"), "지원하는 숫자의 범위를 초과했습니다.");
	EXPECT_EQ(parserrr("(-2147483648)-1"), "1");
	EXPECT_EQ(parserrr("1-(-2147483648)"), "1");

	EXPECT_TRUE(true);
}
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

	if (hashing == "지원하는 숫자의 범위를 초과했습니다.")
		return "지원하는 숫자의 범위를 초과했습니다.";
	else if(hashing == "잘못된 수식입니다.")
		return "잘못된 수식입니다.";
	else {
		Btree1.makeTree(hashing);
		Btree1.makeTreeStream(Btree1.getProot());

		return Btree1.getTreeStream();
	}
}

TEST(Paser, right_) {
	/*EXPECT_EQ(parserrr("2*(2+3)*4"), "#2##2##3##+##*##4##*#");
	EXPECT_EQ(parserrr("12*(12+13)*14"), "#12##12##13##+##*##14##*#");
	EXPECT_EQ(parserrr("12*(12+3)*4"), "#12##12##3##+##*##4##*#");
	EXPECT_EQ(parserrr("(3+4)*8/"), "#3##4##+##8##*#");
	EXPECT_EQ(parserrr("12*(13-12)*14"), "#12##13##12##-##*##14##*#");
	EXPECT_EQ(parserrr("3+20*3/2-1/"), "#3##20##3##*##2##/##+##1##-#");
	EXPECT_EQ(parserrr("1234*((-56)*789)+1200/"), "#1234##-56##789##*##*##1200##+#");
	EXPECT_EQ(parserrr("12*((-1)+13)*14"), "#12##-1##13##+##*##14##*#");
	EXPECT_EQ(parserrr("12*((-11)+13)*14"), "#12##-11##13##+##*##14##*#");
	EXPECT_EQ(parserrr("12*((-11)+13)*(-12)"), "#12##-11##13##+##*##-12###*#");
	EXPECT_EQ(parserrr("12+(-13)+"), "#12##-13###+#");
	EXPECT_EQ(parserrr("123*+/456"), "#123##456##/#");
	EXPECT_EQ(parserrr("123*+/456++"), "#123##456##/#");
	EXPECT_EQ(parserrr("12*((-11)+13)*14"), "#12##-11##13##+##*##14##*#");
	EXPECT_EQ(parserrr("12*((-11)+13)*(-12)"), "#12##-11##13##+##*##-12###*#");
	EXPECT_EQ(parserrr("(1234+5678*91)"), "#1234##5678##91##*##+#"); */
	EXPECT_EQ(parserrr("12/0"), "#12##0##/#");		//파싱까진 잘됨
	
	EXPECT_TRUE(true);
}

TEST(Paser, worng_) {
	EXPECT_EQ(parserrr(")12+3("), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr(")12+33"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(12+33"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(12+33))"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("()1234"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(1+1)1234"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("(1+1)1234"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("a12+34"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("12(-123)"), "잘못된 수식입니다.");
	EXPECT_EQ(parserrr("12(123)"), "잘못된 수식입니다1.");
	EXPECT_EQ(parserrr("12*345(67)"), "잘못된 수식입니다.");

	EXPECT_TRUE(true);
}

TEST(Paser, MaxMin_) {

	EXPECT_EQ(parserrr("2147483647+1"), "#2147483647##1##+#");
	EXPECT_EQ(parserrr("1+2147483647"), "#1##2147483647##+#");
	EXPECT_EQ(parserrr("2147483648+1"), "지원하는 숫자의 범위를 초과했습니다.");
	EXPECT_EQ(parserrr("1+2147483648"), "지원하는 숫자의 범위를 초과했습니다.");
	EXPECT_EQ(parserrr("(-2147483648)-1"), "#-2147483648##1##-#");
	EXPECT_EQ(parserrr("1-(-2147483648)"), "#1##-2147483648###-#");
	EXPECT_EQ(parserrr("1+489451165156"), "지원하는 숫자의 범위를 초과했습니다.");
	EXPECT_EQ(parserrr("1-(-7895151226)"), "지원하는 숫자의 범위를 초과했습니다.");

	EXPECT_TRUE(true);
}
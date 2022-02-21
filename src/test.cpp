#include "Calculator.hpp"
#include <gtest/gtest.h>
#include <iostream>

using std::string;

Calculator calc;

TEST(Calc, add_1_and_1) {
	double val =  1 + 1;
	string exp = "1 + 1";
	calc.calculate(exp);
	ASSERT_DOUBLE_EQ(val, calc.get());
}

TEST(Calc, subtract_tiny_float) {
	double val =  1560 - 0.00002;
	string exp = "1560 - 0.00002";
	calc.calculate(exp);
	ASSERT_DOUBLE_EQ(val, calc.get());
}

TEST(Calc, basic_mul) {
	double val =  2 * 13 * 98;
	string exp = "2 * 13 * 98";
	calc.calculate(exp);
	ASSERT_DOUBLE_EQ(val, calc.get());
}

TEST(Calc, parentheses) {
	double val =  100 / (33 + 17);
	string exp = "100 / (33 + 17)";
	calc.calculate(exp);
	ASSERT_DOUBLE_EQ(val, calc.get());
}

TEST(Calc, floats) {
	double val =  1.1 * 13 / 0.4 + .2;
	string exp = "1.1 * 13 / 0.4 + .2";
	calc.calculate(exp);
	ASSERT_DOUBLE_EQ(val, calc.get());
}

TEST(Calc, zero) {
	double val =  0;
	string exp = "0";
	calc.calculate(exp);
	ASSERT_DOUBLE_EQ(val, calc.get());
}

TEST(Calc, loong) {
	double val =  33 + 19 / 9 + (1.11 / 4 + 202) * 1 * 2 * 3 / 5;
	string exp = "33 + 19 / 9 + (1.11 / 4 + 202) * 1 * 2 * 3 / 5";
	calc.calculate(exp);
	ASSERT_NEAR(val, calc.get(), 1);
}

TEST(Calc, division_by_zero) {
	string exp = "2 / 00000";
	bool result = calc.calculate(exp);
	ASSERT_FALSE(result);
}

TEST(Calc, parse_word) {
	bool result = calc.calculate("something");
	ASSERT_FALSE(result);
}

TEST(Calc, typo) {
	string exp = "55 + 14 / 2a";
	bool result = calc.calculate(exp);
	ASSERT_FALSE(result);
}

int main(int ac, char **av) {
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}

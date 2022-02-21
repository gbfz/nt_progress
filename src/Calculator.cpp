#include "Calculator.hpp"

struct Calculator::Parser: qi::grammar<Iter, double(), space_type> {

	Rule operand, factor, expression;
	Parser(): Parser::base_type(expression) {

		operand %= qi::double_
			| '(' >> expression >> ')'
			| ('+' >> operand)
			| ('-' >> operand [_val = -_1]);

		factor  %= operand >> *(
			('*' >> operand [_val *= _1])
			|
			('/' >> operand [_val /= _1] [qi::_pass = _1 != 0])
		);

		expression %= factor >> *(
			('+' >> factor [_val += _1])
			|
			('-' >> factor [_val -= _1])
		);
	}
};

void Calculator::replace_commas(std::string& input) {
	for (char& c: input) {
		if (c == ',')
			c = '.';
	}
}

bool Calculator::calculate(const std::string& input) {
	Iter it = input.begin(),
	     end = input.end();
	bool parse_success = qi::phrase_parse(
		it, end, Parser(), space_type(), result
	);
	if (!parse_success || it != end) {
		std::cerr << "Parsing failed at \"";
		std::cerr << std::string(it, end) << "\"" << std::endl;
		return false;
	}
	return true;
}

void Calculator::print() const {
	std::cout
		<< std::fixed << std::setprecision(2)
		<< result
		<< std::endl;
}

double Calculator::get() const { return result; }

Calculator::Calculator(): result(0) {}

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/operator.hpp>
#include <iostream>
#include <iomanip>
#include <string>

namespace qi = boost::spirit::qi;
using qi::_val;
using qi::_1;
using boost::spirit::ascii::space_type;
using Iter = std::string::const_iterator;

struct Parser: qi::grammar<Iter, double(), space_type> {

	qi::rule<Iter, double(), space_type> operand,
					     factor,
					     expression;
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

bool parse_calculate(const std::string& input, double& result) {
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

void print_result(double result) {
	std::cout
		<< std::fixed << std::setprecision(2)
		<< result
		<< std::endl;
}

int main(int ac, char **av) {
	std::string input;
	if (ac == 2)
		input = av[1];
	else {
		std::cout << "Enter expression: ";
		std::getline(std::cin, input);
	}
	double result = 0;
	if (parse_calculate(input, result) == false)
		return 2;
	print_result(result);
	return 0;
}

/*
int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Program must be launched with 1 argument: arithmetic expression" << std::endl;
		std::cerr << "Example: ./calculate \"100 / (30 * 0.5)\"" << std::endl;
		return 1;
	}
	double result = 0;
	if (parse_calculate(std::string(av[1]), result) == false)
		return 2;
	print_result(result);
	return 0;
}
*/

#pragma  once
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
using Rule = qi::rule<Iter, double(), space_type>;

class Calculator {
private:
	struct		Parser;
	double		result;

public:
	Calculator();
	bool	calculate(const std::string& input);
	double	get() const;
	void	print() const;
};

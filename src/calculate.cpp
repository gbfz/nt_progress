#include "Calculator.hpp"

int main(int ac, char **av) {
	std::string input;
	if (ac == 2)
		input = av[1];
	else {
		std::cout << "Enter expression: ";
		std::getline(std::cin, input);
	}
	Calculator calculator;
	calculator.replace_commas(input);
	bool good = calculator.calculate(input);
	if (!good) return 2;
	calculator.print();
	return 0;
}

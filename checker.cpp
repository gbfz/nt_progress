#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string cmd = "./calculate ";

std::string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	return result;
}

void test1() {
	std::string exp = "1 + 1";
	std::cout << "Expression: " << exp << std::endl;
	std::cout << "Correct result: " << (1 + 1) << std::endl;
	std::string local_cmd = std::string(cmd + exp);
	std::cout << "Calculator result: " << exec(local_cmd.c_str()) << std::endl;
}

int main() {
	test1();
}

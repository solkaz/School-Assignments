#include "file_handler.hpp"

#include <iostream>

using BoolExpr = std::vector<std::string>;

void PrintExpression(std::vector<std::string>);

int main(int argc, char* argv[]) {

    // Construct a wrapper around the input file stream
    // Defaults to DATA1.txt if the input file wasn't specified
    FileHandler input_file((argv[1] == nullptr ? "DATA1.txt" : argv[1]));
    auto foo = input_file.ReadInputFile();

    for (auto &i : foo) {
	// Print the original boolean expression
	std::cout << "The original boolean expression is:\n";
	PrintExpression(i);

	//auto minimized = MinimizeExpression(i);

	// std::cout << "The minimized boolean expression is:\n";
	// Print the minimized boolean expression
	// PrintExpression(minimized);
    }
    
    return 0;
}

void PrintExpression(BoolExpr bool_expr) {

    std::string expr;
    bool first = true;
    for (const auto &i : bool_expr) {
	if (!first) {
	    expr += " + ";
	} else {
	    first = false;
	}
	auto term_to_add = '(' + i + ')';

	expr += term_to_add;
    }

    std::cout << expr << std::endl;
}

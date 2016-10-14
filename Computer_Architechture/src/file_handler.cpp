#include "file_handler.hpp"

#include <fstream>
#include <iostream>

std::vector<std::vector<std::string>> FileHandler::ReadInputFile() {
    std::ifstream input_file(file_path_, std::fstream::in);

    std::vector<std::string> bool_expr;
    std::vector<std::vector<std::string>> bool_exprs;
    std::string term;
    input_file >> term;
    while (term != "S") {
	while (term != "X") {
	    bool_expr.push_back(term);
	    input_file >> term;
	}
	bool_exprs.push_back(bool_expr);
	bool_expr.clear();
	input_file >> term;
    }
    return bool_exprs;
}

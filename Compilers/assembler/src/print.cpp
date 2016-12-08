#include "print.hpp"

#include <iostream>

// Various print utility functions

void PrintLabel(std::string func_name) {
    std::cout << func_name << ':' << std::endl;
}

void PrintInstruct(std::string instruct, std::string operands) {
    std::cout << "\t" << instruct << "\t" << operands << std::endl;
}

void PrintTableHeader(std::string func) {
    std::cout << "#===== " << func << " ======" << std::endl;
}
void PrintTableFooter(int name_len) {
    std::cout << "#======" << std::string(name_len, '=') << "=======" << std::endl;
}

void PrintAsmHeader(std::string filename) {
    std::cout << "\t.file\t\"" << filename << '\"' << std::endl
	      << "\t.section\t.rodata" << std::endl;
}

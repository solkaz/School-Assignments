#include "print.hpp"

#include <iostream>

void PrintFunc(std::string func_name) {
    std::cout << func_name << ":\tNOP" << std::endl;
}

void PrintInstruct(std::string instruct, std::string operands) {
    std::cout << "\t" << instruct << "\t" << operands << std::endl;
}

void PrintSymbolTable(std::string func) {
    std::cout << "#===== " << func << "======";
    
    std::cout << "#================================";
}

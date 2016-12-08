#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "statement.hpp"
#include "symbol_table.hpp"

#include <iostream>

class Function {
    SymbolTable symbols_;
    std::vector<Statement> statements_;
    int param_counter_;
public:
    Function() : Function("") {}
    Function(std::string func_name) : symbols_(func_name), param_counter_(0) {}

    void AddSymbol(Symbol s) {
	symbols_.AddSymbol(s);
    }

    void AddStatement(std::string instruct, std::string="", std::string="");
    void AddLabel(std::string label) {
	statements_.emplace_back("NOP", std::vector<std::string>(), label);
    }
    void Translate(bool = false);
    void TranslateStatement(Statement);
    std::string TranslateSymbol(std::string);
    std::string GetParamRegister();
    void ResetParamCounter() { param_counter_ = 0; }
};

#endif // FUNCTION_HPP_

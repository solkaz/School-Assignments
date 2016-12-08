#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "statement.hpp"
#include "symbol_table.hpp"

#include <iostream>

class Function {
    SymbolTable symbols_;
    std::vector<Statement> statements_;
    int param_counter_;
    int num_params_;

    std::vector<std::string> params_;
public:
    Function() : Function("") {}
    Function(std::string func_name) : symbols_(func_name), param_counter_(0),
				      num_params_(0) {}

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
    std::string GetParamRegister(int);
    void ResetParamCounter() { param_counter_ = 0; }
    void SetParams(std::string);
};

#endif // FUNCTION_HPP_

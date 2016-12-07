#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "statement.hpp"
#include "symbol_table.hpp"

class Function {
    SymbolTable symbols_;
    std::vector<Statement> statements_;
public:
    Function() : Function("") {}
    Function(std::string func_name) : symbols_(func_name) {
	statements_.emplace_back("NOP", std::vector<std::string>(), func_name);
    }

    void AddSymbol(Symbol s) {
	symbols_.AddSymbol(s);
    }

    void AddStatement(std::string instruct, std::string="", std::string="");
    void AddLabel(std::string label) { statements_.back().AddLabel(label); }
    void Translate(bool);
    void TranslateStatement(Statement);
};

#endif // FUNCTION_HPP_

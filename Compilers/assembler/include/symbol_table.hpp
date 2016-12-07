#ifndef SYMBOL_TABLE_HPP_
#define SYMBOL_TABLE_HPP_

#include <string>
#include <vector>

using Symbol = std::pair<std::string, std::string>;
using SymbolList = std::vector<Symbol>;

class SymbolTable {
    std::string name_;
    SymbolList symbols_;
public:
    SymbolTable();
    SymbolTable(std::string s);
    void AddSymbol(Symbol s) {
	symbols_.push_back(s);
    }

    // void PrintTable() const {
    // 	PrintTableHeader(name_);
    // 	int count = 0;
    // 	for (auto &symbol : symbols_) {
    // 	    PrintSymbol(symbol, count++);
    // 	}
    // 	PrintTableFooter(name_.size());
    // }
};

#endif // SYMBOL_TABLE_HPP_

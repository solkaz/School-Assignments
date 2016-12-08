#ifndef SYMBOL_TABLE_HPP_
#define SYMBOL_TABLE_HPP_

#include <string>
#include <unordered_map>
#include <vector>

using Symbol = std::pair<std::string, std::string>;
using SymbolList = std::vector<Symbol>;
using SymbolMap = std::unordered_map<std::string, int>;

class SymbolTable {
    SymbolList symbols_;
    SymbolMap locations_;
    int position_;
public:
    SymbolTable() : SymbolTable("") {}
    SymbolTable(std::string s);
    void AddSymbol(Symbol s) {
	locations_.insert({s.first, position_});
	symbols_.push_back(s);
	// Increment the position counter
	position_ += 4;
    }

    int GetSymbolLocation(std::string);
    std::string GetTableSize() { return '$' + std::to_string(position_ + 4); }
    std::string name_;

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

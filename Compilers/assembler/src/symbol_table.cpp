#include "symbol_table.hpp"

SymbolTable::SymbolTable() {
    name_ = "";
    symbols_.clear();
}

SymbolTable::SymbolTable(std::string s) {
    name_ = s;
    symbols_.clear();
}

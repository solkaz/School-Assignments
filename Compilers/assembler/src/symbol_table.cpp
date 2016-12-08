#include "symbol_table.hpp"

SymbolTable::SymbolTable(std::string s) {
    name_ = s;
    position_ = 0;
    symbols_.clear();
}

int SymbolTable::GetSymbolLocation(std::string s) {
    return locations_[s] + 4;
}

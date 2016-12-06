#ifndef PRINT_HPP_
#define PRINT_HPP_

#include "types.hpp"

#include <string>

void PrintLabel(std::string);
void PrintInstruct(std::string, std::string = "");
void PrintTableHeader(std::string);
void PrintTableFooter(int);
void PrintSymbol(Symbol, int);

#endif // PRINT_HPP_

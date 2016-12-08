#ifndef PRINT_HPP_
#define PRINT_HPP_

#include <string>

void PrintLabel(std::string);
void PrintInstruct(std::string, std::string = "");
void PrintTableHeader(std::string);
void PrintTableFooter(int);

void PrintAsmHeader(std::string);

#endif // PRINT_HPP_

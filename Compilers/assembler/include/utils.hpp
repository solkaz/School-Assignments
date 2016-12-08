#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "symbol_table.hpp"

#include <string>
#include <vector>

extern SymbolTable globals;

std::vector<std::string> Split(std::string);
std::string Join(std::string, std::string);
std::string Join(std::vector<std::string>);
void PrintInstruction(std::string, std::string="");
std::string TranslateLabel(std::string);
std::string TranslateFunction(std::string);
bool IsNumber(std::string);
void PrintMOVInstruction(std::string, std::string);
bool IsBinaryOp(std::string);
std::string TranslateBinaryOp(std::string);
bool IsRelOp(std::string);
std::string TranslateRelOp(std::string);
bool IsBranchOp(std::string);
std::string TranslateBranchOp(std::string);

bool DoesReferenceRBP(std::string);

#endif // UTILS_HPP_

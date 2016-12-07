#include "function.hpp"
#include "print.hpp"
#include "utils.hpp"

#include <iostream>

void Function::Translate(bool testing=false) {
    auto stmts_itr = statements_.begin();
    auto stmts_end = statements_.end();

    while (stmts_itr != stmts_end) {
	// If testing, print the icode statement
	if (testing)
	    std::cout << "#" << stmts_itr->Print() << std::endl;

	//TranslateStatement(*stmts_itr);

	++stmts_itr;
    }
}

void Function::AddStatement(std::string opcode, std::string operands, std::string label) {
    auto ops = Split(operands);
    statements_.emplace_back(opcode, ops, label);
}

void Function::TranslateStatement(Statement s) {
    std::string opcode = s.opcode_;
    // Painful if ladder to determine
    if (opcode == "MOV") {
	
    } else if (opcode == "RET") {
	
    } else if (opcode == "") {
	
    } else if (opcode == "") {
	
    } else if (opcode == "") {
	
    } else if (opcode == "") {
	
    } else if (opcode == "") {
	
    } else if (opcode == "") {
	
    } else if (opcode == "") {
	
    }
}

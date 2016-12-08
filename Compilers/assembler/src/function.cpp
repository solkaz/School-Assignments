#include "function.hpp"
#include "print.hpp"
#include "utils.hpp"

#include <iostream>

void Function::AddStatement(std::string opcode, std::string operands, std::string label) {
    auto ops = Split(operands);
    statements_.emplace_back(opcode, ops, label);
}

void Function::Translate(bool testing) {

    PrintLabel(symbols_.name_);
    PrintInstruction("pushq", "%rbp");
    PrintInstruction("movq", Join(Operands{"%rsp", "%rbp"}));

    auto stmts_itr = statements_.begin();
    auto stmts_end = statements_.end();

    while (stmts_itr != stmts_end) {
	// If testing, print the icode statement
	if (testing)
	    std::cout << "#" << stmts_itr->Print() << std::endl;

	TranslateStatement(*stmts_itr);

	++stmts_itr;
    }
}

std::string Function::TranslateSymbol(std::string symbol) {
    if (IsNumber(symbol)) {
	return '$' + symbol;
    } else if (symbol[0] == '%') {
	return symbol;
    } 
    
    int symbol_position = symbols_.GetSymbolLocation(symbol);
    return '-' + std::to_string(symbol_position) + "(%rbp)";
}

void Function::TranslateStatement(Statement s) {
    if (s.label_ != "") {
	PrintLabel(s.label_);
	return;
    }
    
    std::string opcode = s.opcode_;
    // Painful if ladder to determine
    if (opcode == "MOV") {
	PrintMOVInstruction(TranslateSymbol(s.operands_[0]),
			    TranslateSymbol(s.operands_[1]));
    } else if (opcode == "RET") {
	PrintInstruction("leave");
	PrintInstruction("ret");
    } else if (IsBinaryOp(opcode)) {
	PrintMOVInstruction(TranslateSymbol(s.operands_[0]), "%eax");
    	PrintInstruction(TranslateBinaryOp(opcode),
			 Join(TranslateSymbol(s.operands_[1]), "%eax"));
    	PrintMOVInstruction("%eax", TranslateSymbol(s.operands_[2]));
    } else if (opcode == "NOT") {
//	PrintInstruction("not", "");
    } else if (opcode == "CALL") {
	PrintInstruction("call", s.operands_[0]);
	ResetParamCounter();
    } else if (opcode == "STRET") {
	PrintMOVInstruction("%eax", TranslateSymbol(s.operands_[0]));
    } else if (opcode == "PARAM") {
	PrintMOVInstruction(TranslateSymbol(s.operands_[0]), GetParamRegister());
    } else if (opcode == "CMP") {
	PrintInstruction("cmp", Join(TranslateSymbol(s.operands_[1]),
				     TranslateSymbol(s.operands_[0])));
    } else if (opcode == "NEG") {
	PrintMOVInstruction(TranslateSymbol(s.operands_[0]),
			    TranslateSymbol(s.operands_[1]));
	PrintInstruction("negl", TranslateSymbol(s.operands_[1]));
    } else if (IsBranchOp(opcode)) {
	PrintInstruction(TranslateBranchOp(opcode), s.operands_[0]);
    }
}

std::string Function::GetParamRegister() {
    std::string reg{""};
    switch (param_counter_) {
	case 0: {
	    reg = "%eax";
	    break;
	}
	case 1: {
	    reg = "%edi";
	    break;
	}
	case 2: {
	    reg = "%esp";
	    break;
	}
	case 3: {
	    reg = "%ebp";
	    break;
	}
    }
    ++param_counter_;
    return reg;
}

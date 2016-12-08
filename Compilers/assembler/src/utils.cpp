#include "utils.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Split(std::string s) {
    std::istringstream iss(s);
    return std::vector<std::string>(std::istream_iterator<std::string>{iss},
				    std::istream_iterator<std::string>{});
}

std::string Join(std::string a, std::string b) {
    return Join(std::vector<std::string>{a, b});
}

std::string Join(std::vector<std::string> vs) {
    std::string new_s = ""; bool first = true;
    for (const auto &s : vs) {
	if (!first) {
	    new_s += ", ";
	} else {
	    first = false;
	}
	new_s += s;
    }
    return new_s;
}

void PrintMOVInstruction(std::string src, std::string dest) {
    if (DoesReferenceRBP(src) && DoesReferenceRBP(dest)) {
	PrintMOVInstruction(src, "%eax");
	PrintMOVInstruction("%eax", dest);
    } else {
	PrintInstruction("movl", Join(src, dest));
    }
}

void PrintInstruction(std::string opcode, std::string operands) {
    std::cout << '\t' << opcode << '\t'  << operands << std::endl;
}

std::string TranslateLabel(std::string label) {
    if (label.find("__L") != 0) {
	return label;
    }
    // Extract the # from the label
    auto label_name_iter = label.cbegin() + 3;
    auto label_name_end = label.cend();
    std::string label_num = "";
    while (label_name_iter != label_name_end) {
	label_num += *(label_name_iter++);
    }
    return std::string(".L") + label_num;
}

bool IsNumber(std::string s) {
    try {
	std::stoi(s);
    } catch (const std::invalid_argument &err) {
	return false;
    }
    return true;
}

bool IsBinaryOp(std::string opcode) {
    std::vector<std::string> binary_ops
    { "ADD", "SUB", "MUL", "DIV", "AND", "OR" };
    return std::find(binary_ops.cbegin(), binary_ops.cend(), opcode) != binary_ops.cend();
}

std::string TranslateBinaryOp(std::string opcode) {
    if (opcode == "ADD") {
	return "addl";
    } else if (opcode == "SUB") {
	return "subl";
    } else if (opcode == "MUL") {
	return "imull";
    } else if (opcode == "DIV") {
	return "idivl";
    } else if (opcode == "AND") {
	return "andl";
    } else {
	return "orl";
    }
}

bool IsRelOp(std::string opcode) {
    std::vector<std::string> binary_ops
    { "LT", "LTE", "GT", "GTE", "EQ", "NEQ" };
    return std::find(binary_ops.cbegin(),
		     binary_ops.cend(), opcode) != binary_ops.cend();
}

std::string TranslateRelOp(std::string opcode) {
    if (opcode == "LT") {
	return "";
    } else if (opcode == "SUB") {
	return "subl";
    } else if (opcode == "MUL") {
	return "imull";
    } else if (opcode == "DIV") {
	return "idivl";
    } else if (opcode == "AND") {
	return "andl";
    } else {
	return "orl";
    }
}

bool IsBranchOp(std::string opcode) {
    std::vector<std::string> binary_ops
    { "BEQ", "BNE", "BGT", "BGE", "BLE", "BLT", "BA" };
    return std::find(binary_ops.cbegin(),
		     binary_ops.cend(), opcode) != binary_ops.cend();
}

std::string TranslateBranchOp(std::string opcode) {
    if (opcode == "BA") {
	return "jmp";
    } else if (opcode == "BEQ") {
	return "je";
    } else if (opcode == "BNE") {
	return "jne";
    } else if (opcode == "BGT") {
	return "jg";
    } else if (opcode == "BGE") {
	return "jge";
    } else if (opcode == "BLE") {
	return "jle";
    } else {
	return "jl";
    }
}

bool DoesReferenceRBP(std::string s) {
    return s.find("%rbp") != -1;
}

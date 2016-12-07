#include "statement.hpp"
#include "utils.hpp"

std::string Statement::Print() {
    if (label_ == "") {
	return "\t" + opcode_ + "\t" + Join(operands_);
    } else {
	// Return a label to print
	return label_ + ":\tNOP";
    }
}

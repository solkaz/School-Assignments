#ifndef STATEMENT_HPP_
#define STATEMENT_HPP_

#include <string>
#include <vector>

using Operands = std::vector<std::string>;

struct Statement {
    std::string opcode_;
    Operands operands_;
    std::string label_;

    Statement(std::string opcode, Operands operands,
	      std::string label="") :
	opcode_(opcode), operands_(operands), label_(label) {}

    void AddLabel(std::string label) { label_ = label; }

    std::string Print();
};

#endif // STATEMENT_HPP_

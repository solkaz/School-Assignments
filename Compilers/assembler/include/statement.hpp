#ifndef STATEMENT_HPP_
#define STATEMENT_HPP_

#include <string>
#include <vector>

struct Statement {
    std::string opcode_;
    std::vector<std::string> operands_;
    std::string label_;

    Statement(std::string opcode, std::vector<std::string> operands,
	      std::string label="") :
	opcode_(opcode), operands_(operands), label_(label) {}

    void AddLabel(std::string label) { label_ = label; }

    std::string Print();
};

#endif // STATEMENT_HPP_

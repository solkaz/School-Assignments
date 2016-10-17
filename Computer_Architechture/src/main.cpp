#include "file_handler.hpp"

#include <algorithm>
#include <iostream>

using Term = std::string;
using BoolExpr = std::vector<Term>;
using TermBucket = std::vector<BoolExpr>;

void PrintExpression(BoolExpr);
BoolExpr MinimizeExpression(BoolExpr);
TermBucket MakeTermBucket(BoolExpr);
unsigned int NumberOfComplements(Term);
void PrintTermBucket(TermBucket);

int main(int argc, char* argv[]) {

    // Construct a wrapper around the input file stream
    // Defaults to DATA1.txt if the input file wasn't specified
    FileHandler input_file((argv[1] == nullptr ? "DATA1.txt" : argv[1]));
    auto foo = input_file.ReadInputFile();

    for (auto &i : foo) {
	// Print the original boolean expression
	std::cout << "The original boolean expression is:\n";
	PrintExpression(i);

	auto minimized = MinimizeExpression(i);

	// std::cout << "The minimized boolean expression is:\n";
	// Print the minimized boolean expression
	// PrintExpression(minimized);
    }

    return 0;
}

void PrintExpression(BoolExpr bool_expr) {

    std::string expr;
    bool first = true;
    for (const auto &i : bool_expr) {
	if (!first) {
	    expr += " + ";
	} else {
	    first = false;
	}
	auto term_to_add = '(' + i + ')';

	expr += term_to_add;
    }

    std::cout << expr << std::endl;
}

BoolExpr MinimizeExpression(BoolExpr bool_expr) {
    // Sort the terms into buckets based on their # of variable complements
    auto terms_buckets = MakeTermBucket(bool_expr);
    PrintTermBucket(terms_buckets);
    return BoolExpr();
}

TermBucket MakeTermBucket(BoolExpr bool_expr) {
    TermBucket buckets;

    // Sort each Term in the BoolExpr into its correct
    // bucket based on the number of variable complements
    for (auto &i : bool_expr) {
	auto num_complements = NumberOfComplements(i);
	if (buckets.size() < num_complements + 1) {
	    buckets.resize(num_complements + 1);
	}
	buckets[num_complements].push_back(i);
    }

    return buckets;
}

void PrintTermBucket(TermBucket buckets) {
    for (const auto &bucket : buckets) {
	for (const auto &term : bucket) {
	    std::cout << term << ' ';
	}
	std::cout << std::endl;
    }
}

unsigned int NumberOfComplements(Term term) {
    return static_cast<unsigned int>(
	std::count_if(
	    term.cbegin(), term.cend(),
	    [](char c) { return std::islower(c); }
	    )
	);
}

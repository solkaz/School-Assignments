#include "file_handler.hpp"

#include <algorithm>
#include <iostream>

using Term = std::string;
using BoolExpr = std::vector<Term>;
using TermBucket = std::vector<BoolExpr>;
using UsedTermRef = std::vector<std::vector<bool>>;

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

BoolExpr FactorBoolExpr(BoolExpr bool_expr) {
    BoolExpr new_expr = bool_expr;
    do {
	auto terms_buckets = MakeTermBucket(bool_expr);
	new_expr = FactorTermBucket(terms_buckets);
    } while (new_expr.size())
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

BoolExpr FactorTermBucket(TermBucket buckets) {
    auto used_ref = MakeUsedTermRef(buckets);
    int num_buckets = buckets.size();

    BoolExpr new_terms(0);
    
    for (auto a = 0; a < num_buckets - 1; ++a) {
	auto b = a + 1;
	auto a_bucket_size = buckets[a].size();
	auto b_bucket_size = buckets[b].size();

	// Don't try to compare the two buckets if one of them is empty
	if (!(a_bucket_size && b_bucket_size)) {
	    // Increment the counter by one as it'll be guaranteed to result
	    // in another continue
	    ++a; continue;
	}
	for (auto i = 0; i < a_bucket_size; ++i) {
	    for (auto j = 0; j < b_bucket_size; ++j) {
		if (!(used_ref[a][i] && used_ref[b][j]) &&
		    SetDifference(buckets[a][i], buckets[b][j]) == 1) {

		    // Set the used references for a and b
		    used_ref[a][i] = true, used_ref[b][j] = true;
		    auto new_term = CombineTerms(buckets[a][i], buckets[b][j]);
		    new_terms.push_back(new_term);
		}
	    }
	}
    }

    auto unused_terms = FlattenTermBucket(buckets, used_ref);
    
    return new_terms;
}

BoolExpr FlattenTermBucket(TermBucket terms_buckets) {
    BoolExpr bool_expr;
    for (const auto &bucket: terms_buckets) {
	for (const auto &term : bucket) {
	    bool_expr.push_back(term);
	}
    }
    return bool_expr;
}

BoolExpr FlattenTermBucket(TermBucket terms_buckets, UsedTermRef used_terms) {
    BoolExpr bool_expr;
    auto num_buckets = terms_buckets.size();
    for (int i = 0; i < num_buckets; ++i) {
	auto bucket_size = terms_buckets[i].size();
	for (int j = 0; j < bucket_size; ++j) {
	    if (!used_terms[i][j]) {
		bool_expr.push_back(term);
	    }
	}
    }
    return bool_expr;
}

unsigned int SetDifference(Term a, Term b) {
    std::string c;
    std::set_difference(a.cbegin(), a.cend(),
			b.cbegin(), b.cend(),
			std::back_inserter(c));
    return static_cast<unsigned int>(c.size());
}

Term CombineTerms(Term a, Term b) {
    std::string c;
    std::set_intersection(a.cbegin(), a.cend(),
			  b.cbegin(), b.cend(),
			  std::back_inserter(c));
    return c;
}

UsedTermBucket MakeUsedTermRef(TermBucket buckets) {
    auto bucket_size = buckets.size();
    UsedTermRef used_buckets(buckets.size());
    for (auto i = 0; i < bucket_size; ++i) {
	used_buckets[i].resize(buckets[i].size(), false);
    }
    return used_buckets;
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

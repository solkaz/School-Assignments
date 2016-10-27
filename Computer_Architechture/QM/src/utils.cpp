#include "utils.hpp"

#include <algorithm>

//************************* FUNCTION CombineBoolExprs **************************
BoolExpr CombineBoolExprs(BoolExpr a, BoolExpr b) {
    /*
     * Receives: Two BoolExprs
     * Task: Concatenate BoolExpr b onto the end of a
     * Returns: A new BoolExpr consisting of a + b
     */
    
    // Create a new BoolExpr that is the concat of to_add onto dest
    std::copy(b.begin(), b.end(), std::back_inserter(a));
    return a;
}
//************************* END OF FUNCTION CombineBoolExprs *******************

//************************* FUNCTION CombineTerms ******************************
Term CombineTerms(Term a, Term b) {
    /*
     * Receives: Two terms
     * Task: Create a new Term that is the combination of the two; if a variable 
     *       differs in a position, remove it
     * Returns: the new Term
     */
    
    Term c; auto term_size = a.size();
    for (int i = 0; i < term_size; ++i) {
	// Add the char to the string if it is in A & B; otherwise add '_'
	c.push_back((a[i] == b[i] ? a[i] : '_'));
    }
    return c;
}
//************************* END OF FUNCTION CombineTerms ***********************

//************************* FUNCTION GetUnusedTerms ****************************
BoolExpr GetUnusedTerms(TermBuckets terms_buckets, UsedTermRef used_terms) {
    /*
     * Receives: TermBuckets and a UsedTermRef of used terms
     * Task: Extract the terms that weren't combined in CompareTerms
     * Returns: the unused terms as a BoolExpr
     */
    
    BoolExpr unused_terms; auto num_buckets = terms_buckets.size();
    for (int i = 0; i < num_buckets; ++i) {
	auto bucket_size = terms_buckets[i].size();
	for (int j = 0; j < bucket_size; ++j) {
	    // Add the term to unused_terms if it hasn't been used
	    if (!used_terms[i][j]) {
		unused_terms.push_back(terms_buckets[i][j]);
	    }
	}
    }
    return unused_terms;
}
//************************* END OF FUNCTION GetUnusedTerms *********************

//************************* FUNCTION StripUnderscores **************************
Term StripUnderscores(Term term) {
    /*
     * Receives: a Term
     * Task: Strip the underscores from the term
     * Returns: the inputted term sans underscores
     */

    // Get the position of the iterator of the new range
    auto end_it = std::remove_if(term.begin(), term.end(),
		   [](char c) { return c == '_'; });
    // erase underscores if there are any (will == term.end() if there are none)
    if (end_it != term.end()) {
	term.erase(end_it);
    }
    return term;
}
//************************* END OF FUNCTION StripUnderscores *******************

//************************* FUNCTION IsSubset **********************************
bool IsSubset(Term minterm, Term prime) {
    /*
     * Receives: A minterm and a prime implicant
     * Task: Determine if prime is a subset of minterm
     * Returns: bool of if prime is a subset of minterm
     */

    // Remove underscores from prime
    prime = StripUnderscores(prime);
    return std::includes(minterm.begin(), minterm.end(),
			 prime.begin(), prime.end());
}
//************************* END OF FUNCTION IsSubset ***************************

//************************* FUNCTION MakeUsedTermRef ***************************
UsedTermRef MakeUsedTermRef(TermBuckets buckets) {
    /*
     * Receives: TermBuckets
     * Task: Make a UsedTermRef to keep track of used Terms
     * Returns: a UsedTermRef
     */
    // Number of rows = number of buckets
    auto num_rows = buckets.size();

    // Construct the UsedTermRef
    UsedTermRef used_terms_ref(num_rows);

    // Resize each row in the UsedTermRef to the same size as its respective
    // row in buckets
    for (int i = 0; i < num_rows; ++i) {
	// Default each term to false
	used_terms_ref[i].resize(buckets[i].size(), false);
    }

    // Return the new UsedTermRef
    return used_terms_ref;
}
//************************* END OF FUNCTION MakeUsedTermRef ********************

//************************* FUNCTION NumberOfComplements ***********************
unsigned int NumberOfComplements(Term term) {
    /*
     * Receives: a Term
     * Task: compute the # of complements in the term
     * Returns: the # of complements in the term
     */
    return static_cast<unsigned int>(
	std::count_if(
	    term.cbegin(), term.cend(),
	    [](char c) { return std::islower(c); }
	    )
	);
}
//************************* END OF FUNCTION NumberOfComplements ****************

//************************* FUNCTION PrintExpression ***************************
std::string PrintExpression(BoolExpr bool_expr) {
    /*
     * Receives: a BoolExpr
     * Task: construct a string to print from the BE
     * Returns: the string to print
     */

    std::string expr; 
    bool first = true;
    
    for (const auto &term : bool_expr) {
	if (!first) {
	    expr += " + ";
	} else {
	    first = false;
	}

	auto formatted = StripUnderscores(term);
	auto term_to_add = '(' + formatted + ')';

	expr += term_to_add;
    }

    return expr;
}
//************************* END OF FUNCTION PrintExpression ********************

//************************* FUNCTION SetDifference *****************************
unsigned int SetDifference(Term a, Term b) {
    /*
     * Receives: Two Terms
     * Task: Compute the Hamming distance between the two terms
     * Returns: the Hamming distance of a and b
     */
    auto term_size = a.size();
    unsigned int diff = 0;
    for (int i = 0; i < term_size; ++i) {
	if (a[i] != b[i]) {
	    ++diff;
	}

    }
    return diff;
}
//************************* END OF FUNCTION SetDifference **********************

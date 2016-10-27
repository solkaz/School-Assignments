//********************* Program ID *********************************************
//                                                                             *
// Program files: main.cpp, file_handler.cpp, file_handler.hpp, utils.cpp,     *
//                utils.hpp, Makefile                                          *
//                                                                             *
// Assignment #:                                                               *
//                                                                             *
// Author: _____________________                                               *
//             Jeff Held                                                       *
//                                                                             *
// Course: CSC 403011                                                          *
//                                                                             *
// Due Date: Oct. 17 2016                                                      *
//                                                                             *
//******************************************************************************

//**************************** Program Description *****************************
//                                                                             *
// This is an implementation of the Quine-McCluskey method. Data is read from  *
// a data file, creating BoolExprs (boolean expressions) made of Terms. Each   *
// BoolExpr is minimized by finding the prime implicants from the minterms and *
// then comparing them to the original terms. Currently not exact because it   *
// essentially covers only essential prime implicants; Petrick's method is     *
// needed in order to solve the problem completely                             *
//                                                                             *
//******************************************************************************

#include "file_handler.hpp"
#include "utils.hpp"

#include <iostream>

BoolExpr MinimizeExpression(BoolExpr);
BoolExpr FindPrimeImplicants(BoolExpr);
TermBuckets BucketSortTerms(BoolExpr);
TermPair CompareTermBuckets(TermBuckets);
PrimeImplChart MakePrimeImplChart(BoolExpr, BoolExpr);
void MarkSubsets(PrimeImplChart&, BoolExpr&, BoolExpr&);
BoolExpr GetEssentialPrimes(PrimeImplChart&, BoolExpr&, BoolExpr&);

int main(int argc, char* argv[]) {
    // Construct a wrapper around the input file stream
    // Defaults to DATA1.txt if the input file wasn't specified
    FileHandler input_file((argv[1] == nullptr ? "DATA1.txt" : argv[1]));
    auto bool_expressions = input_file.ReadInputFile();

    for (auto &expression : bool_expressions) {
	// Print the original boolean expression
	std::cout << "The original boolean expression is:\n"
		  << PrintExpression(expression) << std::endl;

	auto minimized = MinimizeExpression(expression);

	// Print the minimized boolean expression only if it
	// was successfully minimized
	if (minimized.size()) {
	    std::cout << "The minimized boolean expression is:\n"
		      << PrintExpression(minimized) << std::endl;
	}
	std::cout << std::endl;
    }

    return 0;
}

//************************* FUNCTION MinimizeExpression ************************
BoolExpr MinimizeExpression(BoolExpr minterms) {

    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */

    // Find the prime implicants from the minterms given
    auto prime_implicants = FindPrimeImplicants(minterms);

    // Construct a prime implicant chart
    auto prime_impl_chart = MakePrimeImplChart(minterms, prime_implicants);
    
    // Mark the essential prime implicants and get them
    auto essential_primes = GetEssentialPrimes(prime_impl_chart,
					       minterms, prime_implicants);

    // Would implement Petrick's method to ensure that a minimum expression is
    // found here; beyond scope of assignment

    // Return the essential primes
    return essential_primes;
}
//************************* END OF FUNCTION MinimizeExpression *****************

//************************* FUNCTION FindPrimeImplicants ***********************
BoolExpr FindPrimeImplicants(BoolExpr bool_expr) {

    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */
    
    BoolExpr prime_implicants;
    
    do {
	// Sort the terms into groups based on their number of complements
	auto grouped_terms = BucketSortTerms(bool_expr);
	//std::cout << PrintTermBuckets(grouped_terms) << std::endl;
	// Compare the groups with each other to reduce the terms
	auto terms_pair = CompareTermBuckets(grouped_terms);

	// bool_expr will contain the terms that will be sorted into buckets
	// next iteration (if there are still terms to compare)
	bool_expr = terms_pair.first;
	
	// Concatenate the unused terms to the list of prime implicants to return
	prime_implicants = CombineBoolExprs(prime_implicants, terms_pair.second);

	// Continue while there are still terms to compare
    } while (bool_expr.size());

    // Return the list of prime implicants
    return prime_implicants;
}
//************************* END OF FUNCTION FindPrimeImplicants ****************

//************************* FUNCTION BucketSortTerms ***************************
TermBuckets BucketSortTerms(BoolExpr bool_expr) {
    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */

    // Sort the terms w/ bucket sort, using the # of complements as the key
    TermBuckets buckets;

    // Iterate through all terms in the BE
    for (const auto &term : bool_expr) {
	// Get the # of complements
	auto num_complements = NumberOfComplements(term);

	// Resize the # of buckets as needed
	if (buckets.size() < num_complements + 1) {
	    buckets.resize(num_complements + 1);
	}
	// Put the term into the bucket
	buckets[num_complements].push_back(term);
    }
    
    return buckets;
}
//************************* END OF FUNCTION BucketSortTerms ********************

//************************* FUNCTION CompareTermBuckets ************************
TermPair CompareTermBuckets(TermBuckets buckets) {
    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */
    
    // Create a UsedTermRef, which is used to check if a term
    // has already been "checked"
    auto used_term_ref = MakeUsedTermRef(buckets);
    int num_buckets = buckets.size();

    BoolExpr new_terms;

    // Compare each bucket with the one below it (except for the last bucket)
    for (int bucket_a = 0; bucket_a < num_buckets - 1; ++bucket_a) {
	int bucket_b = bucket_a + 1;
	int bucket_a_size = buckets[bucket_a].size();
	int bucket_b_size = buckets[bucket_b].size();

	// Don't try to compare two buckets if one of them is empty
	if (!(bucket_a_size && bucket_b_size)) {
	    continue;
	}

	for (int a_term = 0; a_term < bucket_a_size; ++a_term) {
	    for (int b_term = 0; b_term < bucket_b_size; ++b_term) {
		bool both_terms_checked = (used_term_ref[bucket_a][a_term] &&
					   used_term_ref[bucket_b][b_term]);
		int set_diff = SetDifference(buckets[bucket_a][a_term],
					      buckets[bucket_b][b_term]);
		if (!both_terms_checked && set_diff == 1) {
		    // Set the used references for a and b
		    used_term_ref[bucket_a][a_term] = true;
		    used_term_ref[bucket_b][b_term] = true;

		    auto new_term = CombineTerms(buckets[bucket_a][a_term],
						 buckets[bucket_b][b_term]);
		    new_terms.push_back(new_term);
		}
	    }
	}
    }

    // Get the unused terms
    auto unused_terms = GetUnusedTerms(buckets, used_term_ref);
    
    return std::make_pair(new_terms, unused_terms);
}
//************************* END OF FUNCTION CompareTermBuckets *****************

//************************* FUNCTION MakePrimeImplChart ************************
PrimeImplChart MakePrimeImplChart(BoolExpr minterms, BoolExpr prime_implicants) {
    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */

    PrimeImplChart prime_impl_chart(prime_implicants.size(),
				    PrimeImplCol(minterms.size(), 0));

    // Mark the cells where the prime implicant is a subset of the minterm
    MarkSubsets(prime_impl_chart, minterms, prime_implicants);

    return prime_impl_chart;
}
//************************* END OF FUNCTION MakePrimeImplChart *****************

//************************* FUNCTION MarkSubsets *******************************
void MarkSubsets(PrimeImplChart &chart, BoolExpr &minterms,
		 BoolExpr &prime_implicants) {
    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */

    int num_primes = prime_implicants.size();
    int num_minterms = minterms.size();
    
    // Compare each prime implicant to each minterm to see if it's a subset
    for (int i = 0; i < num_primes; ++i) {
	for (int j = 0; j < num_minterms; ++j) {
	    if (IsSubset(minterms[j], prime_implicants[i])) {
		chart[i][j] = 1;
	    }
	}
    }
}
//************************* END OF FUNCTION MarkSubsets ************************

//************************* FUNCTION GetEssentialPrimes ************************
BoolExpr GetEssentialPrimes(PrimeImplChart &chart, BoolExpr &minterms,
			    BoolExpr &prime_implicants) {
    /*
     * Receives: the inputted minterms for the expression to minimze
     * Task: Get the minimized expression of minterms
     * Returns: the essential primes as a BoolExpr
     */

    int num_primes = prime_implicants.size();
    int num_minterms = minterms.size();

    BoolExpr essentials;

    // Check each column for a lone X; this means that this prime implicant
    // is essential; the expression cannot be built without it
    for (int minterm = 0; minterm < num_minterms; ++minterm) {
	int lone_position = -1;
	for (int prime = 0; prime < num_primes; ++prime) {
	    if (chart[prime][minterm] == 1) {
		// Check if there's been an X found already
		if (lone_position == -1) {
		    // Circle the X to mark the row as an essential PI
		    chart[prime][minterm] = 2;
		    // Save the location of the circled X
		    lone_position = prime;
		} else {
		    // Another X was found; uncircle the previous X
		    chart[lone_position][minterm] = 1;
		    // Reset lone_position to signify that there are multiple Xs
		    lone_position = -1;
		    // End search through this column
		    break;
		}
	    }
	}
	if (lone_position != -1) {
	    // This prime is essential; add it to essentials if it is not
	    // already added
	    auto essential_term = prime_implicants[lone_position];
	    bool not_added = true;
	    
	    for (auto term = essentials.begin(); term != essentials.end(); ++term) {
		if (*term == essential_term) {
		    not_added = false;
		    break;
		}
	    }
	    
	    if (not_added)
		essentials.push_back(essential_term);
	}
    }
    return essentials;
}
//************************* END OF FUNCTION GetEssentialPrimes *****************

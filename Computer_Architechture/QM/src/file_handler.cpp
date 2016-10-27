#include "file_handler.hpp"

#include <fstream>
#include <iostream>

//************************* FUNCTION ReadInputFile *****************************
std::vector<BoolExpr> FileHandler::ReadInputFile() {

    /*
     * Receives: Nothing
     * Task: Read the input file and construct the boolean expressions
     * Returns: A vector of the boolean expressions
     */

    // Open an ifstream to the input file
    std::ifstream input_file(file_path_, std::fstream::in);

    BoolExpr bool_expr;
    std::vector<BoolExpr> bool_exprs;
    Term term;
    
    input_file >> term;
    // Continue reading expressions while the EOF sentinel hasn't been read
    while (term != "S") {

	// Keep reading terms while the end of expr sentinel hasn't been read
	while (term != "X") {
	    // Add the term to the expr
	    bool_expr.push_back(term);
	    // Get another term
	    input_file >> term;
	}
	// Add the bool expr 
	bool_exprs.push_back(bool_expr);
	// Clear the boolean expression
	bool_expr.clear();
	// Get another term
	input_file >> term;
    }
    return bool_exprs;
}
//************************* END OF FUNCTION ReadInputFile **********************

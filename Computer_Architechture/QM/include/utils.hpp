#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "types.hpp"


BoolExpr CombineBoolExprs(BoolExpr, BoolExpr);
Term CombineTerms(Term, Term);
BoolExpr GetUnusedTerms(TermBuckets, UsedTermRef);
bool IsSubset(Term, Term);
UsedTermRef MakeUsedTermRef(TermBuckets);
unsigned int NumberOfComplements(Term);
std::string PrintExpression(BoolExpr);
std::string PrintTermBuckets(TermBuckets);
unsigned int SetDifference(Term, Term);
Term StripUnderscores(Term);

#endif // UTILS_HPP_

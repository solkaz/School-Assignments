#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <string>
#include <vector>

using Term = std::string;
using BoolExpr = std::vector<Term>;
using TermBuckets = std::vector<BoolExpr>;
using TermPair = std::pair<BoolExpr, BoolExpr>;

using PrimeImplCol = std::vector<int>;
using PrimeImplChart = std::vector<PrimeImplCol>;

using UsedTermCol = std::vector<bool>;
using UsedTermRef = std::vector<UsedTermCol>;

#endif // TYPES_HPP_

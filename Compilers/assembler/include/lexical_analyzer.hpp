#ifndef LEXICAL_ANALYZER_HPP_
#define LEXICAL_ANALYZER_HPP_

#include "token_list.hpp"

#include <fstream>
#include <string>

class LexicalAnalyzer {
    TokenList tokens_;
public:
    LexicalAnalyzer() {}
    LexicalAnalyzer(char* c) : LexicalAnalyzer(std::string(c)) {}
    LexicalAnalyzer(std::string);

    TokenPair NextToken() { return tokens_.NextToken(); }
};

#endif // LEXICAL_ANALYZER_HPP_

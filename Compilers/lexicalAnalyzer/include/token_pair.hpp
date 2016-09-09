#ifndef TOKEN_PAIR_HPP_
#define TOKEN_PAIR_HPP_

#include <string>
#include <utility>

using TokenPairType = std::pair<std::string, std::string>;

class TokenPair {
    // Type of token
    std::string token_type_;
    // Actual contents of the token
    std::string token_content_;

    TokenPairType token_pair_;

public:
    TokenPair(TokenPairType &token_pair) :
	token_pair_(token_pair) {}
    
    TokenPair(std::string &token_type, std::string &token_content) :
	token_type_(token_type), token_content_(token_content) {}

    std::string FormatToPrint();
};

#endif // TOKEN_PAIR_HPP_

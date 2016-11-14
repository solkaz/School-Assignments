#ifndef TOKEN_PAIR_HPP_
#define TOKEN_PAIR_HPP_

#include <string>
#include <utility>

using TokenPairType = std::pair<std::string, std::string>;

class TokenPair {

    TokenPairType token_pair_;

public:
    TokenPair(TokenPairType &token_pair) :
	token_pair_(token_pair) {}
    
    TokenPair(std::string &token_type, std::string &token_content) {
	token_pair_ = std::make_pair(token_type, token_content);
    }

    std::string FormatToPrint();

    std::string Type() const { return token_pair_.first; }
    std::string Contents() const { return token_pair_.second; }
};

#endif // TOKEN_PAIR_HPP_

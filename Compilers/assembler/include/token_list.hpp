#ifndef TOKEN_LIST_HPP_
#define TOKEN_LIST_HPP_

#include "token_pair.hpp"

#include <vector>

using TokenListType = std::vector<TokenPair>;
using TokenListCIterator = std::vector<TokenPair>::const_iterator;

class TokenList {
    TokenListType tokens_;
    TokenListCIterator current_token_;
    TokenListCIterator end_;
public:
    TokenList();
    TokenList(TokenListType t);
    TokenPair NextToken();
};

#endif // TOKEN_LIST_HPP_

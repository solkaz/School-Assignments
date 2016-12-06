#include "token_list.hpp"

// Initialize an empty vector
TokenList::TokenList() {
    tokens_.clear();
}

// Construct from a TokenListType (aka std::vector<TokenPair>)
// TokenPair = Wrapper around TokenPairType
// AKA std::pair<std::string, std::string>
TokenList::TokenList(TokenListType t) {
    tokens_ = t;  // Copy t into tokens_

    // Set the current/end iterators
    current_token_ = tokens_.begin();
    end_ = tokens_.end();
}

// Return a TokenPair to mimic "lexically analyzing" the input file
TokenPair TokenList::NextToken() {

    // Return tokens while there are still tokens to return
    if (current_token_ != end_) {
	return *(current_token_++);
    } else {
	// Return a special "EOF" token when there are no more
	// tokens to process
	std::string type = "EOF";
	std::string contents = "0";
	return TokenPair(type, contents);
    }
}

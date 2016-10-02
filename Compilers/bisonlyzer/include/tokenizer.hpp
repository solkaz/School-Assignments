#ifndef TOKENIZER_HPP_
#define TOKENIZER_HPP_

#include "token_pair.hpp"
#include "token_constants.hpp"

#include <string>
#include <vector>

using string_citerator = std::string::const_iterator;

class Tokenizer {
public:
    // Tokenizer accepts a string that is the source code's contents
    Tokenizer(std::string&);

    // Main function that will return a list of tokens
    std::vector<TokenPair> Tokenize();
    
    void SkipWhitespace();

    std::string ExtractSubstring(string_citerator&, string_citerator&);
    
    TokenPairType MakeNumberToken();
    std::string ExtractNumber();

    TokenPairType MakeWordToken();
    std::string ExtractWord();
    
    TokenPairType HandlePunctuation(char);
    void ReadComment();
    std::string ExtractStringToken();

    TokenPairType NewErrorToken(std::string);

    char Next();
    void Increment() { ++source_code_position_; }
    bool IsKeyword(std::string);

private:
    // The source code file's content, represented as a string
    std::string source_code_;
    // Current iterator position in the source code
    string_citerator source_code_position_;
    // "End" iterator position of the source code; when source_code_position_
    // is == source_code_end_ then all chars have been processed
    string_citerator source_code_end_;
};

#endif // TOKENIZER_HPP_

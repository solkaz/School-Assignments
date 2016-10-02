#include "tokenizer.hpp"

#include <algorithm>
#include <iterator>

Tokenizer::Tokenizer(std::string &input) {
    // Hydrate the source code representation
    source_code_ = input;
    // Set the relevant iterators for the source code
    source_code_position_ = source_code_.cbegin();
    source_code_end_ = source_code_.cend();
}

char Tokenizer::Next() {
    // Ensure that the end hasn't been reached, and thus can still
    // read chars in the source code
    if (source_code_position_ + 1 != source_code_end_) {
	return *(source_code_position_ + 1);
    } else {
	return ' ';
    }
}

std::vector<TokenPair> Tokenizer::Tokenize() {
    // Vector container of all the tokens, as strings
    std::vector<TokenPair> tokens;

    // Iterate through each character in the source code
    while (source_code_position_ != source_code_end_) {
	// Get a copy of the char currently pointed at
	char current_char = *source_code_position_;
	
	TokenPairType new_token_pair;
	
	if (std::isspace(current_char)) {
	    // Iterate through white space
	    SkipWhitespace();
	    continue;
	} else if (std::isdigit(current_char)) {
	    // Create a number-type token
	    new_token_pair = MakeNumberToken();
	} else if (std::isalpha(current_char)) {
	    // Create a word-type token (either ID or a keyword)
	    new_token_pair = MakeWordToken();
	} else if (ispunct(current_char)) {
	    // Check that the char is a valid punctuation char (that is a token type)

	    // Get the TokenPairType for the punctuation char
	    new_token_pair = HandlePunctuation(current_char);
	    
	    
	    
	    // Comment isn't a token type that's printed; skip adding it
	    if (new_token_pair.first == "COMMENT") {
		continue;
	    }
	} else {
	    // If there is a strange char that doesn't pass any of the above,
	    // it is an erroneous char; indicate it as such
	    new_token_pair = NewErrorToken(std::string(1, current_char));
	    Increment();
	}
	// Create a new TokenPair at the end by constructing it from
        // new_token_pair's data
	tokens.emplace_back(new_token_pair);
    }
    // Return the final list of tokens parsed
    return tokens;
}

void Tokenizer::SkipWhitespace() {
    // Increment the iterator until a non-whitespace char is found
    while (std::isspace(*source_code_position_)) {
	Increment();
    }
}

TokenPairType Tokenizer::MakeNumberToken() {
    // Construct a NUMBER type token
    std::string token_type = "NUMBER";
    std::string token_contents = ExtractNumber();

    TokenPairType token_pair(token_type, token_contents);
    return token_pair;
}

std::string Tokenizer::ExtractNumber() {
    // Save the starting position of the iterator
    auto num_start_index = source_code_position_;

    // Increment the iterator until the current char is not a digit
    while (std::isdigit(*source_code_position_)) {
	Increment();
    }
    // Save the ending position of the iterator
    auto num_end_index = source_code_position_;
    // Get the substring from the source code and return it
    return ExtractSubstring(num_start_index, num_end_index);
}

TokenPairType Tokenizer::MakeWordToken() {
    // Create a word-based token meaning either an ID token, or a keyword token
    // if it is one of the predefined keyword
    
    // Extract the word from the source code
    std::string token_contents = ExtractWord();
    std::string token_type = "";
    
    // Check if it is a keyword
    if (IsKeyword(token_contents)) {
	// Token's type is simply the caps form of the token's contents

	// Copy token_contents into token_type
	token_type = token_contents;
	
	// Capitalize all letters in token_type
	std::transform(token_type.begin(),
		       token_type.end(),
		       token_type.begin(),
		       [](char c) { return std::toupper(c); });
	
    } else {
	// Token is an ID
	token_type = "ID";
    }
    // Create the TokenPairType and return it
    TokenPairType token_pair(token_type, token_contents);
    return token_pair;
}

std::string Tokenizer::ExtractWord() {
    // Save the starting position of the iterator
    auto word_start_index = source_code_position_;
    
    // Increment the iterator until a non-alphanumeric char is encountered
    while (std::isalnum(*source_code_position_)) {
	Increment();
    }
    
    // Save the ending position of the iterator
    auto word_end_index = source_code_position_;
    
    // Return a copy of the word
    return ExtractSubstring(word_start_index, word_end_index);
}

std::string Tokenizer::ExtractSubstring(string_citerator &start_index,
					string_citerator &end_index) {
    // Create a substring from the source code given the iterator positions
    // and return the substring
    std::string content(start_index, end_index);
    return content;
}

TokenPairType Tokenizer::HandlePunctuation(char c) {
    std::string token_type = "";
    std::string token_contents(1, c);

    // Assign the token type based on the char c
    switch (c) {
	case '\"': {
	    // Quotation signals a STRING
	    token_type = "STRING";
	    
	    // Extract the string from the source code
	    token_contents = ExtractStringToken();
	    break;
	}
	case '#': {
	    // Comment; read until end-of-line
	    ReadComment();
	    // COMMENT isn't a real type; this is used to check if a comment
	    // read, and will be ignored if the token is COMMENT
	    token_type = "COMMENT";
	    break;
	}
	case '=': {
	    // Check that the next character is '=', as '==' is a valid token,
	    // but '=' is NOT
	    auto next_char = static_cast<char>(Next());
	    if (next_char == '=') {
		// Token type is RELOP
		token_type = "RELOP";
		token_contents += next_char;
		Increment();
	    } else {
		// Erroneous token;
		token_type = "ERROR";
	    }
	}

	case '+':
	case '-': {
	    // ADDOP
	    token_type = "ADDOP";
	    break;
	}
	case '&': {
	    token_type = "AND";
	    break;
	}

	case '*':
	case '/': {
	    // MULOP
	    token_type = "MULOP";
	    break;
	}
	case ',': {
	    token_type = "COMMA";
	    break;
	}

	case '{': {
	    token_type = "CURLL";
	    break;
	}
	case '}': {
	    token_type = "CURLR";
	    break;
	}

	case '!': {
	    /*
	     * An exclamation point can be NOT by itself, or
	     * a RELOP if '=' follows it. Check which one it is
	     */
	    auto next_char = static_cast<char>(Next());
	    if (next_char == '=') {
		// Token is a RELOP
		token_type = "RELOP";
		token_contents += next_char;
		// Increment the pointer since the next char is being added to
		// the current token
		Increment();
	    } else {
		// Token is NOT
		token_type = "NOT";
	    }
	    break;
	}
	case '>': {
	    token_type = "RELOP";
	    // Check if token is '>' or '>='
	    auto next_char = static_cast<char>(Next());
	    if (next_char == '=') {
		// Add the second char to the token contents
		token_contents += next_char;
		// Another char was consumed; increment the iterator
		Increment();
	    }
	    break;
	}

	case '<': {
	    /* Token_type can be either:
	     * ASSIGNOP ("<-") -or-
	     * RELOP ("<", "<=")
	     */
	    auto next_char = static_cast<char>(Next());
	    if (next_char == '-') {
		// ASSIGNOP
		token_type = "ASSIGNOP";
		// Add the second char to the token contents
		token_contents += next_char;
		// Another char was consumed; increment the iterator
		Increment();
	    } else {
		// RELOP
		token_type = "RELOP";
		// Check if the token is '<' or '<='
		if (next_char == '=') {
		    // Add the second char to the token contents
		    token_contents += next_char;
		    // Another char was consumed; increment the iterator
		    Increment();
		}
	    }
	    break;
	}
	case '|': {
	    token_type = "OR";
	    break;
	}
	case '(': {
	    token_type = "PARENL";
	    break;
	}
	case ')': {
	    token_type = "PARENR";
	    break;
	}
	case ';': {
	    token_type = "SEMICOLON";
	    break;
	}
	default: {
	    // Chars that aren't any of the above will be treated as errors
	    token_type = "ERROR";
	    break;
	}
    }

    // Increment if the type wasn't a STRING; there could be a valid token
    // immediately after the ending ", which would be missed if the pointer
    // was incremented
    if (token_type != "STRING") {
	Increment();
    }    

    // Make a pair from the token_type & token_contents and return it
    TokenPairType token_pair(token_type, token_contents);

    return token_pair;
}

void Tokenizer::ReadComment() {
    // Increment the iterator until '\n' (end-of-line) has been encountered
    while (*source_code_position_ != '\n') {
	Increment();
    }
}

std::string Tokenizer::ExtractStringToken() {
    // Increment the iterator until a quotation mark is encountered
    // The do-while loop will guarantee that it is incremented at least once,
    // But will stop immediately afterwords if the string is empty

    // Save the starting index of the word
    auto word_start_index = source_code_position_;

    do {
	Increment();
    } while (*source_code_position_ != '\"');
    // source_code_position_ still points to the closing quotation mark, so
    // increment it to capture the entire quote
    Increment();
    auto word_end_index = source_code_position_;

    // Extract the String from the source code and return it
    return ExtractSubstring(word_start_index, word_end_index);
}

TokenPairType Tokenizer::NewErrorToken(std::string s) {
    // Create an ERROR token from the given string/char
    return TokenPairType("ERROR", s);
}

bool Tokenizer::IsKeyword(std::string s) {
    // Check if the string s is in the list of keywords; if not,
    // then std::find will return std::end(TokenConsts::KEYWORDS)
    auto pos = std::find(std::begin(TokenConsts::KEYWORDS),
			 std::end(TokenConsts::KEYWORDS),
			 s
	);
    return pos != std::end(TokenConsts::KEYWORDS);
}

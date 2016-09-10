#include "file_handler.hpp"
#include "tokenizer.hpp"

#include <iostream>

int main() {

    FileHandler fh;
    // Get the location of the source code file
    fh.GetFileLocation();
    // Extract the file's contents, which will be a std::string
    auto file_contents = fh.ExtractSourceCode();

    if (!file_contents.empty()) {
	// Construct a Tokenizer from the file's contents
	Tokenizer tokenizer(file_contents);
    
	// Tokenize the contents and return a std::vector<TokenPair>
	// which will consist of the tokens
	auto list_of_tokens = tokenizer.Tokenize();

	// Print the list of tokens
	for (auto &token : list_of_tokens) {
	    std::cout << token.FormatToPrint() << std::endl;
	}	
    }

    return 0;
}


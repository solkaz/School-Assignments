#include "file_handler.hpp"
#include "tokenizer.hpp"

#include <iostream>

int main(int argc, char *argv[]) {

    try {
	auto file_name = argv[1];
	if (file_name == nullptr) {
	    throw std::logic_error("Missing input file argument");
	} 
	FileHandler input_file(file_name);
	auto file_contents = input_file.ExtractSourceCode();

	if (file_contents.empty()) {
	    throw std::logic_error("Empty file supplied");
	}
	    
	Tokenizer tokenizer(file_contents);
	auto tokens = tokenizer.Tokenize();

	// Print the list of tokens
	for (auto &token : tokens) {
	    std::cout << token.FormatToPrint() << std::endl;
	}
    } catch(const std::logic_error &err) {
	std::cerr << err.what() << std::endl;
	return 1;
    } catch (const std::runtime_error &err) {
	std::cerr << err.what() << std::endl;
	return 1;
    }

    return 0;
}


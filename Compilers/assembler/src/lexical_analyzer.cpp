#include "file_handler.hpp"
#include "lexical_analyzer.hpp"
#include "tokenizer.hpp"

LexicalAnalyzer::LexicalAnalyzer(std::string s) {
    // Create a file handler object
    FileHandler source_file(s);

    auto file_contents = source_file.ExtractSourceCode();

    Tokenizer tokenizer(file_contents);

    tokens_ = tokenizer.Tokenize();
}


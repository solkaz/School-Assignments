#include "file_handler.hpp"
#include "token_constants.hpp"

FileHandler::FileHandler() {
    this->file_location_ = "";
}

void FileHandler::GetFileLocation() {
    std::cout << "Enter the location of the source code file: ";
    std::cin >> this->file_location_;
}

std::string FileHandler::ExtractSourceCode() {
    std::ifstream source_code_file(this->file_location_, std::fstream::in);

    std::string extracted_source_code ((std::istreambuf_iterator<char>(source_code_file)),
					 (std::istreambuf_iterator<char>()));
    std::cout << extracted_source_code << std::endl;
    std::cout << VAR << std::endl;
    return extracted_source_code;
}




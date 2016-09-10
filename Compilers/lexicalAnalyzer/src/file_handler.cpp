#include "file_handler.hpp"

#include <iostream>
#include <fstream>

FileHandler::FileHandler() {
    // Placeholder; is replaced with GetFileLocation
    file_location_ = "";
}

void FileHandler::GetFileLocation() {
    std::cout << "Enter the location of the source code file: ";
    std::cin >> file_location_;
}

std::string FileHandler::ExtractSourceCode() {
    std::ifstream source_code_file(file_location_, std::fstream::in);

    // Check that the file exists
    if (source_code_file) {
	// Get the full contents of the source code file and place it in a string
	std::string extracted_source_code (
	    (std::istreambuf_iterator<char>(source_code_file)),
	    (std::istreambuf_iterator<char>())
	    );
	// Return the source code's contents as a string
	return extracted_source_code;
    } else {
	std::cout << "File doesn't exist; exiting" << std::endl;
	return "";
    }
    
}




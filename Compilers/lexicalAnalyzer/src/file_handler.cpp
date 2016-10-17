#include "file_handler.hpp"

#include <stdexcept>

FileHandler::FileHandler(std::string s) {
    file_location_ = s;
    // Open the source code file to check if it is valid
    source_code_file_.open(file_location_, std::fstream::in);
    // If it isn't valid, then throw an exception to exit the program
    if (!source_code_file_.is_open()) {
	throw std::runtime_error("Unable to open source code file as input");
    }

    // Close access to the input file
    source_code_file_.close();
}



std::string FileHandler::ExtractSourceCode() {
    // Open the ifstream to the source code
    source_code_file_.open(file_location_, std::fstream::in);
    
    // Get the full contents of the source code file and place it in a string
    std::string extracted_source_code (
	(std::istreambuf_iterator<char>(source_code_file_)),
	(std::istreambuf_iterator<char>())
	);

    // Close access to the input file
    source_code_file_.close();
    
    // Return the source code's contents as a string
    return extracted_source_code;

}




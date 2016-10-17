#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <fstream>
#include <string>

class FileHandler {
public:
    // Do not use the default constructor
    FileHandler() = delete;
    FileHandler(char * cp) : FileHandler(std::string(cp)) {}
    FileHandler(std::string);

    
    std::string ExtractSourceCode();
private:
    // Location of the input file
    std::string file_location_;
    std::ifstream source_code_file_;
};

#endif // FILE_HANDLER_HPP_

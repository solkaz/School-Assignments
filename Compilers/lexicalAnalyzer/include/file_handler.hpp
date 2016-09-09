#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <string>

class FileHandler {
public:
    FileHandler();
    void GetFileLocation();
    std::string ExtractSourceCode();
private:
    // Location of the input file
    std::string file_location_;
};

#endif // FILE_HANDLER_HPP_

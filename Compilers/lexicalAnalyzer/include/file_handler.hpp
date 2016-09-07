#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <iostream>
#include <fstream>
#include <string>

class FileHandler {
public:
    FileHandler();
    void GetFileLocation();
    std::string ExtractSourceCode();
private:
    std::string file_location_;
};

#endif // FILE_HANDLER_HPP_

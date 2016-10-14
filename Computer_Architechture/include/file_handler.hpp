#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <string>

class FileHandler {
    std::string file_path_;
public:
    FileHandler();
    FileHandler(char *);
};

#endif // FILE_HANDLER_HPP_

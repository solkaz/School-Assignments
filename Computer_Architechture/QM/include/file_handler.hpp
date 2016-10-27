#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include "types.hpp"

class FileHandler {
    std::string file_path_;
public:
    FileHandler(): file_path_("") {}
    FileHandler(char *cp): file_path_(std::string(cp)) { }
    FileHandler(std::string s): file_path_(s) {}
    std::vector<BoolExpr> ReadInputFile();
};

#endif // FILE_HANDLER_HPP_

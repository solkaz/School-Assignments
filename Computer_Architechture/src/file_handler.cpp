#include "file_handler.hpp"

#include <fstream>
#include <string>
#include <vector>

FileHandler::FileHandler(char *cp) {
    try {
	file_path_ = std::string(cp);
    } catch () {
	
    }
}

std::vector<std::string> FileHandler::ReadInputFile() {
    std::ifstream input_file(file_path_, std::fstream::in);
}

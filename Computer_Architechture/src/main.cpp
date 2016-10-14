#include "file_handler.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    // Construct a wrapper around the input file stream
    // Defaults to DATA1.txt if the input file wasn't specified
    FileHandler input_file((argv[1] == nullptr ? "DATA1.txt" : argv[1]));
    
    return 0;
}

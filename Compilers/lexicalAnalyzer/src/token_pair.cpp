#include "token_pair.hpp"

// Return a formatted string suitable for printing
std::string TokenPair::FormatToPrint() {
    return "TOKEN:" + token_pair_.first + "\t" + token_pair_.second;
}

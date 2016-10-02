#include "token_pair.hpp"

// Return a formatted string suitable for printing
std::string TokenPair::FormatToPrint() {
    return "TOKEN:" + Type() + "\t" + Contents();
}

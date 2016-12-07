#include "utils.hpp"

#include <string>
#include <vector>
#include <iterator>
#include <sstream>

std::vector<std::string> Split(std::string s) {
    std::istringstream iss(s);
    return std::vector<std::string>(std::istream_iterator<std::string>{iss},
				    std::istream_iterator<std::string>{});
}

std::string Join(std::vector<std::string> vs) {
    std::string new_s = "";
    for (const auto &s : vs) {
	new_s += s;
    }
    return new_s;
}

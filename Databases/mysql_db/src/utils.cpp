#include "utils.hpp"

std::string GetPassword () {
    std::string password; char c;
    while (true) {
	c = _getch();
	if (c == 10 || c == 13) {
	    break;
	}
	std::cout << '*';
	password += c;
    }
    std::cin.sync();
    std::cout << std::endl;

    return password;
}

std::vector<std::string> SplitInput(std::string input) {
    std::istringstream iss(input);
    return std::vector<std::string>(istream_iterator<string>{iss},
				    istream_iterator<string>{});
}

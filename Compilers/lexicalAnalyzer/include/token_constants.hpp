#ifndef TOKEN_CONSTANTS_HPP_
#define TOKEN_CONSTANTS_HPP_

#include <string>

namespace TokenConsts {
    // Keywords that need to be tested against when reading a word in
    const std::string KEYWORDS [6] = {
	"else",
	"function",
	"if",
	"return",
	"var",
	"while"
    };
};

#endif // TOKEN_CONSTANTS_HPP_


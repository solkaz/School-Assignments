#ifndef TOKEN_CONSTANTS_HPP_
#define TOKEN_CONSTANTS_HPP_

#include <string>

namespace TokenConsts {

    enum Keyword {
	ELSE,
	FUNCTION,
	IF,
	VAR,
	WHILE
    };
    
    constexpr char AND = '&',
	COMMA = ',',
	CURLL = '{',
	CURLR = '}',
	NOT = '!',
	OR = '|',
	PARENL = '(',
	PARENR = ')',
	SEMICOLON = ';';

    constexpr char ADDOPS [2] = { '+', '-' };
    constexpr char MULOPS [2] = { '/', '*' };

    const std::string KEYWORDS [6] = {
	"else",
	"function",
	"if",
	"return",
	"var",
	"while"
    };
    
    const std::string ASSIGNOP("<-");

};

#endif // TOKEN_CONSTANTS_HPP_

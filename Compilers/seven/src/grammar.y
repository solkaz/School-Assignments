%{
#include <iostream>
#include <string>

int yylex();
void yyerror(const char* message) {
    std::cerr << "Error: " << message << std::endl;
}

%}

%token NUMBER
%token<std::string> STRING

%%

pgm:
    pgmpart pgm
    | pgmpart
    ;

pgmpart: vardecl
         | function
         ;

vardecl:
	VAR varlist ';'
	;

varlist:
	ID ',' varlist
	| ID
	;

%%

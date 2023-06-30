%skeleton "lalr1.cc"
%require "3.8.2"
%header

%define api.token.raw

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>
class driver;
}

%param { driver& drv }

%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full

%code {
#include "driver.hh"
}

%define api.token.prefix {TOK_}
%token
	MOVERIGHT ">"
	MOVELEFT "<"
	INC "+"
	DEC "-"
	PUT "."
	GET ","
;

%token <int> LOOP "["
%token <int> ENDLOOP "]"

%%

%start prg;
prg:
	 stmts
	 ;

stmts:
		%empty
	| stmt stmts			
	;

stmt:
		inst						
	| loop						
	;

inst:
		">"							{ ++drv.ptr; }
	| "<"							{ --drv.ptr; }
	| "+"							{ ++*drv.ptr; }
	| "-"							{ --*drv.ptr; }
	| "."							{ putchar(*drv.ptr); }
	| ","							{ *drv.ptr = getchar(); }
	;

loop:
		"[" stmts "]"		{  }
	;

%%

void yy::parser::error(const location_type &l, const std::string &m) {
	std::cerr << l << ": " << m << "\n";
}


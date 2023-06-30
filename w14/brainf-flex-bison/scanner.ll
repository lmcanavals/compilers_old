%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include "driver.hh"
#include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

blank [ \t\r\n]

%{
#define YY_USER_ACTION loc.columns(yyleng);
%}

%%
%{
	yy::location &loc = drv.location;
	loc.step();
%}

{blank}+	loc.step();
">"				return yy::parser::make_MOVERIGHT(loc);
"<"				return yy::parser::make_MOVELEFT(loc);
"+"				return yy::parser::make_INC(loc);
"-"				return yy::parser::make_DEC(loc);
"."				return yy::parser::make_PUT(loc);
","				return yy::parser::make_GET(loc);
"["				return yy::parser::make_LOOP(1, loc);
"]"				return yy::parser::make_ENDLOOP(2, loc);
.					/**/
<<EOF>>		return yy::parser::make_YYEOF(loc);

%%

void driver::scan_begin() {
	yy_flex_debug = trace_scanning;
	if (file.empty() || file == "-") {
		yyin = stdin;
	} else if (!(yyin = fopen(file.c_str(), "r"))) {
		std::cerr << "Cannot open file " << file << ": " << strerror(errno) << "\n";
		exit(EXIT_FAILURE);
	}
}

void driver::scan_end() {
	fclose(yyin);
}

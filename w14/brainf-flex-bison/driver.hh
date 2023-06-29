#ifndef DRIVER_HH
#define DRIVER_HH

#include "parser.hh"
#include <map>
#include <string>

#define YY_DECL yy::parser::symbol_type yylex(driver &drv)

YY_DECL;

class driver {
public:
  std::string file;
  bool trace_parsing;
  bool trace_scanning;
  yy::location location;

	unsigned char *baseptr;
	unsigned char *ptr;

public:
  driver();
	~driver();
  int parse(const std::string &f);
  void scan_begin();
  void scan_end();
};

#endif

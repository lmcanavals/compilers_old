#include "driver.hh"

driver::driver() : trace_parsing(false), trace_scanning(false) {
	baseptr = new unsigned char[30000];
	ptr = baseptr;
}

driver::~driver() {
	delete[] baseptr;
}

int driver::parse(const std::string &f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  yy::parser parse(*this);
  parse.set_debug_level(trace_parsing);
  int res = parse();
  scan_end();
  return res;
}

#include <iostream>
#include <map>
#include <stack>
#include <vector>
// test
#define MAX 30000

using namespace std;

int main() {
  unsigned char *c = new unsigned char[MAX];
  unsigned char *ptr = c;
  vector<char> program;
  stack<int> loopbegins;
  map<int, int> loopmatch;
  map<int, int> loophctam;
  char chr;

  while ((chr = getchar()) != EOF) {
    switch (chr) {
    case '>':
    case '<':
    case '+':
    case '-':
    case '.':
    case ',':
      break;
    case '[':
      loopbegins.push(program.size());
      break;
    case ']': {
      auto pos = loopbegins.top();
      loopbegins.pop();
      loopmatch[pos] = program.size();
      loophctam[program.size()] = pos;
      break;
    }
    default:
      continue;
    }
    program.push_back(chr);
  }

  for (auto i = 0; i < program.size(); ++i) {
    switch (program[i]) {
    case '>':
      ptr++;
      break;
    case '<':
      ptr--;
      break;
    case '+':
      *ptr += 1;
      break;
    case '-':
      *ptr -= 1;
      break;
    case '.':
      cout << *ptr;
      break;
    case ',':
      cin >> *ptr;
      break;
    case '[':
      if (*ptr == 0)
        i = loopmatch[i];
      break;
    case ']':
      i = loophctam[i] - 1;
      break;
    }
  }
  cout << endl;
  delete[] c;
  return 0;
}

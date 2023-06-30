#include <iostream>
#include <map>
#include <stack>
#include <vector>

#define MAX 30000

using namespace std;

class Program {
  unsigned char *mem = new unsigned char[MAX];
  unsigned char *head = mem;
  vector<char> instructions;
  map<int, int> loopmatch;
  map<int, int> loophctam;
  unsigned int pos;

public:
  Program(istream &is) {
    stack<int> loopbegins;
    char chr;
    while (is.get(chr)) {
      switch (chr) {
      case '>':
      case '<':
      case '+':
      case '-':
      case '.':
      case ',':
        break;
      case '[':
        loopbegins.push(instructions.size());
        break;
      case ']': {
        auto pos = loopbegins.top();
        loopbegins.pop();
        loopmatch[pos] = instructions.size();
        loophctam[instructions.size()] = pos;
        break;
      }
      default:
        continue;
      }
      instructions.push_back(chr);
    }
  }
  unsigned int run(int pos) {
    for (auto i = pos; i < instructions.size(); ++i) {
      switch (instructions[i]) {
      case '>':
        head++;
        break;
      case '<':
        head--;
        break;
      case '+':
        *head += 1;
        break;
      case '-':
        *head -= 1;
        break;
      case '.':
        putchar(*head);
        break;
      case ',':
        *head = getchar();
        break;
      case '[':
        // if (*ptr == 0)
        if (*head == 0)
          i = loopmatch[i];
        break;
      case ']':
        i = loophctam[i] - 1;
        break;
      }
    }
		return pos;
  }
};

int main() {
	Program *program = new Program(cin);

  cout << endl;
	delete program;
  return 0;
}

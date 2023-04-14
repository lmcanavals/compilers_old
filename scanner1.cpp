#include <iostream>

#define START 0

using namespace std;

int main() {
    
    char c;
    int state = 0;
    while (cin.get(c)) {
        switch (state) {
        case START:
            switch (c) {
            case '<': state = 1; continue;
            case '=': state = 5; continue;
            case '>': state = 6; continue;
            case ' ': case '\t': case '\n': continue;
            default: cout << "UNKNOWN TOKEN\n"; continue;
            }
            break;
        case 1:
            switch (c) {
            case '=': state = 2; continue;
            case '>': state = 3; continue;
            default: state = 4; continue;
            }
            break;
        case 2: cout << "relop LE\n"; state = 0; continue;
        case 3: cout << "relop NE\n"; state = 0; continue;
        case 4: cout << "relop LT\n"; state = 0; cin.putback(c); continue;
        case 5: cout << "relop EQ\n"; state = 0; continue;
        case 6:
            switch (c) {
            case '=': state = 7; continue;
            default: state = 8; continue;
            }
        case 7: cout << "relop GE\n"; state = 0; continue;
        case 8:  cout << "relop GT\n"; state = 0; cin.putback(c); continue;
        }
    }

    return 0;
}

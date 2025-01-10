#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') continue;
        cout << ch << " " << hex << (int)ch << " " << oct << (int)ch << endl;
    }
    return 0;
}
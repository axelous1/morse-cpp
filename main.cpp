#include "Morse.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void playMorse(const char* code) {
    for (int i = 0; code[i]; i++) {
        if (code[i] == '.') {
            cout << '\a' << flush;
            usleep(150000);
        } else if (code[i] == '-') {
            cout << '\a' << flush;
            usleep(450000);
        } else {
            usleep(150000);
        }
    }
}

int main() {
    Morse m;
    char text[256];

    cin.getline(text, 256);
    for (int i = 0; text[i]; i++) {
        m << text[i];
    }
    cout << m << "\n";

    char c;
    m >> c;
    cout << c << "\n";

    playMorse(m.data);

    return 0;
}

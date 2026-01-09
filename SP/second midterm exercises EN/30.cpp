//
// Created by cactus on 1/9/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    char text[500];
    bool word = false;
    while (cin.getline(text, 500)) {
        for (int i = 0; i < strlen(text); i++) {
            if (isalpha(text[i])) {
                cout << text[i];
                word = true;
            }
            else if (text[i]==' ' && word) {
                cout<<'\n';
                word=false;
            }
        }
        if (word) {
            cout << '\n';
            word = false;
        }
    }
    return 0;
}

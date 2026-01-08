//
// Created by cactus on 08/01/2026.
//
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;

void transformText(char *str) {
    if (!(*str)) {
        return;
    }
    if (isalpha(*str)) {
        *str = tolower(*str);
        *str = 'a' + ((*str - 'a' + 3) % 26);
    }
    transformText(str + 1);
}

int main() {
    char text[100];
    while (cin.getline(text, 100)) {
        transformText(text);
        cout << text << '\n';
    }
    return 0;
}

//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;

void transform(char *text, int shift) {
    if (*text == '\0') {
        return;
    }
    if (isalpha(*text)) {
        char base;
        if (islower(*text)) {
            base = 'a';
        } else if (isupper(*text)) {
            base = 'A';
        }
        *text = base + (*text - base + shift) % 26;
    }
    transform(text + 1, shift);
}

int main() {
    int n;
    int x;
    cin >> n >> x;
    cin.get();
    for (int i = 0; i < n; i++) {
        char text[100];
        cin.getline(text, 100);
        transform(text, x);
        cout << text << '\n';
    }
    return 0;
}

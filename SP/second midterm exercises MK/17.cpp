//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    char line[100];
    int pairCounter = 0;

    while (cin.getline(line, 100)) {
        if (*line == '#') {
            break;
        }
        char vowels[6] = "aeiou";
        for (int i = 0; i < strlen(line); i++) {
            line[i] = tolower(line[i]);
            line[i+1]=tolower(line[i+1]);
            for (int j = 0; j < strlen(vowels); j++) {
                if (line[i] == vowels[j]) {
                    for (int k = 0; k < strlen(vowels); k++) {
                        if (line[i + 1] == vowels[k]) {
                            cout << line[i] << line[i + 1] << '\n';
                            pairCounter++;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    cout << pairCounter << '\n';

    return 0;
}

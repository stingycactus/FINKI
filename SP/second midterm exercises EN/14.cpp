//
// Created by cactus on 08/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    char word[21];
    char maxWord[21];
    int maxLetters = 0;
    while (cin >> word) {
        if (strlen(word) > 4) {
            int distinctCount = 0;
            bool letters[26] = {};
            for (int i = 0; i < strlen(word); i++) {
                if (letters[tolower(word[i]) - 'a'] == false) {
                    distinctCount++;
                }
                letters[tolower(word[i]) - 'a'] = true;
            }
            if (distinctCount >= maxLetters) {
                maxLetters = distinctCount;
                strcpy(maxWord, word);
            }
        }
    }
    cout << maxWord;
    return 0;
}

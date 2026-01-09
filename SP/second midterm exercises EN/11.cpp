//
// Created by cactus on 08/01/2026.
//
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;
bool palindromeCheck(char *word) {
    int size = strlen(word);
    char vowels[5] = {'a','e','i','o','u'};
    bool palindrome = true;
    for (int i = 0; i<size/2; i++) {
        for (int j = 0; j<5; j++) {
            if (tolower(word[i])==vowels[j]) {
                if (tolower(word[i])!=tolower(word[size-1-i])) {
                    palindrome = false;
                    break;
                }
            }
        }
        if (!palindrome) {
            break;
        }
    }
    return palindrome;
}
int main() {
    char word[30];
    while (cin.getline(word,30)) {
        if (palindromeCheck(word)) {
            cout<<word<<'\n';
        }
    }
}
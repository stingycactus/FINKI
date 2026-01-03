//
// Created by cactus on 03/01/2026.
//
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
void transform (char *text) {
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i<strlen(text); i++) {
        text[i] = tolower(text[i]);
        for (int j = 0; j<5; j++) {
            if (text[i] == vowels[j]) {
                text[i] = toupper(text[i]);
            }
        }
    }
}
int main() {
    char str[100];
    cin.getline(str,100);
    transform (str);
    cout<<str;
    return 0;
}
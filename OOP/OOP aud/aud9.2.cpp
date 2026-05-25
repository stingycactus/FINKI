//
// Created by cactus on 19/05/2026.
//
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    ifstream file("Example.txt");
    if (!file.is_open()) {
        cout<<"Cannot open file"<<'\n';
        return -1;
    }
    char c;
    int lines = 0;
    int vowels = 0;
    int totalVowels = 0;
    while (file.get(c)) {
        if (isVowel(c)) {
            vowels++;
            totalVowels++;
        }
        if (c=='\n') {
            if (vowels>10) {
                lines++;
            }
            vowels=0;
        }
    }
    if (vowels > 10) lines++;
    cout<<"A total of "<<lines<<" rows have more than 10 vowels."<<'\n';
    cout<<"The file has a total of "<<totalVowels<<" vowels."<<'\n';
    file.close();
    return 0;
}
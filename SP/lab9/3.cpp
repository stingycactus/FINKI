//
// Created by cactus on 03/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
bool isPalindrome (char *text, int start, int end) {
    int difference = end-start+1;
    bool palindrome = true;
    for (int i = 0; i<difference/2; i++) {
        if (tolower(text[start + i]) != tolower(text[end - i])) {
            palindrome = false;
        }
    }
    return palindrome;
}
int main () {
    int n;
    cin>>n;
    cin.ignore();
    for (int i = 0; i<n; i++) {
        char text[100];
        cin.getline(text,100);
        int textSize = strlen(text);
        int palindromeCount = 0;
        int wordStart = 0;
        int wordEnd = -1;
        for (int j = 0; j<textSize; j++) {
            if (text[j]==' ') {
                wordEnd = j-1;
                palindromeCount+=isPalindrome(text,wordStart,wordEnd);
                wordStart = j+1;
            }
        }
        wordEnd = textSize - 1;
        palindromeCount += isPalindrome(text, wordStart, wordEnd);
        cout<<text<<": "<<palindromeCount<<'\n';
    }
    return 0;
}
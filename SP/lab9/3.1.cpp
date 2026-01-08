//
// Created by cactus on 06/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
bool isPalindrome(char *word, int size) {
    bool palindrome = true;
    for (int i = 0; i < size/2; i++) {
        if (word[i] != word[size-1-i]) {
            palindrome = false;
            break;
        }
    }
    return palindrome;
}
int main() {
    char msg[100];
    int palindromeCount = 0;
    while (cin>>msg) {
        int n = strlen(msg);
        palindromeCount+=isPalindrome(msg, n);
    }
    cout<<palindromeCount;
    return 0;
}

//
// Created by cactus on 11/01/2026.
//
#include <iostream>
#include <cstring>
using namespace std;

bool isPalindrome(char *text, int start, int end) {
    while (start < end) {
        if (text[start] != text[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    int minSize = 100;
    char maxText[100];
    bool found = false;
    for (int i = 0; i < n; i++) {
        char text[100];
        cin.getline(text, 100);
        if (!isPalindrome(text, 0, strlen(text) - 1)) {
            if (strlen(text) < minSize) {
                minSize = strlen(text);
                strcpy(maxText, text);
                found = true;
            }
            else if (strlen(text)==minSize) {
                if (strcmp(text, maxText)>0) {
                    strcpy(maxText, text);
                }
            }
        }
    }
    if (found) {
        cout << maxText;
    }
    else {
        cout << "NEMA";
    }
    return 0;
}

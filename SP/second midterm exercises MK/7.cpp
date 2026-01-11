//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;
int main() {
    char line[100];
    char maxLine[100];
    int maxSize = 0;
    while (cin.getline(line,100)) {
        if (*line=='0') {
            break;
        }
        int digits = 0;
        for (int i = 0; i<strlen(line); i++) {
            if (isdigit(line[i])) {
                digits++;
            }
        }
        if (strlen(line)>=maxSize && digits>=2) {
            maxSize = strlen(line);
            strcpy(maxLine,line);
        }
    }
    int start = 0;
    int end = strlen(maxLine)-1;
    for (int i = 0; i<strlen(maxLine); i++) {
        if (isdigit(maxLine[i])) {
            start=i;
            break;
        }
    }
    for (int i = strlen(maxLine)-1; i>start; i--) {
        if (isdigit(maxLine[i])) {
            end=i;
            break;
        }
    }
    for (int i = start; i<=end; i++) {
        cout << maxLine[i];
    }
    return 0;
}
//
// Created by cactus on 1/9/2026.
//
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char str[100];
    cin.getline(str, 100);
    int start = -1;
    int end = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i]) && (start == -1)) {
            start = i;
        } else if (isdigit(str[i]) && (start != -1)) {
            end = i;
            break;
        }
    }
    if (start!=-1) {
        for (int i = start; i <= end; i++) {
            cout << str[i];
        }
    }
    else {
        cout << "No digits";
    }

    return 0;
}

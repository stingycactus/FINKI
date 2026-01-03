//
// Created by cactus on 03/01/2026.
//
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;
int main() {
    char str[100];
    cin.getline(str,100);
    char c;
    cin>>c;
    int start = 0;
    int end = 0;
    for (int i = 0; i<strlen(str); i++) {
        if (tolower(str[i])==tolower(c)) {
            start = i;
            break;
        }
    }
    for (int j = strlen(str)-1; j>=0; j--) {
        if (tolower(str[j])==tolower(c)) {
            end = j;
            break;
        }
    }
    for (int i = start; i<=end; i++) {
        cout<<str[i];
    }
    return 0;
}
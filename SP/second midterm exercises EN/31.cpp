//
// Created by cactus on 1/9/2026.
//
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;
int main() {
    char word[21];
    int count = 0;
    while (cin>>word) {
        bool isHex = true;
        for (int i = 0; i < strlen(word); i++) {
            char c = tolower(word[i]);
            if (!((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'))) {
                isHex = false;
                break;
            }
        }
        if (isHex) {
            count++;
            for (int i = 0; i<strlen(word);i++) {
                cout<<static_cast<char>(toupper(word[i]));
            }
            cout<<'\n';
        }
    }
    cout<<"Total: "<<count;
    return 0;
}
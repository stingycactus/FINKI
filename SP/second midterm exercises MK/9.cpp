//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
int main() {
    char z1;
    char z2;
    cin>>z1>>z2;
    cin.get();
    char line[100];
    while (cin.getline(line,100)) {
        if (*line=='#') {
            break;
        }
        int start = -1;
        int end = -1;
        for (int i = 0; i < strlen(line); i++) {
            if (line[i]==z1) {
                start = i;
            }
            else if (line[i]==z2) {
                end = i;
            }
        }
        for (int i = start+1; i<end; i++) {
            cout << line[i];
        }
        cout<<'\n';
    }
    return 0;
}
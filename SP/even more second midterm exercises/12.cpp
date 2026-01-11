//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
int main () {
    int n;
    cin>>n;
    char arr[100][100];
    for (int i = 0; i < n; i++) {
        for (int j=0; j<n; j++) {
            cin>>arr[i][j];
        }
    }
    cin.ignore();
    char word[20];
    bool found = false;
    int firstXPos = -1;
    int firstYPos = -1;
    int lastXPos = -1;
    int lastYPos = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j]==word[0]) {
                for (int k=1; k<n; k++) {
                    for (int l=1; l<strlen(word); l++) {
                        if (arr[i][k]==word[l]) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        firstXPos = ;
                    }
                }
            }
        }
    }
    return 0;
}
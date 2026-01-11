//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
int main() {
    char text[100];
    char maxText[100];
    int maxSvrznici = 0;
    while (cin.getline(text,100)) {
        int letterCounter = 0;
        int svrznici = 0;
        for (int i = 0; i<strlen(text); i++) {
            if (isalpha(text[i])) {
                letterCounter++;
            }
            else {
                if (letterCounter<=3 && letterCounter>0) {
                    svrznici++;
                }
                letterCounter = 0;
            }
        }
        if (svrznici>maxSvrznici) {
            maxSvrznici = svrznici;
            strcpy(maxText,text);
        }
    }
    cout<<maxSvrznici<<": "<<maxText<<'\n';
    return 0;
}
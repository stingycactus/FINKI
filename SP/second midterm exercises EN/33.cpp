//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    char str[100];
    float maxRatio = 0;
    char maxLine[100];
    while (cin.getline(str, 100)) {
        int digits = 0;
        int letters = 0;
        float ratio = 0;
        for (int i = 0; i < strlen(str); i++) {
            if (isdigit(str[i])) {
                digits++;
            }
            else if (isalpha(str[i])) {
                letters++;
            }
        }
        ratio = static_cast<float>(digits) / letters;
        if (ratio>=maxRatio && letters!=0) {
            maxRatio = ratio;
            strcpy(maxLine,str);
        }
    }
    cout<<maxLine;
    return 0;
}

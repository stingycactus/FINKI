//
// Created by cactus on 08/01/2026.
//
#include <iostream>
#include <cctype>
#include <cstring>
#include <iomanip>
using namespace std;

int main() {
    char text[100];
    float maxRatio = 0;
    int maxLine = 0;
    int line = 0;
    while (cin.getline(text,100)) {
        int upper = 0;
        int lower = 0;
        float ratio = 0;
        for (int i = 0; i < strlen(text); i++) {
            if (isalpha(text[i])) {
                if (islower(text[i])) {
                    lower++;
                }
                else {
                    upper++;
                }
            }
        }
        if (lower>0) {
            ratio = float(upper)/lower;
        }
        cout<<fixed<<setprecision(2)<<ratio<<' '<<text<<endl;
        if (ratio>maxRatio) {
            maxRatio = ratio;
            maxLine = line;
        }
        line++;
    }
    cout<<maxLine<<endl;

    return 0;
}
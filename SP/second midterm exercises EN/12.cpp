//
// Created by cactus on 08/01/2026.
//
#include <iostream>
#include <cstring>
using namespace std;

int sumNumbers(char *text) {
    int sum = 0;
    int current = 0;
    bool number = true;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= '0' && text[i] <= '9') {
            current = current * 10 + text[i] - '0';
        }
        else {
            number = false;
            sum += current;
            current=0;
        }
    }
    sum+=current;
    return sum;
}

void transformString(char *text, int sum) {
    int key = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            text[key] = text[i];
            key++;
        }
    }
    text[key] = '\0';

}

int main() {
    char text[80];
    while (cin.getline(text, 80)) {
        int sum = sumNumbers(text);
        transformString(text, sum);
        cout<<text<<sum<<'\n';
    }
    return 0;
}

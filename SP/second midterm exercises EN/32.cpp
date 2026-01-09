//
// Created by cactus on 1/9/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    char text[1000];
    int k;
    cin >> k;
    cin.get();
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    cin.getline(text, 1000);
    for (int i = 0; i < strlen(text); i++) {
        cout << text[i];
        for (int j = 0; j < 5; j++) {
            if (tolower(text[i]) == vowels[j]) {
                for (int l = 1; l < k; l++) {
                    cout << text[i];
                }
            }
        }
    }

    return 0;
}

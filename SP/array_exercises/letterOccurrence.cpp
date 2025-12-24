//
// Created by cactus on 04/12/2025.
//
#include <iostream>
using namespace std;

int main() {
    int arr[26] = {};
    char character;
    while (cin.get(character)) {
        if (character == '.') {
            break;
        }
        if (isalpha(character)) {
            character = toupper(character);
            arr[character - 'A']++;
        }
    }
    for (int i:arr) {
        cout<<i<<" ";
    }
    return 0;
}

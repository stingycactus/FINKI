//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    char symbol;
    int sum = 0;
    int current = 0;
    while (cin >> noskipws >> symbol) {
        if (symbol == '!') {
            sum+=current;
            break;
        }
        if (symbol >= '0' && symbol <= '9') {
            current = current * 10 + (symbol - '0');
        } else {
            sum += current;
            current = 0;
        }
    }
    cout << sum;
    return 0;
}

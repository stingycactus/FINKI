//
// Created by cactus on 13/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    char x;
    int sum = 0;
    while (cin >> x) {
        if (x == '.') {
            break;
        } else {
            if (x >= '0' && x <= '9') {
                sum += x - '0';
            } else if (x >= 'a' && x <= 'z') {
                sum += x - 'a' + 10;
            } else if (x >= 'A' && x <= 'Z') {
                sum += x - 'A' + 10;
            }
        }
    }
    int lastDigit = sum % 10;
    int secondToLastDigit = sum / 10 % 10;
    if ((sum % 16) == 0 && (secondToLastDigit == 1) && (lastDigit == 6)) {
        cout << "Poln pogodok";
    } else if ((sum % 16) == 0) {
        cout << "Pogodok";
    }
    else {
        cout<<sum;
    }
    return 0;
}

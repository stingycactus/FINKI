//
// Created by cactus on 12/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    if (x <= 0 || y <= 0) {
        cout << "Invalid input";
    } else {
        if (y>x) {
            int tmp = y;
            y = x;
            x=tmp;
        }
        int temp = x;
        int counter = 0;
        int evenEquivalent = 0;
        int multiplier = 1;
        while (temp > 0) {
            counter++;
            if (counter % 2 == 0) {
                evenEquivalent += temp % 10 * multiplier;
                multiplier*=10;
            }
            temp /= 10;
        }
        if (evenEquivalent == y) {
            cout << "PAREN";
        } else {
            cout << "NE";
        }
    }
    return 0;
}

//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    while (cin >> a && cin >> b && cin >> c) {
        int temp;
        if (a > b) {
            temp = a;
            a = b;
            b = temp;
        }
        if (a > c) {
            temp = a;
            a = c;
            c = temp;
        }
        if (b > c) {
            temp = b;
            b = c;
            c = temp;
        }
        int diff1 = c - b;
        int diff2 = b - a;
        if (diff1 < diff2) {
            cout << b << " " << c;
        } else if (diff1 > diff2) {
            cout << a << " " << b;
        } else {
            cout << a << " " << b << " " << c;
        }
        cout << '\n';
    }
    return 0;
}

//
// Created by cactus on 03/11/2025.
//
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int counter = 0;
    for (int i = a + 1; i <= b; i++) {
        if (i % 2 == 0 && i % 7 == 0 || i % 2 == 1 && i % 3 != 0) {
            cout << i << '\n';
            counter++;
        }
    }
    if (counter) {
        double percent = counter * 100.0 / (b - a);
        cout << fixed << setprecision(2) << percent;
    } else {
        cout << 0;
    }
}

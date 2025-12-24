//
// Created by cactus on 10/11/2025.
//
#include <iostream>
using namespace std;

int countOccurence(int number, int digit) {
    int counter = 0;
    while (number > 0) {
        int digitOfNum = number % 10;
        if (digitOfNum == digit) {
            counter++;
        }
        number /= 10;
    }
    return counter;
}

int main() {
    int m, n, p;
    cin >> m >> n >> p;

    for (int i = m + 1; i < m + 11; i++) {
        int digitCount = countOccurence(i, n);
        if (digitCount == p) {
            cout<<i<<endl;
        }
    }
    return 0;
}

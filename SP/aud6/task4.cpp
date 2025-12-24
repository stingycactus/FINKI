//
// Created by cactus on 10/11/2025.
//
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int x) {
    if (x == 2) {
        return true;
    }
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int sumOfDigits(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main() {
    for (int i = 3; i < 10000; i++) {
        if (isPrime(i) && isPrime(sumOfDigits(i))) {
            cout << i << '\n';
        }
    }
    return 0;
}

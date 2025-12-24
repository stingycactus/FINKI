//
// Created by cactus on 10/11/2025.
//
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int x) {
    if (x==2) {
        return true;
    }
    for (int i = 2; i<=sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    for (int i = 2; i<10000; i++) {
        if (isPrime(i) && isPrime(i+2)) {
            cout<<i<<" "<<i+2<<'\n';
        }
    }
    return 0;
}
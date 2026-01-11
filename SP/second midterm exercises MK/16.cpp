//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int maxDigit(int number) {
    if (!number) {
        return 0;
    }
    int currentDigit = number%10;
    int rest = maxDigit(number/10);
    if (currentDigit>rest) {
        return currentDigit;
    }
    else {
        return rest;
    }
}
int main() {
    int n;
    while (cin>>n) {
        int maximumDigit = 0;
        cout<<maxDigit(n)<<'\n';
    }
    return 0;
}
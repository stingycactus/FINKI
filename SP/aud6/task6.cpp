//
// Created by cactus on 10/11/2025.
//
#include <iostream>
using namespace std;

int factorial(int num) {
    int product = 1;
    for (int i = 1; i <= num; i++) {
        product *= i;
    }
    return product;
}

int sum(int number) {
    int sum = 0;
    for (int i = 1; i <= number; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    cout << factorial(sum(n));
    return 0;
}

//
// Created by cactus on 12/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int maxSum = 0;
    int maxNum = 0;
    for (int i = n; i > 0; i--) {
        int sumDivisors = 0;
        for (int j = 1; j < n; j++) {
            if ((i % j) == 0) {
                sumDivisors += j;
            }
        }
        if (sumDivisors > maxSum) {
            maxSum = sumDivisors;
            maxNum = i;
        }
    }
    cout<<maxNum;
    return 0;
}

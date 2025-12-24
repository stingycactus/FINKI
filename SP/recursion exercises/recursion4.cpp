//
// Created by cactus on 16/12/2025.
//
/*Implement a recursive function int sumDigits(int n) that calculates the sum of all digits in a given positive integer n.
Example:
Input: n = 3847
Output: 22 (3 + 8 + 4 + 7 = 22)
Read one integer from standard input and print the sum of its digits.*/
#include <iostream>
using namespace std;
int sumDigits(int n) {
    if (!n) {
        return 0;
    }
    else {
        return n%10 + sumDigits(n/10);
    }
}
int main() {
    cout<<sumDigits(3847);
    return 0;
}

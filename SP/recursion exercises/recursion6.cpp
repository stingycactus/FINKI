//
// Created by cactus on 16/12/2025.
//
#include <iostream>
using namespace std;
/*
LAB 6
Implement a recursive function int countOnes(int number, int k) that counts how many digits in the number number are greater than the given k.
Example:
Input: number = 771256, k = 3
Output: 4 (the digits 7, 7, 5, 6 are greater than 3)
Read two integers from standard input (number and k) and print the count.
*/
int countOnes(int number, int k) {
    if (!number) {
        return 0;
    }
    int greaterThanK = number%10>k;
    return greaterThanK+countOnes(number/10,k);
}
int main() {
    cout<<countOnes(771256, 3);
    return 0;
}
//
// Created by cactus on 16/12/2025.
//
#include <iostream>
using namespace std;
/*
LAB 5
Implement a recursive function void printDigitsReverse(int n) that prints the digits of a given positive integer n in reverse order (from the last digit to the first), with each digit on a new line.
Example:
Input: n = 5291
Output:
1
9
2
5
*/
void printDigitsReverse(int n) {
    if (!n) {
        return;
    }
    cout<<n%10<<'\n';
    printDigitsReverse(n/10);
}
int main() {
    printDigitsReverse(5291);
    return 0;
}
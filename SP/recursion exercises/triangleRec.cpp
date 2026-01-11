//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
void printTriangle2 (int number) {
    if (!number) {
        return;
    }
    printTriangle2(number-1);
    cout<<number;
}
void printTriangle(int number) {
    if (!number) {
        return;
    }
    printTriangle(number - 1);
    printTriangle2(number);
    cout<<'\n';
}
int main() {
    printTriangle(4);
    return 0;
}
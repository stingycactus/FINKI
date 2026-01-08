//
// Created by cactus on 07/01/2026.
//
#include <iostream>
using namespace std;
void triangle1(int number) {
    if (!number) {
        return;
    }
    triangle1(number-1);
    cout<<number;
}
void triangle2(int number) {
    if (!number) {
        return;
    }
    triangle2(number-1);
    triangle1(number);
    cout<<'\n';
}

int main() {
    int n;
    cin>>n;
    triangle2(n);
    return 0;
}
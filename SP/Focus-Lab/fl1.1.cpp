//
// Created by cactus on 6/8/2026.
//
#include <iostream>
using namespace std;

int printFromX(int number) {
    if (number==0) {
        return number;
    }
    cout<<number<<'\n';
    return printFromX(number-1);
}

int main() {
    int x;
    cin>>x;
    printFromX(x);
    return 0;
}
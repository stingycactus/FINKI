//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;
int main() {
    int n, max;
    int counter=0;
    while (cin >> n) {
        if (counter==0) {
            max=n;
        }
        counter++;
        if (n>max) {
            max=n;
        }
    }
    cout<<max;
}

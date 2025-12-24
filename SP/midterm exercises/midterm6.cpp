//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    bool valid = false;
    if (n >= 10) {
        for (int i = n-1; i > 0; i--) {
            int opposite = 0;
            int temp = i;
            int digits = 0;
            while (temp > 0) {
                int digit = temp % 10;
                opposite = opposite * 10 + digit;
                digits++;
                temp /= 10;
            }
            if (opposite%digits==0) {
                cout<<i;
                break;
            }
        }
    }
    else {
        cout<<"The number is invalid";
    }
    return 0;
}

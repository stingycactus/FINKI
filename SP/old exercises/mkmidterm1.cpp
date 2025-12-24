//
// Created by cactus on 12/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    bool evenDigits = false;
    for (int i = m; i <= n; i++) {
        int temp = i;
        while (temp > 0) {
            int digit = temp%10;
            if (digit % 2 != 0) {
                evenDigits = false;
                break;
            } else if (digit % 2 == 0) {
                evenDigits = true;
            }
            temp/=10;
        }
        if (evenDigits) {
            cout<<i;
            break;
        }
    }
    if (!evenDigits) {
        cout<<"NE";
    }
    return 0;
}

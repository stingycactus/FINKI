//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int mostSignificantDigit (int number) {
    if (number<10) {
        return number;
    }
    return mostSignificantDigit(number/10);
}
int main() {
    int n;
    while (cin>>n) {
        if (n==0) {
            break;
        }
        int maxFirstDigit = 0;
        int maxNumber = 0;
        for (int i = 0; i<n; i++) {
            int x;
            cin>>x;
            int firstDigit=mostSignificantDigit(x);
            if (firstDigit>maxFirstDigit) {
                maxFirstDigit=firstDigit;
                maxNumber=x;
            }
        }
        cout<<maxNumber<<'\n';
    }
    return 0;
}
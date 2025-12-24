//
// Created by cactus on 10/11/2025.
//
#include <iostream>
using namespace std;
int main() {
    int number;
    int sumOfMaxDigits = 0;
    int maxDigit = 0;
    while (cin>>number) {
        int temp = number;
        while (temp>0) {
            int digit = temp%10;
            if (digit>=maxDigit) {
                maxDigit=digit;
            }
            temp/=10;
        }
        sumOfMaxDigits+=maxDigit;
        cout<<maxDigit<<endl;
    }
    cout<<static_cast<float>(sumOfMaxDigits)/maxDigit<<endl;
    return 0;
}
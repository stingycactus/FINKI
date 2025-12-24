//
// Created by cactus on 10/11/2025.
//
#include <iostream>
using namespace std;
int getFirstTwoDigits(int number) {
    if (number<10) {
        return number%10;
    }
    else if (number>10) {
        int lastDigit, secondLastDigit;
        while (number>10) {
            lastDigit=number%10;
            secondLastDigit=number/10%10;
            number/=10;
        }
        return secondLastDigit*10+lastDigit;
    }
}
int main() {
    cout<<getFirstTwoDigits(1541243);
    return 0;
}
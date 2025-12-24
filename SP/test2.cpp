//
// Created by cactus on 13/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int counter = 0;
    for (int i = a; i < b; i++) {
        int temp = i;
        int ld = temp % 10;
        temp /= 10;
        int prodOfMiddle = 1;
        while (temp > 9) {
            prodOfMiddle *= temp % 10;
            temp /= 10;
        }
        int firstDigit = temp;
        int firstAndLast = firstDigit * 10 + ld;
        if (prodOfMiddle % firstAndLast == 0 && prodOfMiddle !=0) {
            counter++;
            cout<<i<<" -> "<<"("<<prodOfMiddle<<" == "<<firstAndLast<<" * "<<prodOfMiddle/firstAndLast<<")"<<'\n';
        }
    }
    cout<<counter;
    return 0;
}

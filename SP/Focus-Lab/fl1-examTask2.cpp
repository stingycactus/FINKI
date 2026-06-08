//
// Created by cactus on 6/8/2026.
//
//
// Created by cactus on 6/8/2026.
//
#include <iostream>
using namespace std;

bool isValidNumber(int number) {
    int temp = number;
    int evenSum=0;
    int oddSum=0;
    while (temp>0) {
        if (temp%10%2) {
            oddSum+=temp%10;
        }
        else {
            evenSum+=temp%10;
        }
        temp/=10;
    }
    return evenSum==oddSum;
}

int main() {
    int x;
    cin>>x;
    bool found = false;
    for (int i = 10; i<=x/2; i++) {
        if ((x-i>=10) && isValidNumber(i) && isValidNumber(x-i)) {
            cout<<i<<" "<<x-i<<'\n';
            found=true;
        }
    }
    cout<<(found ? "Yes" : "No")<<'\n';
    return 0;
}
//
// Created by cactus on 07/01/2026.
//
#include <iostream>
using namespace std;

int factorial(int number) {
    if (!number) {
        return 1;
    }
    return number * factorial(number - 1);
}

bool strongNumber(int number) {
    int temp = number;
    int sum = 0;
    while (temp > 0) {
        int digit = temp % 10;
        sum+=factorial(digit);
        temp /= 10;
    }
    return sum == number;
}

int main() {
    int arr[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        if (i==0) {
            cout<<"Strong numbers:"<<'\n';
        }
        int x;
        cin>>x;
        if (strongNumber(x)) {
            cout<<x<<'\n';
        }
    }
    return 0;
}

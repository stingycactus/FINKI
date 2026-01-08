//
// Created by cactus on 08/01/2026.
//
#include <iostream>
int countDigits (int number, int digit) {
    if (number<10) {
        return number == digit;
    }
    return ((number%10) == digit) + countDigits(number/10, digit);
}
void transformArr (int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int number = arr[i];
        int digit = number % 10;
        int appearances = countDigits (number, digit);
        arr[i] = appearances;
    }
}
using namespace std;
int main () {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    transformArr(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i]<<' ';
    }
    return 0;
}
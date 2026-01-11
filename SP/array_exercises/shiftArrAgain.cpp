//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
void shiftArrRight(int *arr, int n, int shift) {
    int B[100];
    for (int i = 0; i<shift; i++) {
        B[i] = arr[n-shift+i];
    }
    for (int i = n-1; i>=shift; i--) {
        arr[i]=arr[i-shift];
    }
    for (int i = 0; i<shift; i++) {
        arr[i]=B[i];
    }
}
void shiftArrLeft(int *arr, int n, int shift) {
    int B[100];
    for (int i = 0; i < shift; i++) {
        B[i] = arr[i];
    }
    for (int i = 0; i < n - shift; i++) {
        arr[i] = arr[i + shift];
    }
    for (int i = 0; i < shift; i++) {
        arr[n - shift + i] = B[i];
    }
}
int main() {
    int arr[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        cin>>arr[i];
    }
    int shift;
    cin>>shift;
    shiftArrRight(arr,n, shift);
    // shiftArrLeft(arr,n,shift);
    for (int i = 0; i<n; i++) {
        cout<<arr[i]<<' ';
    }
    return 0;
}
//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int positiveNumbers(int *arr, int size) {
    if (!size) {
        return 0;
    }
    return (*arr > 0) + positiveNumbers(arr+1, size-1);
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    cout<<positiveNumbers(arr,n);
    return 0;
}
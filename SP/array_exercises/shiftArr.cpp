//
// Created by cactus on 02/12/2025.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int arr[n];
    int shift;
    cin>>shift;
    int toShift = shift%n; // if n = 6, shift 7, shift becomes 1
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    // [1,2,3,4,5,6] --> [4,5,6,1,2,3]
    int temp[toShift];
    for (int i = 0; i < toShift; i++) {
        temp[i] = arr[n-toShift+i]; // [1,2,3,4,5,6] --> [4,5,6]
    }
    for (int i = n-1; i>=toShift; i--) { // [1,2,3,4,5,6] --> [1,2,3,1,2,3]
        arr[i] = arr[i-toShift];
    }
    for (int i = 0; i < toShift; i++) { // [1,2,3,1,2,3] --> [1,2,3,4,5,6]
        arr[i] = temp[i];
    }
    for (int i:arr) {
        cout<<i;
    }
    return 0;
}
//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
float fractionRec(int *arr, int size, int index) {
    if (index==size-1) {
        return arr[index];
    }
    return arr[index] + 1.00/fractionRec(arr, size, index + 1);
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    cout<<fractionRec(arr,n, 0);
    return 0;
}
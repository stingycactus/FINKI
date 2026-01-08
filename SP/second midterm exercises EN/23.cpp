//
// Created by cactus on 1/8/2026.
//
#include <iostream>
using namespace std;

int odd(int *arr, int size) {
    if (!size) {
        return 0;
    }
    return (arr[size-1]%2!=0) + odd(arr, size - 1);
}

int main() {
    int n;
    cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << odd(arr, n);
    return 0;
}

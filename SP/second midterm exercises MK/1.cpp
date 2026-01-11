//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int sum_pos (int *arr, int index, int size) {
    if (index>=size) {
        return 0;
    }
    return *(arr+index) + sum_pos (arr, index+1, size);
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i<n; i++) {
        cin>>arr[i];
    }
    int ind;
    cin>>ind;
    cout<<sum_pos(arr, ind, n);
    return 0;
}
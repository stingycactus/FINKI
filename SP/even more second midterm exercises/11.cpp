//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
void shift(int *arr, int n) {
    int B[100];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i]<0) {
            B[j]=arr[i];
            j++;
        }
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i]>=0) {
            arr[k]=arr[i];
            k++;
        }
    }
    for (int i = 0; i<j; i++) {
        arr[i+k]=B[i];
    }
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    shift(arr, n);
    for (int i = 0; i < n; i++) {
        cout<<arr[i]<<' ';
    }
    return 0;
}
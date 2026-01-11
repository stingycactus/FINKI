//
// Created by cactus on 11/01/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
void transformArray(int arr[], int n) {
    int toShift = *arr;
    if (abs(toShift)>n) {
        for (int i=0;i<n;i++) {
            arr[i]=0;
        }
        return;
    }
    if (toShift>=0) {
        for (int i = n-1; i>=toShift; i--) {
            arr[i] = arr[i-toShift];
        }
        for (int i=0; i<toShift; i++) {
            arr[i] = 0;
        }
    }
    else {
        toShift*=-1;
        for (int i = 0; i<n-toShift; i++) {
            arr[i] = arr[i+toShift];
        }
        for (int i=n-toShift; i<n; i++) {
            arr[i] = 0;
        }
    }
}

int main () {
    int m;
    cin>>m;
    int counter = 0;
    for (int i = 0; i < m; i++) {
        int arr[100];
        int n;
        cin>>n;
        for (int j = 0; j<n; j++) {
            cin>>arr[j];
        }
        transformArray(arr, n);
        bool allZero = true;
        for (int k = 0; k<n; k++) {
            if (arr[k]!=0) {
                allZero = false;
            }
        }
        if (allZero) {
            counter++;
        }
        for (int k = 0; k<n; k++) {
            cout<<arr[k]<<' ';
        }
        cout<<'\n';
    }
    cout<<counter;
    return 0;
}
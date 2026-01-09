//
// Created by cactus on 1/9/2026.
//
#include <iostream>
using namespace std;
void transformArr(int *arr, int size) {
    for (int i = 0; i<size-1; i++) {
        if (arr[i]==arr[i+1]) {
            arr[i] *=2;
            arr[i+1]=0;
        }
    }
}
void orderArr(int *arr, int size) {
    int j = 0;
    for (int i = 0; i<size; i++) {
        if (arr[i]!=0) {
            arr[j]=arr[i];
            j++;
        }
    }
    for (int i = j; i<size; i++) {
        arr[i]=0;
    }
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i<n; i++) {
        cin>>arr[i];
    }
    transformArr(arr,n);
    orderArr(arr,n);
    for (int i = 0; i<n; i++) {
        cout<<arr[i]<<' ';
    }
    return 0;
}
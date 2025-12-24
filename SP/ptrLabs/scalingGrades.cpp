//
// Created by cactus on 23/12/2025.
//
#include <iostream>
#include <iomanip>
#include <format>
using namespace std;
void scale(float arr[], int size) {
    int max = *arr;
    for (int i = 0; i < size; i++) {
        if (arr[i]>max) {
            max = arr[i];
        }
    }
    float quotient = 100/float(max);
    for (int i = 0; i < size; i++) {
        arr[i] *= quotient;
    }
}
int main() {
    int n;
    cin>>n;
    float arr[100];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    scale(arr,n);
    for (int i = 0; i < n; i++) {
        cout<<format("{:.2f}", arr[i])<<" ";
    }
    return 0;
}
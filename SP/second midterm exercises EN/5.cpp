//
// Created by cactus on 07/01/2026.
//
#include <iostream>
using namespace std;
void transformArr(int *arr, int size, int k) {
    for (int i = 0; i < size; i++) {
        int temp = arr[i];
        int multiplier = 1;
        int abbreviated = 0;
        while (temp>0) {
            int digit = temp%10;
            if (digit>k) {
                abbreviated = digit * multiplier + abbreviated;
                multiplier*=10;
            }
            temp/=10;
        }
        arr[i] = abbreviated;
    }
}
int maxInArr(int *arr, int size){
    int max = *arr;
    for (int i = 1; i < size; i++) {
        if (arr[i]>max) {
            max=arr[i];
        }
    }
    return max;
}
int main () {
    int arr[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    int k;
    cin>>k;
    transformArr(arr, n, k);
    cout<<maxInArr(arr, n);
    return 0;
}
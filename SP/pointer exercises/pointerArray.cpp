//
// Created by cactus on 18/12/2025.
//
#include <iostream>
using namespace std;

void doArrayShit(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
}

int findMaxArr(int *arr, int size) {
    int max = *arr;
    for (int i = 0; i < size; i++) {
        if (*(arr + i) > max) {
            max = *(arr + i);
        }
    }
    return max;
}

int findMinArr(int *arr, int size) {
    int min = *arr;
    for (int i = 0; i < size; i++) {
        if (*(arr + i) < min) {
            min = *(arr + i);
        }
    }
    return min;
}

void findSubArray(int *arr, int size) {
    int maxSum = *arr;
    int sum = *arr;
    int maxElements = 1;
    int elements = 0;
    int maxPos = 0;
    int subArray[size] = {};
    for (int i = 1; i < size; i++) {
        if (sum + arr[i] < arr[i]) {
            sum = arr[i];
            elements = 1;
        } else {
            sum += *(arr + i);
            elements++;
        }
        if (sum > maxSum) {
            maxPos = i;
            maxSum = sum;
            maxElements = elements;
        }
    }
    for (int j = 0; j<maxElements; j++) {
        *(subArray+j) = *(arr+j+maxPos-(maxElements-1));
    }
    for (int k = 0; k<maxElements; k++) {
        cout<<*(subArray+k)<<" ";
    }
}

int main() {
    int arr[10] = {1, -5, -3, 9, 158};
    int n = 5;
    doArrayShit(arr, n);
    cout << '\n';
    cout << findMaxArr(arr, n) << '\n';
    cout << findMinArr(arr, n) << '\n';
    findSubArray(arr, n);
    return 0;
}

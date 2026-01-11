//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;

int evenAppearances(int *arr, int n) {
    bool found = false;
    int smallestElem = *arr;
    for (int i = 0; i < n; i++) {
        int occurrences = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                occurrences++;
            }
        }
        if (occurrences % 2 == 0) {
            found = true;
            if (arr[i] < smallestElem) {
                smallestElem = arr[i];
            }
        }
    }
    if (found) {
        return smallestElem;
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (evenAppearances(arr, n)) {
        cout << "Najmaliot element koj se pojavuva paren broj pati e " << evenAppearances(arr, n);
    }
    else {
        cout << "Nitu eden element ne se pojavuva paren broj pati!";
    }
    return 0;
}

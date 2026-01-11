//
// Created by cactus on 11/01/2026.
//
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    int arr[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    int arr2[100];
    for (int i = 0; i < m; i++) {
        float maxDifference = -1;
        for (int j = 0; j < n; j++) {
            float sum = 0;
            for (int k = 0; k < n; k++) {
                sum += arr[i][k];
            }
            float average = sum / n;
            float difference = abs(arr[i][j] - average);
            if (difference > maxDifference) {
                maxDifference = difference;
                arr2[i] = arr[i][j];
            }
        }
    }
    for (int i = 0; i < m; i++) {
        cout << arr2[i]<<' ';
    }
    return 0;
}

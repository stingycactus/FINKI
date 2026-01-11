//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    float arr[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    int rowS, colS;
    cin >> rowS >> colS;
    int rowE, colE;
    cin >> rowE >> colE;
    float B[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = arr[i][j];
        }
    }
    for (int i = rowS; i <= rowE; i++) {
        for (int j = colS; j <= colE; j++) {
            float neighborSum = 0;
            int neighborCount = 0;
            neighborSum += arr[i][j];
            neighborCount++;
            if (i > 0) {
                neighborSum += arr[i - 1][j];
                neighborCount++;
            }
            if (i < m - 1) {
                neighborSum += arr[i + 1][j];
                neighborCount++;
            }
            if (j > 0) {
                neighborSum += arr[i][j - 1];
                neighborCount++;
            }
            if (j < n - 1) {
                neighborSum += arr[i][j + 1];
                neighborCount++;
            }
            if (i > 0 && j > 0) {
                neighborSum += arr[i - 1][j - 1];
                neighborCount++;
            }
            if (i > 0 && j < n - 1) {
                neighborSum += arr[i - 1][j + 1];
                neighborCount++;
            }
            if (i < m - 1 && j > 0) {
                neighborSum += arr[i + 1][j - 1];
                neighborCount++;
            }
            if (i < m - 1 && j < n - 1) {
                neighborSum += arr[i + 1][j + 1];
                neighborCount++;
            }
            float average = neighborSum / neighborCount;
            B[i][j] = average;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}

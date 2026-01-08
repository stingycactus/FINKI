//
// Created by cactus on 1/8/2026.
//
#include <iostream>
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
    int B[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int neighborSum = 0;

            if (i > 0) {
                neighborSum += (arr[i - 1][j] > 0) * arr[i - 1][j];
            }
            if (i < m - 1) {
                neighborSum += (arr[i + 1][j] > 0) * arr[i + 1][j];
            }
            if (j > 0) {
                neighborSum += (arr[i][j - 1]>0) * arr[i][j - 1];
            }
            if (j < n - 1) {
                neighborSum += (arr[i][j + 1]>0) * arr[i][j + 1];
            }
            B[i][j] = neighborSum;
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

//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[100][100];
    int B[100][100];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            B[i][j] = arr[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            if (i == j) {
                for (int k = j + 1; k < n; k++) {
                    sum += arr[i][k];
                }
                for (int h = i - 1; h >= 0; h--) {
                    sum += arr[h][j];
                }
            }
            if ((i + j) == (n - 1)) {
                for (int k = 0; k < j; k++) {
                    sum += arr[i][k];
                }
                for (int h = i + 1; h < n; h++) {
                    sum += arr[h][j];
                }
            }
            if (i == j || ((i + j) == (n - 1))) {
                B[i][j] = sum;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}

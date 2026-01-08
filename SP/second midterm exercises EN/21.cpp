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
    int row;
    int col;
    cin >> row >> col;
    if (arr[row][col] == 0) {
        arr[row][col]=1;
        for (int i = row - 1; i >= 0; i--) {
            if (arr[i][col] == 1) {
                break;
            }
            arr[i][col] = 1;
        }
        for (int i = row + 1; i < m; i++) {
            if (arr[i][col] == 1) {
                break;
            }
            arr[i][col] = 1;
        }
        for (int j = col - 1; j >= 0; j--) {
            if (arr[row][j] == 1) {
                break;
            }
            arr[row][j] = 1;
        }
        for (int j = col + 1; j < n; j++) {
            if (arr[row][j] == 1) {
                break;
            }
            arr[row][j] = 1;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}

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
    int rowCount = 0;
    int columnCount = 0;
    for (int i = 0; i < m; i++) {
        int counter = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 1) {
                counter++;
                if (counter == 3) {
                    rowCount++;
                }
            } else {
                counter = 0;
            }
        }
    }
    for (int j = 0; j<n; j++) {
        int counter = 0;
        for (int i = 0; i<m; i++) {
            if (arr[i][j] == 1) {
                counter++;
                if (counter == 3) {
                    columnCount++;
                }
            } else {
                counter = 0;
            }
        }
    }
    cout << rowCount+columnCount;
    return 0;
}

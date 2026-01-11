//
// Created by cactus on 11/01/2026.
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
    int allCounter=0;
    for (int i = 0; i < m; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 1) {
                count++;
                if (count == 3) {
                    allCounter++;
                }
            }
            else {
                count=0;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        int count = 0;
        for (int i = 0; i < m; i++) {
            if (arr[i][j] == 1) {
                count++;
                if (count == 3) {
                    allCounter++;
                }
            }
            else {
                count=0;
            }
        }
    }
    cout << allCounter;
    return 0;
}

//
// Created by cactus on 1/8/2026.
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
    for (int j = 0; j < n; j++) {
        int upperSum = 0;
        int lowerSum = 0;

            for (int i = 0; i < m; i++) {
                if (m%2==0) {
                    int half = m/2;
                    if (i < half) {
                        upperSum += arr[i][j];
                    }
                    if (i >= half) {
                        lowerSum += arr[i][j];
                    }
                }
                else {
                    int half = m/2;
                    if (i<=half) {
                        upperSum += arr[i][j];
                    }
                    if (i >= half) {
                        lowerSum += arr[i][j];
                    }
                }
            }
        int diff = abs(upperSum - lowerSum);
        if (m % 2 == 0) {
            int half = m/2;
            arr[half - 1][j] = diff;
            arr[half][j] = diff;
        } else {
            int half = m/2;
            arr[half][j] = diff;
        }
        // cout<<upperSum<<' '<<lowerSum<<'\n';
    }
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            cout<<arr[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
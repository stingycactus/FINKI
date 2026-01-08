//
// Created by cactus on 08/01/2026.
//
#include <iostream>
using namespace std;

int main() {
    int A[100][100];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    int B[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
            if (A[i][j] == 0) {
                int neighborCounter = 0;
                if (i > 0 && A[i - 1][j] == 1) {
                    neighborCounter++;
                }
                if (j > 0 && A[i][j - 1] == 1) {
                    neighborCounter++;
                }
                if (i < n - 1 && A[i + 1][j] == 1) {
                    neighborCounter++;
                }
                if (j < n - 1 && A[i][j + 1] == 1) {
                    neighborCounter++;
                }
                if (neighborCounter >= 3) {
                    B[i][j]=1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}

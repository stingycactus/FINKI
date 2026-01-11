//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int A[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < m; j++) {
            int number = A[i][j];
            if (number % 2 == (i + j) % 2) {
                count++;
            }
        }
        cout<<i<<": "<<count<<'\n';
    }
    return 0;
}

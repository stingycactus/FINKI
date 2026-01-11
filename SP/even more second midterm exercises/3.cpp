//
// Created by cactus on 11/01/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n, m;
    cin>>n>>m;
    int A[150][150];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            cin>>A[i][j];
        }
    }
    for (int j = 0; j<m; j++) {
        int indexNumbers = 0;
        for (int i = 0; i < n; i++) {
            int concatenated = i;
            int temp = j;
            if (temp == 0) concatenated *= 10;
            while (temp > 0) {
                concatenated *= 10;
                temp /= 10;
            }
            int index = concatenated + j;
            if (index == A[i][j]) {
                indexNumbers++;
            }
        }
        cout<<indexNumbers<<'\n';
    }
    return 0;
}
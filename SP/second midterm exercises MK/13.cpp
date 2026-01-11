//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int A[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n*2; j++) {
            cin>>A[i][j];
        }
    }
    int B[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            B[i][j] = A[i][j];
        }
    }
    for (int i=0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            B[n+i][j]=A[i][n+j];
        }
    }
    for (int i = 0; i<n*2; i++) {
        for (int j = 0; j<n; j++) {
            cout<<B[i][j]<<' ';
        }
        cout<<'\n';
    }

    return 0;
}
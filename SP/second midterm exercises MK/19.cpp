//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    float A[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            cin>>A[i][j];
        }
    }
    float X = 0;
    float Y = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (i>j) {
                X+=A[i][j];
            }
            if ((i+j)>(n-1)) {
                Y+=A[i][j];
            }
        }
    }
    float B[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if ((i==j)&&((i+j)==(n-1))) {
                B[i][j]=X+Y;
            }
            else if (i==j) {
                B[i][j]=X;
            }
            else if ((i+j)==(n-1)) {
                B[i][j]=Y;
            }
            else {
                B[i][j]=0;
            }
        }
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            cout<<B[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
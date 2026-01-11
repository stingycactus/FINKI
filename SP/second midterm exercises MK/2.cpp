//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int n,m;
    cin>>n>>m;
    int A[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            cin>>A[i][j];
        }
    }
    int row, col;
    cin>>row>>col;
    int Fsum = 0;
    int Ssum = 0;
    int Tsum = 0;
    int Qsum = 0;
    for (int i = 0; i<row; i++) {
        for (int j = col; j<m; j++) {
            Fsum+=A[i][j];
        }
    }
    for (int i = 0; i<row; i++) {
        for (int j = 0; j<col; j++) {
            Ssum+=A[i][j];
        }
    }
    for (int i = row; i<n; i++) {
        for (int j = 0; j<col; j++) {
            Tsum+=A[i][j];
        }
    }
    for (int i = row; i<n; i++) {
        for (int j = col; j<m; j++) {
            Qsum+=A[i][j];
        }
    }
    cout<<Fsum<<' '<<Ssum<<' '<<Tsum<<' '<<Qsum<<'\n';
    return 0;
}
//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;

int main() {
    int X;
    cin >> X;
    int m, n;
    cin >> m >> n;
    int arr[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int sum = arr[i][0];
        for (int k = 1; k < n; k++) {
            sum += arr[i][k];
        }
        for (int j = 0; j < n; j++) {
            if (sum>X) {
                arr[i][j]=1;
            }
            else if (sum==X) {
                arr[i][j]=0;
            }
            else {
                arr[i][j]=-1;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout<<arr[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}

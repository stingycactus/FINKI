//
// Created by cactus on 08/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int m, n;
    cin>>m>>n;
    int arr[100][100];
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            cin>>arr[i][j];
        }
    }
    int column = 0;
    int minSum = 0;
    for (int j = 0; j<n; j++) {
        int sum = 0;
        for (int i = 0; i<m; i++) {
            sum+=arr[i][j];
        }
        if (j==0) {
            minSum = sum;
        }
        else if (sum<minSum) {
            minSum = sum;
            column = j;
        }
    }
    cout<<column;
    return 0;
}
//
// Created by cactus on 11/01/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int m,n;
    cin>>m>>n;
    int arr[100][100];
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            cin>>arr[i][j];
        }
    }
    for (int i = 0; i<m; i++) {
        int leftSum = 0;
        int rightSum = 0;
        for (int j = 0; j<n; j++) {
            if (n%2==0) {
                int middle = n/2;
                if (j<middle) {
                    leftSum += arr[i][j];
                }
                else {
                    rightSum += arr[i][j];
                }
            }
            else if (n%2!=0) {
                int middle = n/2;
                if (j<=middle) {
                    leftSum += arr[i][j];
                }
                if (j>=middle) {
                    rightSum += arr[i][j];
                }
            }
        }
        int diff = abs(leftSum - rightSum);
        if (n%2==0) {
            int middle = n/2;
            arr[i][middle-1]=arr[i][middle]=diff;
        }
        else {
            int middle = n/2;
            arr[i][middle]=diff;
        }
    }
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            cout<<arr[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
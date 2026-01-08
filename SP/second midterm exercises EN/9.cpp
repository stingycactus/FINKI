//
// Created by cactus on 08/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int m, n;
    cin>>m>>n;
    int arr[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin>>arr[i][j];
        }
    }
    int arr2[m*n];
    int arr2Elements = 0;
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            int counter = 0;
            for (int k = 0; k<n; k++) {
                if (arr[i][j]==arr[i][k]) {
                    counter++;
                }
            }
            if (counter==1) {
                arr2[arr2Elements]=arr[i][j];
                arr2Elements++;
            }
        }
    }
    if (arr2Elements) {
        for (int i = 0; i<arr2Elements; i++) {
            cout<<arr2[i]<<' ';
        }
    }
    else {
        cout<<"N";
    }
    return 0;
}
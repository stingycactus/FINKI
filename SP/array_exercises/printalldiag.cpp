//
// Created by cactus on 10/12/2025.
//
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int arr[100][100];
    int n,m;
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin>>arr[i][j];
        }
    }
    int biggest = max(n,m);
    for (int i = 0; i<biggest; i++) {
        for (int j = 0; j<n; j++) {
            for (int k = 0; k<m; k++) {
                if ((j+k)==i) {
                    cout<<arr[j][k]<<" ";
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
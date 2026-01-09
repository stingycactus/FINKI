//
// Created by cactus on 1/9/2026.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int arr[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            cin>>arr[i][j];
        }
    }
    int changeCount = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (i==j && arr[i][j]==1) {
                arr[i][j]=0;
                changeCount++;
            }
            if (arr[i][j]!=arr[j][i]) {
                changeCount++;
                arr[j][i]=arr[i][j];
            }
        }
    }
    cout<<changeCount;
    return 0;
}
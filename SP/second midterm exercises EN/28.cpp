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
    int aboveMainMax = arr[0][1];
    int belowMainMin = arr[1][0];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (j>i) {
                if (arr[i][j]>aboveMainMax) {
                    aboveMainMax=arr[i][j];
                }
            }
            if (i>j) {
                if (arr[i][j]<belowMainMin) {
                    belowMainMin=arr[i][j];
                }
            }
        }
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (j>i) {
                arr[i][j]=aboveMainMax;
            }
            if (i>j) {
                arr[i][j]=belowMainMin;
            }
        }
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            cout<<arr[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
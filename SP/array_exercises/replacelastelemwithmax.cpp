//
// Created by cactus on 10/12/2025.
//
#include <iostream>
using namespace std;
int main() {
    int n,m;
    cin >> n >> m;
    int arr[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin>>arr[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        int maxElem = arr[i][0];
        for (int j = 1; j < m; j++) {
            int elem = arr[i][j];
            if (elem>maxElem) {
                maxElem = elem;
            }
        }
        arr[i][m-1]=maxElem;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
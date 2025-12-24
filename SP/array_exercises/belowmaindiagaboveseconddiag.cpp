//
// Created by cactus on 10/12/2025.
//
#include <iostream>
using namespace std;
int main() {
    int arr[100][100];
    int n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin>>arr[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i>j && (i+j)>(n-1)) {
                arr[i][j]*=-1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
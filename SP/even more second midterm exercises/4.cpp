//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int arr[100][100];
    int number = 1;
    for (int i = 0; i<n; i++) {
        if (i%2==0) {
            for (int j = 0; j<n; j++) {
                arr[i][j]=number%10;
                number++;
            }
        }
        else {
            for (int j = n-1; j>=0; j--) {
                arr[i][j]=number%10;
                number++;
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
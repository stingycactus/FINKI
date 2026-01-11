//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    char arr[100][100];
    char letter = 'A';
    for (int i = 0; i<n; i++) {

        if (i%2==0) {
            for (int j = 0; j<n; j++) {
                if (letter=='J') {
                    letter='A';
                }
                arr[i][j]=letter;
                letter++;
            }
        }
        else {
            for (int j = n-1; j>=0; j--) {
                if (letter=='J') {
                    letter='A';
                }
                arr[i][j]=letter;
                letter++;
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
//
// Created by cactus on 09/12/2025.
//
#include <iostream>
#include <algorithm>
using namespace std;
/*
*Input:
3 4
1 2 3 4
5 1 2 3
6 5 1 2

Output:
DA*/
int main() {
    int arr[100][100];
    int x;
    cin >> x;
    int y;
    cin >> y;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> arr[i][j];
        }
    }
    int elem = arr[0][0];
    bool toeplitz = true;
    int minNum = min(x,y);
    for (int i = 0; i < minNum; i++) {
        if (arr[i][i]!=elem) {
            toeplitz = false;
            break;
        }
    }
    cout << (toeplitz ? "DA" : "NE");

    return 0;
}

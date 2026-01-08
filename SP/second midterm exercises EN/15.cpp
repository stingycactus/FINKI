//
// Created by cactus on 08/01/2026.
//
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    float arr[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    float diagArr[n*n];
    int k = 0;

    for (int j = 0; j < n; j++)
        diagArr[k++] = arr[0][j];

    for (int i = 1; i < n - 1; i++)
        diagArr[k++] = arr[i][n - 1 - i];

    for (int j = 0; j < n; j++)
        diagArr[k++] = arr[n - 1][j];

    for (int i = 0; i < k; i++)
        cout << diagArr[i] << " ";
    cout << '\n';

    int index = k - 1;

    for (int j = 0; j < n; j++)
        arr[0][j] = diagArr[index--];

    for (int i = 1; i < n - 1; i++)
        arr[i][n - 1 - i] = diagArr[index--];

    for (int j = 0; j < n; j++)
        arr[n - 1][j] = diagArr[index--];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}